#include "framework.h"
#include "write_text.h"
#include "fonts.h"


namespace write_text
{


   write_text::write_text()
   {


   }


   write_text::~write_text()
   {


   }


   class fonts * write_text::fonts()
   {

      synchronous_lock synchronouslock(mutex());

      if (m_pfonts == nullptr)
      {

         auto estatus = __construct(m_pfonts);

         if (!estatus)
         {

            return nullptr;

         }

         auto psystem = m_psystem->m_paurasystem;

         psystem->signal(id_font_enumeration);

      }

      return m_pfonts;

   }


   void write_text::term()
   {

      try
      {

         if (m_pfonts)
         {

            m_pfonts->destroy();

         }

      }
      catch (...)
      {

      }

      auto estatus = ::acme::department::term();

      return success;

   }


   void write_text::destroy()
   {

      m_pfonts.release();

      auto estatus = ::acme::department::destroy();

      return estatus;

   }


   void write_text::handle_font_enumeration(::subject* psubject)
   {

      __pointer(::subject) psubjectHold(psubject);

      auto pfonts = this->fonts();

      auto estatus = pfonts->enumerate_fonts();

      return estatus;

   }


   font_pointer write_text::point_font(const ::string & pszFontName, double dFontSize, int iFontWeight)
   {

      auto pfont = __create < font >();

      pfont->create_point_font(pszFontName, dFontSize, iFontWeight);

      return ::move(pfont);

   }


   font_pointer write_text::create_font()
   {

      return __create < font > ();
      
   }


} // namespace write_text



