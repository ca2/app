#include "framework.h"
#include "acme/platform/obj_ref_dbg.h"


namespace promise
{


   update::update()
   {

      action_common_construct();

   }


   update::update(const ::id &id, const ::action_context &actioncontext)
   {

      action_common_construct();

      m_id = id;

      m_actioncontext = actioncontext;

   }


   update::update(const ::id &id, ::matter *pmatter) :
           m_pmatter(pmatter)
   {

      action_common_construct();

      m_id = id;

   }


   update::update(::manager *pupdate, const ::action_context &actioncontext) :
           m_pupdate(pupdate)
   {

      action_common_construct();

      m_actioncontext = actioncontext;

   }


   update::update(::manager *pupdate, ::matter *pmatter) :
           m_pupdate(pupdate),
           m_pchange(pmatter ? pupdate->machine(pmatter) : nullptr)
   {

      m_pmatter.reset(pmatter OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

      action_common_construct();

      if (m_pupdate)
      {

         m_id = m_pupdate->m_id;

      }

   }


   update::update(::manager *pupdate, ::machine *pchange, ::matter *pmatter) :
           m_pupdate(pupdate),
           m_pchange(pchange)
   {

      m_pmatter.reset(pmatter OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

      action_common_construct();

      if (m_pupdate)
      {

         m_id = m_pupdate->m_id;

      }

   }


   update::~update()
   {

      m_pmatter.release(OBJ_REF_DBG_THIS_FUNCTION_LINE);

   }


   void update::action_common_construct()
   {

      m_bRet = false;
      m_psender = nullptr;
      m_puserinteraction = nullptr;
      m_pcontrolevent = nullptr;
      //m_iUpdateSerial = 0;
      //m_bFork = false;

   }


   ::estatus update::start_task()
   {

      return ::success_none;

   }


   void update::reset_update(const ::id &id)
   {

      m_pupdate = ::source::fork_update(id);

   }


   ::estatus update::on_task()
   {

      if (m_pupdate)
      {

         m_pmatter->process(this);

         return ::success;

      }
      else
      {

         return m_pmatter->run();

      }

   }


   bool update::is_up_to_date() const
   {

      if (::is_null(m_pchange))
      {

         return false;

      }

      if (m_pchange->m_iUpdateSerial < 0)
      {

         return false;

      }

      if (m_pupdate->m_iUpdateSerial < 0)
      {

         return false;

      }

      return m_pchange->is_up_to_date(m_pupdate);

   }


   void update::set_up_to_date()
   {

      m_pchange->set_up_to_date(m_pupdate);

   }


} // namespace promise



