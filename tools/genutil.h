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


static inline bool endswith(const char *str, const char *suffix) {
    size_t len1 = strlen(str);
    size_t len2 = strlen(suffix);
    if (len1 < len2) {
        return false;
    }
    str += (len1 - len2);
    if (strcmp(str, suffix)) {
        return false;
    }
    return true;
}

static
#if defined(__APPLE__) || defined(__FREEBSD__)
    int selectRPMs(struct dirent *ent)
#else
    int selectRPMs(const struct dirent *ent)
#endif
{
    const char *d = ent->d_name;
    return (*d != '.' && endswith(d, ".rpm"));
}
