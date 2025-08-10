#pragma once


#include "berg/user/experience/experience.h"


namespace experience_tranquillum
{


   class CLASS_DECL_APP_EXPERIENCE_TRANQUILLUM experience:
      public ::experience::experience
   {
   public:


      experience();
      ~experience() override;


      void update() override;


      void initialize(::particle * pparticle) override;

      void get_frame_list(string_array_base & stra) override;


      ::pointer < ::experience::frame > frame_experience(const ::scoped_string & scopedstrFrameSchema) override;


   };


} // namespace experience_tranquillum



