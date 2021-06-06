#include "framework.h"


#define FONTFACENAME_MENU pnode->font_name(e_font_sans)

#define FONTFACENAME_LUCIDA pnode->font_name(e_font_sans)


namespace write_text
{


   fonts::fonts()
   {

      defer_create_mutex();

   }


   fonts::~fonts()
   {

   }


   ::e_status fonts::initialize(::object* pobject)
   {

      auto estatus = ::acme::department::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      return true;

   }


   font_enumeration* fonts::enumeration()
   {

      synchronous_lock syncronouslock(mutex());

      if (!m_pfontenumeration)
      {

         enumerate_fonts();

      }

      return m_pfontenumeration;

   }

   
   ::e_status fonts::enumerate_fonts()
   {

      synchronous_lock syncronouslock(mutex());

      auto pfontenumeration = __create < ::write_text::font_enumeration >();

      if (!pfontenumeration.m_estatus)
      {

         return pfontenumeration.m_estatus;

      }

      if (!m_pfontenumeration)
      {

         m_pfontenumeration = pfontenumeration;

      }

      fork([this, pfontenumeration]
      {

         pfontenumeration->enumerate_fonts();

         synchronous_lock syncronouslock(mutex());

         m_pfontenumeration = pfontenumeration;

      });

      return ::success;

   }


   string fonts::default_font_name()
   {

      return "sans-serif";

   }


   double fonts::font_similarity(const char* pszSystem, const char* pszUser)
   {

      if (::is_null(pszSystem) || ::is_null(pszUser))
      {

         return 0.0;

      }

      if (!stricmp(pszSystem, pszUser))
      {

         return 1.0;

      }

      return 0.0;

   }


} // namespace write_text



