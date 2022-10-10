#pragma once





   namespace experience
   {


      namespace lite

      {


         class CLASS_DECL_APP_EXPERIENCE_LITE experience:
            public ::experience::experience
         {
         public:





            experience(::object * pobject);
            virtual ~experience();

            virtual void update();


            virtual void get_frame_list(string_array & stra);


            virtual ::pointer<::experience::frame>get_frame(const ::string & pszSchema);


         };


      } // namespace lite



   } // namespace experience








