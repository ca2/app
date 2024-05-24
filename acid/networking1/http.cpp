//
// Created by camilo on 2024-05-23 01:35 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "acid/filesystem/filesystem/filesystem.h"
#include "acid/platform/application.h"


namespace acid
{


    bool curl_check_http_ok(const char * pszUrl);

    bool curl_http_download(const char * pszFile, const char * pszUrl);

    bool wget_check_http_ok(const char * pszUrl);

    bool wget_http_download(const char * pszFile, const char * pszUrl);


    bool application::check_http_ok(const char * pszUrl)
    {

        bool bOk = false;

        auto strDistro = get_distro();

        if (strDistro.case_insensitive_equals("freebsd"))
        {

            bOk = curl_check_http_ok(pszUrl);

        }
        else
        {

            bOk = wget_check_http_ok(pszUrl);

        }

        if (bOk)
        {

            printf("File at \"%s\" seems OK!\n", pszUrl);

        }
        else
        {

            printf("Resource at \"%s\" doesn't exist!\n", pszUrl);

        }

        return bOk;

    }


    bool application::http_download(const char * pszFile, const char * pszUrl)
    {

        bool bOk = false;

        auto strDistro = get_distro();

        if (strDistro.case_insensitive_equals("freebsd"))
        {

            bOk = curl_http_download(pszFile, pszUrl);

        }
        else
        {

            bOk = wget_http_download(pszFile, pszUrl);

        }

        if (bOk)
        {

            printf("File at \"%s\" seems OK!\n", pszUrl);

        }
        else
        {

            printf("Resource at \"%s\" doesn't exist!\n", pszUrl);

        }

        return bOk;


    }


} // namespace acid