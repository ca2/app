#pragma once


namespace message
{


   class CLASS_DECL_APEX base :
      virtual public ::message::message
   {
   public:


      __pointer(::channel)       m_pchannel;
      __pointer(::layered)       m_playeredUserPrimitive;
      bool                       m_bConditional;
      bool                       m_bReflect;
      bool                       m_bDestroyed;
      bool                       m_bDoSystemDefault;


      base();
      base(oswindow oswindow, ::layered * playeredUserPrimitive, const ::id & id, wparam wparam, ::lparam lparam);

      base(const base & base);
      virtual ~base();

      inline ::user::primitive * userprimitive()
      {
         
         return __user_primitive(m_playeredUserPrimitive);
         
      }

      inline ::user::interaction * userinteraction()
      {
         
         return __user_interaction(m_playeredUserPrimitive);
         
      }

      virtual void set(oswindow oswindow, ::layered * playeredUserPrimitive, const ::id & id, wparam wparam, ::lparam lparam) override;

      inline void change(wparam wparam, ::lparam lparam) { set(m_oswindow,m_playeredUserPrimitive, m_id, wparam, lparam); }

      //base & operator = (const base & base);

   };


} // namespace message


#define new ACME_NEW


