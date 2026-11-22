if confget("RPM::Preserve-Config/b", "false") == "true" then
	num = 0
	pkgs = pkglist()
	for i, pkg in ipairs(pkgs) do
		if statinstall(pkg) then
			local changed, err = apt.configchanged(pkgname(pkg))
			if changed == nil then
				-- Could not verify (e.g. failed to enter
				-- RPM::RootDir); fail closed and hold back.
				aptwarning(_("Could not verify configuration for "..pkgname(pkg)..": "..(err or "unknown error")))
				changed = true
			end
			if changed then
				num = num + 1
				markkeep(pkg)
			end
		end
	end
	if num > 0 then
		print("\nHolding back "..num.." packages because of changed configuration")
	end
end
-- vim:ts=4
