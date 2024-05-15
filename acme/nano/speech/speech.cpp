//
//  speech.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/05/24.
//  Copyright © 2024 Camilo Sasuke Tsumanuma. All rights reserved.
// Created by camilo on 2024-05-12 02:15 <3ThomasBorregaardSorensen!!

//
#include "framework.h"
#include "speech.h"


namespace nano
{
    namespace speech
    {
        speech::speech()
        {
        }


        speech::~speech()
        {
        }


#ifdef _DEBUG


        i64 speech::increment_reference_count()
        {
            return ::acme::department::increment_reference_count();
        }


        i64 speech::decrement_reference_count()
        {
            return ::acme::department::decrement_reference_count();
        }

        i64 speech::release()
        {
            return ::acme::department::release();
        }

#endif

        void speech::on_initialize_particle()
        {
        }


        void speech::speak(const ::scoped_string& scopedstr, const ::scoped_string& scopedstrLang, enum_gender egender)
        {
        }
    } // namespace speech
} // namespace nano
