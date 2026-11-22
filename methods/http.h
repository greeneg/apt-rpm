/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

// -*- mode: c++; mode: fold -*-
// Description								/*{{{*/// $Id: http.h,v 1.2 2002/07/25 18:07:19 niemeyer Exp $
// $Id: http.h,v 1.2 2002/07/25 18:07:19 niemeyer Exp $
/* ######################################################################

   HTTP Aquire Method - This is the HTTP aquire method for APT.

   ##################################################################### */
/*}}}*/

#ifndef APT_HTTP_H
#define APT_HTTP_H

#define MAXLEN 360

#include <vector>
#include <iostream>

#ifdef WITH_SSL
#include <openssl/ssl.h>
#endif

using std::cout;
using std::endl;

class HttpMethod;

class CircleBuf {
    unsigned char *Buf;
    unsigned long Size;
    unsigned long InP;
    unsigned long OutP;
    string OutQueue;
    unsigned long StrPos;
    unsigned long MaxGet;
    struct timeval Start;

    unsigned long LeftRead() {
        unsigned long Sz = Size - (InP - OutP);
        if (Sz > Size - (InP % Size)) {
            Sz = Size - (InP % Size);
        }
        return Sz;
    }
    unsigned long LeftWrite() {
        unsigned long Sz = InP - OutP;
        if (InP > MaxGet) {
            Sz = MaxGet - OutP;
        }
        if (Sz > Size - (OutP % Size)) {
            Sz = Size - (OutP % Size);
        }
        return Sz;
    }
    void FillOut();

  public:
    Hashes *Hash;
#ifdef WITH_SSL
    // Set by Read()/Write() when the last SSL_read()/SSL_write() call
    // wanted the opposite readiness direction; Go() uses these to pick
    // the right fd_set so the pending op is retried on the right event.
    bool SslWantRead;
    bool SslWantWrite;
    // OpenSSL requires a failed SSL_write() to be retried with the exact
    // same buffer and length, so remember the length used until it succeeds.
    bool SslWritePending;
    unsigned long SslWriteLen;
    // Same requirement applies to SSL_read() retries.
    bool SslReadPending;
    unsigned long SslReadLen;
#endif

    // Read data in
#ifdef WITH_SSL
    bool Read(int Fd, SSL *Ssl = NULL);
#else
    bool Read(int Fd);
#endif
    bool Read(string Data);

    // Write data out
#ifdef WITH_SSL
    bool Write(int Fd, SSL *Ssl = NULL);
#else
    bool Write(int Fd);
#endif
    bool WriteTillEl(string &Data, bool Single = false);

    // Control the write limit
    void Limit(long Max) {
        if (Max == -1) {
            MaxGet = 0 - 1;
        } else {
            MaxGet = OutP + Max;
        }
    }
    bool IsLimit() {
        return MaxGet == OutP;
    }
    void Print() {
        cout << MaxGet << ',' << OutP << endl;
    }

    // Test for free space in the buffer
    bool ReadSpace() {
        return Size - (InP - OutP) > 0;
    }
    bool WriteSpace() {
        return InP - OutP > 0;
    }

    // Dump everything
    void Reset();
    void Stats();

    CircleBuf(unsigned long Size);
    ~CircleBuf() {
        delete[] Buf;
        delete Hash;
    }
};

struct ServerState {
    // This is the last parsed Header Line
    unsigned int Major;
    unsigned int Minor;
    unsigned int Result;
    char Code[MAXLEN];

    // These are some statistics from the last parsed header lines
    unsigned long Size;
    signed long StartPos;
    time_t Date;
    bool HaveContent;
    enum { Chunked,
        Stream,
        Closes } Encoding;
    enum { Header,
        Data } State;
    bool Persistent;
    string Location;
    string Realm, ProxyRealm;

    // This is a Persistent attribute of the server itself.
    bool Pipeline;

    HttpMethod *Owner;

    // This is the connection itself. Output is data FROM the server
    CircleBuf In;
    CircleBuf Out;
    int ServerFd;
    URI ServerName;
#ifdef WITH_SSL
    SSL *Ssl;
#endif

    bool HeaderLine(string Line);
    bool Comp(URI Other) {
        // Access must match too, otherwise a same-host redirect that changes
        // scheme (e.g. http -> https) would wrongly reuse the old connection.
        return Other.Access == ServerName.Access && Other.Host == ServerName.Host && Other.Port == ServerName.Port;
    }
    void Reset() {
        Major = 0;
        Minor = 0;
        Result = 0;
        Size = 0;
        StartPos = 0;
        Encoding = Closes;
        time(&Date);
        ServerFd = -1;
        Pipeline = true;
#ifdef WITH_SSL
        Ssl = NULL;
#endif
    }
    int RunHeaders();
    bool RunData();

    bool Open();
    bool Close();
#ifdef WITH_SSL
    bool ConnectSSL();
    bool ConnectProxyTunnel();
#endif

    ServerState(URI Srv, HttpMethod *Owner);
    ~ServerState() {
        Close();
    }
};

class HttpMethod : public pkgAcqMethod {
    struct AuthRec {
        string Host;
        string Realm;
        string User;
        string Password;
        vector<string *> AuthURIs;
    };

    void SendReq(FetchItem *Itm, CircleBuf &Out);
    bool Go(bool ToFile, ServerState *Srv);
    bool Flush(ServerState *Srv);
    bool ServerDie(ServerState *Srv);
    int DealWithHeaders(FetchResult &Res, ServerState *Srv);

    virtual bool Fetch(FetchItem *);
    virtual bool Configuration(string Message);

    // In the event of a fatal signal this file will be closed and timestamped.
    static string FailFile;
    static int FailFd;
    static time_t FailTime;
    static void SigTerm(int);

    string NextURI;
    vector<AuthRec> AuthList;

  public:
    friend class ServerState;

    FileFd *File;
    ServerState *Server;

    int Loop();

    HttpMethod() : pkgAcqMethod("1.2", Pipeline | SendConfig) {
        File = 0;
        Server = 0;
    }
};

URI Proxy;

#endif
