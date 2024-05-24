#include "framework.h"
#include "ace/filesystem/filesystem/filesystem.h"
#include "ace/primitive/string/string.h"
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <memory.h>

// char * as_string(const char * pszFilename);
//
//
// char * get_line(char * str, char * & next);
// char * get_command_output(const char * pszCommand);
//
//
// char * start_temporary_file_name();
// void end_temporary_file_name(char * ptmpname);
// char * end_temporary_file_name_as_string(char * ptmpname);


bool wget_check_http_ok(const string_pointer & strpointerUrl)
{
    auto strTempName = acefile()->temporary_file_name();

    ::ace::string strCommand;

    strCommand.formatf("wget -o \"%s\" -S \"%s\"", strTempName.c_str(), pszUrl);

    ::system(strCommand);

    auto strOutput = filesystem::as_string(strTempName);

    if (!strOutput)
    {
        return false;
    }

    auto psz = strOutput();

    while (true)
    {
        auto strNewLine = get_line(psz, psz);

        if (!strNewLine)
        {
            return false;
        }


        if (strNewLine[0] == ' '
            && strNewLine[1] == ' '
            && strNewLine[2] == 'H'
            && strNewLine[3] == 'T'
            && strNewLine[4] == 'T'
            && strNewLine[5] == 'P'
            && strNewLine[6] == '/')
        {
            auto pszSpace = strNewLine.find_character(' ', 6);

            if (!pszSpace)
            {
                return false;
            }

            auto pszNonSpace = pszSpace.skip_any_not_in(" \t");

            auto pszNextSpace = pszNonSpace.find_any_in(" \t");

            if (!pszNextSpace)
            {
                return false;
            }

            if (!strncmp(pszNonSpace, "200", pszNextSpace - pszNonSpace))
            {
                return true;
            }

            return false;
        }
    }
}


void wget_http_download(const string_pointer & strpointerFile, const string_pointer & strpointerUrl)
{

    auto strDownloadCommand = cstring();

    strDownloadCommand = "wget ";
    strDownloadCommand += strpointerUrl;
    strDownloadCommand += " -O ";
    strDownloadCommand += strpointerFile;

    ::system(strDownloadCommand);

}
