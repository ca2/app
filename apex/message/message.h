#pragma once


#include "acme/primitive/geometry2d/_geometry2d.h"
#include "dispatcher.h"
#include "acme/platform/message.h"
#include "acme/primitive/primitive/action_context.h"


namespace message
{


   enum enum_flag
   {

      e_flag_none,
      e_flag_synthesized = 1 << 0,

   };


   class key;
   class mouse;
   class particle;
   class context_menu;


   union message_union
   {
     
      void *                        m_p;
      ::message::particle *         m_pparticle;
      ::message::key *              m_pkey;
      ::message::mouse *            m_pmouse;
      ::message::context_menu *     m_pcontextmenu;
      
   };


   class CLASS_DECL_APEX message :
      virtual public ::acme::message
   {
   public:


      //::message::key *              m_pkey;
      //::message::mouse *            m_pmouse;

      message_union                 m_union;

      dispatcher_array *            m_pdispatchera;
      channel *                     m_pchannel;
      oswindow                      m_oswindow;
      enumeration < enum_flag >     m_eflagMessage;
      index                         m_iRouteIndex;
      index                         m_iParam;
      bool                          m_bRet;
      unsigned int                  m_uiMessageFlags;
      ::e_status                     m_estatus;
      ::action_context              m_actioncontext;
      ::point_i32                   m_pointMessage;


      message(const ::atom & atom = ::atom()) { m_atom = atom; common_construct(); }
      virtual ~message();


      inline void common_construct()
      {

         m_union.m_p = nullptr;
         m_pdispatchera = nullptr;
         m_pchannel = nullptr;
         m_wparam = {};
         m_iRouteIndex = -1;
         m_iParam = 0;
         m_bRet = false;
         m_uiMessageFlags = 0;
         m_estatus = ::success;
         m_lresult = 0;

      }


      inline bool is_message() const { return m_atom.is_message(); }
      inline bool is_thread_message() const { return is_message() && m_oswindow == nullptr; }


      virtual bool route_message();


      bool all_previous(); // returns bRet

      bool previous(); // returns bRet

      virtual void set_lresult(lresult lresult);
      //virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam, const ::point_i32 & point);
      virtual void set(oswindow oswindow, ::windowing::window* pwindow, const ::atom& atom, wparam wparam, ::lparam lparam);


      ::u32 GetNotifyCode() const { return __hiword(m_wparam.m_number); }

      ::u32 GetId() const { return __loword(m_wparam.m_number); }

      oswindow get_oswindow() const { return m_oswindow; }


   };



} // namespace message
