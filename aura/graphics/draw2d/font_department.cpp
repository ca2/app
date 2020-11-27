#include "framework.h"


#define FONTFACENAME_MENU FONT_SANS

#define FONTFACENAME_LUCIDA FONT_SANS


font_department::font_department()
   //,
   //m_fontCaption(e_create),
   //m_fontMenu(e_create),
   //m_fontStandard(e_create),
   //m_font(e_create),
   //m_fontListCtrl(e_create),
   //m_fontMeshCtrl(e_create),
   //m_fontGridCtrl(e_create)
{

   //m_pfontLyric = nullptr;
   //m_pfontLyricCompact = nullptr;
   //m_pH3TitleFonts = nullptr;
   m_bInitialized = false;
   //m_bLyric = false;

}


font_department::~font_department()
{

   finalize();

}



bool font_department::is_initialized()
{

   return m_bInitialized;

}


::estatus font_department::initialize(::layered * pobjectContext)
{

   if (is_initialized())
   {

      return false;

   }

   //::draw2d::graphics_pointer spgraphics(e_create);

   //if (spgraphics.is_null())
   //{

   //   return false;

   //}

   //spgraphics->CreateCompatibleDC(nullptr);

   //m_fontMenu->create_point_font(FONTFACENAME_MENU, 9);

   //m_font->create_point_font(FONTFACENAME_LUCIDA, 11, e_font_weight_bold);

   //m_fontStandard->create_point_font(FONTFACENAME_LUCIDA, 8);

   //m_fontCaption->create_point_font(FONTFACENAME_LUCIDA, 11);

   //m_fontListCtrl->create_point_font(FONTFACENAME_LUCIDA, 9);

   //m_fontMeshCtrl->create_point_font(FONTFACENAME_LUCIDA, 9);

   //m_fontGridCtrl->create_point_font(FONTFACENAME_LUCIDA, 9);

   ////CreateLyricViewFonts();

   m_bInitialized = true;

   return true;

}


void font_department::finalize()
{

   if (!is_initialized())
   {

      return;

   }

   m_bInitialized = false;

}


void font_department::defer_create_font_enumeration(::promise::subject * psubject)
{

   if (m_pfontenumeration.is_null())
   {

      m_pfontenumeration = __create_new < ::draw2d::font_enumeration >();
      
      m_pfontenumeration->check_need_update(psubject);

   }

}



