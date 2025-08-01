// Created by Camilo 2021-01-08 <3TBS!!
#include "framework.h"
#include "tab.h"
#include "tab_pane.h"
//#include "acme/prototype/text/_.h"
#include "aura/graphics/draw2d/graphics_extension.h"
#include "aura/graphics/draw2d/brush.h"



#define MAGIC_PALACE_TAB_SPLT "->:<-"


namespace user
{

   
   tab_pane::tab_pane()
   {

      m_bTabPaneVisible = true;
      m_bPermanent = false;
      m_bNeedLayout = false;
      m_item.m_eelement = e_element_tab;

   }


   tab_pane::tab_pane(const ::user::tab_pane & tab_pane)
   {

      operator = (tab_pane);

   }


   tab_pane::~tab_pane()
   {

   }


   void tab_pane::initialize_tab_pane(class tab* ptab)
   {

      //auto estatus =
      
      ::property_object::initialize(ptab);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      m_ptab = ptab;

      __øconstruct(m_pbrushFill);
      __øconstruct(m_pbrushFillSel);
      __øconstruct(m_pbrushFillHover);

      m_pitemClose = __allocate ::item(e_element_close_tab_button);

      //return estatus;

   }


   tab_pane & tab_pane::operator = (const tab_pane & pane)
   {

      if (this != &pane)
      {

         m_ptab = pane.m_ptab;
         m_atomMatterId = pane.m_atomMatterId;
         m_textTitle = pane.m_textTitle;
         m_pimage = pane.m_pimage;
         m_pplaceholder = pane.m_pplaceholder;
         m_bTabPaneVisible = pane.m_bTabPaneVisible;
         m_bPermanent = pane.m_bPermanent;
         m_bNeedLayout = pane.m_bNeedLayout;

      }

      return *this;

   }


   string tab_pane::get_title()
   {

      return m_textTitle.get_text();

   }


   void tab_pane::set_title(const ::scoped_string & scopedstrTitle)
   {

      //string strTitle(scopedstrTitle);

      //auto psystem = system();

      //auto pxml = psystem->xml();

      //auto pdocument = pxml->create_document();

      //if (pdocument->load(strTitle))
      //{

      //   strTitle = pdocument->root()->get_value();

      //}

      m_textTitle = m_ptab->__text(scopedstrTitle);

      m_ptab->set_need_layout();

   }


   void tab_pane::do_split_layout(::draw2d::graphics_extension * pgraphicsextension, ::draw2d::graphics_pointer & pgraphics)
   {

      string_array straTitle = m_straTitle.c_stra();

      straTitle.explode(MAGIC_PALACE_TAB_SPLT, get_title());

      m_sizeaText.set_size(straTitle.get_count());

      for (int iTitle = 0; iTitle < straTitle.get_count(); iTitle++)
      {

         pgraphicsextension->get_text_extent(pgraphics, straTitle[iTitle], m_sizeaText[iTitle]);

      }

   }


} // namespace user



