#include "ace.h"
#include "version.h"

#define VER_PLATFORM_WIN32s                     0
#define VER_PLATFORM_WIN32_WINDOWS              1
#define VER_PLATFORM_WIN32_NT                   2

#ifndef WINDOWS

#define	VER_NT_WORKSTATION			1
#define	VER_NT_DOMAIN_CONTROLLER		2
#define	VER_NT_SERVER				3

#endif



// int_bool get_version_ex_a(LPOSVERSIONINFOEXA pVersionInformation)

// {

// #if defined(_WIN32) || defined(_UWP)

//    /* Windows 10 Version Info */
//    if ((pVersionInformation->dwOSVersionInfoSize == sizeof(OSVERSIONINFOA)) ||

//          (pVersionInformation->dwOSVersionInfoSize == sizeof(OSVERSIONINFOEXA)))

//    {
//       pVersionInformation->dwMajorVersion = 10;

//       pVersionInformation->dwMinorVersion = 0;

//       pVersionInformation->dwBuildNumber = 0;

//       pVersionInformation->dwPlatformId = VER_PLATFORM_WIN32_NT;

//       ZeroMemory(pVersionInformation->szCSDVersion, sizeof(pVersionInformation->szCSDVersion));


//       if (pVersionInformation->dwOSVersionInfoSize == sizeof(OSVERSIONINFOEXA))

//       {
//          LPOSVERSIONINFOEXA pVersionInformationEx = (LPOSVERSIONINFOEXA)pVersionInformation;

//          pVersionInformationEx->wServicePackMajor = 0;

//          pVersionInformationEx->wServicePackMinor = 0;

//          pVersionInformationEx->wSuiteMask = 0;

//          pVersionInformationEx->wProductType = VER_NT_WORKSTATION;

//          pVersionInformationEx->wReserved = 0;

//       }

//       return true;
//    }

// #else

//    /* Windows 7 SP1 Version Info */
//    if ((pVersionInformation->dwOSVersionInfoSize == sizeof(OSVERSIONINFOA)) ||

//          (pVersionInformation->dwOSVersionInfoSize == sizeof(OSVERSIONINFOEXA)))

//    {
//       pVersionInformation->dwMajorVersion = 6;

//       pVersionInformation->dwMinorVersion = 1;

//       pVersionInformation->dwBuildNumber = 7601;

//       pVersionInformation->dwPlatformId = VER_PLATFORM_WIN32_NT;

//       memset(pVersionInformation->szCSDVersion, 0, sizeof(pVersionInformation->szCSDVersion));


//       if (pVersionInformation->dwOSVersionInfoSize == sizeof(OSVERSIONINFOEXA))

//       {
//          LPOSVERSIONINFOEXA pVersionInformationEx = (LPOSVERSIONINFOEXA)pVersionInformation;

//          pVersionInformationEx->wServicePackMajor = 1;

//          pVersionInformationEx->wServicePackMinor = 0;

//          pVersionInformationEx->wSuiteMask = 0;

//          pVersionInformationEx->wProductType = VER_NT_WORKSTATION;

//          pVersionInformationEx->wReserved = 0;

//       }

//       return true;
//    }


// #endif

//    return false;

// }



CLASS_DECL_ACE int _ca_is_basis()
{
#if CA2_PLATFORM_VERSION == CA2_BASIS
   return true;
#else
   return false;
#endif
}

CLASS_DECL_ACE int _ca_is_stage()
{
#if CA2_PLATFORM_VERSION == CA2_STAGE
   return true;
#else
   return false;
#endif
}






