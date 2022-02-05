// Created by camilo on day after ThomasBirthday2021 09:07 BRT
#include "framework.h"


void source::add_handler(::matter * pmatter, bool bPriority)
{

   //auto estatus = 
   __defer_construct_new(m_phandlera);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   if (bPriority)
   {

      m_phandlera->insert_at(0, pmatter);

   }
   else
   {

      m_phandlera->add(pmatter);

   }

   //return estatus;

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

   if (m_phandlera)
   {

      for (auto & phandler : *m_phandlera)
      {

         try
         {

            phandler->handle(ptopic, pcontext);

         }
         catch (...)
         {

         }

         if (ptopic->m_pextendedtopic->m_bRet)
         {

            break;

         }

      }

   }

}



