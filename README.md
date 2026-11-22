# APT-RPM: Debian's APT for RPM-based Distributions

APT-RPM is a version of the Advanced Packaging Tool modified to work with the
RPM Package Manager. It was originally ported to RPM by Alfredo Kojima and then
further developed and improved by Gustavo Niemeyer, both working for the
Conectiva Linux distribution at the time. Later versions were maintained by
Panu Matilainen, and the project is now maintained by Gary L. Greene Jr.

APT-RPM reimplements APT's dependency-resolving package manager and
repository tooling directly against `rpm` and its own `rpmdb`/`librpm`
APIs, rather than `dpkg`, so it can be used on any RPM-based distribution
(historically Conectiva, Red Hat, SUSE, ALT Linux, and others).

## Features

* **Dependency-aware package management** - `apt-get` resolves, downloads,
  and installs/removes/upgrades RPM packages and their dependencies,
  including a "smart" conflict resolution system for `dist-upgrade`.
* **Multiple repository sources** - package sources (HTTP(S), FTP, local
  file, CD-ROM, etc.) are configured via `sources.list`, same as upstream
  APT, and repository metadata/cache is generated and searched with
  `apt-cache`.
* **Version/release pinning** - `apt_preferences` lets you control which
  version or distribution of a package is preferred, independent of the
  order sources are listed.
* **CD-ROM source management** - `apt-cdrom` scans and registers removable
  media as package sources.
* **Repository metadata support** - native `rpm` header-list and `repomd`/
  `sqlite` metadata formats are both supported for building the package
  cache.
* **Optional GPG signature verification** - the `contrib/gpg-check/` Lua
  hook checks package signatures against `librpm`'s keyring before installation.
  Install the hook and configure `Scripts::PM::Pre:: "gpg-check.lua";` and
  `RPM::GPG-Check "true";`; see `contrib/gpg-check/README` for details.
* **GPG signature verification** - package signatures are checked natively
  against `librpm`'s keyring (see `RPM::GPG-Check`) before packages are
  installed.
* **Lua scripting hooks** - a bundled Lua interpreter (`luaext/`) lets you
  plug custom logic into install/transaction events; see `contrib/` for
  bundled examples.
* **Configurable internal or external package manager backend** - the
  default backend talks to `librpm` directly (`RPM::PM=internal`); an
  external-process backend that shells out to an `rpm` binary is also
  available (`RPM::PM=external`) for sandboxing/wrapper scenarios.
* **HTTPS transport with certificate verification** - the `https` acquire
  method uses OpenSSL for TLS, with peer certificate verification on by
  default (`Acquire::https::Verify-Peer`). Fetching through a forward
  proxy is supported for both `http` and `https` sources, with `https`
  tunnelled via the HTTP `CONNECT` method so the proxy never sees
  decrypted traffic.

## Key commands

| Command | Purpose |
| --- | --- |
| `apt-get` | Install, remove, upgrade, and dist-upgrade packages |
| `apt-cache` | Query and inspect the package cache (search, show, depends, ...) |
| `apt-cdrom` | Add CD-ROM/removable media as package sources |
| `apt-config` | Query APT's configuration tree from scripts |

Run any of these with `--help`, or see their man pages in `doc/` (installed
as `apt-get(8)`, `apt-cache(8)`, `apt-cdrom(8)`, `apt-config(8)`, `apt(8)`),
for full usage details.

## Configuration

* `/etc/apt/sources.list` (`sources.list(5)`) - list of package sources.
* `/etc/apt/apt.conf` (`apt.conf(5)`) - general APT configuration tree.
* `/etc/apt/preferences` (`apt_preferences(5)`) - version/release pinning
  rules.

## Contrib scripts

`contrib/` bundles a number of optional Lua hooks and helper scripts that
build on the scripting support in `luaext/`, including:

* `gpg-check/` - enforce GPG signature verification before install.
* `preserve-conf/` - hold back upgrades that would overwrite locally
  edited `%config` files.
* `apt-groupinstall/` - install/remove whole package groups (comps.xml).
* `allow-duplicated/`, `list-nodeps/`, `list-extras/`, `guess/`,
  `install-devel/`, `log/`, `proxypasswd/`, `apt-cron/`, `apt-files/`,
  `apt-wrapper/` - assorted convenience and administration helpers.

See the `README` in each `contrib/` subdirectory for details.

## Building from source

APT-RPM uses the standard GNU autotools build system and requires
development headers and libraries for `rpm` (`librpm`), Lua, `libxml2`,
 `sqlite3`, `popt`, zlib, bzip2, and OpenSSL (required for the `https`
acquire method).

```sh
autoreconf -fiv
./configure
make
make install
```

See `doc/style.txt` for the project's coding style (enforced via the
`.clang-format` file at the repository root) and `TODO` for known work
still needing done.

## Documentation

Man pages and longer-form guides live in `doc/`:

* `apt.8`, `apt-get.8`, `apt-cache.8`, `apt-cdrom.8`, `apt-config.8` -
  command man pages.
* `apt.conf.5`, `sources.list.5`, `apt_preferences.5`, `vendors.list.5` -
  configuration file man pages.
* `guide.md` - the APT User's Guide.
* `design.md`, `cache.md`, `files.md`, `method.md` - internal
  design/architecture notes.
* `offline.md` - using APT to manage packages on an offline system.

## License

APT-RPM is licensed under the GNU General Public License, version 2.0 or
later - see `COPYING` for the full text. A handful of files are instead
Public Domain (inherited from upstream APT) or MIT-licensed (the bundled
Lua extension libraries in `luaext/`); see those files' own headers and
`luaext/COPYING.MIT` for details.

## Authors

See `AUTHORS` for the full list of maintainers and contributors.

