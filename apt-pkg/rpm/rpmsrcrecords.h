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
// $Id: rpmsrcrecords.h,v 1.5 2002/08/08 20:07:33 niemeyer Exp $
/* ######################################################################

   SRPM Records - Parser implementation for RPM style source indexes

   #####################################################################
 */
/*}}}*/
#ifndef PKGLIB_RPMSRCRECORDS_H
#define PKGLIB_RPMSRCRECORDS_H

#include <apt-pkg/srcrecords.h>
#include <apt-pkg/fileutl.h>
#include "rpmhandler.h"

class RPMHandler;

class rpmSrcRecordParser : public pkgSrcRecords::Parser {
    RPMHandler *Handler;

    char *Buffer;
    unsigned int BufSize;
    unsigned int BufUsed;

    void BufCat(const char *text);
    void BufCat(const char *begin, const char *end);
    void BufCatTag(const char *tag, const char *value);
    void BufCatDep(Dependency *Dep);
    void BufCatDescr(const char *descr);

  public:
    virtual bool Restart();
    virtual bool Step();
    virtual bool Jump(off_t Off);

    virtual string Package() const;
    virtual string Version() const;
    virtual string Maintainer() const;
    virtual string Section() const;
    virtual const char **Binaries();
    virtual off_t Offset();
    virtual string AsStr();
    virtual bool Files(vector<pkgSrcRecords::File> &F);
    virtual bool BuildDepends(vector<BuildDepRec> &BuildDeps, bool ArchOnly);

    rpmSrcRecordParser(string File, pkgIndexFile const *Index);
    ~rpmSrcRecordParser();
};

#endif
