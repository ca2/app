#include "framework.h"
//#include "acme/platform/acme.h"
#include "object_reference_count_debug_.h"
//#include "acme/primitive/primitive/matter.h"


extern struct lparam_debug g_lparamdbg;


bool g_bEnableObjRefDbg = true;

//critical_section * g_pcsRefDbg = nullptr;


object_reference_count_debug::object_reference_count_debug()
{

}

object_reference_count_debug::~object_reference_count_debug()
{


}


void defer_delete(object_reference_count_debug* p)
{

   if (::is_null(p))
   {

      return;

   }

   delete p;

};


string object_name(matter* p)
{

   iptr i = (iptr)p;

   if (i < 16)
   {

      return as_string(i);

   }

   return typeid(*p).name();

}


#if OBJECT_REFERENCE_COUNT_DEBUG


void particle::add_ref_history(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEFINITION)
{

   if (!::acme::g_bAcme)
   {

      return;

   }

   if (!is_object_reference_count_debug_enabled())
   {

      return;

   }

   critical_section_lock synchronouslock(::platform::get() ? &::platform::get()->m_criticalsectionRefDbg : nullptr);

   if (g_bEnableObjRefDbg)
   {

      g_bEnableObjRefDbg = false;

      try
      {

         string strType = ::type(this).name();

         if (strType == "pacman::game")
         {

            informationf("pacman::game");

         }

         auto pobjectreferencecountdebug = object_reference_count_debug();

         string strNote = ::type(pReferer).name();

         if (::is_set(pszObjRefDbg))
         {

            strNote += " - " + string(pszObjRefDbg);

         }

         if (strType == "pacman::game")
         {

            informationf("pacman::game");

         }
         else if (strType.case_insensitive_contains("session"))
         {

//            if (m_pobjrefdbg->m_iStep == 39)
//            {
//
//               informationf("session");
//
//            }

         }

         pobjectreferencecountdebug->add(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

      }
      catch (...)
      {

      }

      g_bEnableObjRefDbg = true;

   }

}


void particle::dec_ref_history(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEFINITION)
{

   if (!::acme::g_bAcme)
   {

      return;

   }

   if (!is_object_reference_count_debug_enabled())
   {

      return;

   }

   critical_section_lock synchronouslock(& ::platform::get()->m_criticalsectionRefDbg);

   if (g_bEnableObjRefDbg)
   {

      m_pobjectreferencecountdebug->erase(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }

}


void particle::check_pending_releases()
{

   critical_section_lock synchronouslock(&::platform::get()->m_criticalsectionRefDbg);

   if (!is_object_reference_count_debug_enabled())
   {

      return;

   }

   if (::is_null(m_pobjectreferencecountdebug))
   {

      return;

   }

   if (m_pobjectreferencecountdebug->m_itema.has_element())
   {

      ::informationf("\nThere are pending releases (m_countReference=" + as_string(m_countReference) + "):\n");

      try
      {

         ::informationf("For " + ::type(this).name() + "(" + string(debug_note()) + ")\n");

      }
      catch (...)
      {

      }

      for (index iIndex = 0; iIndex < m_pobjectreferencecountdebug->m_itema.get_count(); iIndex++)
      {

         auto& item = m_pobjectreferencecountdebug->m_itema[iIndex];

         ::index iStep = item.m_iStep;

         ::particle * pobj = item.m_preferer;

         string str = item.m_strDebug;

         try
         {

            ::informationf("%4d: %4d %s", iIndex, iStep, str.c_str());

         }
         catch (...)
         {


         }

      }

      ::informationf("-------------------\n\n");

   }


}

#endif


//struct lparam_debug g_lparamdbg;
//
//
//CLASS_DECL_ACME struct lparam_debug & lparam_debug()
//{
//
//    return g_lparamdbg;
//
//}






#if OBJECT_REFERENCE_COUNT_DEBUG

object_reference_count_debug* particle::object_reference_count_debug()
{

   if (::is_null(m_pobjectreferencecountdebug) && is_object_reference_count_debug_enabled())
   {

      m_pobjectreferencecountdebug = new class object_reference_count_debug;

   }

   return m_pobjectreferencecountdebug;

}


#endif

