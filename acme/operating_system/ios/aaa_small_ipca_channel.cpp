#include "framework.h"
#include <sys/ipc.h>
#include <sys/msg.h>
#include "acme/operating_system/ansi/_pthread.h"




namespace acme
{


   namespace ipc
   {


      base::base()
      {
         
         m_port = nullptr;
         
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
   

      bool tx::open(const ::scoped_string & scopedstrChannel,launcher * plauncher)
      {

         CFDataRef data;
         
         SInt32 messageID = 0x1111;
         
         CFTimeInterval timeout = 10.0;
         
         CFStringRef kungfuck = CFStringCreateWithCString(nullptr,  (string("com.ca2.app.port.server.") + pszChannel), kCFStringEncodingUTF8);
         
         m_port =        CFMessagePortCreateRemote(nil,kungfuck);

         return true;
         
      }
   

      bool tx::close()
      {

         if(m_port == nullptr)
         {
            
            return true;
            
         }

         CFRelease(m_port);

         m_port = nullptr;

         return true;

      }


      bool tx::send(const ::scoped_string & scopedstrMessage,duration durationTimeout)
      {

         if(m_port == nullptr)
         {
            
            return false;
            
         }

         ::collection::count c = ansi_length(scopedstrMessage);

         ::collection::count cSend;

         memory m;

         m.assign(scopedstrMessage, c);

         CFDataRef data = m.get_os_cf_data();

         SInt32 status = CFMessagePortSendRequest(m_port,
                                  I32_MINIMUM,
                                  data,
                                  durationTimeout.get_total_milliseconds() / 1000.0,
                                  durationTimeout.get_total_milliseconds() / 1000.0,
                                  nullptr,
                                  nullptr);
         
         if (status == kCFMessagePortSuccess)
         {
            
            return true;
            
         }
         
         if(status != kCFMessagePortSendTimeout && status != kCFMessagePortReceiveTimeout)
         {
            
            close();
            
         }
         
         return false;

      }


      bool tx::send(int message,void * pdata,int len,duration durationTimeout)
      {

         if(message == I32_MINIMUM)
         {
            
            return false;
            
         }

         if(!is_tx_ok())
         {
            
            return false;
            
         }

         memory m(pdata, len);

         ::collection::count c = len;

         ::collection::count cSend;

         SInt32 status = CFMessagePortSendRequest(m_port,
                                  message,
                                  m.get_os_cf_data(),
                                  durationTimeout.get_total_milliseconds() / 1000.0,
                                  durationTimeout.get_total_milliseconds() / 1000.0,
                                  nullptr,
                                  nullptr);
         
         if (status == kCFMessagePortSuccess)
         {
            
         }
         
         return true;

      }


      bool tx::is_tx_ok()
      {

         return m_port != nullptr;

      }


      rx::rx()
      {

         m_preceiver    = nullptr;

      }


      rx::~rx()
      {

      }

   
      CFDataRef Callback(CFMessagePortRef port, SInt32 messageID, CFDataRef data, void * info)
      {
         
         rx * p = (rx*) info;

         if(messageID == I32_MINIMUM)
         {

            memory m;

            m.set_os_cf_data(data);

            p->on_ipc_receive(p, as_string(m));

         }
         else
         {

            memory m;

            m.set_os_cf_data(data);

            p->on_ipc_receive(p,messageID, m.get_data(), (int)m.get_size());

         }
         
         return nullptr;
         
      }
   

      bool rx::create(const ::scoped_string & scopedstrChannel)
      {

         CFMessagePortContext c = {};

         c.info = this;

         CFStringRef str = CFStringCreateWithCString(nullptr,  (string("com.ca2.app.port.server.") + pszChannel), kCFStringEncodingUTF8);

         Boolean b = false;

         m_port = CFMessagePortCreateLocal(nil, str, Callback, &c, &b);

         CFRelease(str);

         start_receiving();

         return true;
         
      }


      bool rx::destroy()
      {

         if(m_port == nullptr)
         {
            
            return true;
            
         }

         CFRelease(m_port);

         m_port = nullptr;

         return true;

      }
   

      bool rx::start_receiving()
      {

         m_bRunning = true;

         m_bRun = true;

         m_pthread = ::fork(get_app(), [&]()
         {

            receive();

            m_bRunning = false;

            m_bRun = false;

         });

         return true;

      }

//
//      void rx::receiver::on_ipc_receive(rx * prx, const ::scoped_string & scopedstrMessage)
//      {
//
//      }
//

//      void rx::receiver::on_ipc_receive(rx * prx, int message, void * pdata, memsize len)
//      {
//
//      }
//
//
//      void rx::receiver::on_ipc_post(rx * prx, long long a, long long b)
//      {
//
//      }
//

      void * rx::on_ipc_receive(rx * prx, const ::scoped_string & scopedstrMessage)
      {

         if(m_preceiver != nullptr)
         {

            m_preceiver->on_ipc_receive(prx,pszMessage);

         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return nullptr;

      }

   
      void * rx::on_ipc_receive(rx * prx, int message, void * pdata, memsize len)
      {

         if(m_preceiver != nullptr)
         {
            
            m_preceiver->on_ipc_receive(prx,message,pdata,len);
            
         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return nullptr;

      }


      void * rx::on_ipc_post(rx * prx,long long a,long long b)
      {

         if(m_preceiver != nullptr)
         {
            
            m_preceiver->on_ipc_post(prx,a,b);
            
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

         return m_port != nullptr;
      }


      void * rx::receive()
      {

         CFRunLoopSourceRef runLoopSource = CFMessagePortCreateRunLoopSource(nil, m_port, 0);

         CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);

         while(m_bRun)
         {
            
            CFRunLoopRun();
            
         }

         return nullptr;

      }


      ipc::ipc()
      {

         m_durationTimeout = (5000) * 11;

      }


      ipc::~ipc()
      {


      }


      bool ipc::open_ab(const ::scoped_string & scopedstrChannel, launcher * plauncher)
      {

         m_strChannel = pszChannel;

         m_rx.m_preceiver = this;

         string strChannelRx = m_strChannel + "-a";
         
         string strChannelTx = m_strChannel + "-b";

         if(!m_rx.create(strChannelRx))
         {
            
            return false;
            
         }

         if(!tx::open(strChannelTx,plauncher))
         {
            
            return false;
            
         }

         return true;

      }
   

      bool ipc::open_ba(const ::scoped_string & scopedstrChannel, launcher * plauncher)
      {

         m_strChannel = pszChannel;

         m_rx.m_preceiver = this;

         string strChannelRx = m_strChannel + "-b";
         
         string strChannelTx = m_strChannel + "-a";

         if(!m_rx.create(strChannelRx))
         {
            
            return false;
            
         }

         if(!tx::open(strChannelTx,plauncher))
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


} // namespace acme



