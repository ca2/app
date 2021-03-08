#include "framework.h"


namespace interprocess_communication
{


   base::~base()
   {


   }


   tx::~tx()
   {


   }



   rx::~rx()
   {


   }


   void rx::receiver::on_interprocess_receive(rx * prx, const char * pszMessage)
   {

   }


   void rx::receiver::on_interprocess_receive(rx * prx, int message, void * pdata, memsize len)
   {

   }


   void rx::receiver::on_interprocess_post(rx * prx, ::i64 a, ::i64 b)
   {

   }


   bool interprocess_communication::close()
   {

      m_ptx->close();

      m_prx->destroy();

      return true;

   }


   void interprocess_communication::restart_apex_ipc()
   {
   }


   // calls restart if confirm_tx failed
   bool interprocess_communication::ensure_tx(const char * pszMessage, duration durationTimeout)
   {

      if(!m_ptx->send(pszMessage, durationTimeout))
      {

         restart_apex_ipc();

         return false;

      }

      return true;

   }


   bool interprocess_communication::ensure_tx(int message, void * pdata, int len, duration durationTimeout)
   {

      if(message == WM_APP + WM_USER)
      {

         if(!m_ptx->is_tx_ok())
         {

            restart_apex_ipc();

            return false;

         }

      }
      else if(!m_ptx->send(message, pdata, len, durationTimeout))
      {

         restart_apex_ipc();

         return false;

      }

      return true;

   }


   string app_install(string strPlatform)
   {

      return "::ca2::account::ca2_spaboot_install_" + strPlatform + "::7807e510-5579-11dd-ae16-0800200c7784";

   }




   // typedef int (WINAPI * LPFN_ChangeWindowMessageFilter)(const ::id & id, ::u32 dwFlag);


   //extern LPFN_ChangeWindowMessageFilter g_pfnChangeWindowMessageFilter;


   //namespace apex
   //{



      base::base()
      {

         //set_hwnd(nullptr);

      }


    


      tx::tx()
      {

      }



      bool tx::open(const char * pszKey, launcher * plauncher)
      {

         return true;

      }


      bool tx::close()
      {

         //if (get_hwnd() == nullptr)
         //{

         //   return true;

         //}

         //set_hwnd(nullptr);

         m_strBaseChannel = "";

         return true;

      }


      bool tx::send(const char * pszMessage, duration durationTimeout)
      {

         if (!is_tx_ok())
            return false;


         return true;

      }


      bool tx::send(int message, void * pdata, int len, duration durationTimeout)
      {

         if (message == 0x80000000)
            return false;

         if (!is_tx_ok())
            return false;


         return true;

      }



      bool tx::is_tx_ok()
      {

         //return ::IsWindow((HWND)m_oswindow) != false;
         return false;

      }




      rx::rx()
      {

         m_preceiver = nullptr;

      }



      bool rx::create(const char * pszKey)
      {


         /*    if(g_pfnChangeWindowMessageFilter != nullptr)
             {
                g_pfnChangeWindowMessageFilter(WM_COPYDATA,MSGFLT_ADD);
             }*/

             //HINSTANCE hinstance = ::GetModuleHandleA("apex.dll");

             //if(hinstance == nullptr)
             //{

             //   hinstance = ::GetModuleHandleA(nullptr);

             //}

             //auto pappcore = ::apex::get_system()->m_pappcore;

             //auto pmaindata = pappcore->m_pmaindata;

         //HINSTANCE hinstance = (HINSTANCE)::apex::get_system()->m_hinstance;

         //ATOM atom = rx_register_class(hinstance);

         //wstring wstrKey(pszKey);

         //m_oswindow = ::CreateWindowExW(0, L"small_ipc_rx_::color::e_channel_message_queue_class", wstrKey, 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr, hinstance, nullptr);

         //if (m_oswindow == nullptr)
         //{
         //   unsigned int dwLastError = ::GetLastError();
         //   return false;
         //}

         //if (!ChangeWindowMessageFilterEx((HWND)m_oswindow, WM_COPYDATA, MSGFLT_ADD, NULL))
         //{

         //   TRACE("Failed to change WM_COPYDATA message filter");

         //}

         //SetTimer((HWND)m_oswindow, 888888, 84, nullptr);

         //SetWindowLongPtr((HWND)m_oswindow, GWLP_USERDATA, (LONG_PTR)this);

         //m_strWindowProcModule = pszWindowProcModule;

         return true;

      }


      bool rx::destroy()
      {

         //if (m_oswindow != nullptr)
         //{
         //   ::DestroyWindow((HWND)m_oswindow);
         //   m_oswindow = nullptr;
         //}

         return true;

      }


      //void rx::receiver::on_interprocess_receive(rx * prx, const char * pszMessage)
      //{


      //}


      //void rx::receiver::on_interprocess_receive(rx * prx, int message, void * pdata, memsize len)
      //{


      //}


      //void rx::receiver::on_interprocess_post(rx * prx, i64 a, i64 b)
      //{



      //}


      void * rx::on_interprocess_receive(rx * prx, const char * pszMessage)
      {

         string strMessage(pszMessage);

         if (::str::begins_ci(strMessage, "synch_"))
         {

            if (m_preceiver != nullptr)
            {

               m_preceiver->on_interprocess_receive(prx, strMessage);

            }

         }
         else
         {

            get_context_application()->fork([this,prx,strMessage]()
               {

                  if (m_preceiver != nullptr)
                  {

                     m_preceiver->on_interprocess_receive(prx, strMessage);

                  }

               });

         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return nullptr;

      }


      void * rx::on_interprocess_receive(rx * prx, int message, void * pdata, memsize len)
      {

         if (m_preceiver != nullptr)
         {

            m_preceiver->on_interprocess_receive(prx, message, pdata, len);

         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return nullptr;

      }


      void * rx::on_interprocess_post(rx * prx, i64 a, i64 b)
      {

         if (m_preceiver != nullptr)
         {

            m_preceiver->on_interprocess_post(prx, a, b);

         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return nullptr;

      }


      //LRESULT CALLBACK s_rx_message_queue_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
      //{

      //   int iRet = 0;

      //   rx * pchannel = (rx *)GetWindowLongPtr((HWND)hwnd, GWLP_USERDATA);

      //   if (pchannel == nullptr)
      //   {

      //      return ::DefWindowProcW((HWND)hwnd, message, wparam, lparam);

      //   }
      //   else
      //   {

      //      return pchannel->message_queue_proc((enum_message)message, wparam, lparam);

      //   }

      //}


      //ATOM rx_register_class(HINSTANCE hInstance)
      //{
      //   WNDCLASSEXW wcex = {};

      //   wcex.cbSize = sizeof(WNDCLASSEX);

      //   wcex.style = 0;
      //   wcex.lpfnWndProc = &s_rx_message_queue_proc;

      //   wcex.cbClsExtra = 0;
      //   wcex.cbWndExtra = 0;
      //   wcex.hInstance = hInstance;
      //   wcex.hIcon = nullptr;
      //   //wcex.hCursor       = LoadCursor(nullptr, IDC_ARROW);
      //   wcex.hCursor = nullptr;
      //   wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
      //   wcex.lpszMenuName = nullptr;

      //   wcex.lpszClassName = L"small_ipc_rx_::color::e_channel_message_queue_class";

      //   wcex.hIconSm = nullptr;

      //   return RegisterClassExW(&wcex);
      //}


      //LRESULT rx::message_queue_proc(::u32 message, wparam wparam, lparam lparam)
      //{

      //   if (message == WM_USER + 100)
      //   {

      //      on_interprocess_post(this, wparam, lparam);

      //   }
      //   else if (message == WM_COPYDATA)
      //   {

      //      COPYDATASTRUCT * pcds = (COPYDATASTRUCT *)lparam;


      //      if (pcds == nullptr)
      //      {

      //         return 0;

      //      }
      //      else if (pcds->dwData == 0x80000000)
      //      {

      //         string strMessage((const char *)pcds->lpData, pcds->cbData);

      //         on_interprocess_receive(this, strMessage.c_str());

      //      }
      //      else
      //      {

      //         on_interprocess_receive(this, (int)pcds->dwData, pcds->lpData, pcds->cbData);

      //      }

      //   }
      //   else if (message >= WM_APP)
      //   {

      //      on_interprocess_receive(this, message, (void *)wparam, lparam);

      //   }
      //   else
      //   {

      //      return ::DefWindowProcW(m_oswindow, message, wparam, lparam);

      //   }

      //   return 0;

      //}



      bool rx::on_idle()
      {

         return false;

      }


      bool rx::is_rx_ok()
      {

         //return ::IsWindow(m_oswindow) != false;
         return false;

      }


      interprocess_communication::interprocess_communication()
      {

         m_millisTimeout = (5000) * 11;

      }


      interprocess_communication::~interprocess_communication()
      {


      }

#ifdef WINDOWS

      bool interprocess_communication::open_ab(const char * pszKey, const char * pszModule, launcher * plauncher)
      {

         m_strChannel = pszKey;

         m_prx->m_preceiver = this;

         string strChannelRx = m_strChannel + "-a";
         string strChannelTx = m_strChannel + "-b";

         //if (!::IsWindow(m_rx.m_oswindow))
         //{

            if (!m_prx->create(strChannelRx.c_str()))
            {

               return false;

            }

         //}

         if (!m_ptx->open(strChannelTx.c_str(), plauncher))
         {

            return false;

         }

         return true;

      }


      bool interprocess_communication::open_ba(const char * pszKey, const char * pszModule, launcher * plauncher)
      {

         m_strChannel = pszKey;

         m_prx->m_preceiver = this;

         string strChannelRx = m_strChannel + "-b";
         string strChannelTx = m_strChannel + "-a";


         //if (!::IsWindow(m_rx.m_oswindow))
         //{

            if (!m_prx->create(strChannelRx.c_str()))
            {

               return false;

            }

         //}

         if (!m_ptx->open(strChannelTx.c_str(), plauncher))
         {
            
            return false;

         }

         return true;

      }

#else


      bool interprocess_communication::open_ab(const char * pszKey, launcher * plauncher)
      {

         m_strChannel = pszKey;

         m_prx->m_preceiver = this;

         string strChannelRx = m_strChannel + "-a";
         string strChannelTx = m_strChannel + "-b";

         //if (!::IsWindow(m_rx.m_oswindow))
         //{

            if (!m_prx->create(strChannelRx.c_str()))
            {

               return false;

            }

         //}

         if (!m_ptx->open(strChannelTx.c_str(), plauncher))
         {

            return false;

         }

         return true;

      }


      bool interprocess_communication::open_ba(const char * pszKey, launcher * plauncher)
      {

         m_strChannel = pszKey;

         m_prx->m_preceiver = this;

         string strChannelRx = m_strChannel + "-b";
         string strChannelTx = m_strChannel + "-a";


         //if (!::IsWindow(m_rx.m_oswindow))
         //{

            if (!m_prx->create(strChannelRx.c_str()))
            {

               return false;

            }

         //}

         if (!m_ptx->open(strChannelTx.c_str(), plauncher))
         {

            return false;

         }

         return true;

      }


#endif


      bool interprocess_communication::is_rx_tx_ok()
      {

         return m_prx->is_rx_ok() && m_ptx->is_tx_ok();
         //return false;

      }


   //} // namespace interprocess_communication


} // namespace windows



