#pragma once



   namespace experience
   {


      namespace core
      {


         class CLASS_DECL_APP_EXPERIENCE_CORE library:
            virtual public ::apex::library
         {
         public:


            library();
            virtual ~library();


            virtual ::matter * new_object(::layered * pobjectContext, const char * pszClass) override;

            
         };



      } // namespace core


   } // namespace experience



