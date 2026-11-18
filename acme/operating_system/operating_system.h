// Created by camilo on 2023-06-14 13:24 <3ThomasBorregaardSorensen!!
// operating_system class created by camilo on 2026-11-02 16:50 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
#pragma once


//struct no_initialize_t {};
#include "acme/constant/operating_system.h"


namespace operating_system
{

    /// _STUD_API

    class CLASS_DECL_ACME operating_system :
        virtual public ::particle
    {
    public:

#ifdef WINDOWS_DESKTOP
        static constexpr bool c_bWindowsDesktop = true;
#else
        static constexpr bool c_bWindowsDesktop = false;
#endif

#ifdef UNIVERSAL_WINDOWS
        static constexpr bool c_bUniversalWindows = true;
#else
        static constexpr bool c_bUniversalWindows = false;
#endif

#if defined(WINDOWS_DESKTOP) || defined(UNIVERSAL_WINDOWS)
        static constexpr bool c_bWindows = true;
#else
        static constexpr bool c_bWindows = false;
#endif

#if defined(__linux__) && !defined(__ANDROID__)
        static constexpr bool c_bLinux = true;
#else
        static constexpr bool c_bLinux = false;
#endif

#if defined (__linux__) || defined (__unix__)
        static constexpr bool c_bUnix = true;
#else
        static constexpr bool c_bUnix = false;
#endif

#if defined (__APPLE__) || defined(__MACH__)
        static constexpr bool c_bMacos = true;
#else
        static constexpr bool c_bMacos = false;
#endif

#if defined (__APPLE_IOS__)
        static constexpr bool c_bIos = true;
#else
        static constexpr bool c_bIos = false;
#endif

#if defined(__APPLE__)
        static constexpr bool c_bApple = true;
#else
        static constexpr bool c_bApple = false;
#endif

#if defined (__FreeBSD__)
        static constexpr bool c_bFreebsd = true;
#else
        static constexpr bool c_bFreebsd = false;
#endif

#if defined (__ANDROID__)
        static constexpr bool c_bAndroid = true;
#else
        static constexpr bool c_bAndroid = false;
#endif


#if defined (__HAIKU__)
        static constexpr bool c_bHaiku = true;
#else
        static constexpr bool c_bHaiku = false;
#endif

#if defined(MACOS) || defined(WINDOWS_DESKTOP) || defined(LINUX) || defined(__BSD__) || defined(__SUNOS__)
        static constexpr bool c_bDesktopSystem = true;
#else
        static constexpr bool c_bDesktopSystem = false;
#endif

#if defined(APPLE_IOS) || defined(__ANDROID__) || defined(UNIVERSAL_WINDOWS)
        static constexpr bool c_bSandboxed = true;
#else
        static constexpr bool c_bSandboxed = false;
#endif


        operating_system();
        ~operating_system() override;


        virtual bool is(::enum_operating_system eoperatingsystem);
        virtual ::enum_operating_system get();


    };


        //constexpr bool is_apple(const enum_operating_system & eoperatingsystem) noexcept
        //{

        //    return eoperatingsystem == e_operating_system_macos || eoperatingsystem == e_operating_system_ios;

        //}

#undef OPERATING_SYSTEM_DECLARE_IS


#define OPERATING_SYSTEM_DECLARE_IS(is_, bIs) constexpr bool is_() noexcept { return (bIs); }


    OPERATING_SYSTEM_DECLARE_IS(is_windows_desktop, operating_system::c_bWindowsDesktop)
    OPERATING_SYSTEM_DECLARE_IS(is_universal_windows, operating_system::c_bUniversalWindows)
    OPERATING_SYSTEM_DECLARE_IS(is_windows, operating_system::c_bWindows)
    OPERATING_SYSTEM_DECLARE_IS(is_macos, operating_system::c_bMacos)
    OPERATING_SYSTEM_DECLARE_IS(is_ios, operating_system::c_bIos)
    OPERATING_SYSTEM_DECLARE_IS(is_apple, operating_system::c_bApple)
    OPERATING_SYSTEM_DECLARE_IS(is_linux, operating_system::c_bLinux)
    OPERATING_SYSTEM_DECLARE_IS(is_unix, operating_system::c_bUnix)
    OPERATING_SYSTEM_DECLARE_IS(is_freebsd, operating_system::c_bFreebsd)
    OPERATING_SYSTEM_DECLARE_IS(is_android, operating_system::c_bAndroid)
    OPERATING_SYSTEM_DECLARE_IS(is_haiku, operating_system::c_bHaiku)
    OPERATING_SYSTEM_DECLARE_IS(is_desktop_system, operating_system::c_bDesktopSystem)
    OPERATING_SYSTEM_DECLARE_IS(is_sandboxed, operating_system::c_bSandboxed)


#undef OPERATING_SYSTEM_DECLARE_IS




    constexpr bool is(::enum_operating_system eoperatingsystem) noexcept
    {
        if (eoperatingsystem == ::e_operating_system_windows_desktop) {
            return is_windows_desktop();
        }
        else if (eoperatingsystem == ::e_operating_system_windows)
        {
           return is_windows();
        }
        else if (eoperatingsystem == ::e_operating_system_linux)
        {
            return is_linux();
        }
        else if (eoperatingsystem == ::e_operating_system_unix) {
            return is_unix();
        }
        else if (eoperatingsystem == ::e_operating_system_macos) {
            return is_macos();
        }
        else if (eoperatingsystem == ::e_operating_system_freebsd) {
            return is_freebsd();
        }
        else if (eoperatingsystem == ::e_operating_system_android) {
            return is_android();
        }
        else if (eoperatingsystem == ::e_operating_system_haiku) {
            return is_haiku();
        }
        else if (eoperatingsystem == ::e_operating_system_desktop_system) {
            return is_desktop_system();
        }
        else if (eoperatingsystem == ::e_operating_system_sandboxed) {
            return is_sandboxed();
        }
        else {
            return false;
        }
    }

    constexpr ::enum_operating_system get() noexcept
    {
        if (is_windows_desktop()) {
            return ::e_operating_system_windows_desktop;
        }
        else if (is_universal_windows()) {
           return ::e_operating_system_universal_windows;
        }
        else if (is_linux()) {
            return ::e_operating_system_linux;
        }
        else if (is_macos()) {
            return ::e_operating_system_macos;
        }
        else if (is_freebsd()) {
            return ::e_operating_system_freebsd;
        }
        else if (is_android()) {
            return ::e_operating_system_android;
        }
        else if (is_haiku()) {
            return ::e_operating_system_haiku;
        }
        else {
            return ::e_operating_system_none;
        }
    }

    constexpr bool is_apple(::enum_operating_system eoperatingsystem) noexcept
    {
        if (eoperatingsystem == ::e_operating_system_macos) {
            return true;
        }
        else if (eoperatingsystem == ::e_operating_system_ios) {
            return true;
        }
        else {
            return false;
        }
    }


} // namespace operating_system



