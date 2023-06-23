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


void source::add_handler(::matter* pmatter, bool bPriority)
{

   return add_signal_handler(::signal_handler( {e_use, pmatter}), bPriority);

}


void source::add_signal_handler(const ::signal_handler& signalhandler, bool bPriority)
{

   __defer_construct_new(m_psignalhandlera);

   if (bPriority)
   {

      m_psignalhandlera->insert_unique_at(0, signalhandler);

   }
   else
   {

      m_psignalhandlera->add_unique(signalhandler);

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
//   auto puserprimitive = dynamic_cast <::user::primitive *>(pusercallback);
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


void source::route(::topic * ptopic, ::context * pcontext)
{

   if (m_psignalhandlera)
   {

      for (auto & signalhandler : *m_psignalhandlera)
      {

         try
         {

            signalhandler(ptopic, pcontext);

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



