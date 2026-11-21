/* Compatibility shims so the bundled Lua 5.0/5.1-era posix/rex
 * extensions build against Lua 5.2+ (which dropped luaL_openlib
 * and lua_strlen). Include after lua.h/lauxlib.h. */
#ifndef APT_LUACOMPAT_H
#define APT_LUACOMPAT_H

#if LUA_VERSION_NUM >= 502

#ifndef lua_strlen
#define lua_strlen(L,i) lua_rawlen(L, (i))
#endif

static int luaL_openlib_compat(lua_State *L, const char *libname,
                                const luaL_Reg *l, int nup)
{
   if (libname != NULL) {
      lua_createtable(L, 0, 0);
      if (nup > 0)
         lua_insert(L, -(nup + 1));
   }
   luaL_setfuncs(L, l, nup);
   if (libname != NULL) {
      lua_pushvalue(L, -1);
      lua_setglobal(L, libname);
   }
   return 1;
}
#define luaL_openlib(L, n, l, nup) luaL_openlib_compat((L), (n), (l), (nup))

#endif /* LUA_VERSION_NUM >= 502 */

#endif /* APT_LUACOMPAT_H */
