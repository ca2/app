#include "framework.h"


namespace draw2d
{


   pen::pen()
   {

      m_elinecapBeg           = ::draw2d::e_line_cap_flat;
      m_elinecapEnd           = ::draw2d::e_line_cap_flat;
      m_elinejoin             = ::draw2d::e_line_join_miter;
      m_color                 = ARGB(127, 0, 0, 0);
      m_epen                  = e_pen_solid;
      m_dWidth                = 1.0;
      m_epenalign             = e_pen_align_center;

   }


   pen::~pen()
   {

   }


   void pen::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      ::exception::throw_interface_only();
   }


   bool pen::create_null()
   {

      m_epen                  = e_pen_null;
      m_dWidth                = 0.0;
      m_color                 = ARGB(0, 0, 0, 0);
      
      set_modified();

      return true;

   }


   bool pen::create_solid(double dWidth, const ::color& color)
   {

      if (m_epen == e_pen_solid
            && dWidth >= (m_dWidth - 0.1)
            && dWidth <= (m_dWidth + 0.1)
            && m_color == color)
         return true;

      m_epen            = e_pen_solid;
      m_dWidth          = dWidth;
      m_color           = color;
      
      set_modified();

      return true;

   }


   bool pen::create_brush(double dWidth, ::draw2d::brush * pbrush)
   {

      m_epen = e_pen_brush;
      m_dWidth = dWidth;
      m_pbrush = pbrush;

      set_modified();

      return true;

   }


   pen & pen::operator = (const pen & penSrc)
   {

      m_epen            = penSrc.m_epen;
      m_dWidth          = penSrc.m_dWidth;
      m_color           = penSrc.m_color;
      m_pbrush          = penSrc.m_pbrush;
      m_elinecapBeg     = penSrc.m_elinecapBeg;
      m_elinecapEnd     = penSrc.m_elinecapEnd;
      m_elinejoin       = penSrc.m_elinejoin;
      m_epenalign       = penSrc.m_epenalign;
      set_modified();

      return *this;

   }


   enum_line_cap pen::get_beg_cap()
   {

      return m_elinecapBeg;

   }


   bool pen::set_beg_cap(enum_line_cap elinecapBeg)
   {

      m_elinecapBeg = elinecapBeg;

      return true;

   }


   enum_line_cap pen::get_end_cap()
   {

      return m_elinecapEnd;

   }


   bool pen::set_end_cap(enum_line_cap elinecapEnd)
   {

      m_elinecapEnd = elinecapEnd;

      return true;

   }


   enum_line_join pen::get_line_join()
   {

      return m_elinejoin;

   }

   
   bool pen::set_line_join(enum_line_join elinejoin)
   {

      m_elinejoin = elinejoin;
      
      set_modified();

      return true;

   }


} // namespace draw2d



