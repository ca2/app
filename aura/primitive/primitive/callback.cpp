#include "framework.h"


callback & callback::operator = (const ::var& var)
{

   if (var.get_type() == ::type_callback)
   {

      m_pobjectTask = var.m_functionbase.m_pobjectTask;

   }
   else if (var.get_type() == ::type_pvar)
   {

      operator = (*var.m_pvar);

   }
   else if (var.get_type() == ::type_prop)
   {

      operator = (*var.m_pprop);

   }
   else
   {

      m_pobjectTask.release();

   }

   return *this;

}


//void callback::receive_response(const var& var)
//{
//
//   if (::is_null(m_pobjectTask))
//   {
//
//      return;
//
//   }
//
//   m_pobjectTask->receive_response(var);
//
//}


