#include "framework.h"
//#include "universal_windows.h"
//#ifndef _UWP

// loop question http://stackoverflow.com/users/2101860/loop
// http://stackoverflow.com/questions/23709329/launch-one-metro-app-from-other-metro-app-windows-8
// souvickcse http://stackoverflow.com/users/2246798/souvickcse

namespace aura
{


   namespace ipc
   {


      // extern bool (WINAPI * g_pfnChangeWindowMessageFilter)(
      // _In_ const ::atom & atom,
      // _In_ ::u32 dwFlag);


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

      //bool tx::open(const ::string & pszChannel, launcher * plauncher)
      //{

      //   __UNREFERENCED_PARAMETER(plauncher);

      //   if (m_strBaseChannel.has_char())
      //      close();

      //   // LaunchUri protocol is m_strBaseChannel

      //   m_strBaseChannel = pszChannel;

      //   m_strBaseChannel.replace("_", "-");
      //   m_strBaseChannel.replace("/", "-");

      //   return true;

      //}

      bool tx::open(const ::string & pszChannel)
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


      bool tx::send(const ::string & pszMessage, duration durationTimeout)
      {

         if (!is_tx_ok())
            return false;

         string anotherappURI = m_strBaseChannel + ":///send?message=" + psystem->url_encode(pszMessage);

         Uri ^uri = ref memory_new Uri(anotherappURI);

         main_sync([uri, durationTimeout]()
            {

               ::wait(Launcher::LaunchUriAsync(uri), durationTimeout);

            });

         return true;

      }


      bool tx::is_tx_ok()
      {

         //return ::IsWindow(m_hwnd) != false;

         return m_strBaseChannel.has_char();


      }


      bool tx::send(int message, void * pdata, int len, ::duration durationTimeout)
      {

         if (!is_tx_ok())
            return false;

         memory m;



         string anotherappURI = m_strBaseChannel + "://send?messagebin=" + __string(message)+ "," + psystem->url_encode(pbase64->encode((byte *)pdata, len));

         Uri ^uri = ref memory_new Uri(anotherappURI);

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


      bool rx::create(const ::string & pszChannel)
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

      //void rx::receiver::on_ipc_receive(rx * prx, const ::string & pszMessage)
      //{

      //}

      //void rx::receiver::on_ipc_receive(rx * prx, int message, void * pdata, memsize len)
      //{

      //}


      //void rx::receiver::on_ipc_post(rx * prx, long long int a, long long int b)
      //{

      //}


      void * rx::on_ipc_receive(rx * prx, const ::string & pszMessage)
      {

         if (m_preceiver != nullptr)
         {
            m_preceiver->on_ipc_receive(prx, pszMessage);
         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return nullptr;

      }

      void * rx::on_ipc_receive(rx * prx, int message, void * pdata, memsize len)
      {

         if (m_preceiver != nullptr)
         {
            m_preceiver->on_ipc_receive(prx, message, pdata, len);
         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return nullptr;

      }


      void * rx::on_ipc_post(rx * prx, long long int a, long long int b)
      {

         if (m_preceiver != nullptr)
         {
            m_preceiver->on_ipc_post(prx, a, b);
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


      ipc::ipc()
      {


      }


      ipc::~ipc()
      {


      }


      //bool ipc::open_ab(const ::string & pszChannel, const ::string & pszModule, launcher * plauncher)
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


      //bool ipc::open_ba(const ::string & pszChannel, const ::string & pszModule, launcher * plauncher)
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


      bool ipc::open_ab(const ::string & pszChannel, const ::string & pszModule)
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


      bool ipc::open_ba(const ::string & pszChannel, const ::string & pszModule)
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




      bool ipc::is_rx_tx_ok()
      {

         return m_rx.is_rx_ok() && is_tx_ok();

      }


   } // namespace ipc


} // namespace aura



//#endif
