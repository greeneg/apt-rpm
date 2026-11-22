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

#ifndef _APTRPM_RPMCALLBACK_H
#define _APTRPM_RPMCALLBACK_H

#include <apt-pkg/progress.h>
#include <rpm/rpmcli.h>
#include "rapttypes.h"

void *rpmCallback(const void *arg,
    rpmCallbackType what,
    rpm_loff_t amount, rpm_loff_t total,
    const void *pkgKey, void *data);

#endif /* _APTRPM_RPMCALLBACK_H */
// vim:ts=4:sw=4:et
