//
// Created by camilo on 2024-05-27 02:10 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/platform/department.h"


namespace nano
{


    namespace compress
    {


        class CLASS_DECL_ACME compress :
        virtual public ::acme::department
        {
        public:


            inline static const_char_pointer  represented_component_name()
            {

                return "nano_compress";

            }


            compress();
            ~compress() override;


            virtual void unzip(const ::file::path & pathFolder, const ::payload & payloadZip);


        };


    } // namespace archive


} // namespace nano

