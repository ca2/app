#include "framework.h"
//#include "uwp.h"
//#ifndef _UWP

// loop question http://stackoverflow.com/users/2101860/loop
// http://stackoverflow.com/questions/23709329/launch-one-metro-app-from-other-metro-app-windows-8
// souvickcse http://stackoverflow.com/users/2246798/souvickcse

//namespace apex
//{


   namespace interprocess_communication
   {


      // extern bool (WINAPI * g_pfnChangeWindowMessageFilter)(
      // _In_ UINT message,
      // _In_ DWORD dwFlag);


      base::base()
      {

      }

      base::~base()
      {
      }

      tx::tx()
      {

      }

      tx::~tx()
      {
      }

      //bool tx::open(const char * pszChannel, launcher * plauncher)
      //{

      //   UNREFERENCED_PARAMETER(plauncher);

      //   if (m_strBaseChannel.has_char())
      //      close();

      //   // LaunchUri protocol is m_strBaseChannel

      //   m_strBaseChannel = pszChannel;

      //   m_strBaseChannel.replace("_", "-");
      //   m_strBaseChannel.replace("/", "-");

      //   return true;

      //}

      bool tx::open(const char * pszChannel)
      {

         if (m_strBaseChannel.has_char())
            close();

         // LaunchUri protocol is m_strBaseChannel

         m_strBaseChannel = pszChannel;

         m_strBaseChannel.replace("_", "-");
         m_strBaseChannel.replace("/", "-");

         return true;

      }


      bool tx::close()
      {

         if (m_strBaseChannel.is_empty())
            return true;

         m_strBaseChannel.Empty();

         return true;

      }


      bool tx::send(const char * pszMessage, duration durationTimeout)
      {

         if (!is_tx_ok())
            return false;

         string anotherappURI = m_strBaseChannel + ":///send?message=" + ::get_context_system()->url_encode(pszMessage);

         ::Windows::Foundation::Uri ^uri = ref new ::Windows::Foundation::Uri(anotherappURI);

         main_sync([uri, durationTimeout]()
            {

               ::wait(Launcher::LaunchUriAsync(uri), durationTimeout);

            });

         return true;

      }


      bool tx::is_tx_ok()
      {

         //return ::IsWindow(m_hwnd) != FALSE;

         return m_strBaseChannel.has_char();


      }


      bool tx::send(int message, void * pdata, int len, ::duration durationTimeout)
      {

         if (!is_tx_ok())
            return false;

         memory m;

         string anotherappURI = m_strBaseChannel + "://send?messagebin=" + __str(message) + "," + ::get_context_system()->url_encode(::get_context_system()->base64().encode({ pdata, len }));

         ::Windows::Foundation::Uri ^uri = ref new ::Windows::Foundation::Uri(anotherappURI);

         ::wait(Launcher::LaunchUriAsync(uri), durationTimeout);

         return true;

      }


      rx::rx()
      {

         m_preceiver = nullptr;

      }


      rx::~rx()
      {

      }


      bool rx::create(const char * pszChannel)
      {

         if (m_strBaseChannel.has_char())
            destroy();

         m_strBaseChannel = pszChannel;

         m_strBaseChannel.replace("_", "-");
         m_strBaseChannel.replace("/", "-");


         return true;

      }


      bool rx::destroy()
      {

         if (m_strBaseChannel.is_empty())
         {

            return true;

         }


         m_strBaseChannel.Empty();

         return true;

      }

      //void rx::receiver::on_ipc_receive(rx * prx, const char * pszMessage)
      //{

      //}

      //void rx::receiver::on_ipc_receive(rx * prx, int message, void * pdata, memsize len)
      //{

      //}


      //void rx::receiver::on_ipc_post(rx * prx, long long int a, long long int b)
      //{

      //}


      void * rx::on_ipc_receive(rx * prx, const char * pszMessage)
      {

         if (m_preceiver != nullptr)
         {
            m_preceiver->on_interprocess_receive(prx, pszMessage);
         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return nullptr;

      }

      void * rx::on_ipc_receive(rx * prx, int message, void * pdata, memsize len)
      {

         if (m_preceiver != nullptr)
         {
            m_preceiver->on_interprocess_receive(prx, message, pdata, len);
         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return nullptr;

      }


      void * rx::on_ipc_post(rx * prx, long long int a, long long int b)
      {

         if (m_preceiver != nullptr)
         {
            m_preceiver->on_interprocess_post(prx, a, b);
         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return nullptr;

      }



      bool rx::on_idle()
      {

         return false;

      }

      bool rx::is_rx_ok()
      {

         return m_strBaseChannel.has_char();

      }


      interprocess_communication::interprocess_communication()
      {


      }


      interprocess_communication::~interprocess_communication()
      {


      }


      //bool ipc::open_ab(const char * pszChannel, const char * pszModule, launcher * plauncher)
      //{

      //   m_strChannel = pszChannel;

      //   m_rx.m_preceiver = this;

      //   string strChannelRx = m_strChannel;

      //   string strChannelTx = m_strChannel;

      //   if (!m_rx.create(strChannelRx))
      //   {

      //      return false;

      //   }

      //   if (!tx::open(strChannelTx, plauncher))
      //   {

      //      return false;

      //   }

      //   return true;

      //}


      //bool ipc::open_ba(const char * pszChannel, const char * pszModule, launcher * plauncher)
      //{

      //   m_strChannel = pszChannel;

      //   m_rx.m_preceiver = this;

      //   string strChannelRx = m_strChannel;

      //   string strChannelTx = m_strChannel;

      //   if (!m_rx.create(strChannelRx))
      //   {

      //      return false;

      //   }

      //   if (!tx::open(strChannelTx, plauncher))
      //   {

      //      return false;

      //   }

      //   return true;

      //}


      bool interprocess_communication::open_ab(const char * pszChannel, const char * pszModule)
      {

         m_strChannel = pszChannel;

         m_rx.m_preceiver = this;

         string strChannelRx = m_strChannel;

         string strChannelTx = m_strChannel;

         if (!m_rx.create(strChannelRx))
         {

            return false;

         }

         if (!tx::open(strChannelTx))
         {

            return false;

         }

         return true;

      }


      bool interprocess_communication::open_ba(const char * pszChannel, const char * pszModule)
      {

         m_strChannel = pszChannel;

         m_rx.m_preceiver = this;

         string strChannelRx = m_strChannel;

         string strChannelTx = m_strChannel;

         if (!m_rx.create(strChannelRx))
         {

            return false;

         }

         if (!tx::open(strChannelTx))
         {

            return false;

         }

         return true;

      }




      bool interprocess_communication::is_rx_tx_ok()
      {

         return m_rx.is_rx_ok() && is_tx_ok();

      }


   } // namespace ipc


//} // namespace apex



//#endif
