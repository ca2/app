// Created by camilo on 2023-06-28 18:27 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "font_family.h"
#include "acme/platform/node.h"


namespace write_text
{


   font_family::font_family(enum_font efont)
   {

      m_efont = efont;

   }

   font_family::font_family(const ::scoped_string & scopedstrFamilyName, const ::scoped_string & scopedstrBranch)
   {

      m_efont = e_font_with_family_name;

      m_strFamilyName = scopedstrFamilyName;

      m_strBranch = scopedstrBranch;

   }

   font_family::font_family(const font_family & fontfamily) :
      m_efont(fontfamily.m_efont),
      m_strFamilyName(fontfamily.m_strFamilyName)
   {

   }


   font_family & font_family::operator = (const ::scoped_string & scopedstrFamilyName)
   {

      m_efont = e_font_with_family_name;

      m_strFamilyName = scopedstrFamilyName;

      m_strBranch.empty();

      return *this;

   }


   font_family & font_family::operator = (const font_family & fontfamily)
   {

      m_efont = fontfamily.m_efont;

      m_strFamilyName = fontfamily.m_strFamilyName;

      return *this;

   }

   ::string font_family::family_name(::particle * pparticle) const
   {

      if (m_efont == e_font_with_family_name)
      {

         return m_strFamilyName;

      }

      return pparticle->node()->font_name(m_efont);

   }


   ::particle_pointer font_family::clone()
   {

      return __new font_family(*this);

   }

   font_family_pointer::font_family_pointer(enum_font efont):
      ::pointer<font_family>{ place_t{}, new font_family(efont) }
   {

   }

   font_family_pointer::font_family_pointer(const ::scoped_string & scopedstrFamilyName, const ::scoped_string & scopedstrBranch) :
      ::pointer<font_family>{ place_t {}, new font_family(scopedstrFamilyName, scopedstrBranch) }
   {

   }

   font_family_pointer::font_family_pointer(const font_family & fontfamily) :
      ::pointer<font_family>{ place_t {}, new font_family(fontfamily) }
   {

   }

   font_family_pointer::font_family_pointer(const ::particle_pointer & pparticle) :
      ::pointer<font_family>(pparticle)
   {

   }



} // namespace write_text



