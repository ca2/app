#pragma once


namespace experience
{


   class CLASS_DECL_BASE department :
      virtual public ::aura::department
   {
   public:


      string_map < __composite(::experience::experience) >   m_mapExperience;

      department();
      virtual ~department();


      virtual ::experience::experience * get_new_experience2(::object* pobjectContext, const char * pszExperienceLibrary);
      virtual ::experience::experience * get_experience2(::object* pobjectContext, const char * pszExperienceLibrary);
      virtual ::experience::frame * experience_get_frame2(::object * pobjectContext, const char * pszExperienceLibrary, const char * pszFrame, const char * pszStyle = nullptr);

   };


} // namespace experience

