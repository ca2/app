// Created by Camilo 2021-01-08 <3TBS!!
#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif
#include "aqua/xml.h"


#define MAGIC_PALACE_TAB_SPLT "->:<-"


namespace user
{


   tab_pane::tab_pane(const ::user::tab_pane & tab_pane)
   {

      operator = (tab_pane);

   }


   tab_pane::~tab_pane()
   {

   }


   tab_pane & tab_pane::operator = (const tab_pane & tab_pane)
   {

      if (this != &tab_pane)
      {

         m_ptab = tab_pane.m_ptab;
         m_id = tab_pane.m_id;
         m_strTitle = tab_pane.m_strTitle;
         m_pimage = tab_pane.m_pimage;
         m_pplaceholder = tab_pane.m_pplaceholder;
         m_bTabPaneVisible = tab_pane.m_bTabPaneVisible;
         m_bPermanent = tab_pane.m_bPermanent;
      }

      return *this;

   }


   string tab_pane::get_title()
   {

      return m_strTitle;

   }


   void tab_pane::set_title(const char * pszTitle)
   {

      string strTitle(pszTitle);

      auto pdocument = create_xml_document();

      if (pdocument->load(strTitle))
      {

         strTitle = pdocument->root()->get_value();

      }

      m_strTitle = strTitle;

      m_ptab->set_need_layout();

   }


   void tab_pane::do_split_layout(::draw2d::graphics_extension & dc, ::draw2d::graphics_pointer & pgraphics)
   {

      string_array straTitle = m_straTitle.c_stra();

      straTitle.explode(MAGIC_PALACE_TAB_SPLT, get_title());

      m_sizeaText.set_size(straTitle.get_count());

      for (int iTitle = 0; iTitle < straTitle.get_count(); iTitle++)
      {

         dc.GetTextExtent(pgraphics, straTitle[iTitle], m_sizeaText[iTitle]);

      }

   }


} // namespace user



