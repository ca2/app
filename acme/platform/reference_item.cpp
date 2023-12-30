// Created by camilo More work on 2023-11-22 22:40 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme.h"
#if   REFERENCING_DEBUGGING
#include "reference_item.h"

//
//extern struct lparam_debug g_lparamdbg;
//
//
//bool g_bEnableObjRefDbg = true;
//::i64 g_iInspectedItems = true;

//critical_section * g_pcsRefDbg = nullptr;

reference_item::reference_item(::reference_item_array * pitema) :
   m_pitema(pitema)
   //,m_bOn(true)
{

}


reference_item::~reference_item()
{

   if (::is_set(m_preferer))
   {
    
      ::allocator::erase_referer(m_preferer);

   }

}

interlocked_count g_interlockedcountNewReferenceItemSerial;

CLASS_DECL_ACME::index new_reference_item_serial()
{

   auto i = (::i64) g_interlockedcountNewReferenceItemSerial;

   g_interlockedcountNewReferenceItemSerial++;

   return i;

}


//
//void defer_delete(reference_count_debug * p)
//{
//
//   if (::is_null(p))
//   {
//
//      return;
//
//   }
//
//   delete p;
//
//};
//
//
//string object_name(matter * p)
//{
//
//   iptr i = (iptr)p;
//
//   if (i < 16)
//   {
//
//      return as_string(i);
//
//   }
//
//   return typeid(*p).name();
//
//}
//
//
//#if REFERENCING_DEBUGGING
//
//
//void particle::add_ref_history()
//{
//
//   if (!::acme::g_bAcme)
//   {
//
//      return;
//
//   }
//
//   if (!is_referencing_debugging_enabled())
//   {
//
//      return;
//
//   }
//
//   critical_section_lock synchronouslock(&::acme::get()->m_criticalsectionRefDbg);
//
//   if (g_bEnableObjRefDbg)
//   {
//
//      g_bEnableObjRefDbg = false;
//
//      try
//      {
//
//         string strType = ::type(this).name();
//
//         if (strType == "pacman::game")
//         {
//
//            informationf("pacman::game");
//
//         }
//
//         auto pobjectreferencecountdebug = reference_count_debug();
//
//         if (pobjectreferencecountdebug->m_bFirstReference)
//         {
//
//            pobjectreferencecountdebug->m_strDebug = pszObjRefDbg;
//
//            pobjectreferencecountdebug->m_bFirstReference = false;
//
//         }
//         else if (!pobjectreferencecountdebug->m_strDebug.is_empty())
//         {
//
//            pobjectreferencecountdebug->m_strDebug = "For " + ::type(this).name() + "(" + string(debug_note()) + ")";
//
//         }
//
//         string strNote = ::type(pReferer).name();
//
//         if (::is_set(pszObjRefDbg))
//         {
//
//            strNote += " - " + string(pszObjRefDbg);
//
//         }
//
//         if (strType == "pacman::game")
//         {
//
//            informationf("pacman::game");
//
//         }
//         else if (strType.case_insensitive_contains("session"))
//         {
//
//            //            if (m_pobjrefdbg->m_iStep == 39)
//            //            {
//            //
//            //               informationf("session");
//            //
//            //            }
//
//         }
//
//         pobjectreferencecountdebug->add();
//
//      }
//      catch (...)
//      {
//
//      }
//
//      g_bEnableObjRefDbg = true;
//
//   }
//
//}
//
//
//void particle::dec_ref_history()
//{
//
//   if (!::acme::g_bAcme)
//   {
//
//      return;
//
//   }
//
//   if (!is_referencing_debugging_enabled())
//   {
//
//      return;
//
//   }
//
//   critical_section_lock synchronouslock(&::acme::get()->m_criticalsectionRefDbg);
//
//   if (g_bEnableObjRefDbg)
//   {
//
//      m_pobjectreferencecountdebug->erase();
//
//   }
//
//}
//
//
//void particle::check_pending_releases()
//{
//
//   critical_section_lock synchronouslock(&::acme::get()->m_criticalsectionRefDbg);
//
//   if (!is_referencing_debugging_enabled())
//   {
//
//      return;
//
//   }
//
//   if (::is_null(m_pobjectreferencecountdebug))
//   {
//
//      return;
//
//   }
//
//   ::string str;
//
//   m_pobjectreferencecountdebug->dump_pending_releases(str);
//
//   ::output_debug_string(str);
//
//}
//
//#endif
//
//
//void reference_count_debug::dump_pending_releases(::string & strDump)
//{
//
//   if (m_itema.is_empty())
//   {
//
//      return;
//
//   }
//
//   strDump.append_formatf("m_iLastReferenceCount=%d\n", m_iLastReferenceCount);
//
//   strDump += m_strDebug + "\n";
//
//   for (index iIndex = 0; iIndex < m_itema.get_count(); iIndex++)
//   {
//
//      auto & item = m_itema[iIndex];
//
//      ::index iStep = item.m_iStep;
//
//      ::particle * pobj = item.m_preferer;
//
//      string str = item.m_strDebug;
//
//      try
//      {
//
//         strDump.append_formatf("%4d: %4d %s", iIndex, iStep, str.c_str());
//
//      }
//      catch (...)
//      {
//
//      }
//
//   }
//
//   strDump += "-------------------\n\n";
//
//}
//
////struct lparam_debug g_lparamdbg;
////
////
////CLASS_DECL_ACME struct lparam_debug & lparam_debug()
////{
////
////    return g_lparamdbg;
////
////}
//
//
//
//
//
//
//#if REFERENCING_DEBUGGING
//
//reference_count_debug * particle::reference_count_debug()
//{
//
//   if (::is_null(m_pobjectreferencecountdebug) && is_referencing_debugging_enabled())
//   {
//
//      m_pobjectreferencecountdebug = new class reference_count_debug(this);
//
//   }
//
//   return m_pobjectreferencecountdebug;
//
//}
//
//
//#endif
//
//
//
//void check_all_pending_releases()
//{
//
//   auto c = ::acme::get()->m_pobjectreferencecountdebuga->size();
//
//   {
//
//      ::string strDump;
//
//      strDump.append_formatf("Inspected Items : %d\n", g_iInspectedItems);
//
//      strDump.append_formatf("Found %d items with pending releases.\n", c);
//
//      ::output_debug_string(strDump);
//
//   }
//
//   for (::index i = 0; i < c; i++)
//   {
//
//      auto p = g_pobjectreferencecountdebuga->element_at(i);
//
//      {
//
//         ::string strDump;
//
//         strDump.append_formatf("\n\n%d:\n", i);
//
//         try
//         {
//
//            p->dump_pending_releases(strDump);
//
//         }
//         catch (...)
//         {
//
//
//         }
//
//         ::output_debug_string(strDump);
//
//      }
//
//   }
//
//}


#endif


