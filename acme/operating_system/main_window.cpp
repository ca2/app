// Created by camilo on 2023-04-15 19:25 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "main_window.h"
#include "acme/exception/interface_only.h"


namespace operating_system
{


   main_window::main_window()
   {


   }


   main_window::~main_window()
   {


   }


   void main_window::from_application(::operating_system::application * papplication)
   {

      throw interface_only();

   }


   bool main_window::is_window()
   {

      return false;

   }


   void main_window::post_close()
   {

      throw interface_only();

   }


   void main_window::post_application_exit()
   {

      throw interface_only();

   }


   void main_window::activate()
   {


   }

   ::string main_window::get_window_text(const ::iptr_array & idPath)
   {

      throw interface_only();

      return {};

   }


   ::string main_window::indexed_get_window_text(const ::iptr_array & idPath)
   {

      throw interface_only();

      return {};

   }


} // namespace operating_system



