# APT Files

Jason Gunthorpe &lt;jgg@debian.org&gt;

This document describes the complete implementation and format of the
installed APT directory structure. It also serves as guide to how APT
views the Debian archive.

Copyright &copy; Jason Gunthorpe, 1998-1999.

"APT" and this document are free software; you can redistribute them
and/or modify them under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

For more details, on Debian GNU/Linux systems, see the file
/usr/share/common-licenses/GPL for the full license.

## Introduction

### General

This document serves two purposes. The first is to document the
installed directory structure and the format and purpose of each file.
The second purpose is to document how APT views the Debian archive and
deals with multiple package files.

The var directory structure is as follows:

```
  /var/lib/apt/
		  lists/
		       partial/
		  xstatus
		  userstatus
		  cdroms.list
  /var/cache/apt/
                  pkgcache.bin
		  srcpkgcache.bin
		  archives/
		          partial/
  /etc/apt/
           sources.list
	   apt.conf
  /usr/lib/apt/
                methods/
		       cdrom
		       ftp
		       http
		       file
		       gzip
		       copy
```

As is specified in the FHS 2.1 /var/lib/apt is used for application data
that is not expected to be user modified. /var/cache/apt is used for
regeneratable data and is where the package cache and downloaded .debs go.

## Files

### Distribution Source list (sources.list)

The distribution source list is used to locate archives of the debian
distribution. It is designed to support any number of active sources and
to support a mix of source media. The file lists one source per line,
with the fastest source listed first. The format of each line is:

*type uri args*

The first item, *type*, indicates the format for the remainder of the
line. It is designed to indicate the structure of the distribution the
line is talking about. Currently the only defined value is *deb* which
indicates a standard debian archive with a dists dir.

#### The deb Type

The *deb* type is to be a typical two level debian distributions,
dist/*distribution*/*component*. Typically distribution is one of stable,
unstable or testing while component is one of main, contrib, non-free or
non-us. The format for the deb line is as follows:

deb *uri* *distribution* *component* [*component* ...]

*uri* for the *deb* type must specify the base of the debian
distribution. APT will automatically generate the proper longer URIs to
get the information it needs. *distribution* can specify an exact path,
in this case the components must be omitted and *distribution* must end
in a slash.

Since only one distribution can be specified per deb line it may be
necessary to list a number of deb lines for the same URI. APT will sort
the URI list after it has generated a complete set to allow connection
reuse. It is important to order things in the sourcelist from most
preferred to least preferred (fastest to slowest).

#### URI specification

URIs in the source list support a large number of access schemes.

**cdrom**
: The cdrom scheme is special in that If Modified Since queries are never
  performed and that APT knows how to match a cdrom to the name it was
  given when first inserted. APT also knows all of the possible mount
  points the cdrom drives and that the user should be prompted to insert
  a CD if it cannot be found. The path is relative to an arbitrary mount
  point (of APT's choosing) and must not start with a slash. The first
  pathname component is the given name and is purely descriptive and of
  the users choice. However, if a file in the root of the cdrom is called
  '.disk/info' its contents will be used instead of prompting. The name
  serves as a tag for the cdrom and should be unique.

  ```
  cdrom:Debian 1.3/debian
  ```

**http**
: This scheme specifies a HTTP server for the debian archive. HTTP is
  preferred over FTP because If Modified Since queries against the
  Package file are possible as well as deep pipelining and resume
  capabilities.

  ```
  http://www.debian.org/archive
  ```

**ftp**
: This scheme specifies a FTP connection to the server. FTP is limited
  because there is no support for IMS and is hard to proxy over
  firewalls.

  ```
  ftp://ftp.debian.org/debian
  ```

**file**
: The file scheme allows an arbitrary directory in the file system to be
  considered as a debian archive. This is useful for NFS mounts and local
  mirrors/archives.

  ```
  file:/var/debian
  ```

**smb**
: A possible future expansion may be to have direct support for smb
  (Samba servers).

  ```
  smb://ftp.kernel.org/pub/mirrors/debian
  ```

#### Hashing the URI

All permanent information acquired from any of the sources is stored in
the lists directory. Thus, there must be a way to relate the filename in
the lists directory to a line in the sourcelist. To simplify things this
is done by quoting the URI and treating \_'s as quoteable characters and
converting / to \_. The URI spec says this is done by converting a
sensitive character into %xx where xx is the hexadecimal representation
from the ASCII character set. Examples:

```
http://www.debian.org/archive/dists/stable/binary-i386/Packages
/var/lib/apt/lists/www.debian.org_archive_dists_stable_binary-i386_Packages

cdrom:Debian 1.3/debian/Packages
/var/lib/apt/info/Debian%201.3_debian_Packages
```

The other alternative that was considered was to use a deep directory
structure but this poses two problems, it makes it very difficult to
prune directories back when sources are no longer used and complicates
the handling of the partial directory. This gives a very simple way to
deal with all of the situations that can arise. Also note that the same
rules described in the *Archive Directory* section regarding the partial
sub dir apply here as well.

### Extra Status File (xstatus)

The extra status file serves the same purpose as the normal dpkg status
file (/var/lib/dpkg/status) except that it stores information unique to
apt. This includes the autoflag, target distribution and version and any
other unique features that come up over time. It duplicates nothing from
the normal dpkg status file. Please see other APT documentation for a
discussion of the exact internal behaviour of these fields. The Package
field is placed directly before the new fields to indicate which package
they apply to. The new fields are as follows:

**X-Auto**
: The Auto flag can be Yes or No and controls whether the package is in
  auto mode.

**X-TargetDist**
: The TargetDist item indicates which distribution versions are offered
  for installation from. It should be stable, unstable or testing.

**X-TargetVersion**
: The target version item is set if the user selects a specific version,
  it overrides the TargetDist selection if both are present.

### Binary Package Cache (pkgcache.bin)

Please see [cache.md](cache.md) for a complete description of what this
file is. The cache file is updated whenever the contents of the lists
directory changes. If the cache is erased, corrupted or of a
non-matching version it will be automatically rebuilt by all of the tools
that need it. *srcpkgcache.bin* contains a cache of all of the package
files in the source list. This allows regeneration of the cache when the
status files change to use a prebuilt version for greater speed.

### Downloads Directory (archives)

The archives directory is where all downloaded .deb archives go. When the
file transfer is initiated the deb is placed in partial. Once the file is
fully downloaded and its MD5 hash and size are verified it is moved from
partial into archives/. Any files found in archives/ can be assumed to be
verified.

No directory structure is transfered from the receiving site and all
.deb file names conform to debian conventions. No short (msdos) filename
should be placed in archives. If the need arises .debs should be
unpacked, scanned and renamed to their correct internal names. This is
mostly to prevent file name conflicts but other programs may depend on
this if convenient. A conforming .deb is one of the form,
name_version_arch.deb. Our archive scripts do not handle epochs, but they
are necessary and should be re-inserted. If necessary \_'s and :'s in the
fields should be quoted using the % convention. It must be possible to
extract all 3 fields by examining the file name. Downloaded .debs must be
found in one of the package lists with an exact name + version match..

### The Methods Directory (/usr/lib/apt/methods)

The Methods directory is more fully described in the APT Methods
interface document.

### The Mirror List

The mirror list is stored on the primary debian web server
(www.debian.org) and contains a machine readable list of all known
debian mirrors. It's format and style mirror the Package file.

**Site**
: This is the proper host name of the site. It should not be a host
  within debian.org and generally cnames should be avoided here.

**Aliases**
: These list any commonly used aliases for the site. This field is used
  to make sure that a site is not added twice.

**Type**
: This field can either be *Push-Primary* or *leaf*. *Push-Primary* are
  authorized top level mirrors of the archive, all other mirrors are
  leaf.

**Archive-[access]**
: The Archive field gives the path(s) to the debian archive. [access]
  specifies the access method and may be one of ftp, http, rsync, nfs, or
  smb. For many of the types it is possible to prefix the path with :###
  indicating that an alternate port should be used. Generally paths
  start with a / and end with a /, rsync is an exception in that the
  first directory component is not a path but a label.

**WWW-[access]**
: The WWW field gives the path(s) to the debian web site.

**CDImage-[access]**
: The WWW field gives the path(s) to the debian CD-ROM images

**Incoming-[access]**
: The Incoming field gives the path(s) to a mirror of the debian incoming
  directory.

**nonUS-[access]**
: The nonUS field gives the path(s) to a mirror of the non-US
  distribution.

**Maintainer**
: This is the email address of the maintainer of the mirror.

**Location**
: Location gives the general geographical region the mirror is in.

**Sponsor**
: The Sponsor field indicates who owns the mirror and a URL to a web page
  describing the organization.

**Comment**
: General free-form text.

Some form of network measurement will have to be used to gauge
performance of each of the mirrors. This will be discussed later, initial
versions will use the first found URI.

### The Release File

This file plays and important role in how APT presents the archive to
the user. Its main purpose is to present a descriptive name for the
source of each version of each package. It also is used to detect when
new versions of debian are released. It augments the package file it is
associated with by providing meta information about the entire archive
which the Packages file describes.

The full name of the distribution for presentation to the user is formed
as 'label version archive', with a possible extended name being 'label
version archive component'.

The file is formed as the package file (RFC-822) with the following tags
defined:

**Archive**
: This is the common name we give our archives, such as *stable* or
  *unstable*.

**Component**
: Refers to the sub-component of the archive, *main*, *contrib* etc.
  Component may be omitted if there are no components for this archive.

**Version**
: This is a version string with the same properties as in the Packages
  file. It represents the release level of the archive.

**Origin**
: This specifies who is providing this archive. In the case of Debian
  the string will read 'Debian'. Other providers may use their own
  string

**Label**
: This carries the encompassing name of the distribution. For Debian
  proper this field reads 'Debian'. For derived distributions it should
  contain their proper name.

**Architecture**
: When the archive has packages for a single architecture then the
  Architecture is listed here. If a mixed set of systems are represented
  then this should contain the keyword *mixed*.

**NotAutomatic**
: A Yes/No flag indicating that the archive is extremely unstable and
  its version's should never be automatically selected. This is to be
  used by experimental.

**Description**
: Description is used to describe the release. For instance experimental
  would contain a warning that the packages have problems.

The location of the Release file in the archive is very important, it
must be located in the same location as the packages file so that it can
be located in all situations. The following is an example for the current
stable release, 1.3.1r6

```
Archive: stable
Component: main
Version: 1.3.1r6
Origin: Debian
Label: Debian
Architecture: i386
```

This is an example of experimental,

```
Archive: experimental
Version: 0
Origin: Debian
Label: Debian
Architecture: mixed
NotAutomatic: Yes
```

And unstable,

```
Archive: unstable
Component: main
Version: 2.1
Origin: Debian
Label: Debian
Architecture: i386
```
