#include "framework.h"


//
//
///*
//extern LPFN_ChangeWindowMessageFilter g_pfnChangeWindowMessageFilter;
//
//
//namespace aura
//{
//
//
//   namespace ipc
//   {
//
//
//      base::base(::object * pobject) :
//         object(pobject)
//      {
//
//         m_iSerial = 1;
//
//      }
//
//
//      base::~base()
//      {
//
//         //if(m_oswindow != nullptr)
//         //{
//
//         //   ::DestroyWindow(m_oswindow);
//
//         //   m_oswindow = nullptr;
//
//         //}
//
//      }
//
//
//      tx::tx(::object * pobject):
//         object(pobject),
//         base(pobject)
//      {
//
//
//      }
//
//
//      tx::~tx()
//      {
//
//
//      }
//
//
//      bool tx::open(const ::string & pszKey,launcher * plauncher)
//      {
//
//         m_strBaseChannel = "aura\\appdata\\interprocess_communication\\" + string(pszKey);
//
//         if(m_strBaseChannel.is_empty())
//         {
//
//            return false;
//
//         }
//
//         return true;
//
//      }
//
//
//      bool tx::close()
//      {
//
//         //if(m_oswindow == nullptr)
//         //   return true;
//
//         //m_oswindow = nullptr;
//
//         //m_strBaseChannel = "";
//
//         return true;
//
//      }
//
//
//      bool tx::send(const ::string & pszMessage,unsigned int tickTimeout)
//      {
//
//         ::winrt::Windows::Storage::StorageFolder ^ folder = ::winrt::Windows::Storage::KnownFolders::DocumentsLibrary;
//
//         ::winrt::Windows::Storage::StorageFolder ^ folderTopic = ::wait(folder->CreateFolderAsync(wstring(m_strBaseChannel),::winrt::Windows::Storage::CreationCollisionOption::OpenIfExists));
//
//         ::winrt::Windows::Storage::StorageFile ^ file = ::wait(folderTopic->CreateFileAsync(wstring("aura.topic"),::winrt::Windows::Storage::CreationCollisionOption::OpenIfExists));
//
//         string strMessage;
//
//         strMessage = pszMessage;
//
//         strMessage += "\n";
//
//         ::wait(::winrt::Windows::Storage::FileIO::AppendTextAsync(file,wstring(strMessage)));
//
//         return true;
//
//      }
//
//
//      bool tx::send(int message,void * pdata,int len,unsigned int tickTimeout)
//      {
//
//
//         return true;
//
//      }
//
//
//
//      bool tx::is_tx_ok()
//      {
//
////         return ::IsWindow(m_oswindow) != false;
//         return m_strBaseChannel.has_char();
//
//      }
//
//
//      class rx_private
//      {
//      public:
//
//
//         ::winrt::Windows::Storage::StorageFolder ^                      folder;
//         ::winrt::Windows::Storage::StorageFolder ^                      folderTopic;
//         ::winrt::Windows::Storage::Search::StorageFileQueryResult ^     result;
//
//
//      };
//
//
//
//
//
//
//      rx::rx(::object * pobject) :
//         object(pobject),
//         base(pobject)
//      {
//
//         m_preceiver    = nullptr;
//
//
//      }
//
//
//      rx::~rx()
//      {
//
//      }
//
//
//      bool rx::create(const ::string & pszKey)
//      {
//
//
//         if(g_pfnChangeWindowMessageFilter != nullptr)
//         {
//            g_pfnChangeWindowMessageFilter(WM_COPYDATA,MSGFLT_ADD);
//         }
//
//         m_strBaseChannel = "aura\\appdata\\interprocess_communication\\" + string(pszKey);
//
//         if(m_strBaseChannel.is_empty())
//         {
//
//            return false;
//
//         }
//
//         m_pp = new rx_private;
//
//         try
//         {
//
//            m_pp->folder = ::winrt::Windows::Storage::KnownFolders::DocumentsLibrary;
//
//         }
//         catch (...)
//         {
//
//            return false;
//
//         }
//
//         m_pp->folderTopic = ::wait(m_pp->folder->CreateFolderAsync(wstring(m_strBaseChannel),::winrt::Windows::Storage::CreationCollisionOption::OpenIfExists));
//
//         ::winrt::Windows::Storage::StorageFile ^ f = ::wait(m_pp->folderTopic->GetFileAsync(wstring("aura.topic")));
//
//         if(f != nullptr)
//         {
//
//            ::wait(f->DeleteAsync());
//
//         }
//
//
//         //::winrt::Windows::Storage::Search::QueryOptions ^ options = ref new ::winrt::Windows::Storage::Search::QueryOptions();
//
//         //options->FileTypeFilter->Append(wstring(".topic"));
//
//         //::winrt::Windows::Storage::Search::StorageFileQueryResult  ^ result = m_pp->folderTopic->CreateFileQueryWithOptions(options);
//
//         m_pp->result = m_pp->folderTopic->CreateFileQuery();
//
//         m_pp->result->ContentsChanged += ref new TypedEventHandler < ::winrt::Windows::Storage::Search::IStorageQueryResultBase ^,Object ^ >([this](::winrt::Windows::Storage::Search::IStorageQueryResultBase ^ result,Object ^ o)
//         {
//
//            ::winrt::Windows::Storage::StorageFile ^ f = ::wait(result->Folder->GetFileAsync(wstring("aura.topic")));
//
//            if(f != nullptr)
//            {
//
//               string str(::wait(::winrt::Windows::Storage::FileIO::ReadTextAsync(f)));
//
//               ::wait(f->DeleteAsync());
//
//               string_array stra;
//
//               stra.add_lines(str);
//
//               for(auto & strLine : stra)
//               {
//
//                  ::fork(get_application(),[=]()
//                  {
//
//                     on_receive(this,strLine);
//
//                  });
//
//               }
//
//            }
//
//         });
//
//         ::wait(m_pp->result->GetFilesAsync());
//
//         //HINSTANCE hinstance = ::GetModuleHandleA(pszWindowProcModule);
//
//         //ATOM atom = register_class(hinstance);
//
//         //m_oswindow = ::CreateWindowExA(0,"small_ipc_rx_::color::e_channel_message_queue_class",pszKey,0,0,0,0,0,HWND_MESSAGE,nullptr,hinstance,nullptr);
//
//         //if(m_oswindow == nullptr)
//         //{
//         //   unsigned int dwLastError = ::get_last_error();
//         //   return false;
//         //}
//
//         //SetTimer(m_oswindow,888888,84,nullptr);
//
//         //SetWindowLongPtr(m_oswindow,GWLP_USERDATA,(LONG_PTR) this);
//
//         //m_strWindowProcModule = pszWindowProcModule;
//
//
//
//         return true;
//      }
//
//
//      bool rx::destroy()
//      {
//
//         ::acme::del(m_pp);
//
//         return true;
//
//      }
//
//
//      void rx::receiver::on_receive(rx * prx, const ::string & pszMessage)
//      {
//      }
//
//      void rx::receiver::on_receive(rx * prx,int message,void * pdata,memsize len)
//      {
//      }
//
//      void rx::receiver::on_post(rx * prx,long long int a,long long int b)
//      {
//      }
//
//      void * rx::on_receive(rx * prx, const ::string & pszMessage)
//      {
//
//         if(m_preceiver != nullptr)
//         {
//            m_preceiver->on_receive(prx,pszMessage);
//         }
//
//         // ODOW - on date of writing : return ignored by this windows implementation
//
//         return nullptr;
//
//      }
//
//      void * rx::on_receive(rx * prx,int message,void * pdata,memsize len)
//      {
//
//         if(m_preceiver != nullptr)
//         {
//            m_preceiver->on_receive(prx,message,pdata,len);
//         }
//
//         // ODOW - on date of writing : return ignored by this windows implementation
//
//         return nullptr;
//
//      }
//
//
//      void * rx::on_post(rx * prx,long long int a,long long int b)
//      {
//
//         if(m_preceiver != nullptr)
//         {
//            m_preceiver->on_post(prx,a,b);
//         }
//
//         // ODOW - on date of writing : return ignored by this windows implementation
//
//         return nullptr;
//
//      }
//
//
//      //LRESULT CALLBACK rx::s_message_queue_proc(oswindow oswindow,const ::id & id,wparam wparam,lparam lparam)
//      //{
//
//      //   //int iRet = 0;
//
//      //   //rx * pchannel = (rx *)GetWindowLongPtr(oswindow,GWLP_USERDATA);
//
//      //   //if(pchannel == nullptr)
//      //   //{
//
//      //   //   return ::DefWindowProcW(oswindow,message,wparam,lparam);
//
//      //   //}
//      //   //else
//      //   //{
//
//      //   //   return pchannel->message_queue_proc(message,wparam,lparam);
//
//      //   //}
//
//      //   return 0;
//
//      //}
//
//
//
//      //ATOM rx::register_class(HINSTANCE hInstance)
//      //{
//      //   //WNDCLASSEX wcex;
//
//      //   //wcex.cbSize = sizeof(WNDCLASSEX);
//
//      //   //wcex.style			   = 0;
//      //   //wcex.lpfnWndProc	   = &rx::s_message_queue_proc;
//      //   //wcex.cbClsExtra	   = 0;
//      //   //wcex.cbWndExtra	   = 0;
//      //   //wcex.hInstance		   = hInstance;
//      //   //wcex.hIcon			   = nullptr;
//      //   ////wcex.hCursor		   = LoadCursor(nullptr, IDC_ARROW);
//      //   //wcex.hCursor		   = nullptr;
//      //   //wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
//      //   //wcex.lpszMenuName	   = nullptr;
//      //   //wcex.lpszClassName	= "small_ipc_rx_::color::e_channel_message_queue_class";
//      //   //wcex.hIconSm		   = nullptr;
//
//      //   //return RegisterClassEx(&wcex);
//      //   return true;
//      //}
//
//
//      //LRESULT rx::message_queue_proc(const ::id & id,wparam wparam,lparam lparam)
//      //{
//
//      //   //if(message == WM_USER + 100)
//      //   //{
//
//      //   //   on_post(this,wparam,lparam);
//
//      //   //}
//      //   //else if(message == WM_COPYDATA)
//      //   //{
//
//      //   //   COPYDATASTRUCT * pcds = (COPYDATASTRUCT *)lparam;
//
//      //   //   if(pcds == nullptr)
//      //   //   {
//
//      //   //      return 0;
//
//      //   //   }
//      //   //   else if(pcds->dwData == 0x80000000)
//      //   //   {
//
//      //   //      string strMessage((const ::string &)pcds->lpData,pcds->cbData);
//
//      //   //      on_receive(this,strMessage.c_str());
//
//      //   //   }
//      //   //   else
//      //   //   {
//
//      //   //      on_receive(this,(int)pcds->dwData,pcds->lpData,pcds->cbData);
//
//      //   //   }
//
//      //   //}
//      //   //else if(message >= WM_APP)
//      //   //{
//
//      //   //   on_receive(this,message,(void *)wparam,lparam);
//
//      //   //}
//      //   //else
//      //   //{
//
//      //   //   return ::DefWindowProcW(m_oswindow,message,wparam,lparam);
//
//      //   //}
//
//      //   return 0;
//
//      //}
//
//
//
//      bool rx::on_idle()
//      {
//
//         return false;
//
//      }
//
//      bool rx::is_rx_ok()
//      {
//
//         //return ::IsWindow(m_oswindow) != false;
//         return true;
//
//      }
//
//      ipc::ipc(::object * pobject):
//         object(pobject),
//         base(pobject),
//         tx(pobject),
//         m_rx(pobject)
//      {
//
//         m_durationTimeout = (5000) * 11;
//
//      }
//
//
//      ipc::~ipc()
//      {
//
//
//      }
//
//      bool ipc::open_ab(const ::string & pszKey, const ::string & pszModule,launcher * plauncher)
//      {
//
//         /*m_strChannel = pszKey;
//
//         m_rx.m_preceiver = this;
//
//         string strChannelRx = m_strChannel + "-a";
//         string strChannelTx = m_strChannel + "-b";
//
//         if(!::IsWindow(m_rx.m_oswindow))
//         {
//
//            if(!m_rx.create(strChannelRx.c_str(),pszModule))
//            {
//
//               return false;
//
//            }
//
//         }
//
//         if(!tx::open(strChannelTx.c_str(),plauncher))
//         {
//            return false;
//         }
//*/
//         return true;
//
//      }
//
//      bool ipc::open_ba(const ::string & pszKey, const ::string & pszModule,launcher * plauncher)
//      {
//
//         //m_strChannel = pszKey;
//
//         //m_rx.m_preceiver = this;
//
//         //string strChannelRx = m_strChannel + "-b";
//         //string strChannelTx = m_strChannel + "-a";
//
//
//         //if(!::IsWindow(m_rx.m_oswindow))
//         //{
//
//         //   if(!m_rx.create(strChannelRx.c_str(),pszModule))
//         //   {
//
//         //      return false;
//
//         //   }
//
//         //}
//
//         //if(!tx::open(strChannelTx.c_str(),plauncher))
//         //{
//         //   return false;
//         //}
//
//         return true;
//
//      }
//
//
//      bool ipc::is_rx_tx_ok()
//      {
//
//         return m_rx.is_rx_ok() && is_tx_ok();
//
//      }
//
//
//   } // namespace ipc
//
//
//} // namespace aura
//
//
//
//
//
//
