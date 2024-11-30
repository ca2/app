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


      //void on_set_platform() override;


      //virtual void initialize(::particle * pparticle) override;


      void initialize_rich_text() override;

      void InsertTime(::ftp::file_status& ftpFileStatus) override;
     

   };


} // namespace core




