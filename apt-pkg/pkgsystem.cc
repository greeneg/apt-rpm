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
// $Id: pkgsystem.cc,v 1.1 2002/07/23 17:54:50 niemeyer Exp $
/* ######################################################################

   System - Abstraction for running on different systems.

   Basic general structure..

   ##################################################################### */
/*}}}*/
// Include Files							/*{{{*/
#include <apt-pkg/pkgsystem.h>
#include <apt-pkg/policy.h>
/*}}}*/
#include <cstring>

pkgSystem *_system = 0;
static pkgSystem *SysList[10];
pkgSystem **pkgSystem::GlobalList = SysList;
unsigned long pkgSystem::GlobalListLen = 0;

// System::pkgSystem - Constructor					/*{{{*/
// ---------------------------------------------------------------------
/* Add it to the global list.. */
pkgSystem::pkgSystem() {
    SysList[GlobalListLen] = this;
    GlobalListLen++;
}
/*}}}*/
// System::GetSystem - Get the named system				/*{{{*/
// ---------------------------------------------------------------------
/* */
pkgSystem *pkgSystem::GetSystem(const char *Label) {
    for (unsigned I = 0; I != GlobalListLen; I++) {
        if (strcmp(SysList[I]->Label, Label) == 0) {
            return SysList[I];
        }
    }
    return 0;
}
/*}}}*/
