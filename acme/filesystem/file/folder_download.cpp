// Created by camilo on 2026-11-14 01:24 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
#include "platform.h"
#include "folder.h"
#include "folder_download.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/platform/application.h"


folder_download::folder_download()
{


}
folder_download::~folder_download()
{


}


void folder_download::initialize(::particle* pparticle)
{

   ::task::initialize(pparticle);

   defer_create_synchronization();

   defer_construct_newø(m_pmanualresethappening);

   branch_asynchronously();

}


void folder_download::add_download_path(const ::file::path& path, const ::particle_array & particleaNotify)
{

   _synchronous_lock synchronouslock(this->synchronization());

   auto pitem = create_newø<item>();

   pitem->m_path = path;

   pitem->m_particleaNotify = particleaNotify;

   m_itema.add(pitem);

   m_pmanualresethappening->set_happening();

}


void folder_download::run()
{

   _synchronous_lock synchronouslock(this->synchronization());

   while (task_get_run())
   {

      if (m_itema.is_empty())
      {

         m_pmanualresethappening->reset_happening();

         synchronouslock.unlock();

         m_pmanualresethappening->wait(1_s);

      }
      else
      {

         auto pitem = m_itema.pick_first();

         synchronouslock.unlock();

         try
         {

            pitem->m_pfile = m_pfolder->get_file(pitem->m_path);

         }
         catch (...)
         {


         }

         if (pitem->m_pfile && pitem->m_pfile.ok())
         {

            information("background file download worked : " + pitem->m_path);

         }
         else
         {

            information("background file download failed : " + pitem->m_path);

         }

         if (pitem->m_particleaNotify.has_element())
         {

            auto ptopic = create_topic("folder_download");

            ptopic->m_pparticle = pitem;

            for (auto& pparticleNotify : pitem->m_particleaNotify)
            {

               if (pparticleNotify)
               {

                  try
                  {

                     pparticleNotify->handle(ptopic, nullptr);

                  }
                  catch (...)
                  {


                  }

               }


            }

         }

      }

      synchronouslock._lock();

   }

}



