//
// Created by camilo on 2024-06-02 20:06 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "id.h"
#include "acme/exception/interface_only.h"


namespace nano
{


   namespace account
   {


      id::id()
      {


      }


      id::~id()
      {


      }



      bool id::is_equal(id *pid)
      {

         throw interface_only();

         return false;

      }


      bool id::is_less(id *pid)
      {

         throw interface_only();

         return false;

      }

      ::string id::as_string()
      {

         throw interface_only();

         return {};

      }


   } // namespace account


} // namespace nano



