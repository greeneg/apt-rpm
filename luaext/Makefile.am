noinst_LTLIBRARIES = libluaext.la

EXTRA_DIST = \
	modemuncher.c \
	userconfig.c \
	linit.lua

AM_CPPFLAGS = -I$(top_builddir)
AM_CPPFLAGS += -I$(srcdir)/include -I.
AM_CPPFLAGS += $(LUA_CFLAGS)

libluaext_la_CPPFLAGS = $(AM_CPPFLAGS) -DWITH_POSIX
libluaext_la_LIBADD = $(LUA_LIBS)
libluaext_la_SOURCES = \
		linit.h \
		lposix.h \
		lposix.c \
		lrexlib.h \
		lrexlib.c \
		luacompat.h

linit.lch: linit.lua
	bin2c linit.lua > linit.lch
