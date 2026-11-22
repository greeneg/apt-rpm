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

/*
 * $Id: cached_md5.cc,v 1.4 2003/01/29 13:47:31 niemeyer Exp $
 */
#include <alloca.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <rpm/rpmlib.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>

#include "cached_md5.h"

#include <apt-pkg/error.h>
#include <apt-pkg/tagfile.h>
#include <apt-pkg/configuration.h>
#include <apt-pkg/rhash.h>
#include "rpmhandler.h"

#include <config.h>

CachedMD5::CachedMD5(string DirName, string Domain) {
    string fname = DirName;
    for (string::iterator i = fname.begin(); i != fname.end(); ++i) {
        if ('/' == *i) {
            *i = '_';
        }
    }
    CacheFileName = _config->FindDir("Dir::Cache", "/var/cache/apt") + '/' +
                    Domain + '/' + fname + ".md5cache";

    FILE *f = fopen(CacheFileName.c_str(), "r");
    if (!f) {
        return;
    }

    while (1) {
        char buf[BUFSIZ];
        if (!fgets(buf, sizeof(buf), f)) {
            break;
        }
        char *p1 = strchr(buf, ' ');
        assert(p1);

        string File;
        File = string(buf, p1++);
        char *p2 = strchr(p1, ' ');
        assert(p2);

        FileData Data;
        Data.MD5 = string(p1, p2++);
        Data.TimeStamp = atol(p2);
        MD5Table[File] = Data;
    }

    fclose(f);
}

CachedMD5::~CachedMD5() {
    FILE *f = fopen(CacheFileName.c_str(), "w+");
    if (f) {
        for (map<string, FileData>::const_iterator I = MD5Table.begin();
            I != MD5Table.end(); I++) {
            const string &File = (*I).first;
            const FileData &Data = (*I).second;
            fprintf(f, "%s %s %lu\n",
                File.c_str(), Data.MD5.c_str(), Data.TimeStamp);
        }
        fclose(f);
    }
}

void CachedMD5::MD5ForFile(string FileName, time_t TimeStamp, char *buf) {
    if (MD5Table.find(FileName) != MD5Table.end() && TimeStamp == MD5Table[FileName].TimeStamp) {
        strcpy(buf, MD5Table[FileName].MD5.c_str());
    } else {
        raptHash MD5("MD5-Hash");
        FileFd File(FileName, FileFd::ReadOnly);
        MD5.AddFD(File.Fd(), File.Size());
        File.Close();
        FileData Data;
        Data.MD5 = MD5.Result();
        Data.TimeStamp = TimeStamp;
        MD5Table[FileName] = Data;
        strcpy(buf, Data.MD5.c_str());
    }
}

// vim:ts=4:sw=4:et
