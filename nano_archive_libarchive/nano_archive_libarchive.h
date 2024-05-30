//
// Created by camilo on 2024-05-26 21:25 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/archive/archive.h"

namespace libarchive
{
    namespace nano
    {
        namespace archive
        {
            class CLASS_DECL_NANO_ARCHIVE_LIBARCHIVE archive:
    virtual public ::nano::archive::archive
            {
            public:

                archive();
                ~archive() override;


                void untar(const ::file::path & pathFolder, const ::payload & payloadTar, int iStripComponent, ::function<void(const::scoped_string& scopedstr) > functionCallback) override;


            };
        } // namespace archive
    } // namespace nano
} // namespace libarchive