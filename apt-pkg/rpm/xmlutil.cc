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


#include "xmlutil.h"
#include <string>

#ifdef APT_WITH_REPOMD
xmlNode *XmlFindNode(xmlNode *Node, const string &Name) {
    for (xmlNode *n = Node->children; n; n = n->next) {
        if (xmlStrcmp(n->name, (xmlChar *) Name.c_str()) == 0) {
            return n;
        }
    }
    return NULL;
}

string XmlFindNodeContent(xmlNode *Node, const string &Name) {
    xmlNode *n = XmlFindNode(Node, Name);
    return XmlGetContent(n);
}

string XmlGetContent(xmlNode *Node) {
    string str = "";
    if (Node) {
        xmlChar *content = xmlNodeGetContent(Node);
        if (content) {
            str = (char *) content;
            xmlFree(content);
        }
    }
    return str;
}

string XmlGetProp(xmlNode *Node, const string &Prop) {
    string str = "";
    if (Node) {
        xmlChar *prop = xmlGetProp(Node, (xmlChar *) Prop.c_str());
        if (prop) {
            str = (char *) prop;
            xmlFree(prop);
        }
    }
    return str;
}

#endif

// vim:ts=4:sw=4:et
