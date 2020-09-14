#pragma once



namespace experience
{


   namespace anthill
   {


         class CLASS_DECL_APP_EXPERIENCE_ANTHILL library:
            virtual public ::apex::library
         {
         public:


            library();
            virtual ~library();


            virtual ::context_object * new_object(::layered * pobjectContext, const char * pszClass) override;


         };


   } // namespace anthill


} // namespace experience




