//
// Created by camilo on 2024-05-26 02:14 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "acme/nano/shell/shell.h"
#include "acme/exception/interface_only.h"


namespace nano
{


   namespace shell
   {


      shell::shell()
      {

      }


      shell::~shell()
      {

      }


      void shell::launch_no_hup(const ::file::path & pathExecutable, const ::file::path & pathLog)
      {

         throw interface_only();

      }


   } // namespace shell


} // namespace nano