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

#ifndef PKGLIB_REPOMD_H
#define PKBLIB_REPOMD_H

#include <apt-pkg/aptconf.h>
#include <apt-pkg/repository.h>

#ifdef APT_WITH_REPOMD

#include <libxml/parser.h>
#include <libxml/tree.h>
#include "rpmhandler.h"

using std::map;
using std::string;

inline string chk2hash(const string &ht) {
    if (ht == "sha") {
        return "SHA1-Hash";
    } else if (ht == "sha256") {
        return "SHA256-Hash";
    } else if (ht == "sha512") {
        return "SHA512-Hash";
    } else if (ht == "md5") {
        return "MD5-Hash";
    } else {
        return "Unknown-Hash"; /* XXX W2DO? */
    }
}

class repomdXML {
  protected:
    string Path;
    struct RepoFile {
        string Path;
        string RealPath;
        string Type;
        string TimeStamp;
        string ChecksumType;
        string Hash;
        string HashType;
        off_t Size;
    };

    map<string, RepoFile> RepoFiles;

  public:
    friend class repomdRepository;
    string FindURI(string DataType) const;
    string ID() const {
        return Path;
    };
    string GetComprMethod(string URI) const;
    RPMHandler *CreateHandler() const;

    repomdXML(const string File);
    ~repomdXML() {};
};

class repomdRepository : public pkgRepository {
  protected:
    repomdXML *repomd;

  public:
    virtual bool IsAuthenticated() const {
        return false;
    }
    virtual bool ParseRelease(string File);
    virtual string FindURI(string DataType);
    virtual string GetComprMethod(string URI);

    repomdRepository(string URI, string Dist, const pkgSourceList::Vendor *Vendor,
        string RootURI)
        : pkgRepository(URI, Dist, Vendor, RootURI) {
        // repomd always has a "release" file
        GotRelease = true;
    }

    virtual ~repomdRepository() {
    }
};

#endif /* APT_WITH_REPOMD */

#endif

// vim:ts=4:sw=4:et
