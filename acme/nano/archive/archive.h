//
// Created by camilo on 2024-05-26 21:30 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/platform/department.h"


namespace nano
{


    namespace archive
    {


        class CLASS_DECL_ACME archive :
        virtual public ::acme::department
        {
        public:


            inline static const_char_pointer represented_component_name()
            {

                return "nano_archive";

            }


            archive();
            ~archive() override;


            virtual void untar(const ::file::path & pathFolder, const ::payload & payloadTar, int iStripComponent, ::function<void(const::scoped_string& scopedstr) > functionCallback);


        };


    } // namespace archive


} // namespace nano

