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
