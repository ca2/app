//
// Created by camilo on 2024-05-27 02:12 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/platform/department.h"


namespace nano
{


    namespace shell
    {


        class CLASS_DECL_ACME shell :
        virtual public ::acme::department
        {
        public:


            inline static const char * represented_component_name()
            {

                return "nano_shell";

            }


            shell();
            ~shell() override;


            virtual void launch_no_hup(const ::file::path & pathExecutable, const ::file::path & pathLog);


        };


    } // namespace shell


} // namespace nano

