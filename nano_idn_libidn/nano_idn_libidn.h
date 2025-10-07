//
// Created by camilo on 2024-05-26 21:25 <3ThomasBorregaardSorensen!!
// From nano_archive_libarchive by camilo on 2024-06-02 17:28 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/idn/idn.h"

namespace libidn
{


    namespace nano
    {


        namespace idn
        {


            class CLASS_DECL_NANO_IDN_LIBIDN idn:
               virtual public ::nano::idn::idn
            {
            public:

                idn();
                ~idn() override;


               virtual string idn_to_punycode(const ::scoped_string & scopedstr) override;
               virtual string idn_from_punycode(const ::scoped_string & scopedstr) override;


            };


        } // namespace idn


    } // namespace nano


} // namespace libidn



