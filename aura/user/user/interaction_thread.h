#pragma once


#include "apex/parallelization/thread.h"
#include "acme/parallelization/manual_reset_happening.h"


#ifdef WINDOWS_DESKTOP

#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK
#include <msctf.h>
#include "aura/os/windows_common/comptr.h"
#include "windows_tsf/edit_window.h"
#endif
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

      ::pointer < ::windowing::window >            m_pwindow;
      //::pointer<prodevian>                       m_pgraphicsthread;
      //oswindow                                     m_oswindow;

      //manual_reset_happening                           m_happeningApplyVisual;
      //::pointer<::windowing::windowing>            m_pwindowing;


      thread();
      ~thread() override;


#ifdef _DEBUG


      huge_integer increment_reference_count() override;
      huge_integer decrement_reference_count() override;
      huge_integer release() override;


#endif


      virtual void initialize_user_thread(::windowing::window * pwindow);


#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK

#ifdef WINDOWS

      virtual HRESULT initialize_tsf_thread();

#endif

#endif


      void on_before_branch() override;

      virtual void init_task() override;
      virtual void term_task() override;


//#ifdef WINDOWS_DESKTOP
//      virtual int _GetMessage(LPMSG lpMsg, HWND hWnd, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax) override;
//#endif

      //bool task_get_run() const override;

      //bool thread_iteraction() override;

      //virtual bool pump_runnable() override;

      virtual bool process_message() override;

      virtual bool process_message(::message::message * pmessage) override;

      virtual bool process_user_message(::message::message * pmessage);

      void run() override;

      void destroy() override;

      void set_finish() override;

      //void destroy() override;

      bool task_get_run() const override;

      virtual void enumerate_composite(matter_array& a);

      //virtual void set_finish_composites(::property_object * pcontextobjectFinish) override;
      void on_destroy() override;


      void on_task_quit() override;

      // deprecated schedule window visual
      //void start_window_visual();

      virtual void task_caller_on_init() override;


   };


} // namespace user



