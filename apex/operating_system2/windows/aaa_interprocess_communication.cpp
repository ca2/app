#include "framework.h"
#include "apex/operating_system.h"
#include "apex/platform/app_core.h"


// typedef int (WINAPI * LPFN_ChangeWindowMessageFilter)(const ::atom & atom, unsigned int dwFlag);


//extern LPFN_ChangeWindowMessageFilter g_pfnChangeWindowMessageFilter;


//namespace apex
//{


   namespace inteprocess_channel
   {


      ATOM rx_register_class(HINSTANCE hInstance);
      LRESULT CALLBACK s_rx_message_queue_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);



      base::base()
      {

         m_oswindow = nullptr;

      }


      base::~base()
      {

         if(m_oswindow != nullptr)
         {

            ::DestroyWindow((HWND) m_oswindow);

            m_oswindow = nullptr;

         }

      }


      tx::tx()
      {

      }


      tx::~tx()
      {

      }


      bool tx::open(const ::scoped_string & scopedstrKey,launcher * plauncher)
      {

         if(m_oswindow != nullptr)
            close();


         int jCount = 23;
         int iCount;

         if(plauncher != nullptr)
            iCount = plauncher->m_iStart + 1;
         else
            iCount = 2;

         m_oswindow = nullptr;

         for(int i = 0; i < iCount; i++)
         {
            for(int j = 0; j < jCount; j++)
            {
               m_oswindow = ::FindWindowW(nullptr,wstring(scopedstrKey));
               if(m_oswindow != nullptr)
                  break;
               //         m_oswindow = FindDesktopWindow(scopedstrKey);
               //       if(m_oswindow != nullptr)
               //        break;
               if(i <= 0)
               {
                  break;
               }
               int k = 40;
               while (k > 0)
               {
                  if (!task_get_run())
                  {
                     return false;
                  }
                  sleep(25_ms);
                  k--;
               }
            }
            if(m_oswindow != nullptr)
               break;
            if(plauncher != nullptr)
            {
               if(plauncher->m_iStart <= 0)
                  return false;
               plauncher->start();
               plauncher->m_iStart--;
            }
         }
         m_strBaseChannel = pszKey;
         return true;

      }

      bool tx::close()
      {

         if(m_oswindow == nullptr)
            return true;

         m_oswindow = nullptr;

         m_strBaseChannel = "";

         return true;

      }


      bool tx::send(const ::scoped_string & scopedstrMessage, duration durationTimeout)
      {

         if(!is_tx_ok())
            return false;

         COPYDATASTRUCT cds;

         cds.dwData = I32_MINIMUM;
         cds.cbData = (unsigned int)strlen(scopedstrMessage);
         cds.lpData = (void *)pszMessage;


         if(durationTimeout.is_pos_infinity())
         {

            SendMessage((HWND) m_oswindow,WM_COPYDATA,(WPARAM)0,(LPARAM)&cds);

         }
         else
         {

            DWORD_PTR dwptr;

            if (!::SendMessageTimeout((HWND)m_oswindow, WM_COPYDATA, (WPARAM)0, (LPARAM)&cds, SMTO_ABORTIFHUNG, (unsigned int)(durationTimeout.u32_millis()), &dwptr))
            {

               return false;

            }

            unsigned int dwError = ::GetLastError();

            if(dwError == ERROR_TIMEOUT)
               return false;

         }

         return true;
      }

      bool tx::send(int message, void * pdata, int len, duration durationTimeout)
      {

         if(message == I32_MINIMUM)
            return false;

         if(!is_tx_ok())
            return false;

         COPYDATASTRUCT cds;

         cds.dwData = (unsigned int)message;
         cds.cbData = (unsigned int)maximum(0,len);
         cds.lpData = (void *)pdata;


         if(durationTimeout.is_pos_infinity())
         {

            if(message >= WM_APP)
            {

               SendMessage((HWND) m_oswindow,message,0,0);

            }
            else
            {

               SendMessage((HWND) m_oswindow,WM_COPYDATA,(WPARAM)0,(LPARAM)&cds);

            }

         }
         else
         {

            DWORD_PTR dwptr;

            if (!::SendMessageTimeout((HWND)m_oswindow, WM_COPYDATA, (WPARAM)0, (LPARAM)&cds, SMTO_BLOCK, (unsigned int)(durationTimeout.u32_millis()), &dwptr))
            {

               return false;

            }

            unsigned int dwError = ::GetLastError();

            if(dwError == ERROR_TIMEOUT)
               return false;

         }

         return true;

      }



      bool tx::is_tx_ok()
      {

         return ::IsWindow((HWND) m_oswindow) != false;

      }




      rx::rx()
      {

         m_preceiver    = nullptr;

      }


      rx::~rx()
      {

      }


      bool rx::create(const ::scoped_string & scopedstrKey)
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

         //auto pappcore = ::apexacmesystem()->m_pappcore;

         //auto pmaindata = pappcore->m_pmaindata;

         HINSTANCE hinstance = (HINSTANCE) ::apexacmesystem()->m_hinstance;

         ATOM atom = rx_register_class(hinstance);

         wstring wstrKey(scopedstrKey);

         m_oswindow = ::CreateWindowExW(0,L"small_ipc_rx_::color::e_channel_message_queue_class", wstrKey,0,0,0,0,0,HWND_MESSAGE,nullptr,hinstance,nullptr);

         if(m_oswindow == nullptr)
         {
            unsigned int dwLastError = ::GetLastError();
            return false;
         }

         if (!ChangeWindowMessageFilterEx((HWND) m_oswindow, WM_COPYDATA, MSGFLT_ADD, NULL))
         {

            informationf("Failed to change WM_COPYDATA message filter");

         }

         set_timer((HWND) m_oswindow,888888,84,nullptr);

         SetWindowLongPtr((HWND) m_oswindow,GWLP_USERDATA,(LONG_PTR) this);

         //m_strWindowProcModule = pszWindowProcModule;

         return true;

      }


      bool rx::destroy()
      {

         if(m_oswindow != nullptr)
         {
            ::DestroyWindow((HWND) m_oswindow);
            m_oswindow = nullptr;
         }

         return true;

      }



      void * rx::on_interprocess_receive(rx * prx,const ::scoped_string & scopedstrMessage)
      {

         string strMessage(scopedstrMessage);

         if (case_insensitive_string_begins(strMessage, "synch_"))
         {

            if (m_preceiver != nullptr)
            {

               m_preceiver->on_interprocess_receive(prx, strMessage);

            }

         }
         else
         {

            get_app()->fork([=]()
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


      void * rx::on_interprocess_receive(rx * prx,int message,void * pdata,memsize len)
      {

         if(m_preceiver != nullptr)
         {

            m_preceiver->on_interprocess_receive(prx,message,pdata,len);

         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return nullptr;

      }


      void * rx::on_interprocess_post(rx * prx,long long int a,long long int b)
      {

         if(m_preceiver != nullptr)
         {
            
            m_preceiver->on_interprocess_post(prx,a,b);

         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return nullptr;

      }


      LRESULT CALLBACK s_rx_message_queue_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
      {

         int iRet = 0;

         rx * pchannel = (rx *) GetWindowLongPtr((HWND) hwnd, GWLP_USERDATA);

         if(pchannel == nullptr)
         {

            return ::DefWindowProcW((HWND) hwnd, message, wparam, lparam);

         }
         else
         {

            return pchannel->message_queue_proc((enum_message) message, wparam, lparam);

         }

      }


      ATOM rx_register_class(HINSTANCE hInstance)
      {
         WNDCLASSEXW wcex = {};

         wcex.cbSize = sizeof(WNDCLASSEX);

         wcex.style           = 0;
         wcex.lpfnWndProc     = &s_rx_message_queue_proc;

         wcex.cbClsExtra      = 0;
         wcex.cbWndExtra      = 0;
         wcex.hInstance       = hInstance;
         wcex.hIcon           = nullptr;
         //wcex.hCursor       = LoadCursor(nullptr, IDC_ARROW);
         wcex.hCursor         = nullptr;
         wcex.hbrBackground   = (HBRUSH)(COLOR_WINDOW + 1);
         wcex.lpszMenuName    = nullptr;

         wcex.lpszClassName   = L"small_ipc_rx_::color::e_channel_message_queue_class";

         wcex.hIconSm         = nullptr;

         return RegisterClassExW(&wcex);
      }


      LRESULT rx::message_queue_proc(unsigned int message,wparam wparam,lparam lparam)
      {

         if(message == WM_USER + 100)
         {

            on_interprocess_post(this,wparam,lparam);

         }
         else if(message == WM_COPYDATA)
         {

            COPYDATASTRUCT * pcds = (COPYDATASTRUCT *)lparam;


            if(pcds == nullptr)
            {

               return 0;

            }
            else if(pcds->dwData == I32_MINIMUM)
            {

               string strMessage((const char *)pcds->lpData,pcds->cbData);

               on_interprocess_receive(this,strMessage.c_str());

            }
            else
            {

               on_interprocess_receive(this,(int)pcds->dwData,pcds->lpData,pcds->cbData);

            }

         }
         else if(message >= WM_APP)
         {

            on_interprocess_receive(this,message,(void *)wparam,lparam);

         }
         else
         {

            return ::DefWindowProcW(m_oswindow,message,wparam,lparam);

         }

         return 0;

      }



      bool rx::on_idle()
      {

         return false;

      }

      bool rx::is_rx_ok()
      {

         return ::IsWindow(m_oswindow) != false;

      }


      inteprocess_channel::inteprocess_channel()
      {

         m_durationTimeout = (5000) * 11;

      }


      inteprocess_channel::~inteprocess_channel()
      {


      }


      bool inteprocess_channel::open_ab(const ::scoped_string & scopedstrKey,const ::scoped_string & scopedstrModule,launcher * plauncher)
      {

         m_strChannel = pszKey;

         m_rx.m_preceiver = this;

         string strChannelRx = m_strChannel + "-a";
         string strChannelTx = m_strChannel + "-b";

         if(!::IsWindow(m_rx.m_oswindow))
         {

            if(!m_rx.create(strChannelRx.c_str()))
            {

               return false;

            }

         }

         if(!tx::open(strChannelTx.c_str(),plauncher))
         {

            return false;

         }

         return true;

      }

      bool inteprocess_channel::open_ba(const ::scoped_string & scopedstrKey,const ::scoped_string & scopedstrModule,launcher * plauncher)
      {

         m_strChannel = pszKey;

         m_rx.m_preceiver = this;

         string strChannelRx = m_strChannel + "-b";
         string strChannelTx = m_strChannel + "-a";


         if(!::IsWindow(m_rx.m_oswindow))
         {

            if(!m_rx.create(strChannelRx.c_str()))
            {

               return false;

            }

         }

         if(!tx::open(strChannelTx.c_str(),plauncher))
         {
            return false;
         }

         return true;

      }


      bool inteprocess_channel::is_rx_tx_ok()
      {

         return m_rx.is_rx_ok() && is_tx_ok();

      }


   } // namespace inteprocess_channel


//} // namespace apex






