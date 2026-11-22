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
// $Id: cdromutl.h,v 1.1 2002/07/23 17:54:51 niemeyer Exp $
/* ######################################################################

   CDROM Utilities - Some functions to manipulate CDROM mounts.

   ##################################################################### */
/*}}}*/
#ifndef PKGLIB_CDROMUTL_H
#define PKGLIB_ACQUIRE_METHOD_H

#include <string>

using std::string;

bool MountCdrom(string Path);
bool UnmountCdrom(string Path);
bool IdentCdrom(string CD, string &Res, unsigned int Version = 2);

#endif
