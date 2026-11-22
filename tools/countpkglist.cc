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

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <rpm/rpmlib.h>

int main(int argc, char *argv[]) {
    Header header = NULL;
    long count = 0;
    FD_t fd;
    if (argc != 2) {
        fprintf(stderr, "usage: countpkglist <pkglist>\n");
        exit(1);
    }
    fd = Fopen(argv[1], "r");
    if (fd == NULL) {
        fprintf(stderr, "error: can't open %s: %s",
            argv[1], strerror(errno));
        exit(1);
    }
    while ((header = headerRead(fd, HEADER_MAGIC_YES)) != NULL) {
        headerFree(header);
        count++;
    }
    Fclose(fd);
    printf("%ld\n", count);
    return 0;
}
