#pragma once


namespace message
{


   class CLASS_DECL_APEX base :
      virtual public ::message::message
   {
   public:


      __pointer(::channel)       m_pchannel;
      ::user::primitive *        m_puserinteraction;
      bool                       m_bConditional;
      bool                       m_bReflect;
      bool                       m_bDestroyed;
      bool                       m_bDoSystemDefault;


      base();
      base(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam);

      base(const base & base);
      virtual ~base();


      virtual void set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam) override;

      inline void change(WPARAM wparam, ::lparam lparam) { set(m_puserinteraction, m_id.u32(), wparam, lparam); }

      //base & operator = (const base & base);

   };


} // namespace message


#define new ACME_NEW


