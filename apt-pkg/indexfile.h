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
// $Id: indexfile.h,v 1.2 2002/07/25 18:07:18 niemeyer Exp $
/* ######################################################################

   Index File - Abstraction for an index of archive/source file.

   There are 3 primary sorts of index files, all represented by this
   class:

   Binary index files
   Bianry index files decribing the local system
   Source index files

   They are all bundled together here, and the interfaces for
   sources.list, acquire, cache gen and record parsing all use this class
   to acess the underlying representation.

   ##################################################################### */
/*}}}*/
#ifndef PKGLIB_INDEXFILE_H
#define PKGLIB_INDEXFILE_H

#include <string>
#include <apt-pkg/pkgcache.h>
#include <apt-pkg/srcrecords.h>
#include <apt-pkg/pkgrecords.h>

using std::string;

class pkgAcquire;
class pkgCacheGenerator;
class OpProgress;
class pkgIndexFile {
  public:
    class Type {
      public:
        // Global list of Items supported
        static Type **GlobalList;
        static unsigned long GlobalListLen;
        static Type *GetType(const char *Type);

        const char *Label;

        virtual pkgRecords::Parser *CreatePkgParser(pkgCache::PkgFileIterator /*File*/) const {
            return 0;
        }
        virtual ~Type() {
        }
        Type();
    };

    virtual const Type *GetType() const = 0;

    // Return descriptive strings of various sorts
    virtual string ArchiveInfo(pkgCache::VerIterator Ver) const;
    virtual string SourceInfo(pkgSrcRecords::Parser const &Record,
        pkgSrcRecords::File const &File) const;
    virtual string Describe(bool Short = false) const = 0;

    // Interface for acquire
    virtual string ArchiveURI(string /*File*/) const {
        return string();
    }
    virtual bool GetIndexes(pkgAcquire *Owner) const;
    // LORG:2006-03-16
    virtual string ChecksumType() {
        return "MD5-Hash";
    }

    // CNC:2002-07-04
    virtual bool GetReleases(pkgAcquire *Owner) const {
        return true;
    }

    // Interface for the record parsers
    virtual pkgSrcRecords::Parser *CreateSrcParser() const {
        return 0;
    }

    // Interface for the Cache Generator
    virtual bool Exists() const = 0;
    virtual bool HasPackages() const = 0;
    virtual off_t Size() const = 0;
    virtual bool Merge(pkgCacheGenerator & /*Gen*/, OpProgress & /*Prog*/) const {
        return false;
    }
    virtual bool MergeFileProvides(pkgCacheGenerator & /*Gen*/, OpProgress & /*Prog*/) const {
        return true;
    }
    virtual pkgCache::PkgFileIterator FindInCache(pkgCache &Cache) const;

    virtual ~pkgIndexFile() {
    }
};

#endif
