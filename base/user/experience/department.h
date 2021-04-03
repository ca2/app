#pragma once


namespace experience
{


   class CLASS_DECL_BASE department :
      virtual public ::apex::department
   {
   public:


      
      string_map < __composite(::experience::experience) >   m_mapExperience;


      department();
      virtual ~department();


      virtual __pointer(::experience::experience) create_experience2(::object * pobject, const char * pszExperienceLibrary);
      virtual __pointer(::experience::experience) get_experience2(::object * pobject, const char * pszExperienceLibrary);
      virtual __pointer(::experience::frame) experience_get_frame2(::object * pobject, const char * pszExperienceLibrary, const char * pszFrame);


   };


} // namespace experience



