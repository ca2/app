#pragma once


//#include "zip_unzip.h"


namespace zip
{


   class CLASS_DECL_ACID api
   {
   public:


      api();
      virtual ~api();


      static void * unzip_open(memory_file * pfile);
      static void * unzip_open(file * pfile);

      static void * zip_open(file * pfile);




   };


} // namespace zip
