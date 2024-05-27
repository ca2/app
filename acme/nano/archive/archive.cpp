//
// Created by camilo on 2024-05-26 21:30 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "acme/nano/archive/archive.h"
#include "acme/exception/interface_only.h"


namespace nano
{


   namespace archive
   {


      archive::archive()
      {

      }


      archive::~archive()
      {

      }


      void archive::untar(const ::file::path & pathFolder, const ::payload & payloadTar, int iStripComponent, ::function<void(const::scoped_string& scopedstr) > functionCallback)
      {

         throw interface_only();

      }


   } // namespace archive


} // namespace nano