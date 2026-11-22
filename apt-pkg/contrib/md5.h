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
// $Id: md5.h,v 1.1 2002/07/23 17:54:51 niemeyer Exp $
/* ######################################################################

   Legacy wrapper around raptHash class.

   ##################################################################### */
/*}}}*/
#ifndef APTPKG_MD5_H
#define APTPKG_MD5_H

#include <string>
#include <cstring>
#include <apt-pkg/rhash.h>

using std::string;

typedef string MD5SumValue;

class MD5Summation : public raptHash {
  public:
    MD5Summation() : raptHash("MD5-Hash") {};
};

#endif
