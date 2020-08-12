#pragma once


namespace user
{


   namespace experience
   {


      namespace experience_core
      {


         class CLASS_DECL_APP_CORE_EXPERIENCE_CORE interaction:
            public ::experience::experience
         {
         public:


            


            interaction(::object * pobject);
            virtual ~interaction();

            virtual void update();


            virtual void get_frame_list(string_array & stra);


            virtual __pointer(::experience::frame) experience_get_frame(const char * pszSchema);


         };


      } // namespace experience_core


   } // namespace experience


} // namespace user





