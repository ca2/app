#include "framework.h"
#include "acme/platform/obj_ref_dbg.h"


namespace promise
{


   subject::subject()
   {

      action_common_construct();

   }


   subject::subject(const ::id &id, const ::action_context &actioncontext)
   {

      action_common_construct();

      m_id = id;

      m_actioncontext = actioncontext;

   }


   subject::subject(const ::id &id, ::matter *pmatter) :
           m_pmatter(pmatter)
   {

      action_common_construct();

      m_id = id;

   }


   subject::subject(::promise::handler * phandler, const ::action_context & actioncontext) :
      m_phandler(phandler)
   {

      action_common_construct();

      m_actioncontext = actioncontext;

   }


   subject::subject(::promise::handler * phandler, ::matter *pmatter) :
           m_phandler(phandler),
           m_pcontext(pmatter ? phandler->context(pmatter) : nullptr)
   {

      m_pmatter.reset(pmatter OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

      action_common_construct();

      if (m_phandler)
      {

         m_id = m_phandler->m_id;

      }

   }


   subject::subject(::promise::handler * phandler, ::promise::context * pcontext, ::matter * pmatter) :
      m_phandler(phandler),
      m_pcontext(pcontext)
   {

      m_pmatter.reset(pmatter OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

      action_common_construct();

      if (m_phandler)
      {

         m_id = m_phandler->m_id;

      }

   }


   subject::~subject()
   {

      m_pmatter.release(OBJ_REF_DBG_THIS_FUNCTION_LINE);

   }


   void subject::action_common_construct()
   {

      m_bRet = false;
      m_psender = nullptr;
      m_puserinteraction = nullptr;
      m_pcontrolevent = nullptr;
      //m_iUpdateSerial = 0;
      //m_bFork = false;

   }


   ::estatus subject::start_task()
   {

      return ::success_none;

   }


   void subject::reset_update(const ::id &id)
   {

      //m_phandler = ::promise::backing::fork_handler(id);

   }


   ::estatus subject::on_task()
   {

      if (m_phandler)
      {

         m_phandler->process(this);

         return ::success;

      }
      else
      {

         return m_pmatter->run();

      }

   }


   bool subject::is_up_to_date() const
   {

      if (::is_null(m_pcontext))
      {

         return false;

      }

      if (m_pcontext->m_iUpdateSerial < 0)
      {

         return false;

      }

      if (m_phandler->m_iUpdateSerial < 0)
      {

         return false;

      }

      return m_pcontext->is_up_to_date(m_phandler);

   }


   void subject::set_up_to_date()
   {

      m_pcontext->set_up_to_date(m_phandler);

   }


} // namespace promise



