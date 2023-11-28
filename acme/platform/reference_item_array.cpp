// Created by camilo More work on 2023-11-22 22:40 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme.h"
#include "reference_item.h"
#include "reference_item_array.h"
#include "referencing_debugging.h"
#include "system.h"


extern bool g_bDefaultEnableObjectReferenceCountDebug;


void destruct_particle_reference_item_array(::particle * pparticle);


//extern struct lparam_debug g_lparamdbg;
::i64 g_iReferenceItemArraySerial = 0;


//CLASS_DECL_ACME::particle * task_get_top_track();

namespace allocator
{


   extern thread_local ::particle * t_pparticleTrackAllocation;


} // namespace allocator


reference_item_array::reference_item_array(::particle * pparticle, ::particle * pparticleParent) :
   m_pparticle(pparticle),
   m_pparticleParent(pparticleParent),
   m_iStep(0),
   m_bFirstReference(true),
   m_iSerial(g_iReferenceItemArraySerial++)
{

   //auto ptoptrack = ::allocator::task_get_top_track();

   ASSERT(::is_null(pparticleParent) || pparticleParent->is_referencing_debugging_enabled());

   ASSERT(pparticle->is_referencing_debugging_enabled());

   if (::is_null(pparticleParent))
   {

      ::acme::get()->m_preferencingdebugging->add_item_array(this);

   }
   else
   {

      ASSERT(pparticleParent->m_preferenceitema);

      pparticleParent->m_preferenceitema->add_item_array(this);

   }

}


reference_item_array::~reference_item_array()
{

#if REFERENCING_DEBUGGING

   for (auto & preferenceitema : m_item2a)
   {

      ::platform::raw_allocator::__delete(preferenceitema);

   }

   if (g_bDefaultEnableObjectReferenceCountDebug)
   {

      if (::is_set(m_pparticleParent))
      {

         m_pparticleParent->m_preferenceitema->erase_item_array(this);

      }
      else
      {

         auto pacme = ::acme::get();

         if (!pacme)
         {

            ::acme::get()->platform()->warningf("Something has gone wrong... acme doesn't exist");

         }

         auto preferencingdebugging = pacme->m_preferencingdebugging;

         if (!preferencingdebugging)
         {

            ::acme::get()->platform()->warningf("Something is wrong... referencing debugging doesn't exist (anymore)?");

         }

         preferencingdebugging->erase_item_array(this);

      }

   }

#endif // REFERENCING_DEBUGGING

}


void reference_item_array::add_item_array(::reference_item_array * pitema)
{

   critical_section_lock criticalsectionlock(&::acme::get()->m_preferencingdebugging->m_criticalsection);

   m_item2a.add(pitema);

}


bool reference_item_array::erase_item_array(::reference_item_array * pitema)
{

   critical_section_lock criticalsectionlock(&::acme::get()->m_preferencingdebugging->m_criticalsection);

   auto iFind = m_item2a.erase_last(pitema);

   if (iFind < 0)
   {

      throw ::exception(error_wrong_state, "reference_item_array wasn't in referencing_debugging");

      return false;

   }

   return true;

}


//void reference_item_array::initialize_reference_item_array(::referencing_debugging * preferencingdebugging)
//{
//
//   if (m_preferencingdebugging)
//   {
//
//      return;
//
//   }
//
//   m_preferencingdebugging = preferencingdebugging;
//
//   m_preferencingdebugging->add_item_array(this);
//
//}


void reference_item_array::add_item(REFERENCING_DEBUGGING_PARAMETERS_DEFINITION)
{

   auto pitem = new reference_item(this);

   pitem->m_iStep = m_iStep++;
   pitem->m_referer = referer;
   pitem->m_strDebug = referer.m_cstringDebug;

   m_bFirstReference = false;

   m_itema.add(pitem);

}


::index reference_item_array::find_item(REFERENCING_DEBUGGING_PARAMETERS_DEFINITION)
{

   if (::type(m_pparticle).name().contains("app_app::application"))
   {

      if (!referer)
      {

         output_debug_string("erase_item app_app::application (null) referer");

      }

   }

   auto iFind = m_itema.predicate_find_last([&referer](auto & pitem)
      {

         return pitem->m_bOn && pitem->m_referer == referer;

      });

   if (iFind < 0)
   {

      ::string strList;

      for (auto & p : m_itema)
      {
         try
         {

            //strList += " - " + ::type(p->m_preferer).name();

            strList += " : " + as_string(p->m_iStep) + ::string(" : ") + (p->m_bOn ? "On" : "Off");

            strList += "\n";

            strList += p->m_strDebug + ": Increment";

            strList += "\n";

            strList += p->m_strDebugDecrement + ": Decrement";

            strList += "\n";

         }
         catch (...)
         {

            strList += "(exc);";

         }

      }

      output_debug_string("referer wasn't on list : \n" + strList);

      throw ::exception(error_debug_warning, "referer wasn't on list (" + strList + ")");

   }

   return iFind;

}


bool reference_item_array::erase_item(REFERENCING_DEBUGGING_PARAMETERS_DEFINITION)
{

   auto iFind = find_item(REFERENCING_DEBUGGING_ARGS);

   if (iFind >= 0)
   {

      auto p = m_itema[iFind];

      p->m_bOn = false;

      p->m_strDebugDecrement = referer.m_cstringDebug;

   }

   return true;

}


bool reference_item_array::replace_item(REFERENCING_DEBUGGING_PARAMETERS_DEFINITION)
{

   auto iFind = find_item(REFERENCING_DEBUGGING_ARGS);

   if (iFind >= 0)
   {

      auto p = m_itema[iFind];

      p->m_strDebug = referer.m_cstringDebug;

   }

   return true;

}


string object_name(matter* p)
{

   iptr i = (iptr)p;

   if (i < 16)
   {

      return as_string(i);

   }

   return typeid(*p).name();

}


#if REFERENCING_DEBUGGING


//void particle::add_initial_reference_item()
//{
//
//   if (!is_referencing_debugging_enabled())
//   {
//
//      return;
//
//   }
//
//   auto pitema = reference_itema();
//
//   auto preferencingdebugging = pitema->m_preferencingdebugging;
//
//   critical_section_lock synchronouslock(&preferencingdebugging->m_criticalsection);
//
//   auto c = m_countReference;
//
//   for (::index i = pitema->m_itema.size(); i < c; i++)
//   {
//
//      _add_reference_item(REFERENCING_DEBUGGING_ARGS);
//
//   }
//
//   pitema->m_iLastReferenceCount = c;
//
//}



void particle::add_reference_item(REFERENCING_DEBUGGING_PARAMETERS_DEFINITION)
{

   critical_section_lock synchronouslock(&::acme::get()->m_preferencingdebugging->m_criticalsection);

   if (!is_referencing_debugging_enabled())
   {

      return;

   }

   auto pitema = reference_itema();

//   auto c = m_countReference;
//
//   for (::index i = pitema->m_itema.size(); i < c; i++)
//   {
//
//      _add_reference_item(REFERENCING_DEBUGGING_ARGS);
//
//   }
//
//   pitema->m_iLastReferenceCount = c;
//
//}
//
//
//void particle::_add_reference_item(REFERENCING_DEBUGGING_PARAMETERS_DEFINITION)
//{
//
//   auto pitema = m_preferenceitema.m_p;

   //auto preferencingdebugging = pitema->m_preferencingdebugging;

   try
   {

      string strType = ::type(this).name();

      if (strType == "pacman::game")
      {

         informationf("pacman::game");

      }

      if (pitema->m_bFirstReference)
      {

         pitema->m_strDebug = referer.m_cstringType;

      }
      else if (!pitema->m_strDebug.is_empty())
      {

         pitema->m_strDebug = "For " + ::type(this).name() + "(" + string(debug_note()) + ")";

      }

      string strRefererType;

      strRefererType = referer.m_cstringType;

      string strRefererDebug;

      strRefererDebug = referer.m_cstringDebug;

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

      pitema->add_item(REFERENCING_DEBUGGING_ARGS);

   }
   catch (...)
   {

   }

}


void particle::erase_reference_item(REFERENCING_DEBUGGING_PARAMETERS_DEFINITION)
{

   critical_section_lock synchronouslock(&::acme::get()->m_preferencingdebugging->m_criticalsection);

   if (!is_referencing_debugging_enabled())
   {

      return;

   }

   auto pitema = m_preferenceitema;

   if (::is_null(pitema))
   {

      return;

   }

   pitema->erase_item(REFERENCING_DEBUGGING_ARGS);

}


void particle::check_pending_releases()
{

   if (!is_referencing_debugging_enabled())
   {

      return;

   }

   auto pitema = m_preferenceitema;

   critical_section_lock synchronouslock(&::acme::get()->m_preferencingdebugging->m_criticalsection);

   ::string str;

   pitema->dump_pending_releases(str);

   ::output_debug_string(str);

}

#endif


void reference_item_array::dump_pending_releases(::string & strDump)
{

   if (m_itema.is_empty())
   {

      return;

   }

   strDump.append_formatf("Serial: %lld, m_iLastReferenceCount=%d\n", m_iSerial, m_iLastReferenceCount);

   strDump += m_strDebug + "\n";
 
   for (index iIndex = 0; iIndex < m_itema.get_count(); iIndex++)
   {

      auto & pitem = m_itema[iIndex];

      ::index iStep = pitem->m_iStep;

      auto & referer = pitem->m_referer;

      string str = pitem->m_strDebug;

      try
      {

         strDump.append_formatf("%4d: %4d %s", iIndex, iStep, str.c_str());

      }
      catch (...)
      {

      }

   }

   strDump += "-------------------\n\n";

}

//struct lparam_debug g_lparamdbg;
//
//
//CLASS_DECL_ACME struct lparam_debug & lparam_debug()
//{
//
//    return g_lparamdbg;
//
//}






#if REFERENCING_DEBUGGING



void particle::add_top_track(::particle * pparticle)
{

   if (::is_null(pparticle))
   {

      throw ::exception(::error_wrong_state, "cannot track null particle");

   }

   if (contains_top_track(pparticle))
   {

      throw ::exception(::error_wrong_state, "particle is already tracked");
      
   }

   auto pparticleTop = get_top_track();

   pparticleTop->m_pparticleTopTrack = pparticle;

}


::particle * particle::get_top_track() const
{

   return ::is_null(m_pparticleTopTrack) ?
      (::particle *) this :
      m_pparticleTopTrack->get_top_track();

}


void particle::erase_top_track(::particle * pparticle)
{

   if (::is_null(pparticle))
   {

      return;

   }

   if (::is_null(m_pparticleTopTrack))
   {

      throw ::exception(error_wrong_state);

   }
   
   auto pNextTop = m_pparticleTopTrack->m_pparticleTopTrack;

   if (::is_set(pNextTop))
   {

      pNextTop->erase_top_track(pparticle);

      return;

   }

   ASSERT(pparticle == m_pparticleTopTrack);

   m_pparticleTopTrack = m_pparticleTopTrack->m_pparticleTopTrack;

}


bool particle::find_top_track(::particle * pparticle, ::particle ** pparticleParent) const
{

   if (::is_null(pparticle))
   {

      return false;

   }

   if (pparticle == this)
   {

      return true;

   }

   if (::is_null(m_pparticleTopTrack))
   {

      return false;

   }

   if (m_pparticleTopTrack == pparticle)
   {

      return true;

   }

   if (pparticleParent)
   {

      *pparticleParent = (::particle *) this;

   }

   return m_pparticleTopTrack->contains_top_track(pparticle);

}



bool particle::contains_top_track(::particle * pparticle) const
{

   if (::is_null(pparticle))
   {

      return false;

   }

   if (pparticle == this)
   {

      return true;

   }

   if (::is_null(m_pparticleTopTrack))
   {

      return false;

   }

   if (m_pparticleTopTrack == pparticle)
   {

      return true;

   }
   
   return m_pparticleTopTrack->contains_top_track(pparticle);

}


reference_item_array * particle::reference_itema()
{

   if (!is_referencing_debugging_enabled())
   {

      return nullptr;

   }

   //if (::is_null(m_preferenceitema))
   //{

   //   m_preferenceitema = __allocate< reference_item_array >(this);

   //}

   return m_preferenceitema;

}


#endif



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
//
//
//namespace platform
//{
//
//
//   extern thread_local void * t_pStartConstruct;
//   extern thread_local memsize t_sStartConstruct;
//
//
//} // namespace platform
//



void destruct_particle_reference_item_array(::particle * pparticle)
{

   auto preferenceitema = pparticle->m_preferenceitema;

   if (::is_set(preferenceitema))
   {

      pparticle->m_preferenceitema = nullptr;

      ::platform::raw_allocator::__delete(preferenceitema);

   }

}







