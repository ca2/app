#pragma once


#include "bred/platform/system.h"


namespace core
{


   class CLASS_DECL_CORE system :
      virtual public ::bred::system
   {
   public:


      system();
      ~system() override;


      void common_construct();


      virtual void initialize(::particle * pparticle) override;


      virtual void initialize_rich_text();

      virtual void InsertTime(::ftp::file_status& ftpFileStatus);
     

   };


} // namespace core




