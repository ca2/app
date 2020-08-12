#pragma once


namespace user
{


   namespace experience
   {

      namespace experience_core
      {


         class CLASS_DECL_APP_CORE_EXPERIENCE_CORE library:
            virtual public ::aura::library
         {
         public:


            library(::object * pobject);
            virtual ~library();


//            virtual bool is_uinteraction_library() override;
            virtual __pointer(::context_object) alloc(::object * pobject,const char * pszClass, object * p) override;


         };


      } // namespace experience_core


   } // namespace experience


} // namespace user






