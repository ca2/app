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

   ::string strRefrain;

   ::string strDump;

   strDump.m_erange |= e_range_buffer;

   auto cFiltered = 0;

   for (::collection::index i = 0; i < c; i++)
   {

      auto p = m_item2a.element_at(i);

      //if(p->m_iLastReferenceCount > 0)
      if (p->m_psubparticle->m_countReference > 0)
      {
         
         cFiltered++;

      }

   }

   {

      strDump.append_formatf("\n\nrefdbg0--\n\n");

      strDump.append_formatf("Inspected Top Level Items : %d\n", m_iCount);

      strDump.append_formatf("Found %d items with pending releases.\n", c);

      if (c != cFiltered)
      {

         strDump.append_formatf("Found %d items with referencing counting...\nProblem with referencing debugging pairing of referer/release?", cFiltered);

      }

      if (c == 1)
      {

         strRefrain.append("   We are almost there... Only one remaining...");

      }
      else if (c == 0)
      {

         strRefrain.append("   Cleared!! This is awesome!!");

      }
      else
      {

         strRefrain.append_formatf("  As reported : \"Found %d items with pending releases.\"...\n", c);

      }

      strDump += new_line_quote(dash_quote(new_line_quote(strRefrain)));

   }

   for (::collection::index i = 0; i < c; i++)
   {

      auto p = m_item2a.element_at(i);

      //if(p->m_iLastReferenceCount > 0)
      if (p->m_psubparticle->m_countReference.as_integer() > 0)
      {

         strDump.append_formatf("\n\n%d:\n", i);

         try
         {

            p->dump_pending_releases(strDump);

         }
         catch (...)
         {


         }

      }

   }

   strDump += new_line_quote(strRefrain);

   auto range = strDump();

   ansi_range line;

   while(range.consume_line(line))
   {

      ::ansi_output_debug_line(line);

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



