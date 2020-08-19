#include "framework.h"


namespace draw2d
{


   pen::pen()
   {

      m_elinecapBeg           = line_cap_flat;
      m_elinecapEnd           = line_cap_flat;
      m_elinejoin             = line_join_miter;
      m_color                 = ARGB(127, 0, 0, 0);
      m_etype                 = type_solid;
      m_dWidth                = 1.0;
      m_ealign                = align_center;
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

      m_etype                 = type_null;
      m_dWidth                = 0.0;
      m_color                 = ARGB(0, 0, 0, 0);
      
      set_modified();

      return true;

   }


   bool pen::create_solid(double dWidth, COLORREF crColor)
   {

      if (m_etype == type_solid
            && dWidth >= (m_dWidth - 0.1)
            && dWidth <= (m_dWidth + 0.1)
            && m_color == crColor)
         return true;

      m_etype                 = type_solid;
      m_dWidth                = dWidth;
      m_color                 = crColor;
      
      set_modified();

      return true;

   }


   bool pen::create_brush(double dWidth, ::draw2d::brush * pbrush)
   {

      m_etype = type_brush;
      m_dWidth = dWidth;
      m_pbrush = pbrush;

      set_modified();

      return true;

   }


   pen & pen::operator = (const pen & penSrc)
   {

      m_etype           = penSrc.m_etype;
      m_dWidth          = penSrc.m_dWidth;
      m_color           = penSrc.m_color;
      m_pbrush          = penSrc.m_pbrush;
      m_elinecapBeg     = penSrc.m_elinecapBeg;
      m_elinecapEnd     = penSrc.m_elinecapEnd;
      m_elinejoin       = penSrc.m_elinejoin;
      set_modified();

      return *this;

   }

   pen::e_line_cap pen::get_beg_cap()
   {

      return m_elinecapBeg;

   }

   bool pen::set_beg_cap(e_line_cap elinecapBeg)
   {

      m_elinecapBeg = elinecapBeg;

      return true;

   }


   pen::e_line_cap pen::get_end_cap()
   {

      return m_elinecapEnd;

   }

   bool pen::set_end_cap(e_line_cap elinecapEnd)
   {

      m_elinecapEnd = elinecapEnd;

      return true;

   }


   pen::e_line_join pen::get_line_join()
   {

      return m_elinejoin;

   }

   
   bool pen::set_line_join(e_line_join elinejoin)
   {

      m_elinejoin = elinejoin;
      
      set_modified();

      return true;

   }


} // namespace draw2d



