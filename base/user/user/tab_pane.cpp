// Created by Camilo 2021-01-08 <3TBS!!
#include "framework.h"
#include "tab.h"
#include "tab_pane.h"
//#include "acme/primitive/text/_.h"
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

      m_pbrushFill.create(ptab);
      m_pbrushFillSel.create(ptab);
      m_pbrushFillHover.create(ptab);

      //return estatus;

   }


   tab_pane & tab_pane::operator = (const tab_pane & pane)
   {

      if (this != &pane)
      {

         m_ptab = pane.m_ptab;
         m_atom = pane.m_atom;
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


   void tab_pane::set_title(const ::string & pszTitle)
   {

      //string strTitle(pszTitle);

      //auto psystem = acmesystem()->m_pbasesystem;

      //auto pxml = psystem->xml();

      //auto pdocument = pxml->create_document();

      //if (pdocument->load(strTitle))
      //{

      //   strTitle = pdocument->root()->get_value();

      //}

      m_textTitle = m_ptab->__text(pszTitle);

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



