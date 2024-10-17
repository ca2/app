// Created by camilo More work on 2023-11-22 22:40 <3ThomasBorregaardSorensen!!
#include "framework.h"


#if REFERENCING_DEBUGGING


#include "acme.h"
#include "reference_item_array.h"
#include "referencing_debugging.h"


referencing_debugging::referencing_debugging()
{


}


referencing_debugging::~referencing_debugging()
{


}


void referencing_debugging::add_item_array(::reference_item_array * pitema)
{

   critical_section_lock criticalsectionlock(&m_criticalsection);

   m_item2a.add(pitema);

   m_iCount++;

}


bool referencing_debugging::erase_item_array(::reference_item_array * pitema)
{

   critical_section_lock criticalsectionlock(&m_criticalsection);

   auto iFind = m_item2a.erase_last(pitema);

   if(iFind < 0)
   {

      throw ::exception(error_wrong_state, "reference_item_array wasn't in referencing_debugging");

      return false;

   }

   return true;

}


void referencing_debugging::dump_pending_releases()
{

   auto c = m_item2a.size();

   {

      ::string strDump;

      strDump.append_formatf("\n\nrefdbg0--\n\n");

      strDump.append_formatf("Inspected Top Level Items : %d\n", m_iCount);

      strDump.append_formatf("Found %d items with pending releases.\n", c);

      ::output_debug_string(strDump);

   }

   for (::collection::index i = 0; i < c; i++)
   {

      auto p = m_item2a.element_at(i);

      //if(p->m_iLastReferenceCount > 0)
      if (p->m_psubparticle->m_countReference.operator long long() > 0)
      {

         ::string strDump;

         strDump.append_formatf("\n\n%d:\n", i);

         try
         {

            p->dump_pending_releases(strDump);

         }
         catch (...)
         {


         }

         ::output_debug_string(strDump);

      }

   }

}


namespace acme
{


#if REFERENCING_DEBUGGING


   void acme::initialize_referencing_debugging()
   {

      //m_preferencingdebugging = ::platform::allocator::__callnew referencing_debugging();

      m_preferencingdebugging = __raw_new referencing_debugging();

   }


#endif

   class ::time acme::start_time()
{

   return m_timeStart;

}

   //void acme::dump_pending_releases()
   //{

   //   m_preferencingdebugging->dump_pending_releases();

   //}

} // namespace acme


#endif // REFERENCING_DEBUGGING



