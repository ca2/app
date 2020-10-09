#pragma once



   namespace experience
   {


      namespace aura
      {


         class CLASS_DECL_APP_EXPERIENCE_CORE library:
            virtual public ::apex::library
         {
         public:


            library();
            virtual ~library();


            virtual ::element * new_object(::layered * pobjectContext, const char * pszClass) override;

            
         };



      } // namespace aura


   } // namespace experience



