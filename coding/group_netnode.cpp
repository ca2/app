// Created by camilo on 2024-02-24 03:52 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "application.h"
#include "group_netnode.h"
#include "integration.h"
#include "apex/networking/http/context.h"
#include "apex/platform/context.h"


namespace coding
{


   group_netnode::group_netnode()
   {


   }


   group_netnode::~group_netnode()
   {

   }


   void group_netnode::initialize_group_netnode(const ::string_array& straNetnode)
   {

      m_straNetnode = straNetnode;

   }


   ::collection::count group_netnode::get_size()
   {

      return m_straNetnode.size();

   }


   enum_integrate group_netnode::get_eintegrate(::collection::index i)
   {

      return e_integrate_netnode;

   }


   ::string group_netnode::get_name(::collection::index i)
   {

      return m_straNetnode[i];

   }



   void group_netnode::start_integration(::coding::integration * pintegration)
   {

      m_psemaphore = allocateø::semaphore(0, (int)m_straNetnode.size());

      for (auto strNetnode : m_straNetnode)
      {

         application()->fork([this, pintegration, strNetnode]()
            {

               try
               {

                  pintegration->integrate_netnode(strNetnode);

               }
               catch (...)
               {


               }

               m_psemaphore->lock();

            });

         preempt(5_s);

      }

   }


   //void integration::start_netnode(const ::scoped_string& scopedstrNetnode)
   //{

   //   ::string strUrl;

   //   ::string strIntegration;

   //   strIntegration = m_strIntegration;

   //   strUrl = "http://" + scopedstrNetnode + "/call_integration?integration=" + ::url::encode(strIntegration);

   //   main_status("integrate netnode : " + scopedstrNetnode);

   //   m_straLine2.add("integrate netnode : " + scopedstrNetnode);

   //   m_pimpactinterface->on_lines_change();

   //   ::property_set set;

   //   m_pcontext->m_papexcontext->http().get(strUrl, set);

   //   m_straLine2.add("commanded integrate netnode : " + scopedstrNetnode);

   //   m_pimpactinterface->on_lines_change();


   //}


   //void integration::start_netnode(const ::scoped_string& scopedstrNetnode)
   //{

   //   while (true)
   //   {

   //      ::string strRunningStatus = m_pgroupnetnode->running_status();

   //      if (strRunningStatus == "no")
   //      {

   //         break;

   //      }

   //      ::string_array stra;

   //      stra.add_lines(strRunningStatus);

   //      {

   //         _synchronous_lock synchronous_lock(this->synchronization());

   //         m_straLine2.append_container(stra);

   //      }

   //      m_pimpactinterface->on_lines_change();

   //      preempt(3_s);



   //   }

   //}


   void group_netnode::wait_to_finish()
   {

      m_psemaphore->wait(5_days);

   }


} // namespace coding



