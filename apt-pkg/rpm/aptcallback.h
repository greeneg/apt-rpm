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
