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


            inline static const_char_pointer represented_component_name()
            {

                return "nano_shell";

            }


            shell();
            ~shell() override;


            virtual void detached_command(const ::scoped_string & scopedstrCommand, const ::file::path & pathLog);


        };


    } // namespace shell


} // namespace nano

