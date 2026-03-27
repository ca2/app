// From integration.h on 2024-05-02 02:15 <3ThomasBorregaardSørensen!!
#pragma once


#include "_constant.h"
#include "acme/constant/integration.h"


namespace coding
{



   class CLASS_DECL_CODING task :
      virtual public ::particle
   {
   public:

      ::pointer < task_group >   m_ptaskgroup;
      ::string    m_strLabel2;
      ::string    m_strSpeechLabel;
      ::string    m_strCommand;
      enum_task   m_etaskOrdinal;
      ::string                                     m_strTopic1;
      ::string                                     m_strTopic12;

      ::numeric_array_base<::coding::enum_index>   m_eindexa;
      ::pointer<::coding::log_interface>   m_plog;
      class ::time m_timeStart;
      class ::time m_timeEnd;



      int m_iExitCode;
      task(task_group * ptaskgroup,
         const ::scoped_string & scopedstrLabel,
         const ::scoped_string& scopedstrSpeechLabel,
         const ::scoped_string& scopedstrCommand,
         enum_task etaskOrdinal);

      ~task() override;

      void on_initialize_particle() override;

      enum_task etask() const;

      virtual void on_update_topic();

      virtual void on_start();

      virtual void on_finished(int iExitCode);

      class ::time elapsed() const { return m_timeEnd - m_timeStart; }


      virtual ::collection::index status_index(const ::scoped_string& scopedstrLine);



   };


} // namespace coding



