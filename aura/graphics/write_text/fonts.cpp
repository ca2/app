#include "framework.h"
#include "fonts.h"
#include "font.h"
#include "font_enumeration_item.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"


#define FONTFACENAME_MENU pnode->font_name(e_font_sans)

#define FONTFACENAME_LUCIDA pnode->font_name(e_font_sans)


namespace write_text
{


   fonts::fonts()
   {

      information("write_text::fonts");

   }


   fonts::~fonts()
   {

      information("write_text::~fonts");

   }


   void fonts::initialize(::particle * pparticle)
   {

      ::platform::department::initialize(pparticle);

      defer_create_synchronization();

   }


   font_enumeration* fonts::enumeration(const ::scoped_string & scopedstrFontBranch)
   {

      _synchronous_lock syncronouslock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

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

         enumerate_fonts(true, strFontBranch);

      }

      return m_mapFontEnumeration[strFontBranch];

   }

   
   void fonts::enumerate_fonts(bool bSynchronously, const ::scoped_string & scopedstrFontBranch)
   {

      ::pointer < ::write_text::font_enumeration > pfontenumeration;

      ::string strFontBranch = scopedstrFontBranch;

      auto pparticleSynchronization = this->synchronization();

      _synchronous_lock synchronouslock(pparticleSynchronization, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      strFontBranch.make_lower();

      strFontBranch.trim();

      strFontBranch.find_replace("-", "_");

      if (strFontBranch.is_empty())
      {

         strFontBranch = "system";

      }

      if (strFontBranch == "system")
      {

         pfontenumeration = createø < ::write_text::font_enumeration >();

      }
      else
      {

         auto pfactory = system()->factory("font_enumeration", strFontBranch);

         pfontenumeration = createø < ::write_text::font_enumeration >(pfactory);

      }


      //if (!pfontenumeration.m_estatus)
      //{

      //   return pfontenumeration.m_estatus;

      //}

      auto & pfontenumerationAssign = m_mapFontEnumeration[strFontBranch];

      if (!pfontenumerationAssign)
      {

         pfontenumerationAssign = pfontenumeration;

      }

      if (bSynchronously)
      {

         pfontenumeration->enumerate_fonts();

         pfontenumerationAssign = pfontenumeration;

      }
      else
      {

         synchronouslock.unlock();

         ::procedure procedure = [this, pfontenumeration, strFontBranch]()
         {

            ::procedure procedure = [this, pfontenumeration, strFontBranch]()
            {

               auto pparticleSynchronization = this->synchronization();

               _synchronous_lock syncronouslock(pparticleSynchronization, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

               m_mapFontEnumeration[strFontBranch] = pfontenumeration;

            };

            pfontenumeration->enumerate_fonts(procedure);

         };

         m_papplication->fork(procedure);

      }

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



