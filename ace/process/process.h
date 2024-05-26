//
// Created by camilo on 2024-05-22 22:30 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "ace/primitive/primitive/quantum.h"
#include "ace/primitive/string/string.h"


namespace shell
{


    class shell :
        virtual public ::quantum
    {
    public:


        cstring command_output(const string_pointer & strpointerCommand);

        cstring environment_variable(const string_pointer & strpointerKey);


    };


} // namespace shell



