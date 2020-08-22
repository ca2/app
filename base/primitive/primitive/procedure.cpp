#include "framework.h"


procedure & procedure::operator = (const ::var& var)
{
   
   if (var.get_type() == ::type_procedure)
   {

      m_pobjectTask = var.m_functionbase.m_pobjectTask;

   }
   else
   {

      m_pobjectTask.release();

   }

   return *this;

}


