#pragma once


using lresult = iptr;



namespace message
{


   enum enum_flag
   {

      e_flag_none,
      flag_synthesized = 1 << 0,

   };


   class CLASS_DECL_APEX message :
      virtual public context_object
   {
   public:


      __pointer(route_array)        m_proutea;
      __pointer(channel)            m_pchannel;
      oswindow                      m_oswindow;
      wparam                        m_wparam;
      lparam                        m_lparam;
      lresult                       m_lresult;
      enumeration < enum_flag >     m_eflagMessage;
      index                         m_iRouteIndex;
      index                         m_iParam;
      bool                          m_bRet;
      unsigned int                  m_uiMessageFlags;
      ::e_status                    m_estatus;
      ::action_context              m_actioncontext;


      message(const ::id& id = ::id()) : id_matter(id) { common_construct(); }
      virtual ~message();


      inline void common_construct()
      {

         m_pchannel = nullptr;
         m_wparam = 0;
         m_iRouteIndex = -1;
         m_iParam = 0;
         m_bRet = false;
         m_uiMessageFlags = 0;
         m_estatus = ::success;
         m_lresult = 0;

      }

      inline bool is_message() const { return m_id.is_message(); }
      inline bool is_thread_message() const { return is_message() && m_oswindow == nullptr; }


      inline auto route_message() { m_proutea.m_p->m_pData[m_iRouteIndex].m_p->m_pmessageable.m_p->on_message(this); return m_bRet; }

      bool all_previous(); // returns bRet

      bool previous(); // returns bRet

      virtual void set_lresult(lresult lresult);
      virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam);


      ::u32 GetNotifyCode() const { return __hiword(m_wparam.m_number); }

      ::u32 GetId() const { return __loword(m_wparam.m_number); }

      oswindow get_oswindow() const { return m_oswindow; }


   };



} // namespace message
