#include "framework.h"
#include "base/user/user/_component.h"


namespace aura
{


   context_thread::context_thread()
   {

   }


   context_thread::~context_thread()
   {

   }


   void context_thread::on_command_create(::create* pcreate)
   {

      if (m_payloadFile.is_empty())
      {

         m_payloadFile = pcreate->m_payloadFile;

      }
      else
      {

         m_payloadFile.payloada().add(pcreate->m_payloadFile);

      }

      //).merge(pcreate->));

      get_property_set().merge(pcreate->));


   }

   bool context_thread::contains(::create* pcreate) const
   {

      if (::is_null(pcreate))
      {

         return false;

      }

      synchronous_lock synchronouslock(mutex());

      return m_createaPending.predicate_contains([&pcreate](auto& p) {return p.get() == pcreate; })
      || m_createaHistory.predicate_contains([&pcreate](auto& p) {return p.get() == pcreate; })
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


   void context_thread::destroy()
   {

      ::thread::destroy();

      ::context::destroy();

   }

   //void command::on_create(::create* pcreate)
   //{

   //   if (m_payloadFile.is_empty())
   //   {

   //      m_payloadFile = pcreate->m_payloadFile;

   //   }
   //   else
   //   {

   //      m_payloadFile.payloada().add(pcreate->m_payloadFile);

   //   }

   //   ).merge(pcreate->));

   //}


   void context_thread::add_create(::create* pcreate)
   {

      synchronous_lock synchronouslock(mutex());

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

      synchronous_lock synchronouslock(mutex());

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

         m_createaPending.erase_at(0);

      }

      m_createaHistory.add(m_pcreate);

      m_pcreate->m_bNew = false;

      return m_pcreate.get();

   }


} // namespace aura



