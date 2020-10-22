#include "framework.h"
#include "acme/platform/obj_ref_dbg.h"


action::action()
{

   action_common_construct();

}



action::action(const ::id& id, const ::action_context & actioncontext)
{

   action_common_construct();

   m_id = id;

   m_actioncontext = actioncontext;

}


action::action(const ::id& id, ::matter* pmatter) :
   m_pmatter(pmatter)
{

   action_common_construct();

   m_id = id;

}


action::action(::update* pupdate, const ::action_context& actioncontext) :
   m_pupdate(pupdate)
{

   action_common_construct();

   m_actioncontext = actioncontext;

}


action::action(::update* pupdate, ::matter* pmatter) :
   m_pupdate(pupdate),
   m_pchange(pmatter ? pupdate->change(pmatter) : nullptr)
{

   m_pmatter.reset(pmatter OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

   action_common_construct();

   if (m_pupdate)
   {

      m_id = m_pupdate->m_id;

   }

}


action::action(::update* pupdate, ::change * pchange, ::matter* pmatter) :
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


action::~action()
{

   m_pmatter.release(OBJ_REF_DBG_THIS_FUNCTION_LINE);

}


void action::action_common_construct()
{

   m_bRet = false;
   m_psender = nullptr;
   m_puserinteraction = nullptr;
   m_pcontrolevent = nullptr;
   //m_iUpdateSerial = 0;
   //m_bFork = false;

}


::estatus action::start_task()
{

   return ::success_none;

}


void action::reset_update(const ::id& id)
{

   m_pupdate = ::source::fork_update(id);

}


::estatus action::on_task()
{

   if (m_pupdate)
   {

      m_pmatter->apply(this);

      return ::success;

   }
   else
   {

      return m_pmatter->run();

   }

}


bool action::is_up_to_date() const
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


void action::set_up_to_date()
{

   m_pchange->set_up_to_date(m_pupdate);

}



