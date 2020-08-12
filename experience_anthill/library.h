#pragma once



namespace experience
{


   namespace anthill
   {


         class CLASS_DECL_APP_EXPERIENCE_ANTHILL library:
            virtual public ::aura::library
         {
         public:


            library();
            virtual ~library();


            virtual ::context_object * new_object(::object * pobjectContext, const char * pszClass) override;


         };


   } // namespace anthill


} // namespace experience




