// Created by camilo More work on 2023-11-22 22:40 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme.h"
#if   REFERENCING_DEBUGGING
#include "reference_item.h"
#include "reference_item_array.h"
#include "referencing_debugging.h"
#include "system.h"


extern bool g_bDefaultEnableObjectReferenceCountDebug;


void destruct_particle_reference_item_array(::subparticle * psubparticle);


//extern struct lparam_debug g_lparamdbg;
::i64 g_iReferenceItemArraySerial = 0;


//CLASS_DECL_ACME::particle * task_get_top_track();

namespace allocator
{


   extern thread_local ::particle * t_psubparticleTrackAllocation;


} // namespace allocator


reference_item_array::reference_item_array(::subparticle* psubparticle, ::subparticle* psubparticleParent) :
   m_psubparticle(psubparticle),
   m_psubparticleParent(psubparticleParent),
   m_iStep(0),
   m_bFirstReference(true),
   m_iSerial(g_iReferenceItemArraySerial++)
{

   //auto ptoptrack = ::allocator::task_get_top_track();

   ASSERT(::is_null(psubparticleParent) || psubparticleParent->is_referencing_debugging_enabled());

   ASSERT(psubparticle->is_referencing_debugging_enabled());

   if (::is_null(psubparticleParent))
   {

      ::acme::get()->m_preferencingdebugging->add_item_array(this);

   }
   else
   {

      ASSERT(psubparticleParent->m_preferenceitema);

      psubparticleParent->m_preferenceitema->add_item_array(this);

   }

}


reference_item_array::~reference_item_array()
{

#if REFERENCING_DEBUGGING

   for (auto & preferenceitema : m_item2a)
   {

      //::platform::allocator::__delete(preferenceitema);

      delete preferenceitema;

   }

   if (g_bDefaultEnableObjectReferenceCountDebug)
   {

      if (::is_set(m_psubparticleParent))
      {
         
         if (m_psubparticleParent->m_preferenceitema)
         {

            m_psubparticleParent->m_preferenceitema->erase_item_array(this);

         }

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


::reference_item * new_reference_item(::reference_item_array * parray)
{

   auto p = malloc(sizeof(::reference_item));

   auto preferenceitem = ::new(p) ::reference_item(parray);

   return preferenceitem;

}


void delete_reference_item(::reference_item * preferenceitem)
{

   preferenceitem->~reference_item();

   ::free(preferenceitem);

}


void reference_item_array::add_item()
{

   critical_section_lock criticalsectionlock(&::acme::get()->m_preferencingdebugging->m_criticalsection);

   auto pitem = new_reference_item(this);

   pitem->m_iStep = m_iStep++;

   auto iSerial = m_iSerial;

   if (iSerial == 148)
   {

      output_debug_string("iSerial == 148");

   }


   //auto iSerial = pitem->m_preferer->m_iSerial;

   //if (iSerial == 148)
   //{

   //   output_debug_string("iSerial == 148");

   //}


   //pitem->m_referer = referer;
   if (pitem->m_preferer)
   {
         pitem->m_strDebug = pitem->m_preferer->m_cstringDebug;
   }
   if (!m_bFirstAllocationInformation)
   {
      m_bFirstAllocationInformation = true;

      m_strFirstAllocation = pitem->m_preferer->m_cstringType;
      m_strFirstAllocation += "\n";
      m_strFirstAllocation += pitem->m_preferer->m_cstringDebug;

   }
   m_bFirstReference = false;





   m_itema.add(pitem);

}


::collection::index reference_item_array::find_item(reference_referer * preferer)
{

   critical_section_lock criticalsectionlock(&::acme::get()->m_preferencingdebugging->m_criticalsection);

   //if (::type(m_psubparticle).name().contains("app_app::application"))
   //{

   //   if (!referer)
   //   {

   //      output_debug_string("erase_item app_app::application (null) referer");

   //   }

   //}

   auto iFind = m_itema.predicate_find_last([preferer](auto & pitem)
      {

         //return pitem->m_bOn && pitem->m_referer == referer;

         return pitem->m_preferer == preferer;

      });

   if (iFind < 0)
   {

      ::string strList;

      for (auto & preferenceitem : m_itema)
      {
         try
         {

            //strList += " - " + ::type(p->m_preferer).name();

            //strList += " : " + as_string(p->m_iStep) + ::string(" : ") + (p->m_bOn ? "On" : "Off");

            strList += " : " + as_string(preferenceitem->m_iStep);

            strList += "\n";

            //strList += p->m_strDebug + ": Increment";

            strList += preferenceitem->m_strDebug;

            strList += "\n";

            //strList += p->m_strDebugDecrement + ": Decrement";

            //strList += "\n";

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


bool reference_item_array::erase_item()
{

   critical_section_lock criticalsectionlock(&::acme::get()->m_preferencingdebugging->m_criticalsection);

   auto prefererRelease = ::allocator::pop_releaser();

   auto iFind = find_item(prefererRelease);

   if (iFind >= 0)
   {

      auto preferenceitem = m_itema.at(iFind);

      delete_reference_item(preferenceitem);

      m_itema.erase_at(iFind);

      //auto p = m_itema[iFind];

      //p->m_bOn = false;

      //p->m_strDebugDecrement = referer.m_cstringDebug;

   }

   return true;

}


bool reference_item_array::replace_item(reference_item * preferenceitem)
{

   critical_section_lock criticalsectionlock(&::acme::get()->m_preferencingdebugging->m_criticalsection);

   auto iFind = find_item(preferenceitem->m_preferer);

   if (iFind >= 0)
   {

      auto p = m_itema[iFind];

      p->m_strDebug = preferenceitem->m_preferer->m_cstringDebug;

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
//   for (::collection::index i = pitema->m_itema.size(); i < c; i++)
//   {
//
//      _add_reference_item();
//
//   }
//
//   pitema->m_iLastReferenceCount = c;
//
//}



void subparticle::add_reference_item()
{

   critical_section_lock synchronouslock(&::acme::get()->m_preferencingdebugging->m_criticalsection);

   if (!is_referencing_debugging_enabled())
   {

      ::allocator::defer_erase_referer();

      return;

   }

   //if (!m_bHeapAllocation)
   //{

   //   return;

   //}

   auto pitema = reference_itema();

//   auto c = m_countReference;
//
//   for (::collection::index i = pitema->m_itema.size(); i < c; i++)
//   {
//
//      _add_reference_item();
//
//   }
//
//   pitema->m_iLastReferenceCount = c;
//
//}
//
//
//void particle::_add_reference_item()
//{
//
//   auto pitema = m_preferenceitema.m_p;

   //auto preferencingdebugging = pitema->m_preferencingdebugging;

   try
   {

//      string strType = ::type(this).name();
//
//      if (strType == "pacman::game")
//      {
//
//         informationf("pacman::game");
//
//      }
//
//      if (pitema->m_bFirstReference)
//      {
//
//         pitema->m_strDebug = preferer->m_cstringType;
//
//      }
//      else if (!pitema->m_strDebug.is_empty())
//      {
//
//         pitema->m_strDebug = "For " + ::type(this).name() + "(" + string(debug_note()) + ")";
//
//      }
//
//      string strRefererType;
//
//      strRefererType = preferer->m_cstringType;
//
//      string strRefererDebug;
//
//      strRefererDebug = preferer->m_cstringDebug;
//
//      if (strType == "pacman::game")
//      {
//
//         informationf("pacman::game");
//
//      }
//      else if (strType.case_insensitive_contains("session"))
//      {
//
////            if (m_pobjrefdbg->m_iStep == 39)
////            {
////
////               informationf("session");
////
////            }
//
//      }

      //pitema->add_item(preferenc);

      pitema->add_item();

   }
   catch (...)
   {

   }

}


void subparticle::erase_reference_item()
{

   critical_section_lock synchronouslock(&::acme::get()->m_preferencingdebugging->m_criticalsection);

   if (!is_referencing_debugging_enabled())
   {

      ::allocator::defer_erase_releaser();

      return;

   }

   auto pitema = m_preferenceitema;

   if (::is_null(pitema))
   {

      return;

   }

   pitema->erase_item();

}


void subparticle::check_pending_releases()
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

   strDump += m_strFirstAllocation + "\n";
 
   for (::collection::index iIndex = 0; iIndex < m_itema.get_count(); iIndex++)
   {

      auto & pitem = m_itema[iIndex];

      ::collection::index iStep = pitem->m_iStep;

      ::collection::index iSerial = pitem->m_iSerial;

      auto preferer = pitem->m_preferer;

      string str = pitem->m_strDebug;

      string str2;

      try
      {

         if (pitem->m_preferer)
         {

            str2 += pitem->m_preferer->m_cstringType;

            str2.append_formatf(" (%lld)", pitem->m_preferer->m_iSerial);

         }

      }
      catch (...)
      {

      }

      try
      {

         strDump.append_formatf("%4d: %4d (%7lld) %s: %s\n", iIndex, iStep, iSerial, str.c_str(), str2.c_str());

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

//::particle * particle::__call__add_referer(const ::reference_referer & referer) const
//{
//
//   ::allocator::add_referer(referer);
//
//   return (::particle *)this;
//
//}

void subparticle::add_top_track(::subparticle* psubparticle)
{

   if (::is_null(psubparticle))
   {

      throw ::exception(::error_wrong_state, "cannot track null particle");

   }

   if (contains_top_track(psubparticle))
   {

      throw ::exception(::error_wrong_state, "particle is already tracked");
      
   }

   auto psubparticleTop = get_top_track();

   psubparticleTop->m_psubparticleTopTrack = psubparticle;

}


::subparticle* subparticle::get_top_track() const
{

   return ::is_null(m_psubparticleTopTrack) ?
      (::subparticle *) this :
      m_psubparticleTopTrack->get_top_track();

}


void subparticle::erase_top_track(::subparticle * psubparticle)
{

   if (::is_null(psubparticle))
   {

      return;

   }

   if (::is_null(m_psubparticleTopTrack))
   {

      throw ::exception(error_wrong_state);

   }

   if (psubparticle == m_psubparticleTopTrack)
   {

      m_psubparticleTopTrack = m_psubparticleTopTrack->m_psubparticleTopTrack;

   }
   else
   {

      auto pNextTop = m_psubparticleTopTrack->m_psubparticleTopTrack;

      if (::is_set(pNextTop))
      {

         pNextTop->erase_top_track(psubparticle);

         return;

      }

   }

}


bool subparticle::find_top_track(::subparticle * psubparticle, ::subparticle ** psubparticleParent) const
{

   if (::is_null(psubparticle))
   {

      return false;

   }

   if (psubparticle == this)
   {

      return true;

   }

   if (::is_null(m_psubparticleTopTrack))
   {

      return false;

   }

   if (m_psubparticleTopTrack == psubparticle)
   {

      if (psubparticleParent)
      {

         *psubparticleParent = (::subparticle*)this;

      }

      return true;

   }

   if (psubparticleParent)
   {

      *psubparticleParent = (::subparticle *)this;

   }

   return m_psubparticleTopTrack->find_top_track(psubparticle, psubparticleParent);

}



bool subparticle::contains_top_track(::subparticle* psubparticle) const
{

   if (::is_null(psubparticle))
   {

      return false;

   }

   if (psubparticle == this)
   {

      return true;

   }

   if (::is_null(m_psubparticleTopTrack))
   {

      return false;

   }

   if (m_psubparticleTopTrack == psubparticle)
   {

      return true;

   }
   
   return m_psubparticleTopTrack->contains_top_track(psubparticle);

}


reference_item_array * subparticle::reference_itema()
{

   if (!is_referencing_debugging_enabled())
   {

      return nullptr;

   }

   //if (::is_null(m_preferenceitema))
   //{

   //   m_preferenceitema = __new reference_item_array(this);

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
//   for (::collection::index i = 0; i < c; i++)
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



void destruct_particle_reference_item_array(::subparticle * psubparticle)
{

   auto preferenceitema = psubparticle->m_preferenceitema;

   if (::is_set(preferenceitema))
   {

      psubparticle->m_preferenceitema = nullptr;

      delete preferenceitema;

   }

}





CLASS_DECL_ACME::critical_section * refdbg_cs()
{

   return &::acme::get()->m_preferencingdebugging->m_criticalsection;

}


#endif



