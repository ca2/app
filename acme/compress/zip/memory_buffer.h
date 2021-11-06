#pragma once


namespace zip
{


   class CLASS_DECL_ACME memory_file :
      public ::memory_file

   {
   public:


      void *               m_pvoidFileFuncDef;


      memory_file();
      memory_file(memory_base * pmemory);
      virtual ~memory_file();


      void common_construct();



   };


} // namespace zip



