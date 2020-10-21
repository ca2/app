#include "framework.h"


namespace apex
{

   
   context_thread::context_thread()
   {

   }


   context_thread::~context_thread()
   {

   }


   void context_thread::on_command_create(::create* pcreate)
   {

      if (m_varFile.is_empty())
      {

         m_varFile = pcreate->m_pcommandline->m_varFile;

      }
      else
      {

         m_varFile.vara().add(pcreate->m_pcommandline->m_varFile);

      }

      //m_varQuery.propset().merge(pcreate->m_pcommandline->m_varQuery.propset());

      get_property_set().merge(pcreate->m_pcommandline->m_varQuery.propset());


   }

   bool context_thread::contains(::create* pcreate) const
   {

      if (::is_null(pcreate))
      {

         return false;

      }

      sync_lock sl(mutex());

      return m_createaPending.pred_contains([&pcreate](auto& p) {return p.get() == pcreate; })
      || m_createaHistory.pred_contains([&pcreate](auto& p) {return p.get() == pcreate; })
      || m_pcreate.get() == pcreate;

   }


   string context_thread::command_line_text() const
   {

      if (!m_pcreate)
      {

         return "";

      }

      if (!m_pcreate->m_pcommandline)
      {

         return "";

      }

      return m_pcreate->m_pcommandline->m_strCommandLine;

   }


   void context_thread::finalize()
   {

      ::thread::finalize();

      ::context::finalize();

   }


   ::task_pool* context_thread::taskpool()
   {

      __defer_construct_new(m_ptaskpool);

      return m_ptaskpool;

   }


   //void command::on_create(::create* pcreate)
   //{

   //   if (m_varFile.is_empty())
   //   {

   //      m_varFile = pcreate->m_pcommandline->m_varFile;

   //   }
   //   else
   //   {

   //      m_varFile.vara().add(pcreate->m_pcommandline->m_varFile);

   //   }

   //   m_varQuery.propset().merge(pcreate->m_pcommandline->m_varQuery.propset());

   //}


   void context_thread::add_create(::create* pcreate)
   {

      sync_lock sl(mutex());

      if (::is_null(pcreate) || contains(pcreate))
      {

         throw invalid_argument_exception();

      }

      if (!m_pcreate)
      {

         __refer(m_pcreate, pcreate);

         m_pcreate->m_bNew = true;

         on_command_create(pcreate);

      }
      else
      {

         __refer(m_createaPending.add_new(), pcreate);

      }

   }


   create * context_thread::get_create()
   {

      sync_lock sl(mutex());

      if (!m_pcreate || !m_pcreate->m_bNew)
      {

         if (m_pcreate)
         {

            __release(m_pcreate);

         }

         if (m_createaPending.isEmpty())
         {

            return nullptr;

         }

         auto pcreate = m_createaPending[0];

         m_pcreate = pcreate;

         m_pcreate->m_bNew = true;

         on_command_create(pcreate);

         m_createaPending.remove_at(0);

      }

      auto & pcreateNew = m_createaHistory.add_new();

      __m_bind(this, pcreateNew, m_pcreate OBJ_REF_DBG_ADD_THIS_FUNCTION_LINE);

      m_pcreate->m_bNew = false;

      return m_pcreate.get();

   }


} // namespace apex



