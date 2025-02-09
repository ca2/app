

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

      tx::tx()
      {


      }

      tx::~tx()
      {


      }

      bool tx::open(const ::scoped_string & scopedstrChannel,launcher * plauncher)
      {

         if(m_iQueue >= 0)
            close();

         /*   m_key = ftok(".", 'c');

            if(m_key == 0)
            return false;

            if((m_iQueue = msgget(m_key, 0660)) == -1)
            {
            return false;
            }

            m_strBaseChannel = pszChannel;*/

         return true;

      }

      bool tx::close()
      {

         if(m_iQueue < 0)
            return true;

         m_iQueue = -1;

         m_strBaseChannel = "";

         return true;

      }


      bool tx::send(const ::scoped_string & scopedstrMessage,duration durationTimeout)
      {

         data_struct data;
         data.mtype        = 20170101;
         data.request      = 0;
         data.size         = ansi_length(pszMessage);
         if(data.size > 512)
            return false;

         /* The length is essentially the size of the structure minus sizeof(mtype) */
         int length = sizeof(data_struct) - sizeof(long);

         int result;
         /*
            if((result = msgsnd(m_iQueue, &data, length, 0)) == -1)
            {
            return false;
            }
            */
         return true;
      }


      bool tx::send(int message,void * pdata,int len,duration durationTimeout)
      {

         if(message == (int) I32_MINIMUM)
            return false;


         if(!is_tx_ok())
            return false;

         const ::scoped_string & scopedstrMessage = (const char *)pdata;

         ::collection::count c = len;

         ::collection::count cSend;

         data_struct data;
         data.mtype        = 20170101;
         data.request      = I32_MINIMUM;
         data.size         = (int)ansi_length(pszMessage);

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

            /* The length is essentially the size of the structure minus sizeof(mtype) */
            int length = sizeof(data_struct) - sizeof(long);

            int result;
            /*
            if((result = msgsnd(m_iQueue, &data, length, 0)) == -1)
            {
            return false;
            }
            */
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


      bool rx::create(const ::scoped_string & scopedstrChannel)
      {
         /*
         m_key = ftok(".", 'c');

         if(m_key == 0)
         return false;

         if((m_iQueue = msgget(m_key, IPC_CREAT | IPC_EXCL | 0660 )) == -1)
         {
         return false;
         }
         */

         return true;
      }


      bool rx::destroy()
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
         /*
         if(msgctl( m_iQueue, IPC_RMID, 0) == -1)
         {
         return false;
         }
         */
         m_iQueue = -1;

         return true;

      }

      bool rx::start_receiving()
      {

         m_bRunning = true;

         m_bRun = true;

         m_pthread = ::fork(get_app(), [&]()
         {


            receive();


         });

         return true;

      }

      //void * rx::receive_proc(void * param)
      //{

      //   rx * pchannel = (rx *)param;

      //   return pchannel->receive();

      //}



      // void rx::receiver::on_ipc_receive(rx * prx,const ::scoped_string & scopedstrMessage)
      // {
      // }

      // void rx::receiver::on_ipc_receive(rx * prx,int message,void * pdata,memsize len)
      // {
      // }

      // void rx::receiver::on_ipc_post(rx * prx,long long a,long long b)
      // {
      // }



      void * rx::on_ipc_receive(rx * prx,const ::scoped_string & scopedstrMessage)
      {

         if(m_preceiver != nullptr)
         {
            m_preceiver->on_ipc_receive(prx,pszMessage);
         }

         // ODOW - on date of writing : return ignored by this windows implementation

         return nullptr;

      }

      void * rx::on_ipc_receive(rx * prx,int message,void * pdata,memsize len)
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

         return m_iQueue != -1;
      }






      void * rx::receive()
      {

         while(m_bRun)
         {

            m_bRunning = true;

            ssize_t  result;

            //int length;

            data_struct data;

            /* The length is essentially the size of the structure minus sizeof(mtype) */
            //length = sizeof(data_struct) - sizeof(long);

            memory mem;

            do
            {
               /*
               if((result = msgrcv(m_iQueue, &data, length, 20170101, IPC_NOWAIT)) == -1)
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
               return (void *) -1;
               }

               }
               */

               mem.assign(data.data,data.size);

               if (data.size < 512)
               {

                  break;

               }

            }
            while(true);

            if(data.request == 0)
            {

               string str;

               mem.to_string(str);

               on_ipc_receive(this, str);

            }
            else
            {

               on_ipc_receive(this,data.request,mem.get_data(),mem.get_size());

            }

         }

         m_bRunning = false;

         return nullptr;

      }

      ipc::ipc()
      {

         m_durationTimeout = (5000) * 11;

      }


      ipc::~ipc()
      {


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









