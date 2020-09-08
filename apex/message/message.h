#pragma once


namespace message
{


   enum e_flag
   {

      flag_none,
      flag_synthesized = 1 << 0,

   };


   class CLASS_DECL_APEX message :
      virtual public context_object
   {
   public:


      id                         m_id;
      __pointer(route_array)     m_proutea;
      __pointer(channel)         m_pchannel;
      wparam                     m_wparam;
      lparam                     m_lparam;
      LRESULT                    m_lresult;
      cflag < e_flag >           m_eflagMessage;

      index                      m_iRouteIndex;
      index                      m_iParam;
      bool                       m_bRet;
      unsigned int               m_uiMessageFlags;
      ::estatus                  m_estatus;
      ::action_context           m_actioncontext;


      message();
      message(::message::e_type etype);
      virtual ~message();


      void common_construct(::message::e_type etype = ::message::type_null);


      inline bool is_message() { return m_id.m_emessagetype == ::message::type_message; }


      inline auto route_message() { m_proutea.m_p->m_pData[m_iRouteIndex].m_p->m_pmessageable.m_p->on_message(this); return m_bRet; }

      bool all_previous(); // returns bRet

      bool previous(); // returns bRet

      virtual void set_lresult(LRESULT lresult);
      virtual void set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam);


   };



} // namespace message
