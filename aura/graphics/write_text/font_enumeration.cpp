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

      //psystem->add_process(id_os_font_change, this);

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

         update(psubject);

      }

   }


   bool font_enumeration::has_font_name(const string& str)
   {

      synchronous_lock synchronouslock(mutex());

      for (auto& pitem : *m_pitema)
      {

         if (pitem->m_strName.compare_ci(str) == 0)
         {

            return true;

         }

      }

      return false;

   }


   __pointer(::write_text::font_enum_item) font_enumeration::similar_font(const char* psz)
   {

      synchronous_lock synchronouslock(mutex());

      __pointer(::write_text::font_enum_item) pitemFound;

      double dMaxSimilarity = 0.2;

      __pointer(::aura::system) psystem = m_psystem;

      auto * pdraw2d = psystem->draw2d();

      auto * pwritetext = pdraw2d->write_text();

      auto * pfonts = pwritetext->fonts();

      for(auto & pitem : *m_pitema)
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

      __pointer(::write_text::font_enum_item_array) pitema;

      pitema = __new(::write_text::font_enum_item_array);

      auto psystem = m_psystem->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      pdraw2d->write_text()->fonts()->sorted_fonts(*pitema);

      if (m_pitema.is_set() && ::papaya::array::are_all_elements_equal(*pitema, *m_pitema))
      {

         m_bUpdating = false;

         psubject->m_esubject = e_subject_not_modified;

         return;

      }

      m_pitema = pitema;

      m_iUpdateId++;

      m_bUpdating = false;

      psubject->set_modified();

      psubject->m_esubject = e_subject_deliver;

   }


   bool font_enumeration::update(::subject::subject * psubject)
   {

      m_bUpdating = true;

      //auto g = create_memory_graphics();

      __pointer(::write_text::font_enum_item_array) pitema;

      pitema = __new(::write_text::font_enum_item_array);

      auto psystem = m_psystem->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      pdraw2d->write_text()->fonts()->sorted_fonts(*pitema);

      m_pitema = pitema;

      m_iUpdateId++;

      m_bUpdating = false;

      psubject->set_modified();

      return true;

   }


} // namespace write_text


