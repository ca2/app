#include "framework.h"
#include "fonts.h"
#include "font.h"
#include "font_enumeration_item.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/system.h"


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


   font_enumeration* fonts::enumeration(const ::scoped_string & scopedstrFontBranch)
   {

      synchronous_lock syncronouslock(synchronization());

      ::string strFontBranch = scopedstrFontBranch;

      strFontBranch.make_lower();

      strFontBranch.trim();

      strFontBranch.find_replace("-", "_");

      if (strFontBranch.is_empty())
      {

         strFontBranch = "system";

      }

      if (!m_mapFontEnumeration[strFontBranch])
      {

         enumerate_fonts(strFontBranch);

      }

      return m_mapFontEnumeration[strFontBranch];

   }

   
   void fonts::enumerate_fonts(const ::scoped_string & scopedstrFontBranch)
   {

      synchronous_lock syncronouslock(synchronization());

      ::pointer < ::write_text::font_enumeration > pfontenumeration;

      ::string strFontBranch = scopedstrFontBranch;

      strFontBranch.make_lower();

      strFontBranch.trim();

      strFontBranch.find_replace("-", "_");

      if (strFontBranch.is_empty())
      {

         strFontBranch = "system";

      }

      if (strFontBranch == "system")
      {

         pfontenumeration = __create < ::write_text::font_enumeration >();

      }
      else
      {

         auto pfactory = acmesystem()->factory("font_enumeration", strFontBranch);

         pfontenumeration = __create < ::write_text::font_enumeration >(pfactory);

      }


      //if (!pfontenumeration.m_estatus)
      //{

      //   return pfontenumeration.m_estatus;

      //}

      if (!m_mapFontEnumeration[scopedstrFontBranch])
      {

         m_mapFontEnumeration[scopedstrFontBranch] = pfontenumeration;

      }

      fork([this, pfontenumeration, scopedstrFontBranch]
      {

         pfontenumeration->enumerate_fonts();

         synchronous_lock syncronouslock(synchronization());

         m_mapFontEnumeration[scopedstrFontBranch] = pfontenumeration;

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



