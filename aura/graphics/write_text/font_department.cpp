#include "framework.h"


#define FONTFACENAME_MENU os_font_name(e_font_sans)

#define FONTFACENAME_LUCIDA os_font_name(e_font_sans)


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


::e_status font_department::initialize(::context_object * pcontextobject)
{

   if (is_initialized())
   {

      return false;

   }

   //auto estatus = __construct_new(m_pfontenumeration);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   

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


::e_status font_department::init1()
{

   enum_fonts(m_fontenumitema);

   return ::success;

}


void font_department::finalize()
{

   if (!is_initialized())
   {

      return;

   }

   m_bInitialized = false;

}


void font_department::defer_create_font_enumeration(::subject::subject * psubject)
{

   if (m_pfontenumeration.is_null())
   {

      m_pfontenumeration = __create_new < ::write_text::font_enumeration >();
      
      m_pfontenumeration->check_need_update(psubject);

   }

}




void font_department::enum_fonts(::write_text::font_enum_item_array & itema)
{

   UNREFERENCED_PARAMETER(itema);

}


void font_department::sorted_fonts(::write_text::font_enum_item_array & itema)
{

   enum_fonts(itema);

   ::sort::array::predicate_sort(itema, [&](auto & a, auto & b)
      {

         return a->m_strName < b->m_strName;

      });

}


string font_department::default_font_name()
{

   return "sans-serif";

}


double font_department::font_similarity(const char * pszSystem, const char * pszUser)
{

   if (::is_null(pszSystem) || ::is_null(pszUser))
   {

      return 0.0;

   }

   if (!stricmp(pszSystem, pszUser))
   {

      return 1.0;

   }

   return 0.0;

}
