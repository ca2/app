#pragma once


#include "base/user/experience/experience.h"


namespace experience_nanoui
{


   class CLASS_DECL_APP_EXPERIENCE_CORE experience :
      public ::experience::experience
   {
   public:


      experience();
      ~experience() override;


      void initialize(::particle * pparticle) override;


      void update() override;


      void get_frame_list(string_array & stra) override;


      ::experience::frame * frame_experience(const ::string & strFrameSchema) override;


   };


} // namespace experience_nanoui



