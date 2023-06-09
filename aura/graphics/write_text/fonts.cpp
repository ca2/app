#include "framework.h"
#include "fonts.h"
#include "font.h"
#include "font_enumeration_item.h"
#include "acme/parallelization/synchronous_lock.h"


#define FONTFACENAME_MENU pnode->font_name(e_font_sans)

#define FONTFACENAME_LUCIDA pnode->font_name(e_font_sans)


namespace write_text
{


   fonts::fonts()
   {

      defer_create_synchronization();

   }


   fonts::~fonts()
   {

   }


   void fonts::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::acme::department::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return true;

   }


   font_enumeration* fonts::enumeration()
   {

      synchronous_lock syncronouslock(synchronization());

      if (!m_pfontenumeration)
      {

         enumerate_fonts();

      }

      return m_pfontenumeration;

   }

   
   void fonts::enumerate_fonts()
   {

      synchronous_lock syncronouslock(synchronization());

      auto pfontenumeration = __create < ::write_text::font_enumeration >();

      //if (!pfontenumeration.m_estatus)
      //{

      //   return pfontenumeration.m_estatus;

      //}

      if (!m_pfontenumeration)
      {

         m_pfontenumeration = pfontenumeration;

      }

      fork([this, pfontenumeration]
      {

         pfontenumeration->enumerate_fonts();

         synchronous_lock syncronouslock(synchronization());

         m_pfontenumeration = pfontenumeration;

      });

      //return ::success;

   }


   string fonts::default_font_name()
   {

      return "sans-serif";

   }


   double fonts::font_similarity(const ::string & strSystem, const ::string & strUser)
   {

      if (strSystem.is_empty() || strUser.is_empty())
      {

         return 0.0;

      }

      if (strSystem.case_insensitive_order(strUser) == 0)
      {

         return 1.0;

      }

      return 0.0;

   }


} // namespace write_text



