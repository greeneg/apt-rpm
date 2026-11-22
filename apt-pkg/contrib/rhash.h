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

// Description								/*{{{*/
/* ######################################################################

   This is a C++ interface to rpm's hash (aka digest) functions.

   ##################################################################### */
/*}}}*/
#ifndef APTPKG_RHASH_H
#define APTPKG_RHASH_H

#include <string>
#include <rpm/rpmpgp.h>

using std::string;

class raptHash {
    DIGEST_CTX HashCtx;
    string Value;
    string HashType;

  public:
    bool Add(const unsigned char *inbuf, unsigned long inlen);
    inline bool Add(const char *Data) {
        return Add((unsigned char *) Data, strlen(Data));
    }
    bool AddFD(int Fd, unsigned long Size);
    inline bool Add(const unsigned char *Beg, const unsigned char *End) {
        return Add(Beg, End - Beg);
    }
    string Result();
    string Type() {
        return HashType;
    };

    raptHash(const string &HashName);
    raptHash(const raptHash &Hash);
    raptHash &operator=(const raptHash &Hash);
    ~raptHash();
};

#endif
