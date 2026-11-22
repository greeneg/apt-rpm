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

#ifndef PKGLIB_RAPTHEADER_H
#define PKGLIB_RAPTHEADER_H

#include <vector>
#include <string>

#include "rapttypes.h"

#include <rpm/header.h>
#include <rpm/rpmtag.h>

using std::string;
using std::vector;

class raptHeader {
  private:
    Header Hdr;

  public:
    bool hasTag(raptTag tag) const;
    bool getTag(raptTag tag, raptInt &data) const;
    bool getTag(raptTag tag, string &data, bool raw = false) const;
    bool getTag(raptTag tag, vector<raptInt> &data) const;
    bool getTag(raptTag tag, vector<string> &data, bool raw = false) const;
    string format(const string fmt) const;

    raptHeader(Header hdr);
    ~raptHeader();
};

#endif /* _PKGLIB_RAPTHEADER_H */

// vim:ts=4:sw=4:et
