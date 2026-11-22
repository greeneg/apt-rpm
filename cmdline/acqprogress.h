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
// $Id: acqprogress.h,v 1.5 2003/02/02 22:24:11 jgg Exp $
/* ######################################################################

   Acquire Progress - Command line progress meter

   ##################################################################### */
/*}}}*/
#ifndef ACQPROGRESS_H
#define ACQPROGRESS_H

#include <apt-pkg/acquire.h>

class AcqTextStatus : public pkgAcquireStatus {
    unsigned int &ScreenWidth;
    char BlankLine[1024];
    unsigned long ID;
    unsigned long Quiet;

  public:
    virtual bool MediaChange(string Media, string Drive);
    virtual bool Authenticate(string Desc, string &User, string &Pass);
    virtual void IMSHit(pkgAcquire::ItemDesc &Itm);
    virtual void Fetch(pkgAcquire::ItemDesc &Itm);
    virtual void Done(pkgAcquire::ItemDesc &Itm);
    virtual void Fail(pkgAcquire::ItemDesc &Itm);
    virtual void Start();
    virtual void Stop();

    bool Pulse(pkgAcquire *Owner);

    AcqTextStatus(unsigned int &ScreenWidth, unsigned int Quiet);
};

#endif
