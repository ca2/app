#pragma once


namespace experience
{


   namespace tranquillum
   {


      class CLASS_DECL_APP_EXPERIENCE_TRANQUILLUM library:
            virtual public ::apex::library
         {
         public:


            library();
            virtual ~library();


            virtual ::generic * new_object(::layered * pobjectContext,const char * lpszClass) override;


         };


      } // namespace tranquillum


   } // namespace experience



