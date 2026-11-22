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
// $Id: cachefile.h,v 1.2 2002/07/25 18:07:18 niemeyer Exp $
/* ######################################################################

   CacheFile - Simple wrapper class for opening, generating and whatnot

   This class implements a simple 2 line mechanism to open various sorts
   of caches. It can operate as root, as not root, show progress and so on,
   it transparently handles everything necessary.

   This means it can rebuild caches from the source list and instantiates
   and prepares the standard policy mechanism.

   ##################################################################### */
/*}}}*/
#ifndef PKGLIB_CACHEFILE_H
#define PKGLIB_CACHEFILE_H

#include <apt-pkg/depcache.h>

class pkgPolicy;
class pkgCacheFile {
  protected:
    MMap *Map;
    pkgCache *Cache;
    pkgDepCache *DCache;

  public:
    pkgPolicy *Policy;

    // We look pretty much exactly like a pointer to a dep cache
    inline operator pkgCache &() {
        return *Cache;
    }
    inline operator pkgCache *() {
        return Cache;
    }
    inline operator pkgDepCache &() {
        return *DCache;
    }
    inline operator pkgDepCache *() {
        return DCache;
    }
    inline pkgDepCache *operator->() {
        return DCache;
    }
    inline pkgDepCache &operator*() {
        return *DCache;
    }
    inline pkgDepCache::StateCache &operator[](pkgCache::PkgIterator const &I) {
        return (*DCache)[I];
    }
    inline unsigned char &operator[](pkgCache::DepIterator const &I) {
        return (*DCache)[I];
    }

    bool BuildCaches(OpProgress &Progress, bool WithLock = true);
    bool Open(OpProgress &Progress, bool WithLock = true);
    void Close();

    pkgCacheFile();
    ~pkgCacheFile();
};

#endif
