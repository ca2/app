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
            ~experience() override;


            virtual void update() override;


            virtual void initialize(::object * pobject) override;

            virtual void get_frame_list(string_array & stra) override;


            ::experience::frame * frame_experience(const ::string & strFrameSchema) override;


         };



      } // namespace tranquillum


   } // namespace experience



