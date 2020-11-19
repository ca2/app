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


      __pointer(route_array)     m_proutea;
      __pointer(channel)         m_pchannel;
      oswindow                   m_oswindow;
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


      message(const ::id& id = ::id()) : context_object(id) { common_construct(); }
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



      //void common_construct(enum_message emessage = ::e_message_null);


      inline bool is_message() const { return m_id.is_message(); }


      inline auto route_message() { m_proutea.m_p->m_pData[m_iRouteIndex].m_p->m_pmessageable.m_p->on_message(this); return m_bRet; }

      bool all_previous(); // returns bRet

      bool previous(); // returns bRet

      virtual void set_lresult(LRESULT lresult);
      virtual void set(oswindow oswindow, ::layered * playeredUserPrimitive, const ::id & id, WPARAM wparam, ::lparam lparam);


   };



} // namespace message
