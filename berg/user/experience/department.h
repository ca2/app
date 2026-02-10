#pragma once


#include "acme/platform/department.h"
#include "acme/prototype/collection/string_map.h"


namespace experience
{


   class CLASS_DECL_BERG department :
      virtual public ::platform::department
   {
   public:


      
      string_map_base < ::pointer<::experience::experience >>  m_mapExperience;


      department();
      ~department() override;


      virtual ::pointer<::experience::experience>create_experience(::particle * pparticle, const ::scoped_string & scopedstrExperience);
      virtual ::pointer<::experience::experience>experience(::particle * pparticle, const ::scoped_string & scopedstrExperience);
      virtual ::pointer<::experience::frame>frame_experience(::particle * pparticle, const ::scoped_string & scopedstrExperience, const ::scoped_string & scopedstrFrameSchema);


   };


} // namespace experience



