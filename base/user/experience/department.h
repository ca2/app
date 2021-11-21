#pragma once


namespace experience
{


   class CLASS_DECL_BASE department :
      virtual public ::acme::department
   {
   public:


      
      string_map < __composite(::experience::experience) >   m_mapExperience;


      department();
      ~department() override;


      virtual __pointer(::experience::experience) create_experience(::object * pobject, const ::string & strExperience);
      virtual __pointer(::experience::experience) experience(::object * pobject, const ::string & strExperience);
      virtual __pointer(::experience::frame) frame_experience(::object * pobject, const ::string & strExperience, const ::string & strFrameSchema);


   };


} // namespace experience



