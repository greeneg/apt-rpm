if confget("RPM::GPG-Check/b", "true") == "false" then
    return
end

if #files_install < 1 then
    return
end

hash = '##############################'
hashestotal = string.len(hash)
interactive = confget("RPM::Interactive/b", "true")
quiet = tonumber(confget("quiet", 0))

function printhash(amount, total)
    -- 5.3+ string.sub/%d require integer args, not floats
    percent = math.floor(amount/total*100)
    if interactive == "true" then
	nrhash = math.floor(hashestotal - hashestotal / total * amount)
	line = string.format("%-31s[%3d%%]", string.sub(hash, nrhash), percent)
	io.stdout.write(io.stdout, line)
	io.stdout.flush(io.stdout)
	for i = 1, string.len(line) do
	    io.stdout.write(io.stdout, '\b')
	end
    else
	io.stdout.write(io.stdout, string.format("%%%% %f\n", percent))
    end
end
	
function showerrors(i, msg)
    apterror(msg)
end

good = 1
unknown = 0
illegal = 0
errors = {}

skiplist = confgetlist("RPM::GPG::Skip-Check", "")

io.stdout.write(io.stdout, string.format("%-41s", _("Checking GPG signatures...")))
if interactive == "false" then
	io.stdout.write(io.stdout, '\n')
end
for i, file in ipairs(files_install) do
    skipthis = false
    for j, skip in ipairs(skiplist) do
	start = string.find(pkgname(pkgs_install[i]), skip)
	if start then
	    skipthis = true
	    aptwarning(_("Skipped GPG check on "..pkgname(pkgs_install[i])))
	    break
	end
    end
    if quiet == 0 then
	printhash(i, #files_install)
    end
    if skipthis == false then
	status = apt.checksig(file)
	if status == "nottrusted" then
	    table.insert(errors, _("Untrusted signature on "..file))
	    unknown = unknown + 1
	    good = nil
	elseif status == "nokey" then
	    table.insert(errors, _("Unknown signature on "..file))
	    unknown = unknown + 1
	    good = nil
	elseif status == "fail" then
	    table.insert(errors, _("Illegal signature on "..file))
	    illegal = illegal + 1
	    good = nil
	elseif status == nil then
	    table.insert(errors, _("Could not open "..file))
	    illegal = illegal + 1
	    good = nil
	end
    end
end
if interactive == "true" then
    io.stdout.write(io.stdout, '\n')
end

if not good then
    for i, msg in ipairs(errors) do showerrors(i, msg) end
    apterror(_("Error(s) while checking package signatures:\n"..unknown.." package(s) with unknown/untrusted signatures\n"..illegal.." package(s) with illegal/corrupted signatures"))
end

-- vim::sts=4:sw=4
