#pragma once


namespace experience
{


   namespace tranquillum
   {


      class CLASS_DECL_APP_EXPERIENCE_TRANQUILLUM library:
            virtual public ::aura::library
         {
         public:


            library();
            virtual ~library();


            virtual ::generic_object * new_object(::object * pobject,const char * lpszClass) override;


         };


      } // namespace tranquillum


   } // namespace experience



