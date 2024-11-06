//
//  speech.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-05-12
//  Copyright © 2024 Camilo Sasuke Tsumanuma. All rights reserved.
//
//
// Created by camilo on 2024-05-12 02:00 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/constant/gender.h"
#include "acme/platform/department.h"


namespace nano
{


   namespace speech
   {
   
   
      class CLASS_DECL_ACME speech :
         virtual public ::acme::department
      {
      public:
         
         
         speech();
         ~speech() override;
         
         
         inline static const char * represented_component_name(){return "nano_speech";}

#ifdef _DEBUG
      
         virtual huge_integer increment_reference_count() override;
         virtual huge_integer decrement_reference_count() override;
         virtual huge_integer release() override;
      
#endif
      
         void on_initialize_particle() override;
      
      
         virtual void speak(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrLang = "en-us", enum_gender egender = e_gender_none);
      
      
      };
   
   
   } // namespace speech


} // namespace nano



