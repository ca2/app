#pragma once





   namespace experience
   {


      namespace lite

      {


         class CLASS_DECL_APP_EXPERIENCE_LITE library:
            virtual public ::acme::library
         {
         public:


            library(::particle * pparticle);
            virtual ~library();


            virtual ::pointer<::object>alloc(::particle * pparticle, const ::string & pszClass, object * p) override;


         };


      } // namespace lite



   } // namespace experience






