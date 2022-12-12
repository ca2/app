#include "framework.h"
#include "font_enumeration.h"
#include "font_enumeration_item.h"
#include "font.h"
#include "acme/constant/id.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/write_text/fonts.h"


namespace write_text
{

   
   font_enumeration::font_enumeration()
   {

      m_bRaster = true;
      m_bTrueType = true;
      m_bOther = true;

      m_iUpdateId = -1;
      m_bUpdating = true;

      m_eventReady.ResetEvent();

   }


   font_enumeration::~font_enumeration()
   {

   }


   void font_enumeration::initialize(::particle * pparticle)
   {

      //auto estatus = 
      ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void font_enumeration::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->m_atom == id_font_enumeration)
      {

         check_need_update(ptopic);

      }
      else if (ptopic->m_atom == id_operating_system_font_list_change)
      {

         ::pointer<::aura::system>psystem = acmesystem();

         psystem->signal(id_operating_system_font_list_change);

         update();

         ptopic->set_modified_flag();

      }

   }


   bool font_enumeration::has_font_name(const string& str)
   {

      synchronous_lock synchronouslock(this->synchronization());

      for (auto& m_pfontenumerationitema : *m_pfontenumerationitema)
      {

         if (m_pfontenumerationitema->m_strName.case_insensitive_order(str) == 0)
         {

            return true;

         }

      }

      return false;

   }


   ::pointer<::write_text::font_enumeration_item>font_enumeration::similar_font(const ::string & psz)
   {

      synchronous_lock synchronouslock(this->synchronization());

      ::pointer<::write_text::font_enumeration_item>pitemFound;

      double dMaxSimilarity = 0.2;

      auto psystem = acmesystem()->m_paurasystem;

      auto * pdraw2d = psystem->draw2d();

      auto * pwritetext = pdraw2d->write_text();

      auto * pfonts = pwritetext->fonts();
      
      if(m_pfontenumerationitema->is_empty())
      {
         
         update();
         
      }

      for(auto & pitem : *m_pfontenumerationitema)
      {

         int iFound = -1;

         double dSimilarity = pfonts->font_similarity(pitem->m_strName, psz);

         if (dSimilarity > dMaxSimilarity)
         {

            pitemFound = pitem;

            dMaxSimilarity = dSimilarity;

         }

         if (dMaxSimilarity >= 1.0)
         {

            break;

         }

      }

      return pitemFound;

   }


   void font_enumeration::adapt_font_name(string& str)
   {

      auto pitem = similar_font(str);

      if (pitem)
      {

         str = pitem->m_strName;

      }
      else
      {

         auto psystem = acmesystem()->m_paurasystem;

         auto pdraw2d = psystem->draw2d();

         auto pwritetext = pdraw2d->write_text();

         auto pfonts = pwritetext->fonts();

         str = pfonts->default_font_name();

      }

   }


   void font_enumeration::check_need_update(::topic * ptopic)
   {

      m_bUpdating = true;

      //auto pgraphics = ::draw2d::create_memory_graphics();

      ::pointer<::write_text::font_enumeration_item_array>pitema;

      pitema = __new(::write_text::font_enumeration_item_array);

      auto psystem = acmesystem()->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      enumerate_fonts();

      sort_fonts();

      if (m_pfontenumerationitema.is_set() && ::acme::array::is_equal(*pitema, *m_pfontenumerationitema))
      {

         m_bUpdating = false;

         ptopic->m_atom = id_not_modified;

         return;

      }

      m_pfontenumerationitema = pitema;

      m_iUpdateId++;

      m_bUpdating = false;

      ptopic->set_modified_flag();

      //ptopic->m_atom = id_handle;

   }


   void font_enumeration::update()
   {

      m_bUpdating = true;

      //auto g = create_memory_graphics();

      ::pointer<::write_text::font_enumeration_item_array>pitema;

      pitema = __new(::write_text::font_enumeration_item_array);

      auto psystem = acmesystem()->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      //auto estatus = 
      
      enumerate_fonts();

      //if (!estatus)
      //{

      //   output_debug_string("write_text::font_enumeration Failed to enumerate fonts");

      //   return estatus;

      //}

      //estatus =
      
      sort_fonts();

      //if (!estatus)
      //{

      //   output_debug_string("write_text::font_enumeration Failed to sort fonts");

      //   //return estatus;

      //}

      m_pfontenumerationitema = pitema;

      m_iUpdateId++;

      m_bUpdating = false;

      //return estatus;

   }


   void font_enumeration::enumerate_fonts()
   {

      m_eventReady.ResetEvent();

      on_enumerate_fonts();

      sort_fonts();

      m_eventReady.SetEvent();

      //return ::success;

   }


   void font_enumeration::sort_fonts()
   {

      ::acme::array::predicate_sort(*m_pfontenumerationitema, [&](auto& a, auto& b)
      {

         return a->m_strName < b->m_strName;

      });

      //return ::success;

   }


   void font_enumeration::on_enumerate_fonts()
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


} // namespace write_text



