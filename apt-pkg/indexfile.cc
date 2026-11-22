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
// $Id: indexfile.cc,v 1.1 2002/07/23 17:54:50 niemeyer Exp $
/* ######################################################################

   Index File - Abstraction for an index of archive/souce file.

   ##################################################################### */
/*}}}*/
// Include Files							/*{{{*/
#include <apt-pkg/indexfile.h>
#include <apt-pkg/error.h>
/*}}}*/
#include <cstring>

// Global list of Item supported
static pkgIndexFile::Type *ItmList[10];
pkgIndexFile::Type **pkgIndexFile::Type::GlobalList = ItmList;
unsigned long pkgIndexFile::Type::GlobalListLen = 0;

// Type::Type - Constructor						/*{{{*/
// ---------------------------------------------------------------------
/* */
pkgIndexFile::Type::Type() {
    ItmList[GlobalListLen] = this;
    GlobalListLen++;
}
/*}}}*/
// Type::GetType - Locate the type by name				/*{{{*/
// ---------------------------------------------------------------------
/* */
pkgIndexFile::Type *pkgIndexFile::Type::GetType(const char *Type) {
    for (unsigned I = 0; I != GlobalListLen; I++) {
        if (strcmp(GlobalList[I]->Label, Type) == 0) {
            return GlobalList[I];
        }
    }
    return 0;
}
/*}}}*/

// IndexFile::GetIndexes - Stub						/*{{{*/
// ---------------------------------------------------------------------
/* */
bool pkgIndexFile::GetIndexes(pkgAcquire *Owner) const {
    return _error->Error("Internal Error, this index file is not downloadable");
}
/*}}}*/
// IndexFile::ArchiveInfo - Stub					/*{{{*/
// ---------------------------------------------------------------------
/* */
string pkgIndexFile::ArchiveInfo(pkgCache::VerIterator Ver) const {
    return string();
}
/*}}}*/
// IndexFile::FindInCache - Stub					/*{{{*/
// ---------------------------------------------------------------------
/* */
pkgCache::PkgFileIterator pkgIndexFile::FindInCache(pkgCache &Cache) const {
    return pkgCache::PkgFileIterator(Cache);
}
/*}}}*/
// IndexFile::SourceIndex - Stub					/*{{{*/
// ---------------------------------------------------------------------
/* */
string pkgIndexFile::SourceInfo(pkgSrcRecords::Parser const &Record,
    pkgSrcRecords::File const &File) const {
    return string();
}
/*}}}*/
