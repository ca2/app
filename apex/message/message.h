#pragma once


//#include "acme/primitive/geometry2d/_geometry2d.h"
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



   class CLASS_DECL_APEX message :
      virtual public ::acme::message
   {
   public:


      //::message::key *              m_pkey;
      //::message::mouse *            m_pmouse;

      dispatcher_array *            m_pdispatchera;
      channel *                     m_pchannel;
      oswindow                      m_oswindow;
      enumeration < enum_flag >     m_eflagMessage;
      ::raw::index                         m_iRouteIndex;
      ::raw::index                         m_iParam;
      bool                          m_bRet;
      unsigned int                  m_uiMessageFlags;
      ::e_status                     m_estatus;
      ::action_context              m_actioncontext;
      ::point_i32                   m_pointMessage;
      bool m_bProbing = false;
      bool m_bCommand = false;



      message(const ::atom & atom = ::atom());
      ~message() override;


      //void common_construct();


      inline bool is_message() const { return m_atom.is_message(); }
      inline bool is_thread_message() const { return is_message() && m_oswindow == nullptr; }


      virtual bool route_message();


      bool all_previous(); // returns bRet

      bool previous(); // returns bRet

      virtual void set_lresult(lresult lresult);
      //virtual void set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam, const ::point_i32 & point);
      //virtual void set(oswindow oswindow, ::windowing::window* pwindow, const ::atom& atom, wparam wparam, ::lparam lparam);


      ::u32 GetNotifyCode() const { return __hiword(m_wparam.m_number); }

      ::u32 GetId() const { return __loword(m_wparam.m_number); }

      oswindow get_oswindow() const { return m_oswindow; }


      message & operator = (const message & message);


   };



} // namespace message
