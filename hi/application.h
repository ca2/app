// Created by camilo from application.cpp on 2023-06-07 02:18 <3ThomasBorregaardSorensen
#pragma once


#include "acme/platform/application.h"


namespace console_hello
{


   class application :
      virtual public ::platform::application
   {

   public:


      application();
      ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();


#if defined(__STD_FORMAT__)

      void test_std_format();

#endif // __STD_FORMAT__

      void test_datetime_format(char ch);
      void test_contatenation(char ch);

      void remove_utf8_bom_phase1();
      void remove_utf8_bom_phase2();

      void search_special_characters();

      void main() override;


   };


} // namespace console_hello



