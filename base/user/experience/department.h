#pragma once


namespace experience
{


   class CLASS_DECL_BASE department :
      virtual public ::acme::department
   {
   public:


      
      string_map < __composite(::experience::experience) >   m_mapExperience;


      department();
      virtual ~department();


      virtual __pointer(::experience::experience) create_experience2(::object * pobject, const ::string & pszExperienceLibrary);
      virtual __pointer(::experience::experience) get_experience2(::object * pobject, const ::string & pszExperienceLibrary);
      virtual __pointer(::experience::frame) experience_get_frame2(::object * pobject, const ::string & pszExperienceLibrary, const ::string & pszFrame);


   };


} // namespace experience



