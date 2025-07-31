#pragma once


#include "base/user/experience/experience.h"


namespace experience_anthill
{


   class CLASS_DECL_APP_EXPERIENCE_ANTHILL experience:
      virtual public ::experience::experience
   {
   public:


      experience();
      ~experience() override;


      void initialize(::particle * pparticle) override;


      void update() override;


      void get_frame_list(string_array & stra) override;



      ::pointer < ::experience::frame > frame_experience(const ::scoped_string & scopedstrFrameSchema) override;


   };



} // namespace experience




