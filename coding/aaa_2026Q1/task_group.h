// From integration.h on 2024-05-02 03:25 <3ThomasBorregaardSørensen!!
#pragma once


#include "_constant.h"
#include "acme/constant/integration.h"
#include "acme/prototype/collection/array_union.h"


namespace coding
{



   class CLASS_DECL_CODING task_group :
      virtual public ::particle
   {
   public:

      ::string                                        m_strId;
      ::string                                        m_strName;
      ::string                                        m_strSpeechName;
      enum_task                                       m_etaskGroup;
      ::string                                        m_strTopic1;
      ::string                                        m_strTopic12;

      //::collection::count                                    m_countQueued;
      string_array                                    m_straPinnedLast2;
      string_array                                    m_straLine3;
      ::array_union < string_array >                  m_straunion;
      ::numeric_array_base<::coding::enum_index>      m_eindexa;
      ::pointer<::coding::integration>           m_pintegration;

      ::numeric_array_base<::coding::enum_task>       m_etaskaOrdinal;

      ::pointer < task >                              m_ptaskSequence;
      ::string_array                                  m_straStage;
      ::map < enum_task, ::pointer < task > >                        m_taskmapTemplate;
      ::pointer_array < task >                        m_taskaInitialQueue;
      ::pointer_array < task >                        m_taskaOk;
      ::pointer_array < task >                        m_taskaNok;
      ::pointer_array < task >                        m_taskaOkSpeech;
      ::pointer_array < task >                        m_taskaNokSpeech;
      class ::time                                    m_timeStart;
      class ::time                                    m_timeEnd;
      ::file::path                                    m_pathBuildFolder;

      ::string                                        m_strTaskParallelizationArguments;
      ::string                                        m_strTaskInteractivenessArguments;


      task_group(::coding::integration * pintegration,
         enum_task etaskGroup,
         const ::scoped_string& scopedstrId,
         const ::scoped_string& scopedstrName
         );

      ~task_group() override;

      void on_initialize_particle() override;

      ::collection::count queued_count() const { return m_taskaInitialQueue.count(); }

      ::collection::count ok_count() const { return m_taskaOk.size(); }

      ::collection::count nok_count() const { return m_taskaNok.size(); }

      //::collection::count queued_count() const { return m_countQueued; }

      ::collection::count completed_count() const { return ok_count() + nok_count(); }

      bool completed() const { return completed_count() == queued_count(); }

      bool all_ok() const { return ok_count() == queued_count(); }

      bool all_failed() const { return nok_count() == queued_count(); }

      ::pointer_array < task > ok_pending_speech();
      ::pointer_array < task > nok_pending_speech();
      ::pointer_array < task > pending_speech();
      


      //enum_task etask() const { return (enum_task)(m_etaskGroup | m_etaskOrdinal); }

      void wait_to_complete();
      void on_start();
      void on_finished();

      virtual ::collection::index status_stage(const ::scoped_string& scopedstrLine);

      void do_tasks(const ::file::path & pathBuildFolder, const ::function < int(::coding::task* ptask) > & dotask);

      void _do_task(::coding::task* ptask, const ::function < int(::coding::task* ptask) >& dotask);

      class ::time elapsed() const { return m_timeEnd - m_timeStart; }

      void defer_speak_completion();

      void _speak_completion(bool bDefer);

      void _queue_speech();

      bool is_sequential();

      virtual void _speak_task(::coding::task* ptask);

      /// <summary>
      /// All tasks in array must have same type of exit code (either they should had all failed, or all succeeded)
      /// </summary>
      /// <param name="taskOk"></param>
      virtual void _speak_tasks(const ::pointer_array < ::coding::task >& task);

   };


} // namespace coding



