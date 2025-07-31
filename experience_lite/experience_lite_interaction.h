#pragma once





   namespace experience
   {


      namespace lite

      {


         class CLASS_DECL_APP_EXPERIENCE_LITE experience:
            public ::experience::experience
         {
         public:





            experience(::particle * pparticle);
            virtual ~experience();

            virtual void update();


            virtual void get_frame_list(string_array & stra);


            virtual ::pointer<::experience::frame>get_frame(const ::scoped_string & scopedstrSchema);


         };


      } // namespace lite



   } // namespace experience








