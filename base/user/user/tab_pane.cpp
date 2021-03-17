// Created by Camilo 2021-01-08 <3TBS!!
#include "framework.h"
#include "base/user/user/_user.h"
#include "aqua/xml.h"
#include "tab_pane.h"


#define MAGIC_PALACE_TAB_SPLT "->:<-"


namespace user
{

   tab_pane::tab_pane() :
      m_brushFill(e_create),
      m_brushFillSel(e_create),
      m_brushFillHover(e_create)
   {

      m_bTabPaneVisible = true;
      m_bPermanent = false;

   }


   tab_pane::tab_pane(const ::user::tab_pane & tab_pane)
   {

      operator = (tab_pane);

   }


   tab_pane::~tab_pane()
   {

   }



   ::e_status tab_pane::initialize_tab_pane(class tab* ptab)
   {

      auto estatus = ::matter::initialize_matter(ptab);

      if(!estatus)
      {

         return estatus;

      }

      m_ptab = ptab;

      return estatus;

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

      auto psystem = get_system();

      auto pxml = psystem->xml();

      auto pdocument = pxml->create_document();

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



