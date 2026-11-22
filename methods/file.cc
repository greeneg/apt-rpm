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
// $Id: file.cc,v 1.9 2003/02/10 07:34:41 doogie Exp $
/* ######################################################################

   File URI method for APT

   This simply checks that the file specified exists, if so the relevent
   information is returned. If a .gz filename is specified then the file
   name with .gz removed will also be checked and information about it
   will be returned in Alt-*

   ##################################################################### */
/*}}}*/
// Include Files							/*{{{*/
#include <apt-pkg/acquire-method.h>
#include <apt-pkg/error.h>

#include <sys/stat.h>
#include <unistd.h>

// CNC:2003-02-20 - Moved header to fix compilation error when
// 		    --disable-nls is used.
#include <apti18n.h>
/*}}}*/

class FileMethod : public pkgAcqMethod {
    virtual bool Fetch(FetchItem *Itm);

  public:
    FileMethod() : pkgAcqMethod("1.0", SingleInstance | LocalOnly) {
    }
};

// FileMethod::Fetch - Fetch a file					/*{{{*/
// ---------------------------------------------------------------------
/* */
bool FileMethod::Fetch(FetchItem *Itm) {
    URI Get = Itm->Uri;
    string File = Get.Path;
    FetchResult Res;
    if (Get.Host.empty() == false) {
        return _error->Error(_("Invalid URI, local URIS must not start with //"));
    }

    // See if the file exists
    struct stat Buf;
    if (stat(File.c_str(), &Buf) == 0) {
        Res.Size = Buf.st_size;
        Res.Filename = File;
        Res.LastModified = Buf.st_mtime;
        Res.IMSHit = false;
        if (Itm->LastModified == Buf.st_mtime && Itm->LastModified != 0) {
            Res.IMSHit = true;
        }
    }

    // CNC:2003-11-04
    // See if we can compute a file without a .gz/.bz2/etc extension
    string ComprExtension = _config->Find("Acquire::ComprExtension", ".bz2");
    string::size_type Pos = File.rfind(ComprExtension);
    if (Pos + ComprExtension.length() == File.length()) {
        File = string(File, 0, Pos);
        if (stat(File.c_str(), &Buf) == 0) {
            FetchResult AltRes;
            AltRes.Size = Buf.st_size;
            AltRes.Filename = File;
            AltRes.LastModified = Buf.st_mtime;
            AltRes.IMSHit = false;
            if (Itm->LastModified == Buf.st_mtime && Itm->LastModified != 0) {
                AltRes.IMSHit = true;
            }

            URIDone(Res, &AltRes);
            return true;
        }
    }

    if (Res.Filename.empty() == true) {
        return _error->Error(_("File not found"));
    }

    URIDone(Res);
    return true;
}
/*}}}*/

int main() {
    FileMethod Mth;
    return Mth.Run();
}
