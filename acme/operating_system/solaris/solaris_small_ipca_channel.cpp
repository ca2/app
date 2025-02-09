#include "framework.h"


#include <sys/ipc.h>
#include <sys/msg.h>
#undef USE_MISC



extern "C" void * small_ipc_rx_::color::e_channel_receive_proc(void * param);

namespace acme
{


   namespace ipc
   {


      base::base()
      {
         m_key = 0;
         m_iQueue = -1;
      }

      base::~base()
      {
      }



      bool tx::open(const ::scoped_string & scopedstrChannel,launcher * plauncher)
      {

         if(m_iQueue >= 0)
            close();

         m_key = ftok(".",'c');

         if(m_key == 0)
            return false;

         if((m_iQueue = msgget(m_key,0660)) == -1)
         {
            return false;
         }

         m_strTxChannel = pszChannel;

         return true;

      }

      bool tx::close()
      {

         if(m_iQueue < 0)
            return true;

         m_iQueue = -1;

         m_strTxChannel = "";

         return true;

      }


      bool tx::send(const ::scoped_string & scopedstrMessage,unsigned int tickTimeout)
      {

         data_struct data;
         data.mtype        = 15112000;
         data.request      = 0;
         data.int_size         = ansi_length(pszMessage);
         if(data.int_size > 512)
            return false;

         /* The length is essentially the int_size of the structure minus sizeof(mtype) */
         int length = sizeof(data_struct) - sizeof(long);

         int result;

         if((result = msgsnd(m_iQueue,&data,length,0)) == -1)
         {
            return false;
         }

         return true;
      }


      bool tx::send(int message,void * pdata,int len,unsigned int tickTimeout)
      {

         if(message == I32_MINIMUM)
            return false;


         if(!is_tx_ok())
            return false;

         const ::scoped_string & scopedstrMessage = (const char *)pdata;

         ::collection::count c = len;

         ::collection::count cSend;

         data_struct data;
         data.mtype        = 15112000;
         data.request      = I32_MINIMUM;
         data.int_size         = (int)ansi_length(pszMessage);

         ::collection::count cPos = 0;

         while(c > 0)
         {

            cSend = minimum(c,511);

            ::memory_copy(data.data,&pszMessage[cPos],minimum(c,511));

            c -= cSend;

            cPos += cSend;

            if(c > 0)
               data.size = 512;
            else
               data.size = (int)cSend;

            /* The length is essentially the int_size of the structure minus sizeof(mtype) */
            int length = sizeof(data_struct) - sizeof(long);

            int result;

            if((result = msgsnd(m_iQueue,&data,length,0)) == -1)
            {
               return false;
            }

         }

         return true;

      }



      bool tx::is_tx_ok()
      {

         return m_iQueue != -1;

      }


      small_ipc_rx_channel::small_ipc_rx_channel()
      {

         m_preceiver    = nullptr;

      }


      small_ipc_rx_channel::~small_ipc_rx_channel()
      {

      }


      bool small_ipc_rx_channel::create(const ::scoped_string & scopedstrChannel)
      {
         m_key = ftok(".",'c');

         if(m_key == 0)
            return false;

         if((m_iQueue = msgget(m_key,IPC_CREAT | IPC_EXCL | 0660)) == -1)
         {
            return false;
         }

         return true;
      }


      bool small_ipc_rx_channel::destroy()
      {

         int iRetry = 23;
         while(m_bRunning && iRetry > 0)
         {
            m_bRun = false;
            sleep(1_ms);
            iRetry--;
         }

         if(m_iQueue < 0)
            return true;

         if(msgctl(m_iQueue,IPC_RMID,0) == -1)
         {
            return false;
         }

         m_iQueue = -1;

         return true;

      }

      bool small_ipc_rx_channel::start_receiving()
      {

         m_bRunning = true;

         m_bRun = true;

         if(pthread_create(&m_thread,nullptr,&small_ipc_rx_::color::e_channel_receive_proc,this) != 0)
         {

            m_bRunning = false;

            m_bRun = false;

            return false;

         }

         return true;

      }


      extern "C" void * small_ipc_rx_::color::e_channel_receive_proc(void * param)
      {

         small_ipc_rx_channel * pchannel = (small_ipc_rx_channel *)param;

         return pchannel->receive();

      }



      void small_ipc_rx_channel::receiver::on_receive(small_ipc_rx_channel * prxchannel,const ::scoped_string & scopedstrMessage)
      {
      }

      void small_ipc_rx_channel::receiver::on_receive(small_ipc_rx_channel * prxchannel,int message,void * pdata,memsize len)
      {
      }

      void small_ipc_rx_channel::receiver::on_post(small_ipc_rx_channel * prxchannel,long long a,long long b)
      {
      }



      void * small_ipc_rx_channel::on_receive(small_ipc_rx_channel * prxchannel,const ::scoped_string & scopedstrMessage)
      {

         if(m_preceiver != nullptr)
         {
            m_preceiver->on_receive(prxchannel,pszMessage);
         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return nullptr;

      }

      void * small_ipc_rx_channel::on_receive(small_ipc_rx_channel * prxchannel,int message,void * pdata,memsize len)
      {

         if(m_preceiver != nullptr)
         {
            m_preceiver->on_receive(prxchannel,message,pdata,len);
         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return nullptr;

      }




      void * small_ipc_rx_channel::on_post(small_ipc_rx_channel * prxchannel,long long a,long long b)
      {

         if(m_preceiver != nullptr)
         {
            m_preceiver->on_post(prxchannel,a,b);
         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return nullptr;

      }



      bool small_ipc_rx_channel::on_idle()
      {

         return false;

      }


      bool small_ipc_rx_channel::is_rx_ok()
      {

         return m_iQueue != -1;
      }






      void * small_ipc_rx_channel::receive()
      {

         while(m_bRun)
         {

            m_bRunning = true;

            ssize_t  result;

            int length;

            data_struct data;

            /* The length is essentially the int_size of the structure minus sizeof(mtype) */
            length = sizeof(data_struct) - sizeof(long);

            memory mem;

            do
            {

               if((result = msgrcv(m_iQueue,&data,length,15112000,IPC_NOWAIT)) == -1)
               {

                  if(errno == ENOMSG)
                  {
                     if(!on_idle())
                     {
                        sleep(100_ms);
                     }
                  }
                  else
                  {
                     return (void *)-1;
                  }

               }

               mem.append(data.data,data.int_size);


               if(data.int_size < 512)
                  break;

            }
            while(true);


            if(data.request == 0)
            {

               on_receive(this,(const char *)mem.get_data());

            }
            else
            {

               on_receive(this,data.request,mem.get_data(),mem.get_size());

            }

         }

         m_bRunning = false;

         return nullptr;

      }



      bool ipc::open_ab(const ::scoped_string & scopedstrChannel,launcher * plauncher)
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

      bool ipc::open_ba(const ::scoped_string & scopedstrChannel,launcher * plauncher)
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









