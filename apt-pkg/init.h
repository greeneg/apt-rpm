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
// $Id: init.h,v 1.2 2002/07/25 18:07:18 niemeyer Exp $
/* ######################################################################

   Init - Initialize the package library

   This function must be called to configure the config class before
   calling many APT library functions.

   ##################################################################### */
/*}}}*/
#ifndef PKGLIB_INIT_H
#define PKGLIB_INIT_H

#include <apt-pkg/configuration.h>
#include <apt-pkg/pkgsystem.h>

// See the makefile
#define APT_PKG_MAJOR 3
#define APT_PKG_MINOR 3
#define APT_PKG_RELEASE 0

extern const char *pkgVersion;
extern const char *pkgLibVersion;
extern const char *pkgOS;
extern const char *pkgCPU;

bool pkgInitConfig(Configuration &Cnf);
bool pkgInitSystem(Configuration &Cnf, pkgSystem *&Sys);

#ifdef APT_COMPATIBILITY
#if APT_COMPATIBILITY != 986
#warning "Using APT_COMPATIBILITY"
#endif

inline bool pkgInitialize(Configuration &Cnf) {
    return pkgInitConfig(Cnf) && pkgInitSystem(Cnf, _system);
};
#endif

#endif
