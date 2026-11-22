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
// $Id: indexcopy.h,v 1.1 2002/07/23 17:54:52 niemeyer Exp $
/* ######################################################################

   Index Copying - Aid for copying and verifying the index files

   ##################################################################### */
/*}}}*/
#ifndef INDEXCOPY_H
#define INDEXCOPY_H

#include <vector>
#include <string>
#include <stdio.h>

using std::string;
using std::vector;

class pkgTagSection;
class FileFd;

class IndexCopy {
  protected:
    pkgTagSection *Section;

    string ChopDirs(string Path, unsigned int Depth);
    bool ReconstructPrefix(string &Prefix, string OrigPath, string CD,
        string File);
    bool ReconstructChop(unsigned long &Chop, string Dir, string File);
    void ConvertToSourceList(string CD, string &Path);
    bool GrabFirst(string Path, string &To, unsigned int Depth);
    virtual bool GetFile(string &Filename, unsigned long &Size) = 0;
    virtual bool RewriteEntry(FILE *Target, string File) = 0;
    virtual const char *GetFileName() = 0;
    virtual const char *Type() = 0;

  public:
    bool CopyPackages(string CDROM, string Name, vector<string> &List);
};

class PackageCopy : public IndexCopy {
  protected:
    virtual bool GetFile(string &Filename, unsigned long &Size);
    virtual bool RewriteEntry(FILE *Target, string File);
    virtual const char *GetFileName() {
        return "Packages";
    }
    virtual const char *Type() {
        return "Package";
    }

  public:
};

class SourceCopy : public IndexCopy {
  protected:
    virtual bool GetFile(string &Filename, unsigned long &Size);
    virtual bool RewriteEntry(FILE *Target, string File);
    virtual const char *GetFileName() {
        return "Sources";
    }
    virtual const char *Type() {
        return "Source";
    }

  public:
};

#endif
