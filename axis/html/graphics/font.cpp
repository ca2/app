#include "framework.h"
#include "font.h"
#include "acme/primitive/string/str.h"
#include "aura/graphics/write_text/font.h"
#include "aura/platform/node.h"
#include "axis/platform/system.h"


namespace html
{


   font::font()
   {
   }

   font::font(const class font & font)
   {
      m_strFamily             = font.m_strFamily;
      m_strSize               = font.m_strSize;
      m_strWeight             = font.m_strWeight;
      m_strTextDecoration     = font.m_strTextDecoration;
   }


   bool font::create(::particle * pparticle)
   {

      initialize(pparticle);

      m_pfont.create(this);

      i32 iWeight;

      m_strWeight.trim();

      if(m_strWeight.case_insensitive_order("bold") == 0)
      {
         iWeight = 800;
      }
      else if (m_strWeight.is_empty())
      {
         iWeight = 400;
      }
      else
      {
         iWeight = maximum(100, atoi(m_strWeight));
      }

      double dSize;

      m_strSize.trim();

      if(m_strSize.is_empty())
      {
         dSize = 11;
      }
      else
      {
         dSize = strtod(m_strSize, nullptr);
      }



      string_array stra;
      stra.add_tokens(m_strFamily,",", false);
      for(i32 i = 0; i < stra.get_size(); i++)
      {
         stra[i].trim();
         if(stra[i].case_insensitive_order("fixed-width") == 0)
         {
         }
         else if(stra[i].case_insensitive_order("sans-serif") == 0)
         {
         }
         else if(stra[i].case_insensitive_order("serif") == 0)
         {
         }
      }
//      strsize iLen;

      auto psystem = acmesystem()->m_paxissystem;

      auto pnode = psystem->node();
      string strName;
      if(stra.get_count() > 0)
      {
         strName = stra[0];
//         iLen = minimum(sizeof(lf.lfFaceName) - 1, stra[0].get_length());
         //       ansi_count_copy(lf.lfFaceName, stra[0], iLen);
         //     lf.lfFaceName[iLen] = '\0';
         strName.trim();
         strName.trim("\"\'");
      }
      else
      {
         strName = pnode->font_name(e_font_sans);
      }


      bool bUnderline = ::str::case_insensitive_find("underline", m_strTextDecoration) >= 0;

      m_pfont->create_point_font(strName, dSize, iWeight, false, bUnderline);

      return true;

   }


   bool font::operator == (const font & font) const
   {
      
      return m_strFamily.case_insensitive_equals(font.m_strFamily)
             && m_strSize.case_insensitive_equals(font.m_strSize)
             && m_strWeight.case_insensitive_equals(font.m_strWeight)
             && m_strTextDecoration.case_insensitive_equals(font.m_strTextDecoration);
      
   }


} // namespace html



