#pragma once


#include "base/user/experience/experience.h"


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

      void get_frame_list(string_array & stra) override;


      ::experience::frame * frame_experience(const ::string & strFrameSchema) override;


   };


} // namespace experience_tranquillum



