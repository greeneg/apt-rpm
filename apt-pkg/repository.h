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

// CNC:2002-07-03

#ifndef PKGLIB_REPOSITORY_H
#define PKGLIB_REPOSITORY_H

#include <string>
#include <map>

#include <apt-pkg/sourcelist.h>

using std::map;

class pkgRepository {
  protected:
    struct Checksum {
        unsigned long Size;
        string Hash;
        string HashType;
    };

    map<string, Checksum> IndexChecksums; // path -> checksum data

    bool GotRelease;

  public:
    string URI;
    string Dist;
    vector<string> FingerPrintList;
    string RootURI;

    bool Acquire;

    // LORG:2006-02-21 make these methods virtual
    virtual bool ParseRelease(string File);
    virtual bool HasRelease() const {
        return GotRelease;
    }

    virtual bool IsAuthenticated() const {
        return !FingerPrintList.empty();
    }
    virtual bool FindChecksums(string URI, off_t &Size, string &Hash, string &HashType);
    // Only used in repomd atm
    virtual string FindURI(string DataType) {
        return "";
    }
    virtual string GetComprMethod(string URI) {
        return "bz2";
    }

    pkgRepository(string URI, string Dist, const pkgSourceList::Vendor *Vendor,
        string RootURI)
        : GotRelease(0), URI(URI), Dist(Dist), RootURI(RootURI),
          Acquire(1) {
        if (Vendor) {
            FingerPrintList = Vendor->FingerPrintList;
        }
    }

    virtual ~pkgRepository() {
    }
};

#endif

// vim:ts=4:sw=4:et
