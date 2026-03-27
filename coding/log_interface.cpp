// Created 2024-05-01 19:05 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "application.h"
#include "impact_interface.h"
#include "log_interface.h"
#include "tab_impact.h"
#include "task.h"
#include "task_group.h"
#include "acme/constant/impact.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/integration_context.h"
#include "aura/user/user/interaction.h"
#include "berg/user/user/tab_pane.h"
#include "coding/integration.h"


//CLASS_DECL_ACME const char* build_step_stage_prefix();
//CLASS_DECL_ACME const char* build_step_radix(::coding::enum_step estep);

namespace coding
{


   void log_interface::on_trace(enum_trace_level etracelevel, const ::scoped_string& scopedstrLine, bool bCarriage)
   {

      ::string s(scopedstrLine);

      if (s.length() > 256)
      {

         s.truncate(256);

      }

      {

         _synchronous_lock synchronouslock(synchronization());

         defer_status(scopedstrLine);

         ::string str;

         str.formatf("%c: %s", trace_level_letter(etracelevel), s.c_str());

         m_straLog.feed_line(str, bCarriage);

      }

      on_lines_change();

   }




   void log_interface::defer_status(const ::scoped_string& scopedstrLine)
   {

      if (!scopedstrLine.case_insensitive_contains(m_ptask->m_ptaskgroup->m_pintegration->m_pintegrationcontext->build_index_stage_prefix()))
      {

         return;

      }

      m_iIndex = m_ptask->status_index(scopedstrLine);

      m_iStage = m_ptask->m_ptaskgroup->status_stage(scopedstrLine);

      if (m_iIndex >= 0 && m_iStage >= 0)
      {

         m_ptask->m_strTopic12.formatf("%s %s...",
            m_ptask->m_ptaskgroup->m_pintegration->m_pintegrationcontext->build_index_radix(m_ptask->m_eindexa[m_iIndex]).c_str(),
            m_ptask->m_ptaskgroup->m_straStage[m_iStage].c_str());

         m_ptask->on_update_topic();

      }

   }

   
   ::user::interaction* log_interface::userinteraction()
   {

      auto ptask = m_ptask;
      if (!ptask) return nullptr;
      auto ptaskgroup = ptask->m_ptaskgroup;
      if (!ptaskgroup) return nullptr;
      auto pintegration = ptaskgroup->m_pintegration;
      if (!pintegration) return nullptr;
      auto ptab = pintegration->m_papp->m_ptabimpact->get_tab_by_id((::enum_impact)((int) e_impact_multitasking | (int) ptask->m_etaskOrdinal));
      if (!ptab) return nullptr;
      auto pplaceholder = ptab->m_pplaceholder;
      if (!pplaceholder) return nullptr; 
      return pplaceholder;


   }


   void log_interface::on_lines_change()
   {

      auto puserinteraction = userinteraction();

      if (puserinteraction)
      {

         if (puserinteraction->is_window_visible())
         {

            puserinteraction->set_need_redraw();
            puserinteraction->post_redraw();

         }

      }

   }


} // namespace coding



