// Created on 2021-04-29 1:03 PM BRT <3TBS_!! Second celebration of Mummis Birthday 70!!
#include "framework.h"
#include "translator.h"


exception_translator::exception_translator()
{

   m_bSet = false;

}


exception_translator::~exception_translator()
{


}


bool exception_translator::attach()
{

   if (!m_bSet)
   {

      m_bSet = true;

      return true;

   }
   else
   {

      return false;

   }

}


bool exception_translator::detach()
{

   if (m_bSet)
   {

      m_bSet = false;

      return true;

   }
   else
   {

      return false;

   }

}


#ifdef WINDOWS


string exception_translator::_get_standard_exception_name(u32 uiCode)
{

   return "";

}


string exception_translator::_get_standard_exception_description(u32 uiCode)
{

   return "";

}


#endif



