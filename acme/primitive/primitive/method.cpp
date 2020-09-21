#include "framework.h"


method & method::operator = (const ::var& var)
{
   
   if (var.get_type() == ::type_method)
   {

      m_pobjectTask = var.m_functionbase.m_pobjectTask;

   }
   else
   {

      m_pobjectTask.release();

   }

   return *this;

}


