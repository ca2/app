// Created by camilo on day after ThomasBirthday2021 09:07 BRT
#include "framework.h"
#include "source.h"
#include "acme/handler/topic.h"


source::source()
{


}


source::~source()
{



}


void source::destroy()
{

   m_particlea.clear();

   ::particle::destroy();

}


//void source::add_handler(::particle * pparticle, bool bPriority)
//{
//   return add_signal_handler(::signal_handler( {e_use, pparticle}), bPriority);
//
//
//}
//
//
//void source::add_signal_handler(const ::signal_handler& signalhandler, bool bPriority)
//{
//
//   __defer_construct_new(m_psignalhandlera);
//
//   if (bPriority)
//   {
//
//      m_psignalhandlera->insert_unique_at(0, signalhandler);
//
//   }
//   else
//   {
//
//      m_psignalhandlera->add_unique(signalhandler);
//
//   }
//
//}



void source::add_handler(::particle * pparticle, bool bPriority)
{

   if (::is_null(pparticle))
   {

      throw ::exception(error_bad_argument);

   }

   if(m_particlea.contains(pparticle))
   {
      
      return;
      
   }

   if (bPriority)
   {

      m_particlea.insert_at(0, pparticle);

   }
   else
   {

      m_particlea.add(pparticle);

   }

}


//void source::add_handler(::matter * pmatter, const ::atom & idChild, bool bPriority)
//{
//
//   if (::is_null(pmatter))
//   {
//
//      return error_null_pointer;
//
//   }
//
//   auto puserprimitive = dynamic_cast <::user::interaction_base *>(pusercallback);
//
//   if (::is_null(puserprimitive))
//   {
//
//      return error_null_pointer;
//
//   }
//
//   auto pchild = puserprimitive->get_primitive_by_id(idChild);
//
//   if (::is_null(pchild))
//   {
//
//      return error_null_pointer;
//
//   }
//
//   auto estatus = pchild->add_control_event_handler(this, bPriority);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   return estatus;
//
//}


void source::route(::topic * ptopic, ::handler_context * phandlercontext)
{

   //if (m_psignalhandlera)
   {

      for (auto & pparticle : m_particlea)
      {

         try
         {

            pparticle->call_handle(ptopic, phandlercontext);

         }
         catch (...)
         {

         }

         if (ptopic->m_bRet)
         {

            break;

         }

      }

   }

}


void source::on_topic(const ::atom & atom, ::particle * pparticle, ::handler_context * pcontext)
{

   notify_topic(atom, pparticle, pcontext);

}


void source::notify_topic(const ::atom & atom, ::particle * pparticle, ::handler_context * phandlercontext)
{

   auto ptopic = create_topic(atom);

   if (::is_set(pparticle))
   {

      ptopic->m_pparticle = pparticle;

   }
   else
   {

      ptopic->m_pparticle = this;

   }

   call_handle(ptopic, phandlercontext);

   route(ptopic, phandlercontext);

}



