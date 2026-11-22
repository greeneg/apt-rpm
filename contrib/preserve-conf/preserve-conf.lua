if confget("RPM::Preserve-Config/b", "false") == "true" then
	num = 0
	pkgs = pkglist()
	for i, pkg in ipairs(pkgs) do
		if statinstall(pkg) then
			if apt.configchanged(pkgname(pkg)) then
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
