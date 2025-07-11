//
// Created by camilo on 2025-07-11 04:40 <3ThomasBorregaardSorensen!!
//
//
// Created by camilo on 2024-05-27 02:10 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/compress/compress.h"


namespace windows_common
{


    namespace nano
    {


        namespace compress
        {


            class CLASS_DECL_ACME compress :
                virtual public ::nano::compress::compress
            {
            public:



                compress();
                ~compress() override;


                virtual void unzip(const ::file::path & pathFolder, const ::payload & payloadZip);


            };


        } // namespace archive


    } // namespace nano


} // namespace windows_common



