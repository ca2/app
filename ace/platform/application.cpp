//
// Created by camilo on 2024-05-22 16:31 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "application.h"
#include "ace/filesystem/filesystem/filesystem.h"
#include "ace/primitive/string/string.h"
#include "ace/process/process.h"


namespace ace
{


    ::ace::string string_formatf_arguments(const char *format, va_list args);


    void information_log(const char * psz)
    {

        fprintf(stdout, "%s\n", psz);

        fflush(stdout);

    }


    void information_log_format(const char * psz,...)
    {

        va_list args;

        va_start(args, psz);
        auto str = string_formatf_arguments(psz, args);
        va_end(args);

        information_log(str);

    }


    void error_log(const char* psz)
    {

        fprintf(stderr, "%s\n", psz);

        fflush(stderr);

    }


    void error_log_format(const char * psz,...)
    {

        va_list args;

        va_start(args, psz);
        auto str = string_formatf_arguments(psz, args);
        va_end(args);

        error_log(str);

    }


    application::application()
    {
        m_iExitCode=0;
        m_argc=0;
        m_args=nullptr;
        m_bOperatingSystemSummary = false;

    }


    application::~application()
    {


    }


    void application::initialize_application(int argc, const char ** args)
    {

        m_argc=argc;
        m_args=args;

    }


    ::ace::string application::get_distro()
    {

        defer_calculate_operating_system_summary();

        return m_strDistro;

    }

    ::ace::string application::get_version()
    {

        defer_calculate_operating_system_summary();

        return m_strVersion;

    }


    ::ace::string application::get_branch()
    {

        defer_calculate_operating_system_summary();

        return m_strBranch;

    }


    void application::defer_calculate_operating_system_summary()
    {

        if(m_bOperatingSystemSummary)
        {

return ;

        }

        m_bOperatingSystemSummary = true;

        auto strEtcOsRelease = ::ace::file_as_string("/etc/os-release");

//m_pszDistro = nullptr;
//m_pszVersion = nullptr;
//m_pszBranch = nullptr;

if (strEtcOsRelease)
{

//printf("%s", pszEtcOsRelease);

auto psz = strEtcOsRelease();

while (true)
{

auto strNewLine = get_line(psz, psz);

if (strNewLine.is_null())
{

break;

}

if (auto strName = strNewLine.case_insensitive_if_begins_eat_and_return("ID="))
{

strName.trim_quotes();

if (strName.case_insensitive_equals("ubuntu"))
{

auto strXdgCurrentDesktop = get_environment_variable("XDG_CURRENT_DESKTOP");

if (strXdgCurrentDesktop.case_insensitive_contains("KDE"))
{

information_log("This is Kubuntu System...");

m_strDistro = "kubuntu";

}
else
{

information_log("This is Ubuntu System (Unity)...");

m_strDistro = "ubuntu";

}


}
else if (strName.case_insensitive_equals("fedora"))
{

printf("This is Fedora Linux System...\n");

m_strDistro = "fedora";

}
else if (strName.case_insensitive_equals("freebsd"))
{

printf("This is FreeBSD System...\n");

m_strDistro = "freebsd";

auto pszDot = m_strVersion.find_character('.');

if (pszDot)
{

   m_strVersion.truncate(pszDot);

}

auto strXdgCurrentDesktop = ace::get_environment_variable("XDG_CURRENT_DESKTOP");

if (strXdgCurrentDesktop.case_insensitive_contains("GNOME"))
{

printf("This is GNOME System...\n");

m_strBranch = "gnome";

}
else if (strXdgCurrentDesktop.case_insensitive_contains("KDE"))
{

printf("This is KDE System...\n");

m_strBranch = "kde";

}
else
{

printf("This is unknown branch...\n");

}


}
else if (!strName.case_insensitive_equals("opensuse-tumbleweed"))
{

printf("This is openSUSE Tumbleweed System...\n");

m_strDistro = "opensuse-tumbleweed";

auto strXdgCurrentDesktop = ace::get_environment_variable("XDG_CURRENT_DESKTOP");

if (strXdgCurrentDesktop.case_insensitive_contains("GNOME"))
{

printf("This is GNOME System...\n");

m_strBranch = "gnome";

}
else if (strXdgCurrentDesktop.case_insensitive_contains("KDE"))
{

printf("This is KDE System...\n");

m_strBranch = "kde";

}
else
{

printf("This is unknown branch...\n");

}

//::system("sudo dnf --assumeyes install freeimage libidn motif libappindicator-gtk3");

}

}
else if (auto strVersionId = strNewLine.case_insensitive_if_begins_eat_and_return("VERSION_ID="))
{

   strVersionId.trim_quotes();

   m_strVersion = strVersionId;

   printf("This System version is %s ...\n", m_strVersion.c_str());

}
else if (auto strBranchId = strNewLine.case_insensitive_if_begins_eat_and_return("VARIANT_ID="))
{

   strBranchId.trim_quotes();

   m_strBranch = strBranchId;

   printf("This System branch is %s ...\n", m_strBranch.c_str());

}

}

}

if (!m_strDistro || !m_strVersion)
{

return nullptr;

}

if (!m_strDistro.case_insensitive_equals("opensuse-tumbleweed") && m_strVersion.size() > 4)
{

printf("This is a openSUSE Tumbleweed System...\n");
printf("Gonna tweak a bit the version :-)...\n");
m_strVersion.truncate(4);
printf("There it is new version : %s\n", m_strVersion.c_str());

}


    }


    void application::run()
    {


    }


    void application::information_log(const char * psz)
    {

        ::ace::information_log(psz);

    }


    void application::informationf_log(const char * psz,...)
    {

        va_list args;

        va_start(args, psz);
        auto str = string_formatf_arguments(psz, args);
        va_end(args);

        information_log(str);


    }



    void application::error_log(const char * psz)
    {

        ::ace::error_log(psz);

    }


    void application::errorf_log(const char * psz,...)
    {

        va_list args;

        va_start(args, psz);
        auto str = string_formatf_arguments(psz, args);
        va_end(args);

        errorinformation_log(str);

    }



} // namespace ace

