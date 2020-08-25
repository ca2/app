#pragma once


namespace experience
{


   /// experience <3tbs
   /// 0123456789 10+10
   class CLASS_DECL_BASE experience :
      virtual public ::object
   {
   public:


      __pointer(::aura::library)           m_plibrary;
      property_set                  m_set;


      experience();
      virtual ~experience();

      virtual void update();

      virtual void get_frame_list(string_array & stra);

      virtual frame * experience_get_frame(const char * pszSchema);


   };


} // namespace experience





