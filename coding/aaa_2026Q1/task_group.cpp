// Created on 2024-05-02 03:30 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "application.h"
#include "impact_interface.h"
#include "integration.h"
#include "task.h"
#include "task_group.h"
#include "acme/constant/id.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/parallelization/queue.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/prototype/string/from_integer.h"


namespace coding
{


   task_group::task_group(
      ::coding::integration* pintegration,
      enum_task etaskGroup,
      const ::scoped_string& scopedstrId,
      const ::scoped_string& scopedstrName) :
      m_pintegration(pintegration),
      m_etaskGroup(etaskGroup),
      m_strId(scopedstrId),
      m_strName(scopedstrName)
   {
      m_straunion.add_array(m_straLine3);
      m_straunion.add_array(m_straPinnedLast2);
   }

   task_group::~task_group()
   {

   }



   void task_group::on_initialize_particle()
   {

      ::particle::on_initialize_particle();

      defer_create_synchronization();

   }


   void task_group::_do_task(::coding::task* ptask, const ::function < int(::coding::task* ptask) >& dotask)
   {

      int iExitCode = -1;

      try
      {

         iExitCode = dotask(ptask);

         //preempt(10_s);
         //iExitCode = 1;

      }
      catch (...)
      {

      }

      ptask->on_finished(iExitCode);

      //   m_pimpactinterface->on_lines_change();
         //auto iExitCode = _do_task(ptask, dotask);

         //if (iExitCode == 0)
         //{

         //   ptask->m_strTopic1 = "build successful";
         //}
         //else
         //{

         //   ptask->m_strTopic1 = "failed to build";

         //}

   }


   void task_group::do_tasks(const ::file::path& pathBuildFolder, const ::function < int(::coding::task* ptask) >& dotask)
   {

      m_pathBuildFolder = pathBuildFolder;

      m_taskaOk.clear();
      m_taskaNok.clear();

      m_taskaOkSpeech.clear();
      m_taskaNokSpeech.clear();

      m_taskaInitialQueue.clear();

      m_straLine3.clear();

      m_straPinnedLast2.clear();

      for (auto & ptask: m_taskmapTemplate.payloads())
      {

         if (m_pintegration->m_baTaskOrdinalEnable[ptask->m_etaskOrdinal])
         {

            m_taskaInitialQueue.add(ptask);

         }

      }

      if (m_taskaInitialQueue.is_empty())
      {

         return;

      }

      ::string strParallelization;

      auto iBuildingProcessorCount = node()->building_core_count(true);

      int iParallelization = -1;
      
      auto cQueued = queued_count();

      if (m_pintegration->should_task_group_tasks_be_sequential(m_etaskGroup))
      {

         iParallelization = iBuildingProcessorCount;

      }
      else
      {

         if (iBuildingProcessorCount >= cQueued)
         {

            iParallelization = iBuildingProcessorCount / cQueued;

         }

      }

      if (iParallelization >= 2)
      {

         m_strTaskParallelizationArguments.formatf(" --parallelization=%d", iParallelization);

      }

      m_strTaskInteractivenessArguments = " --non-interactive";


      //      ::file::path pathBuildFolder = m_pathBuildFolder;

      auto pacmedirectory = directory_system();

      //auto pacmefile = file_system();

      pacmedirectory->create(pathBuildFolder);

      pacmedirectory->change_current(pathBuildFolder);



      on_start();

      //auto& taska = ptaskgroup->m_taska;



      if (m_pintegration->should_task_group_tasks_be_sequential(m_etaskGroup))
      {

         m_pintegration->m_papp->fork([this, dotask]()
            {

               for (auto ptask : m_taskaInitialQueue)
               {

                  m_ptaskSequence = ptask;

                  m_pintegration->m_pimpactinterface->defer_select_sequential_task_ordinal(ptask->m_etaskOrdinal);

                  _do_task(ptask, dotask);

               }

               m_ptaskSequence->release();

               m_pintegration->m_pimpactinterface->defer_select_main_impact();

            });

      }
      else
      {

         for (auto ptask : m_taskaInitialQueue)
         {


            m_pintegration->m_papp->fork([this, ptask, dotask]()
               {

                  _do_task(ptask, dotask);

               });

         }


      }

   }


   bool task_group::is_sequential()
   {

      return m_pintegration->should_task_group_tasks_be_sequential(m_etaskGroup);

   }


   void task_group::_queue_speech()
   {

      application()->queue(id_speech)->async([this]()
         {

            _speak_completion(false);

         });

   }


   void task_group::defer_speak_completion()
   {

      _speak_completion(true);

   }


   void task_group::_speak_completion(bool bDefer)
   {

      _synchronous_lock synchronouslock(synchronization());

      auto taskaOkPendingSpeech = ok_pending_speech();

      auto taskaNokPendingSpeech = nok_pending_speech();

      auto taskaPendingSpeech = pending_speech();

      auto queueSize = queued_count();

      if (taskaOkPendingSpeech.size() == queueSize)
      {

         if (bDefer)
         {

            _queue_speech();

         }
         else
         {

            m_taskaOkSpeech.append(taskaOkPendingSpeech);

            synchronouslock.unlock();

            m_pintegration->_speak("All scheduled " + m_strSpeechName + " tasks succeeded.");

         }

      }
      else if (taskaNokPendingSpeech.size() == queued_count())
      {

         if (bDefer)
         {

            _queue_speech();

         }
         else
         {

            m_taskaNokSpeech.append(taskaNokPendingSpeech);

            synchronouslock.unlock();

            m_pintegration->_speak("All scheduled " + m_strSpeechName + " tasks failed.");

         }

      }
      else
      {

         if ((this->completed() && taskaOkPendingSpeech.has_element())
            || (this->is_sequential() && taskaOkPendingSpeech.has_element() && !taskaOkPendingSpeech.contains(m_ptaskSequence))
            || (m_pintegration->m_timeSpeechSpamControl.elapsed() > 10_s && taskaOkPendingSpeech.size() >= 4)
            || (m_pintegration->m_timeSpeechSpamControl.elapsed() > 20_s && taskaOkPendingSpeech.size() >= 2)
            || (m_pintegration->m_timeSpeechSpamControl.elapsed() > 30_s && taskaOkPendingSpeech.has_element()))
         {

            if (bDefer)
            {

               _queue_speech();

            }
            else
            {

               m_taskaOkSpeech.append(taskaOkPendingSpeech);

               synchronouslock.unlock();

               _speak_tasks(taskaOkPendingSpeech);

            }

         }

         if ((this->completed() && taskaNokPendingSpeech.has_element())
            || (this->is_sequential() && taskaOkPendingSpeech.has_element() && !taskaOkPendingSpeech.contains(m_ptaskSequence))
            || (m_pintegration->m_timeSpeechSpamControl.elapsed() > 10_s && taskaNokPendingSpeech.size() >= 4)
            || (m_pintegration->m_timeSpeechSpamControl.elapsed() > 20_s && taskaNokPendingSpeech.size() >= 2)
            || (m_pintegration->m_timeSpeechSpamControl.elapsed() > 30_s && taskaNokPendingSpeech.has_element()))
         {

            if (bDefer)
            {

               _queue_speech();

            }
            else
            {

               m_taskaNokSpeech.append(taskaNokPendingSpeech);

               synchronouslock.unlock();

               _speak_tasks(taskaNokPendingSpeech);

            }

         }

      }

   }


   void task_group::_speak_tasks(const ::pointer_array < ::coding::task >& taska)
   {

      if (taska.is_empty())
      {

         return;

      }

      if (taska.size() == 1)
      {

         _speak_task(taska.first());

         return;

      }

      ::string strMessage;

      strMessage = "Steps ";

      int i = 0;

      for (auto& ptask : taska)
      {

         strMessage += ::string_from((int)ptask->m_etaskOrdinal + 1);

         i++;

         if (i == taska.get_upper_bound())
         {

            strMessage += " and ";

         }
         else
         {

            strMessage += ", ";

         }

      }

      strMessage += " of " + taska.first()->m_ptaskgroup->m_strSpeechName;

      if (taska.first()->m_iExitCode == 0)
      {

         strMessage += " succeeded... ";

      }
      else
      {

         strMessage += " failed... ";

      }

      i = 0;

      for (auto& ptask : taska)
      {

         strMessage += m_pintegration->m_straTaskOrdinal[ptask->m_etaskOrdinal];

         i++;

         if (i == taska.get_upper_bound())
         {

            strMessage += " and ";

         }
         else
         {

            strMessage += ", ";

         }

      }

      m_pintegration->_speak(strMessage);

   }


   void task_group::_speak_task(::coding::task* ptask)
   {


      //if (ptask->m_ptaskgroup->m_etaskGroup == e_task_port)
      {


         ::string strPlat;

         if (ptask->m_etaskOrdinal & e_task_platform_x64)
         {

            strPlat = "x64";

         }
         else
         {

            strPlat = "Win32";

         }

         ::string strConf;

         if (ptask->m_etaskOrdinal & e_task_configuration_release)
         {

            strConf = "Release";

         }
         else
         {

            strConf = "Debug";

         }

         if (ptask->m_etaskOrdinal & e_task_configuration_static)
         {

            strConf = "Static " + strConf;

         }

         m_pintegration->speak((int)ptask->m_etaskOrdinal + 1, 8, ptask->m_ptaskgroup->m_strSpeechName + " " + strPlat + " " + strConf, ptask->m_iExitCode);

      }

   }



   ::pointer_array < task > task_group::ok_pending_speech()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto taskaPendingSpeech = m_taskaOk;

      taskaPendingSpeech -= m_taskaOkSpeech;

      return ::transfer(taskaPendingSpeech);

   }


   ::pointer_array < task > task_group::nok_pending_speech()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto taskaPendingSpeech = m_taskaNok;

      taskaPendingSpeech -= m_taskaNokSpeech;

      return ::transfer(taskaPendingSpeech);

   }


   ::pointer_array < task > task_group::pending_speech()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto taskaPendingSpeech = m_taskaInitialQueue;

      taskaPendingSpeech -= m_taskaOkSpeech;

      taskaPendingSpeech -= m_taskaNokSpeech;

      return ::transfer(taskaPendingSpeech);

   }


   void task_group::wait_to_complete()
   {

      while (!completed())
      {

         preempt(1_s);

         defer_speak_completion();

      }

      on_finished();


   }


   void task_group::on_start()
   {

      m_timeStart.Now();

   }


   void task_group::on_finished()
   {

      m_timeEnd.Now();

      if (all_ok())
      {

         m_straLine3.append_formatf(
            "All %s Platforms and Configuration Built Successfully!!",
            m_strName.c_str());

      }
      else if (all_failed())
      {

         m_straLine3.append_formatf(
            "All %s Platforms and Configuration Failed to Build!",
            m_strName.c_str());

      }
      else
      {

         m_straLine3.append_formatf(
            "%lld Succeeded and %lld Failed to Build!",
            ok_count(), nok_count());

      }

   }

   ::collection::index task_group::status_stage(const ::scoped_string& scopedstrLine)
   {

      return m_straStage.case_insensitive_substring_find_first(scopedstrLine);

   }


} // namespace coding


