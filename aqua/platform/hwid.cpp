#include "framework.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSION
#undef ERROR
#include "acme/_operating_system.h"
//#include <vector>
//#include <algorithm>
//#include <fstream>

//#include "header.h"
#include "hwid.h"
#include "sha256.h"
//#include "strutils.h"
#ifdef APPLE_BUILD
    #include <CoreFoundation/CFString.h>
    #include <CoreFoundation/CoreFoundation.h>
    #include <IOKit/IOBSD.h>
    #include <IOKit/IOKitLib.h>
    #include <IOKit/storage/IOMedia.h>
#endif

//#ifndef _WIN32
//    #include <cpuid.h>
//#endif


//https://github.com/denisbrodbeck/machineid
static memory getUUID()
{
    memory res;
    const auto ensure_res_size = [&res]()
    {
        res.set_size(100); //warning! UUIDS must fit into!
    };
    ensure_res_size();
#ifdef APPLE_BUILD
    io_registry_entry_t ioRegistryRoot = IORegistryEntryFromPath(kIOMasterPortDefault, "IOService:/");
    CFStringRef uuidCf = (CFStringRef) IORegistryEntryCreateCFProperty(ioRegistryRoot, CFSTR(kIOPlatformUUIDKey), kCFAllocatorDefault, 0);
    IOObjectRelease(ioRegistryRoot);
    CFStringGetCString(uuidCf, res.data(), res.size(), kCFStringEncodingMacRoman);
    CFRelease(uuidCf);
#endif

#ifdef LINUX
    const auto static get = [](const std::string & fn)
    {
        std::string res;
        std::fstream in(fn, std::ios_base::in | std::ios_base::binary);
        if (in.is_open())
        {
            res = utility::read_stream_into_container(in);
            utility::trim(res);
        }

        return res;
    };
    auto s = get("/var/lib/dbus/machine-id");
    if (s.empty())
        s = get("/etc/machine-id");
    ::memory_copy(res.data(), s.c_str(), std::min(s.length(), res.size()));
#endif

#ifdef _WIN32
    HKEY key {0};
    if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Cryptography", 0, KEY_QUERY_VALUE | KEY_WOW64_64KEY, &key))
    {
        long sz = static_cast<long>(res.size());
        RegQueryValueA(key, "MachineGuid", (LPSTR) res.data(), &sz);
        RegCloseKey(key);
    }

#endif
    //std::transform(res.begin(), res.end(), res.begin(), ::toupper);
    for (::index i = 0; i < res.size(); i++)
    {

       ((char &) res[i]) = ::character_toupper((char)res[i]);

    }
    return res;
}

static void queryCpu(unsigned int func, unsigned int& eax, unsigned int& ebx, unsigned int& ecx, unsigned int& edx)
{
//#ifdef _WIN32
//    //https://msdn.microsoft.com/ru-ru/library/hskdteyh.aspx
//    int info[4];
//    __cpuid(info, func);
//    eax = info[0];
//    ebx = info[1];
//    ecx = info[2];
//    edx = info[3];
//#else
//    __get_cpuid(func, &eax, &ebx, &ecx, &edx);
//#endif

}

hwid::CPUVendorID::CPUVendorID()
{
    unsigned int eax;
    queryCpu(0, eax, regs.ebx, regs.ecx, regs.edx);
}

::string hwid::makeHWID()
{
    CPUVendorID id;
    auto cpuID = id.toString();


    unsigned int eax;
    unsigned int ebx;
    unsigned int ecx;
    unsigned int edx;
    queryCpu(1, eax, ebx, ecx, edx);

    SHA256 sha256;
    sha256.add(cpuID.c_str(), cpuID.length());
    sha256.add(eax);
    sha256.add(edx);
    sha256.add(ecx);
    const auto uuid = getUUID();
    sha256.add(uuid.data(), uuid.size());

    return sha256.getHash().uppered();
}
