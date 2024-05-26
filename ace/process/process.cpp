//
// Created by camilo on 2024-05-22 22:40 <3ThomasBorregaardSorensen.
//
#include "framework.h"
#include "process.h"
#include "ace/filesystem/filesystem/filesystem.h"
#include "ace/platform/application.h"
#include <stdlib.h>


namespace shell
{


    cstring command_output(const string_pointer & strpointerCommand)
    {

        auto strTempName = ::filesystem::temporary_file_name();

        cstring strCommand;

        strCommand.formatf("%s &> %s", strpointerCommand.c_str(), strTempName.c_str());

        information_log(strCommand);

        system(strCommand);

        ::ace::string strOutput = ::ace::file_as_string(strTempName);

        remove(strTempName);

        return strOutput;

    }


    ::ace::string get_environment_variable(const string_pointer & strpointerKey)
    {

        return getenv(strpointerKey.m_psz);

    }


} // namespace ace



