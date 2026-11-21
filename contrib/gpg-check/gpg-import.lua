
-- don't bother if no write access to rpmdb
if not posix.access("/var/lib/rpm", "w") then
	return
end

if confget("RPM::GPG-Import", "true") == "false" then
	return
end


keypath = confget("Dir::Etc/f").."gpg/"
keys = posix.dir(keypath)

if not keys then
	return
end

-- Lua 5.1 os.execute returns an exit-status number (0 == success);
-- 5.2+ returns true/nil, "exit"|"signal", code instead.
local function execsucceeded(ok)
	if type(ok) == "number" then
		return ok == 0
	end
	return ok == true
end

first = 1
for i, key in ipairs(keys) do
	if string.sub(key, 1, 10) == "gpg-pubkey" then
		if not execsucceeded(os.execute("LANG=C rpm -q `basename "..key.."` > /dev/null 2>&1")) then
			if first then
				print(_("You don't seem to have one or more of the needed GPG keys in your RPM database."))
				print(_("Importing them now..."))
				first = nil
			end
			if not execsucceeded(os.execute("LANG=C rpm --import "..keypath..key.." > /dev/null 2>&1")) then
				print(_("Error importing GPG keys"))
				return
			end
		end
	end
end

-- vim:ts=4
