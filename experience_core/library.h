#pragma once



   namespace experience
   {


      namespace aura
      {


         class CLASS_DECL_APP_EXPERIENCE_CORE library:
            virtual public ::aura::library
         {
         public:


            library();
            virtual ~library();


            virtual ::generic_object * new_object(::object * pobject, const char * pszClass) override;


         };



      } // namespace aura


   } // namespace experience



