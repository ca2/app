﻿#pragma once



namespace experience
{


   namespace anthill
   {


         class CLASS_DECL_APP_EXPERIENCE_ANTHILL experience:
            public ::experience::experience
         {
         public:


            experience();
            virtual ~experience();


            virtual ::e_status initialize(::object * pobject) override;


            virtual void update() override;


            virtual void get_frame_list(string_array & stra) override;




            virtual ::experience::frame * experience_get_frame(const ::string & pszSchema) override;


         };


   } // namespace anthill


} // namespace experience




