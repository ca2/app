#include "framework.h"


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


action::action(::update* pupdate, ::matter* pmatter) :
   m_pupdate(pupdate),
   m_pchange(pupdate ? pupdate->change(pmatter) : nullptr),
   m_pmatter(pmatter)
{

   action_common_construct();

   if (m_pupdate)
   {

      m_id = m_pupdate->m_id;

   }

}


action::action(::update* pupdate, ::change * pchange, ::matter* pmatter) :
   m_pupdate(pupdate),
   m_pchange(pchange),
   m_pmatter(pmatter)
{ 

   action_common_construct();

   if (m_pupdate)
   {

      m_id = m_pupdate->m_id;

   }

}


action::~action()
{

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


::estatus action::__thread_proc()
{


   try
   {

      if(m_pmatter)
      {

         if (m_pupdate)
         {

            m_pmatter->apply(this);

         }
         else
         {

            return m_pmatter->__thread_proc();

         }

      }

   }
   catch (...)
   {

   }

   return ::success;

}


bool action::is_up_to_date() const
{

   if (::is_null(m_pchange))
   {

      return false;

   }

   return m_pchange->is_up_to_date(m_pupdate);

}


void action::set_up_to_date()
{

   m_pchange->set_up_to_date(m_pupdate);

}



