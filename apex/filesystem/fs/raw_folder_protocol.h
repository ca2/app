// From fs/raw_folder by camilo on 2025-03-10 22:04 <3ThomasBorregaardSorensen!!
#pragma once


#include "raw_folder.h"


namespace fs
{


   class CLASS_DECL_APEX raw_folder_protocol :
      virtual public ::fs::raw_folder
   {
   public:



      raw_folder_protocol();
      ~raw_folder_protocol() override;


      void on_initialize_particle() override;


      virtual ::string protocol();

      ::file::listing & root_ones(::file::listing & listing) override;



   };


} // namespace fs



