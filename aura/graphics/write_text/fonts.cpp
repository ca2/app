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

   }


   fonts::~fonts()
   {

   }


   void fonts::initialize(::particle * pparticle)
   {


      ::acme::department::initialize(pparticle);

      defer_create_synchronization();

   }


   font_enumeration* fonts::enumeration(const ::scoped_string & scopedstrFontBranch)
   {

      _synchronous_lock syncronouslock(synchronization());

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

      _synchronous_lock syncronouslock(synchronization());

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

         pfontenumeration = __øcreate < ::write_text::font_enumeration >();

      }
      else
      {

         auto pfactory = system()->factory("font_enumeration", strFontBranch);

         pfontenumeration = __øcreate < ::write_text::font_enumeration >(pfactory);

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

         _synchronous_lock syncronouslock(synchronization());

         m_mapFontEnumeration[scopedstrFontBranch] = pfontenumeration;

      });

      //return ::success;

   }


   string fonts::default_font_name()
   {

      return "sans-serif";

   }


   double fonts::font_similarity(const ::scoped_string & scopedstrSystem, const ::scoped_string & scopedstrUser)
   {

      if (scopedstrSystem.is_empty() || scopedstrUser.is_empty())
      {

         return 0.0;

      }

      if (scopedstrSystem.case_insensitive_order(scopedstrUser) == 0)
      {

         return 1.0;

      }

      return 0.0;

   }


} // namespace write_text



