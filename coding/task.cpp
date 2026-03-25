// Created on 2024-05-02 02:26 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "application.h"
//#include "impact_interface.h"
#include "integration.h"
#include "task.h"
#include "task_group.h"
#include "acme/constant/id.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/queue.h"
#include "acme/platform/node.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/prototype/string/from_integer.h"


namespace coding
{


   task::task(task_group* ptaskgroup,
      const ::scoped_string& scopedstrLabel,
      const ::scoped_string& scopedstrSpeechLabel,
      const ::scoped_string& scopedstrCommand,
      enum_task etaskOrdinal) :
      m_ptaskgroup(ptaskgroup),
      m_strLabel2(scopedstrLabel),
      m_strSpeechLabel(scopedstrSpeechLabel),
      m_strCommand(scopedstrCommand),
      m_etaskOrdinal(etaskOrdinal)
   {


   }


   task::~task()
   {

   }


   void task::on_initialize_particle()
   {

      ::particle::on_initialize_particle();

      defer_create_synchronization();

   }


   enum_task task::etask() const
   {

      enum_task etask;

      etask = (enum_task)(m_ptaskgroup->m_etaskGroup | m_etaskOrdinal);

      return etask;

   }


   void task::on_update_topic()
   {

      {

         _synchronous_lock synchronous_lock(m_ptaskgroup->synchronization());

         ::string strStatus;

         strStatus.formatf("[%d] %s> %s", (int)m_etaskOrdinal + 1, m_strTopic1.c_str(), m_strTopic12.c_str());

         m_ptaskgroup->m_straPinnedLast2.set_at_grow(m_etaskOrdinal, strStatus);

      }

   }

   void task::on_start()
   {

      m_eindexa = m_ptaskgroup->m_eindexa;

      m_timeStart.Now();



   }


   void task::on_finished(int iExitCode)
   {

      m_timeEnd.Now();

      m_iExitCode = iExitCode;

      auto elapsed = this->elapsed();

      ::string strElapsed = datetime()->elapsed_time_text(elapsed);

      {

         _synchronous_lock synchronouslock(this->synchronization());

         if (m_iExitCode == 0)
         {

            m_strTopic12.formatf("Completed Successfully (%s)!!", strElapsed.c_str());

         }
         else
         {

            m_strTopic12.formatf("Failed with exit code %d (%s)", m_iExitCode, strElapsed.c_str()) ;

         }

         m_plog->m_straLog.add(m_strTopic12);

      }

      on_update_topic();

      {

         _synchronous_lock synchronouslock(m_ptaskgroup->synchronization());

         if (m_iExitCode == 0)
         {

            m_ptaskgroup->m_taskaOk.add(this);

         }
         else
         {

            m_ptaskgroup->m_taskaNok.add(this);

         }

      }

      {

         auto pintegration = m_ptaskgroup->m_pintegration;

         _synchronous_lock synchronouslock(pintegration->synchronization());

         auto pitem = pintegration->summary_item(m_strLabel2);

         pitem->m_timeStore = elapsed;
         
         if (m_iExitCode == 0)
         {
            
            pitem->m_strStatus="✓ " + m_strLabel2;

         }
         else
         {

            pitem->m_strStatus="✗ " + m_strLabel2;

            pintegration->m_iFailedTasks++;

         }

         //if (m_ptaskgroup->completed_count() <= 2)
         //{

         //   preempt(10_s);

         //}
         //pintegration->m_papp->fork([this, pintegration]()
           // {

         pintegration->m_pimpactinterface->on_lines_change();

      }

      m_ptaskgroup->defer_speak_completion();

   }



   ::collection::index task::status_index(const ::scoped_string& scopedstrLine)
   {

      for (::collection::index iIndex = 0; iIndex < m_eindexa.size(); iIndex++)
      {

         auto eindex = m_eindexa[iIndex];

         ::string strIndex;

         strIndex = m_ptaskgroup->m_pintegration->m_pintegrationcontext->build_index_radix(eindex);

         if (scopedstrLine.case_insensitive_contains(strIndex))
         {

            return iIndex;

         }

      }

      return -1;

   }


} // namespace coding


