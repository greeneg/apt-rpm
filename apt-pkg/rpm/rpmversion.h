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
// $Id: rpmversion.h,v 1.1 2002/07/23 17:54:51 niemeyer Exp $
/* ######################################################################

   RPM Version - Versioning system for RPM

   This implements the RPM versioning system.

   ##################################################################### */
/*}}}*/
#ifndef PKGLIB_RPMVERSION_H
#define PKGLIB_RPMVERSION_H

#include <apt-pkg/version.h>
#include <apt-pkg/strutl.h>

class rpmVersioningSystem : public pkgVersioningSystem {
  public:
    // Compare versions..
    virtual int DoCmpVersion(const char *A, const char *Aend,
        const char *B, const char *Bend);
    virtual int DoCmpVersionArch(const char *A, const char *Aend,
        const char *AA, const char *AAend,
        const char *B, const char *Bend,
        const char *BA, const char *BAend);
    virtual bool CheckDep(const char *PkgVer, int Op, const char *DepVer);
    virtual bool CheckDep(const char *PkgVer, pkgCache::DepIterator Dep);
    virtual int DoCmpReleaseVer(const char *A, const char *Aend,
        const char *B, const char *Bend) {
        return DoCmpVersion(A, Aend, B, Bend);
    }
    virtual string UpstreamVersion(const char *A);

    rpmVersioningSystem();
};

extern rpmVersioningSystem rpmVS;

#endif
