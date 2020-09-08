#pragma once


#ifdef WINDOWS_DESKTOP

#include <msctf.h>
#include "aura/os/windows_common/comptr.h"
#include "windows_tsf/edit_window.h"

#endif


namespace user
{


   // the thread
   // must be child of an application thread.
   // The window must not be parent of the window thread.
   // The window thread isn't a child worker thread of the window.
   // The window thread is some sort of parent of the window it works upon.
   class CLASS_DECL_AURA thread :
      virtual public ::thread
   {

   public:

#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK

#ifdef WINDOWS

      comptr < ITfThreadMgr >                      m_pthreadmgr;
      comptr < ITfThreadMgrEx >                    m_pthreadmgrex;
      TfClientId                                   m_tfClientID;
      comptr < ITfKeystrokeMgr >                   m_pkeystrokemgr;
      comptr < ITfMessagePump >                    m_pmessagepump;
      array < comptr < tsf::edit_window > >        m_editwindowa;

#endif

#endif

      __pointer(interaction_impl)            m_pimpl;
      ::user::create_struct *                m_pcreatestruct;
      prodevian *                            m_pprodevian;
      oswindow                               m_oswindow;

      manual_reset_event                     m_evApplyVisual;
      __pointer_array(::message::base)       m_messagebasea;

      thread();
      virtual ~thread();

      virtual ::estatus     initialize_user_thread(interaction_impl * pimpl, ::user::create_struct & cs);


#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK

#ifdef WINDOWS

      virtual HRESULT initialize_tsf_thread();

#endif
#endif
      virtual ::estatus init_thread() override;
      virtual void term_thread() override;

#ifdef WINDOWS_DESKTOP
      virtual int _GetMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax) override;
#endif

      virtual bool pump_message() override;

      virtual bool pump_runnable() override;

      virtual bool process_message() override;

      virtual ::estatus     run() override;

      virtual void finalize() override;

      virtual bool thread_get_run() const override;

      void start_window_visual();


   };


} // namespace user



