#pragma once





   namespace experience
   {


      namespace lite

      {


         class CLASS_DECL_APP_EXPERIENCE_LITE library:
            virtual public ::aura::library
         {
         public:


            library(::object * pobject);
            virtual ~library();


            virtual __pointer(::context_object) alloc(::object * pobject, const char * pszClass, object * p) override;


         };


      } // namespace lite



   } // namespace experience






