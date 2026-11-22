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


/* ######################################################################

   Index Copying - Aid for copying and verifying the index files

   #####################################################################
 */

#ifndef RPMINDEXCOPY_H
#define RPMINDEXCOPY_H

#include <vector>
#include <string>

class pkgTagSection;
class FileFd;

class RPMIndexCopy {
  protected:
    string RipComponent(string Path);
    string RipDirectory(string Path);
    string RipDistro(string Path);

    void ConvertToSourceList(string CD, string &Path);

  public:
    bool CopyPackages(string CDROM, string Name, vector<string> &List);
};

class RPMPackageCopy : public RPMIndexCopy {};

class RPMSourceCopy : public RPMIndexCopy {};

#endif
