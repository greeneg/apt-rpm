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
// $Id: hashes.h,v 1.1 2002/07/23 17:54:51 niemeyer Exp $
/* ######################################################################

   Hashes - Simple wrapper around the hash functions

   This is just used to make building the methods simpler, this is the
   only interface required..

   ##################################################################### */
/*}}}*/
#ifndef APTPKG_HASHES_H
#define APTPKG_HASHES_H

#include <vector>
#include <apt-pkg/rhash.h>

typedef std::vector<raptHash> HashContainer;

class Hashes {
  public:
    HashContainer HashSet;

    bool Add(const unsigned char *Data, unsigned long Size);
    inline bool Add(const char *Data) {
        return Add((unsigned char *) Data, strlen(Data));
    }
    bool AddFD(int Fd, unsigned long Size);
    inline bool Add(const unsigned char *Beg, const unsigned char *End) {
        return Add(Beg, End - Beg);
    }

    Hashes();
};

#endif
