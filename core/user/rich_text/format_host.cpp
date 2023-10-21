// Created by camilo on 2023-10-09 19:01 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "format_host.h"


namespace user
{


   namespace rich_text
   {


      format_host::format_host()
      {


      }


      format_host::~format_host()
      {

      }


      ::pointer<format>format_host::add_format()
      {

         auto pformat = __create_new < format >();

         pformat->initialize_user_rich_text_format(this);

         add(pformat);

         return ::transfer(pformat);

      }


      //::pointer<format>format_host::get_selection_common_format()
      //{

      //   return nullptr;

      //}




   } // namespace rich_text


} // namespace user


