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

#ifndef XMLUTIL_H
#define XMLUTIL_H

#include <apt-pkg/aptconf.h>

#ifdef APT_WITH_REPOMD
#include <string>
#include <libxml/parser.h>
#include <libxml/tree.h>

using std::string;

xmlNode *XmlFindNode(xmlNode *Node, const string &Name);
string XmlFindNodeContent(xmlNode *Node, const string &Name);
string XmlGetContent(xmlNode *Node);
string XmlGetProp(xmlNode *Node, const string &Prop);
#endif

#endif

// vim:ts=4:sw=4:et
