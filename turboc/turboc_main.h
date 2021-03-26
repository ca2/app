#pragma once


namespace turboc
{


   typedef void FN_MAIN();
   typedef FN_MAIN * PFN_MAIN;


   class CLASS_DECL_TURBOC main:
      virtual public ::thread
   {
   public:

      
      PFN_MAIN       m_pfnMain;


      main(::object * pobject);
      virtual ~main();


      virtual i32 run();


   };


} // namespace userstack



