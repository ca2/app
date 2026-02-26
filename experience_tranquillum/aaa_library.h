#pragma once


namespace experience
{


   namespace tranquillum
   {


      class CLASS_DECL_APP_EXPERIENCE_TRANQUILLUM library:
            virtual public ::acme::library
         {
         public:


            library();
            virtual ~library();


            virtual ::matter * new_object(const ::scoped_string & scopedstrClass) override;


         };


      } // namespace tranquillum


   } // namespace experience



