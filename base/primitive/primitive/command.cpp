#include "framework.h"


////namespace command
////{
////
////
////   command::command()
////   {
////
////      defer_create_mutex();
////
////   }
//
//
//   //command::~command()
//   //{
//
//   //}
//
//
//   bool command::contains(::create* pcreate) const
//   {
//
//      sync_lock sl(mutex());
//
//      return m_createaPending.contains(pcreate) || m_createaHistory.contains(pcreate) || pcreate == m_pcreate;
//
//   }
//
//
//   string command::command_line_text() const
//   {
//
//      if (!m_pcreate)
//      {
//
//         return "";
//
//      }
//
//      if (!m_pcreate->m_pcommandline)
//      {
//
//         return "";
//
//      }
//
//      return m_pcreate->m_pcommandline->m_strCommandLine;
//
//   }
//
//
//   //void command::on_create(::create* pcreate)
//   //{
//
//   //   if (m_varFile.is_empty())
//   //   {
//
//   //      m_varFile = pcreate->m_pcommandline->m_varFile;
//
//   //   }
//   //   else
//   //   {
//
//   //      m_varFile.vara().add(pcreate->m_pcommandline->m_varFile);
//
//   //   }
//
//   //   m_varQuery.propset().merge(pcreate->m_pcommandline->m_varQuery.propset());
//
//   //}
//
//
//   void command::add_create(::create* pcreate)
//   {
//
//      sync_lock sl(mutex());
//
//      if (::is_null(pcreate) || contains(pcreate))
//      {
//
//         throw invalid_argument_exception();
//
//      }
//
//      if (!m_pcreate)
//      {
//
//         m_pcreate = pcreate;
//
//         m_pcreate->m_bNew = true;
//
//         on_create(pcreate);
//
//      }
//      else
//      {
//
//         m_createaPending.add(pcreate);
//
//      }
//
//   }
//
//
//   __pointer(create) command::get_create()
//   {
//
//      sync_lock sl(mutex());
//
//      if (!m_pcreate || !m_pcreate->m_bNew)
//      {
//
//         if (m_pcreate)
//         {
//
//            m_pcreate.release();
//
//         }
//
//         if (m_createaPending.isEmpty())
//         {
//
//            return nullptr;
//
//         }
//
//         auto pcreate = m_createaPending[0];
//
//         m_pcreate = pcreate;
//
//         m_pcreate->m_bNew = true;
//
//         on_create(pcreate);
//
//         m_createaPending.remove_at(0);
//
//      }
//
//      m_createaHistory.add(m_pcreate);
//
//      m_pcreate->m_bNew = false;
//
//      return m_pcreate;
//
//   }
//
//
//} // namespace command



