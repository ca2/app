//
// Created by camilo on 2024-05-22 16:08 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acid/platform/context.h"
#include "acid/primitive/string/string.h"


namespace acid
{



    class application :
        virtual public ::acid::context
    {
    public:

        int                 m_argc;
        const char **       m_args;
        int                 m_iExitCode;

        ::cstring           m_strDistro;
        ::cstring           m_strVersion;
        ::cstring           m_strBranch;

        bool m_bOperatingSystemSummary;


        application();
        ~application() override;

        ::cstring           get_distro();
        ::cstring           get_version();
        ::cstring           get_branch();

        bool check_http_ok(const char * pszUrl);

        bool http_download(const char * pszFile, const char * pszUrl);

        virtual void initialize_application(int argc, const char ** args);

        virtual void defer_calculate_operating_system_summary();

        virtual void run();

#if defined(LINUX)
        bool _curl_check_http_ok(const char * pszUrl);
        bool _wget_check_http_ok(const char * pszUrl);
        void _curl_http_download(const char * pszFile, const char * pszUrl);
        void _wget_http_download(const char * pszFile, const char * pszUrl);
#endif

    };

template < typename APPLICATION >
int main(int argc, const char ** args)
{
    APPLICATION application;

    application.initialize_application(argc, args);

    try
    {

        application.run();

    }
    catch(const char * psz)
    {
        error_log(psz);

    }

    return application.m_iExitCode;
}

} // namespace acid



