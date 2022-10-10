#pragma once





   namespace experience
   {


      namespace lite

      {


         class CLASS_DECL_APP_EXPERIENCE_LITE library:
            virtual public ::acme::library
         {
         public:


            library(::object * pobject);
            virtual ~library();


            virtual ::pointer<::object>alloc(::object * pobject, const ::string & pszClass, object * p) override;


         };


      } // namespace lite



   } // namespace experience






