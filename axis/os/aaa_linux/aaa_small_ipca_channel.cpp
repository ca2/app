#include "framework.h"


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


namespace axis
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


      tx::tx()
      {

         //mutex() = new ::mutex(pobject);

      }


      tx::~tx()
      {

      }

      bool tx::open(const char * pszChannel,launcher * plauncher)
      {

         if(m_iQueue >= 0)
            close();

         if(!file_exists(pszChannel))
         {

            file_put_contents(pszChannel, pszChannel);

         }

         m_key = ftok(pszChannel,'c');

         if(m_key == 0)
            return false;

         if((m_iQueue = msgget(m_key,IPC_CREAT | 0660)) == -1)
         {

            return false;

         }

         m_strBaseChannel = pszChannel;

         return true;

      }


      bool tx::close()
      {

         if(m_iQueue < 0)
         {

            return true;

         }

         m_iQueue = -1;

         m_strBaseChannel = "";

         return true;

      }


      bool tx::send(const char * pszMessage, duration durationTimeout)
      {

         memory m;

         int iLen = ansi_length(pszMessage);

         m.set_size(sizeof(data_struct) + iLen);

         data_struct * pdata  = (data_struct *)m.get_data();

         pdata->mtype         = 15111984;

         pdata->request       = 1024;

         pdata->size          = iLen;

         ::memcpy_dup(pdata->data, pszMessage, iLen);

         int result = 0;

         msqid_ds b;

         xxf_zero(b);

         if((result = msgsnd(m_iQueue, pdata, m.get_size() - sizeof(long), 0)) == -1)
         {

            int iError = errno;

            return false;

         }

         ::output_debug_string("functon: \"tx::send\"\n");

         ::output_debug_string("channel: \"" +m_strBaseChannel+ "\"\n");

         ::output_debug_string("message: \"" +string(pszMessage)+ "\"\n");

         return true;

      }


      bool tx::send(i32 message,void * p,i32 iLen,duration durationTimeout)
      {

         if(message == 1024)
            return false;


         if(!is_tx_ok())
            return false;

         memory m;

         m.set_size(sizeof(data_struct) + iLen);

         data_struct * pdata = (data_struct *)m.get_data();
         pdata->mtype        = 15111984;
         pdata->request      = 1024;
         pdata->size         = iLen;
         //if(data.size > 512)
         // return false;

         /* The length is essentially the size of the structure minus sizeof(mtype) */
         /*         i32 length = sizeof(data_struct) - sizeof(long);

                  i32 result;

                  ::memcpy_dup(data.data, pszMessage, data.size);

                  if((result = msgsnd(m_iQueue,&data,length,0)) == -1)
                  {
                     return false;
                  }
                  */

         //const char * pszMessage = (const char *)pdata;

         ::memcpy_dup(pdata->data,p,iLen);

         int result = 0;

         if((result = msgsnd(m_iQueue,pdata,m.get_size() - sizeof(long),0)) == -1)
         {
            return false;
         }

         return true;

      }



      bool tx::is_tx_ok()
      {

         return m_iQueue != -1;

      }


      rx::rx()
      {

         m_preceiver    = nullptr;

      }


      rx::~rx()
      {

      }


      bool rx::create(const char * pszChannel)
      {



         if(!file_exists(pszChannel))
         {

            file_put_contents(pszChannel, pszChannel);

         }



         m_key = ftok(pszChannel,'c');

         if(m_key == 0)
            return false;

         //if((m_iQueue = msgget(m_key,IPC_CREAT | IPC_EXCL | 0660)) == -1)
         if((m_iQueue = msgget(m_key,IPC_CREAT | 0660)) == -1)
         {
            return false;
         }

         start_receiving();

         return true;

      }


      bool rx::destroy()
      {

         i32 iRetry = 23;
         while(m_bRunning && iRetry > 0)
         {
            m_bRun = false;
            sleep(1);
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


      bool rx::start_receiving()
      {

         m_bRunning = true;

         m_bRun = true;

         m_pthread = fork([&]()
         {

            receive();

         });

         return true;

      }


//      void rx::receiver::on_ipc_receive(rx * prx,const char * pszMessage)
//      {
//
//      }
//
//
//      void rx::receiver::on_ipc_receive(rx * prx,i32 message,void * pdata,memsize len)
//      {
//
//      }
//

//      void rx::receiver::on_ipc_post(rx * prx, i64 a, i64 b)
//      {
//
//      }


      void * rx::on_ipc_receive(rx * prx,const char * pszMessage)
      {

         if(m_preceiver != nullptr)
         {

            m_preceiver->on_ipc_receive(prx,pszMessage);

         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return nullptr;

      }


      void * rx::on_ipc_receive(rx * prx,i32 message,void * pdata,memsize len)
      {

         if(m_preceiver != nullptr)
         {

            m_preceiver->on_ipc_receive(prx,message,pdata,len);

         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return nullptr;

      }




      void * rx::on_ipc_post(rx * prx, i64 a, i64 b)
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

         return m_iQueue != -1;

      }


      void * rx::receive()
      {

         memory mem;

         memory m;

         m.set_size(10000000);

         while(thread_get_run())
         {

            m_bRunning = true;

            ssize_t  result;

            i32 length;

            data_struct * pdata = (data_struct *) m.get_data();

            length = m.get_size() - sizeof(long);

            if((result = msgrcv(m_iQueue, pdata, length, 15111984, IPC_NOWAIT)) == -1)
            {

               if(errno == ENOMSG)
               {

                  Sleep(100);

                  continue;

               }
               else
               {

                  return (void *)-1;

               }

            }

            mem.assign(pdata->data,pdata->size);

            long lRequest = pdata->request;

            fork([this, mem, lRequest]()
            {

               memory m2(mem);

               if(lRequest == 1024)
               {

                  on_ipc_receive(this, __str(m2));

               }
               else
               {

                  on_ipc_receive(this, lRequest, m2.get_data(), m2.get_size());

               }

            });

         }

         m_bRunning = false;

         return nullptr;

      }


      ipc::ipc()
      {

         m_millisTimeout = (5000) * 11;

      }


      ipc::~ipc()
      {


      }

      bool ipc::open_ab(const char * pszChannel,launcher * plauncher)
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

      bool ipc::open_ba(const char * pszChannel,launcher * plauncher)
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


} // namespace axis






