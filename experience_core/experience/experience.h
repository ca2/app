#pragma once


#include "berg/user/experience/experience.h"


namespace experience_core
{


   class CLASS_DECL_APP_EXPERIENCE_CORE experience:
      public ::experience::experience
   {
   public:


      experience();
      ~experience() override;


      virtual void initialize(::particle * pparticle) override;


      virtual void update() override;


      virtual void get_frame_list(string_array_base & stra) override;


      ::pointer < ::experience::frame > frame_experience(const ::scoped_string & scopedstrFrameSchema) override;


   };


} // namespace experience_core



