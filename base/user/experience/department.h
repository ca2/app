#pragma once


#include "acme/platform/department.h"
#include "acme/prototype/collection/string_map.h"


namespace experience
{


   class CLASS_DECL_BASE department :
      virtual public ::acme::department
   {
   public:


      
      string_map < ::pointer<::experience::experience >>  m_mapExperience;


      department();
      ~department() override;


      virtual ::pointer<::experience::experience>create_experience(::particle * pparticle, const ::scoped_string & scopedstrExperience);
      virtual ::pointer<::experience::experience>experience(::particle * pparticle, const ::scoped_string & scopedstrExperience);
      virtual ::pointer<::experience::frame>frame_experience(::particle * pparticle, const ::scoped_string & scopedstrExperience, const ::scoped_string & scopedstrFrameSchema);


   };


} // namespace experience



