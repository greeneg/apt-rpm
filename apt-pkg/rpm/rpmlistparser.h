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
// Description								/*{{{*/
// $Id: rpmlistparser.h,v 1.2 2002/07/26 17:39:28 niemeyer Exp $
/* ######################################################################

   RPM Package List Parser - This implements the abstract parser
   interface for RPM package files

   #####################################################################
 */
/*}}}*/
// Header section: pkglib
#ifndef PKGLIB_RPMLISTPARSER_H
#define PKGLIB_RPMLISTPARSER_H

#include <apt-pkg/aptconf.h>
#include <apt-pkg/pkgcachegen.h>
#include "rpmhandler.h"

#ifdef APT_WITH_REPOMD
#include <libxml/parser.h>
#include <libxml/tree.h>
#endif

#include <vector>
#include <regex.h>

#ifdef HAVE_TR1_UNORDERED_SET
#include <tr1/unordered_set>
#else
#include <set>
#endif

using std::string;
using std::vector;

class RPMHandler;
class RPMPackageData;

class rpmListParser : public pkgCacheGenerator::ListParser {
    RPMHandler *Handler;
    RPMPackageData *RpmData;

    string CurrentName;
    const pkgCache::VerIterator *VI;

#ifdef HAVE_TR1_UNORDERED_SET
    typedef std::tr1::unordered_set<string> SeenPackagesType;
#else
    typedef std::set<string> SeenPackagesType;
#endif
    SeenPackagesType *SeenPackages;

    bool Duplicated;

    bool ParseStatus(pkgCache::PkgIterator Pkg, pkgCache::VerIterator Ver);
    bool ParseDepends(pkgCache::VerIterator Ver, unsigned int Type);
    bool ParseProvides(pkgCache::VerIterator Ver);

  public:
    // These all operate against the current header
    virtual string Package();
    virtual string Version();
    virtual string Architecture();
    virtual bool NewVersion(pkgCache::VerIterator Ver);
    virtual unsigned short VersionHash();
    virtual bool UsePackage(pkgCache::PkgIterator Pkg,
        pkgCache::VerIterator Ver);
    virtual off_t Offset() {
        return Handler->Offset();
    }
    virtual off_t Size();

    virtual bool OrderedOffset() {
        return Handler->OrderedOffset();
    }

    virtual bool IsDatabase() {
        return Handler->IsDatabase();
    }

    virtual bool CollectFileProvides(pkgCache &Cache,
        pkgCache::VerIterator Ver);
    virtual bool Step();

    bool LoadReleaseInfo(pkgCache::PkgFileIterator FileI, FileFd &File);

    void VirtualizePackage(string Name);

    rpmListParser(RPMHandler *Handler);
    ~rpmListParser();
};

#ifdef APT_WITH_REPOMD
class rpmRepomdParser : public rpmListParser {
  protected:
    string Primary;
    string Filelist;
    string Other;

  public:
    bool LoadReleaseInfo(pkgCache::PkgFileIterator FileI, const string File,
        const string Dist);

    rpmRepomdParser(RPMHandler *Handler) : rpmListParser(Handler) {
    }
};
#endif /* APT_WITH_REPOMD */

#endif
