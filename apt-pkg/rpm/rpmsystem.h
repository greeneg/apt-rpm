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
// $Id: rpmsystem.h,v 1.2 2002/07/30 20:43:41 niemeyer Exp $
/* ######################################################################

   System - RPM version of the  System Class

   #####################################################################
 */
/*}}}*/
#ifndef PKGLIB_RPMSYSTEM_H
#define PKGLIB_RPMSYSTEM_H

#include <apt-pkg/pkgsystem.h>
#include <apt-pkg/algorithms.h>
#include "rpmindexfile.h"

#include <map>

class RPMDBHandler;
class pkgSourceList;
class rpmIndexFile;

class rpmSystem : public pkgSystem {
    int LockCount;
    RPMDBHandler *RpmDB;
    rpmDatabaseIndex *StatusFile;

    bool processIndexFile(rpmIndexFile *Handler, OpProgress &Progress);

  public:
    RPMDBHandler *GetDBHandler();

    virtual bool LockRead();
    virtual bool Lock();
    virtual bool UnLock(bool NoErrors = false);
    virtual pkgPackageManager *CreatePM(pkgDepCache *Cache) const;
    virtual bool Initialize(Configuration &Cnf);
    virtual bool ArchiveSupported(const char *Type);
    virtual signed Score(Configuration const &Cnf);
    virtual string DistroVer();
    virtual bool AddStatusFiles(vector<pkgIndexFile *> &List);
    virtual bool AddSourceFiles(vector<pkgIndexFile *> &List);
    virtual bool FindIndex(pkgCache::PkgFileIterator File,
        pkgIndexFile *&Found) const;
    virtual bool ProcessCache(pkgDepCache &Cache, pkgProblemResolver &Fix);
    virtual bool IgnoreDep(pkgVersioningSystem &VS, pkgCache::DepIterator &Dep);
    virtual void CacheBuilt();

    virtual unsigned long OptionsHash() const;

    rpmSystem();
    virtual ~rpmSystem();
};

extern rpmSystem rpmSys;
extern bool HideZeroEpoch;

#endif
