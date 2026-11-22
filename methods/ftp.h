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
// Description								/*{{{*/// $Id: ftp.h,v 1.1 2002/07/23 17:54:53 niemeyer Exp $
// $Id: ftp.h,v 1.1 2002/07/23 17:54:53 niemeyer Exp $
/* ######################################################################

   FTP Aquire Method - This is the FTP aquire method for APT.

   ##################################################################### */
/*}}}*/
#ifndef APT_FTP_H
#define APT_FTP_H

class FTPConn {
    char Buffer[1024 * 10];
    size_t Len;
    int ServerFd;
    int DataFd;
    int DataListenFd;
    URI ServerName;
    bool ForceExtended;
    bool TryPassive;
    bool Debug;

    struct addrinfo *PasvAddr;

    // Generic Peer Address
    struct sockaddr_storage PeerAddr;
    socklen_t PeerAddrLen;

    // Generic Server Address (us)
    struct sockaddr_storage ServerAddr;
    socklen_t ServerAddrLen;

    // Private helper functions
    bool ReadLine(string &Text);
    bool Login();
    bool CreateDataFd();
    bool Finalize();

  public:
    bool Comp(URI Other) {
        return Other.Host == ServerName.Host && Other.Port == ServerName.Port;
    }

    // Raw connection IO
    bool ReadResp(unsigned int &Ret, string &Text);
    bool WriteMsg(unsigned int &Ret, string &Text, const char *Fmt, ...);

    // Connection control
    bool Open(pkgAcqMethod *Owner);
    void Close();
    bool GoPasv();
    bool ExtGoPasv();

    // Query
    bool Size(const char *Path, size_t &Size);
    bool ModTime(const char *Path, time_t &Time);
    bool Get(const char *Path, FileFd &To, unsigned long Resume,
        Hashes &MD5, bool &Missing);

    FTPConn(URI Srv);
    ~FTPConn();
};

class FtpMethod : public pkgAcqMethod {
    virtual bool Fetch(FetchItem *Itm);
    virtual bool Configuration(string Message);

    FTPConn *Server;

    static string FailFile;
    static int FailFd;
    static time_t FailTime;
    static void SigTerm(int);

  public:
    FtpMethod();
};

#endif
