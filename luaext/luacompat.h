/* Compatibility shims so the bundled Lua 5.0/5.1-era posix/rex
 * extensions build against Lua 5.2+ (which dropped luaL_openlib
 * and lua_strlen). Include after lua.h/lauxlib.h.
 *
 * Copyright (C) apt-rpm contributors.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. See COPYING.MIT in this directory for the full license. */
#ifndef APT_LUACOMPAT_H
#define APT_LUACOMPAT_H

#if LUA_VERSION_NUM >= 502

#ifndef lua_strlen
#define lua_strlen(L, i) lua_rawlen(L, (i))
#endif

static int luaL_openlib_compat(lua_State *L, const char *libname,
    const luaL_Reg *l, int nup) {
    if (libname != NULL) {
        lua_createtable(L, 0, 0);
        if (nup > 0) {
            lua_insert(L, -(nup + 1));
        }
    }
    luaL_setfuncs(L, l, nup);
    if (libname != NULL) {
        /* mirror 5.1's luaL_openlib: register in both _G and
         * package.loaded so require(libname) finds this table. */
        lua_pushvalue(L, -1);
        lua_setglobal(L, libname);
        luaL_getsubtable(L, LUA_REGISTRYINDEX, "_LOADED");
        lua_pushvalue(L, -2);
        lua_setfield(L, -2, libname);
        lua_pop(L, 1);
    }
    return 1;
}
#define luaL_openlib(L, n, l, nup) luaL_openlib_compat((L), (n), (l), (nup))

#endif /* LUA_VERSION_NUM >= 502 */

#endif /* APT_LUACOMPAT_H */
