#pragma once


#include "base/user/experience/experience.h"


namespace experience_core
{


   class CLASS_DECL_APP_EXPERIENCE_CORE experience:
      public ::experience::experience
   {
   public:


      experience();
      ~experience() override;


      virtual void initialize(::object * pobject) override;


      virtual void update() override;


      virtual void get_frame_list(string_array & stra) override;


      virtual ::experience::frame * frame_experience(const ::string & strFrameSchema) override;


   };


} // namespace experience_core



