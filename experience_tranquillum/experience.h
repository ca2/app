#pragma once


namespace experience
{


   namespace tranquillum
   {


      class CLASS_DECL_APP_EXPERIENCE_TRANQUILLUM experience:
            public ::experience::experience
         {
         public:





            experience();
            virtual ~experience();

            virtual void update() override;


            virtual ::estatus initialize(::object * pobjectContext) override;

            virtual void get_frame_list(string_array & stra) override;


            virtual ::experience::frame * experience_get_frame(const char * pszSchema) override;


         };



      } // namespace tranquillum


   } // namespace experience



