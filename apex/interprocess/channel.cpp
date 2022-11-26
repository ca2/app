// From interprocess*.h/*.cpp by camilo on 2022-10-11 00:18 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "channel.h"
#include "caller.h"
#include "target.h"


namespace interprocess
{


   channel::channel()
   {

      m_timeTimeout = (5000) * 11;

   }


   channel::~channel()
   {


   }



   bool channel::close()
   {

      m_pcaller->close();

      m_ptarget->destroy();

      return true;

   }


   void channel::restart_apex_ipc()
   {
   }


   // calls restart if confirm_tx failed
   bool channel::ensure_caller(const ::string & strUri,const class time & timeTimeout)
   {

      try
      {

         m_pcaller->call(strUri, timeTimeout);

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   //bool channel::ensure_caller(int message, void * pdata, int len, time timeTimeout)
   //{

   //   if (message == WM_APP + WM_USER)
   //   {

   //      if (!m_pcaller->is_tx_ok())
   //      {

   //         restart_apex_ipc();

   //         return false;

   //      }

   //   }
   //   else
   //   {

   //      try
   //      {

   //         m_pcaller->send(message, pdata, len, timeTimeout);

   //      }
   //      catch (...)
   //      {

   //         restart_apex_ipc();

   //         return false;

   //      }

   //   }

   //   return true;

   //}


   //#ifdef WINDOWS
   //
   //
   //      bool channel::open_ab(const ::string & pszKey, const ::string & pszModule, launcher * plauncher)
   //      {
   //
   //         m_strChannel = pszKey;
   //
   //         m_ptarget->m_ptarget = this;
   //
   //         string strChannelRx = m_strChannel + "-a";
   //
   //         string strChannelTx = m_strChannel + "-b";
   //
   //         if (!m_ptarget->create(strChannelRx.c_str()))
   //         {
   //
   //            return false;
   //
   //         }
   //
   //         if (!m_pcaller->open(strChannelTx.c_str(), plauncher))
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

        /* bool channel::open_ba(const ::string & pszKey, const ::string & pszModule, launcher * plauncher)
         {

            m_strChannel = pszKey;

            m_ptarget->m_ptarget = this;

            string strChannelRx = m_strChannel + "-b";

            string strChannelTx = m_strChannel + "-a";

            if (!m_ptarget->create(strChannelRx.c_str()))
            {

               return false;

            }

            if (!m_pcaller->open(strChannelTx.c_str(), plauncher))
            {

               return false;

            }

            return true;

         }

   #else*/


   bool channel::open_ab(const ::string & pszKey, launcher * plauncher)
   {

      m_strChannel = pszKey;

      //m_ptarget->m_phandler = this;

      string strChannelRx = m_strChannel + "-a";

      string strChannelTx = m_strChannel + "-b";

      m_ptarget->create(strChannelRx.c_str());

      m_pcaller->open(strChannelTx.c_str(), plauncher);

      return true;

   }


   bool channel::open_ba(const ::string & pszKey, launcher * plauncher)
   {

      m_strChannel = pszKey;

      //m_ptarget->m_listenera.add_unique(this);

      string strChannelRx = m_strChannel + "-b";

      string strChannelTx = m_strChannel + "-a";

      m_ptarget->create(strChannelRx.c_str());

      m_pcaller->open(strChannelTx.c_str(), plauncher);

      return true;

   }


   bool channel::is_channel_ok()
   {

      return m_ptarget->is_target_ok() && m_pcaller->is_caller_ok();

   }


} // namespace channel



