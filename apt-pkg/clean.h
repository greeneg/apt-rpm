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
// $Id: clean.h,v 1.1 2002/07/23 17:54:50 niemeyer Exp $
/* ######################################################################

   Clean - Clean out downloaded directories

   ##################################################################### */
/*}}}*/
#ifndef APTPKG_CLEAN_H
#define APTPKG_CLEAN_H

#include <apt-pkg/pkgcache.h>

class pkgArchiveCleaner {
  protected:
    virtual void Erase(const char * /*File*/, string /*Pkg*/, string /*Ver*/, struct stat & /*St*/) {
    }

  public:
    bool Go(string Dir, pkgCache &Cache);
    virtual ~pkgArchiveCleaner() {
    }
};

#endif
