#pragma once
#define original_linux linux
#define linux original_linux

namespace linux
{


   class CLASS_DECL_ACME exception_engine :
      public ::exception_engine
   {
   public:


      exception_engine();
      virtual ~exception_engine();

   };


} // namespace linux



