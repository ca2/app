#pragma once


namespace experience
{


   class CLASS_DECL_BASE department :
      virtual public ::acme::department
   {
   public:


      
      string_map < ::pointer<::experience::experience >>  m_mapExperience;


      department();
      ~department() override;


      virtual ::pointer<::experience::experience>create_experience(::particle * pparticle, const ::string & strExperience);
      virtual ::pointer<::experience::experience>experience(::particle * pparticle, const ::string & strExperience);
      virtual ::pointer<::experience::frame>frame_experience(::particle * pparticle, const ::string & strExperience, const ::string & strFrameSchema);


   };


} // namespace experience



