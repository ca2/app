#pragma once


#include "base/user/experience/experience.h"


namespace experience_nanogui
{


   class CLASS_DECL_APP_EXPERIENCE_CORE experience :
      public ::experience::experience
   {
   public:


      experience();
      ~experience() override;


      void initialize(::object * pobject) override;


      void update() override;


      void get_frame_list(string_array & stra) override;


      ::experience::frame * frame_experience(const ::string & strFrameSchema) override;


   };


} // namespace experience_nanogui



