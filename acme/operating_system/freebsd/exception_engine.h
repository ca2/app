#pragma once
#define original_linux linux
#define linux original_linux


namespace linux
{


   namespace exception
   {


      class CLASS_DECL_ACME engine :
         public ::exception_engine
      {
      public:


         engine();
         virtual ~engine();


      };


   } // namespace exception


} // namespace linux



