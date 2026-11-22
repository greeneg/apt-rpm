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
// $Id: version.cc,v 1.1 2002/07/23 17:54:50 niemeyer Exp $
/* ######################################################################

   Version - Versioning system..

   ##################################################################### */
/*}}}*/
// Include Files							/*{{{*/
#include <apt-pkg/version.h>
#include <apt-pkg/pkgcache.h>

#include <stdlib.h>
/*}}}*/

static pkgVersioningSystem *VSList[10];
pkgVersioningSystem **pkgVersioningSystem::GlobalList = VSList;
unsigned long pkgVersioningSystem::GlobalListLen = 0;

// pkgVS::pkgVersioningSystem - Constructor				/*{{{*/
// ---------------------------------------------------------------------
/* Link to the global list of versioning systems supported */
pkgVersioningSystem::pkgVersioningSystem() {
    VSList[GlobalListLen] = this;
    GlobalListLen++;
}
/*}}}*/
// pkgVS::GetVS - Find a VS by name					/*{{{*/
// ---------------------------------------------------------------------
/* */
pkgVersioningSystem *pkgVersioningSystem::GetVS(const char *Label) {
    for (unsigned I = 0; I != GlobalListLen; I++) {
        if (strcmp(VSList[I]->Label, Label) == 0) {
            return VSList[I];
        }
    }
    return 0;
}
/*}}}*/
// vim:ts=4:sw=4:et
