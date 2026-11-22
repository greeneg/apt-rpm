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

#ifndef PKGLIB_RAPTTYPES_H
#define PKGLIB_RAPTTYPES_H

/*
 * Layer of insulation against differing types used in rpm versions.
 * C happily converts enum to int etc automatically, C++ doesn't...
 */

#include <rpm/rpmtypes.h>
#include <rpm/rpmds.h>
#ifdef RPM_HAVE_RPMTAGVAL
typedef rpm_tag_t raptTag;
typedef rpm_tagtype_t raptTagType;
#else
typedef rpmTag raptTag;
typedef rpmTagType raptTagType;
#endif
typedef rpmsenseFlags raptDepFlags;
typedef uint32_t raptInt;
typedef uint32_t raptDbOffset;

#define raptInitIterator(a, b, c, d) rpmtsInitIterator(a, (rpmTag) b, c, d)
#endif /* PKGLIB_RAPTTYPES_H */
