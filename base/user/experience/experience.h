#pragma once


namespace experience
{


   /// experience <3tbs
   /// 0123456789 10+10
   class CLASS_DECL_BASE experience :
      virtual public ::object
   {
   public:


      __pointer(::factory::factory)       m_pfactory;
      property_set                        m_set;
      string                              m_strExperience;


      experience();
      ~experience() override;


      inline ::base::application* get_app() const { return m_pcontext ? m_pcontext->m_pbaseapplication : nullptr; }
      inline ::base::session* get_session() const { return m_pcontext ? m_pcontext->m_pbasesession : nullptr; }
      inline ::base::system* get_system() const { return m_psystem ? m_psystem->m_pbasesystem : nullptr; }
      inline ::base::user* user() const { return get_session() ? get_session()->user() : nullptr; }


      virtual void update();

      virtual void get_frame_list(string_array & stra);

      virtual frame * frame_experience(const ::string & strFrameSchema);


   };


} // namespace experience





