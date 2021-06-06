#include "framework.h"


namespace write_text
{

   
   font_enumeration::font_enumeration()
   {

      m_iUpdateId = -1;
      m_bUpdating = true;

   }


   font_enumeration::~font_enumeration()
   {

   }


   ::e_status font_enumeration::initialize(::object * pobject)
   {

      auto estatus = ::object::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void font_enumeration::on_subject(::subject::subject * psubject)
   {

      if (psubject->m_esubject == e_subject_prepare)
      {

         if (psubject->id() == id_font_enumeration)
         {

            check_need_update(psubject);

         }

      }

   }


   void font_enumeration::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      if (psubject->id() == id_os_font_change)
      {

         __pointer(::aura::system) psystem = m_psystem;

         auto psubject = psystem->subject(id_os_font_change);

         update();
         
         psubject->set_modified();

      }

   }


   bool font_enumeration::has_font_name(const string& str)
   {

      synchronous_lock synchronouslock(mutex());

      for (auto& m_pfontenumerationitema : *m_pfontenumerationitema)
      {

         if (m_pfontenumerationitema->m_strName.compare_ci(str) == 0)
         {

            return true;

         }

      }

      return false;

   }


   __pointer(::write_text::font_enumeration_item) font_enumeration::similar_font(const char* psz)
   {

      synchronous_lock synchronouslock(mutex());

      __pointer(::write_text::font_enumeration_item) pitemFound;

      double dMaxSimilarity = 0.2;

      __pointer(::aura::system) psystem = m_psystem;

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

         __pointer(::aura::system) psystem = m_psystem;

         auto pdraw2d = psystem->draw2d();

         auto pwritetext = pdraw2d->write_text();

         auto pfonts = pwritetext->fonts();

         str = pfonts->default_font_name();

      }

   }


   void font_enumeration::check_need_update(::subject::subject * psubject)
   {

      m_bUpdating = true;

      //auto pgraphics = ::draw2d::create_memory_graphics();

      __pointer(::write_text::font_enumeration_item_array) pitema;

      pitema = __new(::write_text::font_enumeration_item_array);

      auto psystem = m_psystem->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      enumerate_fonts();

      sort_fonts();

      if (m_pfontenumerationitema.is_set() && ::papaya::array::are_all_elements_equal(*pitema, *m_pfontenumerationitema))
      {

         m_bUpdating = false;

         psubject->m_esubject = e_subject_not_modified;

         return;

      }

      m_pfontenumerationitema = pitema;

      m_iUpdateId++;

      m_bUpdating = false;

      psubject->set_modified();

      psubject->m_esubject = e_subject_deliver;

   }


   ::e_status font_enumeration::update()
   {

      m_bUpdating = true;

      //auto g = create_memory_graphics();

      __pointer(::write_text::font_enumeration_item_array) pitema;

      pitema = __new(::write_text::font_enumeration_item_array);

      auto psystem = m_psystem->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto estatus = enumerate_fonts();

      if (!estatus)
      {

         output_debug_string("write_text::font_enumeration Failed to enumerate fonts");

         return estatus;

      }

      estatus = sort_fonts();

      if (!estatus)
      {

         output_debug_string("write_text::font_enumeration Failed to sort fonts");

         //return estatus;

      }

      m_pfontenumerationitema = pitema;

      m_iUpdateId++;

      m_bUpdating = false;

      return estatus;

   }


   ::e_status font_enumeration::enumerate_fonts()
   {

      on_enumerate_fonts();

      sort_fonts();

      m_eventReady.SetEvent();

      return ::success;

   }


   ::e_status font_enumeration::sort_fonts()
   {

      ::sort::array::predicate_sort(*m_pfontenumerationitema, [&](auto& a, auto& b)
      {

         return a->m_strName < b->m_strName;

      });

      return ::success;

   }


   ::e_status font_enumeration::on_enumerate_fonts()
   {

      __throw(error_interface_only);

      return ::error_interface_only;

   }


} // namespace write_text



