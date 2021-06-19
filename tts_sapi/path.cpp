#include "framework.h"


#undef new


bool almost_integer(double d)
{

   if (fmod(fabs(d), 1.0) < 0.01)
   {

      return true;

   }

   return false;
}

namespace draw2d_gdiplus
{



   path::path()
   {

      m_pthis = this;
      m_ppath = nullptr;
      m_bHasPath = false;

   }


   path::~path()
   {

      destroy();

   }



   point_f64 path::internal_last_point()
   {

      if(m_bHasPointInternal)
      {

         return point_f64((LONG) m_pointInternal.X, (LONG) m_pointInternal.Y);

      }
      else
      {

         throw ::exception::exception("path does not have last point_i32");

      }

   }


   bool path::internal_begin_figure()
   {

      if (m_ppath == nullptr)
      {

         return false;

      }

      try
      {

         return m_ppath->StartFigure() == Gdiplus::Status::Ok;

      }
      catch (...)
      {


      }


      return false;

   }


   bool path::internal_close_figure()
   {

      if (m_ppath == nullptr)
      {

         return false;

      }

      try
      {

         m_bHasPointInternal = false;

         return m_ppath->CloseFigure() == Gdiplus::Status::Ok;

      }
      catch (...)
      {


      }

      m_bHasPointInternal = false;

      return true;

   }


   bool path::internal_add_line(double x1, double y1, double x2, double y2)
   {


      if (m_ppath == nullptr)
      {

         return false;

      }

      bool bOk1 = false;

      bool bOk2 = false;

      try
      {

         bOk1 = true;

         if (m_bHasPointInternal)
         {
            if (almost_integer(m_pointInternal.X)
                  && almost_integer(m_pointInternal.Y)
                  && almost_integer(x1)
                  && almost_integer(x2))
            {

               bOk1 = m_ppath->AddLine((INT) m_pointInternal.X, (INT)m_pointInternal.Y, (INT)x1, (INT)y1) == Gdiplus::Status::Ok;

            }
            else
            {

               bOk1 = m_ppath->AddLine(m_pointInternal.X, m_pointInternal.Y, (FLOAT)x1, (FLOAT)y1) == Gdiplus::Status::Ok;

            }

         }

         if (bOk1)
         {

            if (almost_integer(m_pointInternal.X)
                  && almost_integer(m_pointInternal.Y)
                  && almost_integer(x1)
                  && almost_integer(x2))
            {

               bOk2 = m_ppath->AddLine((INT) x1, (INT) y1, (INT) x2, (INT) y2) == Gdiplus::Status::Ok;

            }
            else
            {

               bOk2 = m_ppath->AddLine((FLOAT)x1, (FLOAT)y1, (FLOAT)x2, (FLOAT)y2) == Gdiplus::Status::Ok;

            }

         }

         m_pointInternal.X = (Gdiplus::REAL) x2;
         m_pointInternal.Y = (Gdiplus::REAL) y2;

         m_bHasPointInternal = true;

      }
      catch (...)
      {

      }

      return bOk1 && bOk2;

   }


   bool path::internal_add_rect(double x,double y, double cx, double cy)
   {

      if (m_ppath == nullptr)
      {

         return false;

      }

      bool bOk2 = false;

      if (almost_integer(x) && almost_integer(cx) && almost_integer(y) && almost_integer(cy))
      {

         Gdiplus::Rect rectangle_i32(
         (INT) (x),
         (INT)(y),
         (INT)(cx),
         (INT)(cy)
         );

         try
         {

            bOk2 = m_ppath->AddRectangle(rectangle) == Gdiplus::Status::Ok;

         }
         catch (...)
         {


         }

      }
      else
      {

         Gdiplus::RectF rectangle_i32(
         (float)(x),
         (float)(y),
         (float)(cx),
         (float)(cy)
         );

         try
         {

            bOk2 = m_ppath->AddRectangle(rectangle) == Gdiplus::Status::Ok;

         }
         catch (...)
         {


         }
      }

      return bOk2;

   }


   //bool path::internal_add_line(double x, double y)
   //{

   //   bool bOk1 = true;

   //   if(m_bHasPointInternal)
   //   {

   //      if (almost_integer(m_pointInternal.X)
   //            && almost_integer(m_pointInternal.Y)
   //            && almost_integer(x)
   //            && almost_integer(y))
   //      {

   //         bOk1 = m_ppath->AddLine((INT) m_pointInternal.X, (INT)m_pointInternal.Y, (INT)x, (INT)y) == Gdiplus::Status::Ok;

   //      }
   //      else
   //      {

   //         bOk1 = m_ppath->AddLine((FLOAT)m_pointInternal.X, (FLOAT) m_pointInternal.Y, (FLOAT)x, (FLOAT)y) == Gdiplus::Status::Ok;

   //      }

   //   }

   //   m_bHasPointInternal = true;

   //   m_pointInternal.X = (Gdiplus::REAL) x;
   //   m_pointInternal.Y = (Gdiplus::REAL) y;

   //   return bOk1;

   //}

   point_f64 path::internal_current_point()
   {

      return get_current_point();

   }


   //bool path::internal_add_move(double x, double y)
   //{

   //   if(!m_bHasPointInternal)
   //   {
   //      //internal_begin_figure(m_bFill,m_efillmode);

   //      internal_begin_figure();

   //   }

   //   m_pointInternal.X   = (Gdiplus::REAL) x;
   //   m_pointInternal.Y   = (Gdiplus::REAL) y;
   //   m_bHasPointInternal     = true;
   //   m_bHasPath = false;


   //   return true;

   //}


   bool path::create(::draw2d::graphics * pgraphicsParam, ::i8 iCreate)
   {

      auto pgdiplusgraphics = __graphics(pgraphicsParam);

      if (::is_null(pgdiplusgraphics))
      {

         return false;

      }

      auto pgraphics = pgdiplusgraphics->m_pgraphics;

      if (::is_null(pgraphics))
      {

         return false;

      }

      if(m_efillmode == ::draw2d::fill_mode_winding)
      {

         m_ppath = new Gdiplus::GraphicsPath(Gdiplus::FillModeWinding);

      }
      else
      {

         m_ppath = new Gdiplus::GraphicsPath(Gdiplus::FillModeAlternate);

      }

      m_bHasPoint = false;

      m_pointInternal.X = 69;

      m_pointInternal.Y = 69;

      m_bHasPointInternal = false;

      //if(m_elementa.get_count() != 1 && m_elementa[0].m_etype != matter::type_string)
      {
         //internal_begin_figure(m_bFill,m_efillmode);
      }

      //for(i32 i = 0; i < m_elementa.get_count(); i++)
      //{

        // set(pgraphicsParam, m_elementa(i));

      //}

      _set_create(pgraphicsParam);

      m_osdata[0] = m_ppath;

      return true;

   }


   void path::destroy()
   {

      ::acme::del(m_ppath);

   }



   bool path::internal_add_arc(const ::rectangle_f64 & rectangle, const ::angle& angleBeg, const ::angle& angleEnd)
   {

      if (m_ppath == nullptr)
      {

         return false;

      }

      try
      {


         ::Gdiplus::RectF rectangle_f32((Gdiplus::REAL) rectangle.left, (Gdiplus::REAL) rectangle.top, (Gdiplus::REAL) width(rectangle), (Gdiplus::REAL) height(rectangle));


         m_ppath->AddArc(rectangle_f32, (Gdiplus::REAL) angleBeg.degree(), (Gdiplus::REAL) (angleEnd - angleBeg).degree());

         ::Gdiplus::PointF point_i32;

         m_ppath->GetLastPoint(&point);

         m_pointInternal.X = point.X;
         m_pointInternal.Y = point.Y;

      }
      catch (...)
      {

      }

      return true;

   }


   bool path::internal_add_text_out(::draw2d::graphics * pgraphics,i32 x,i32 y,const string & strText,::write_text::font * pfont)
   {

      if (m_ppath == nullptr)
      {

         return false;

      }

      try
      {

         Gdiplus::FontFamily fontFamily;

         Gdiplus::StringFormat format(Gdiplus::StringFormat::GenericTypographic());

         wstring wstr(strText);

         Gdiplus::REAL dSize = (Gdiplus::REAL) pfont->m_dFontSize;

         Gdiplus::Unit unit = __graphics(pgraphics)->m_pgraphics->GetPageUnit();

         switch (unit)
         {

         case Gdiplus::UnitMillimeter:
            dSize = dSize * 25.4f / __graphics(pgraphics)->m_pgraphics->GetDpiY();
            break;

         case Gdiplus::UnitInch:

            dSize = dSize / __graphics(pgraphics)->m_pgraphics->GetDpiY();
            break;
         case Gdiplus::UnitPoint:

            dSize = dSize * 72.0f / __graphics(pgraphics)->m_pgraphics->GetDpiY();
            break;

         }

         auto pdrawdgdiplusfont = __font(pfont);

         auto pfont = pdrawdgdiplusfont->get_os_data < Gdiplus::Font * > (pgraphics);

         INT iStyle = pfont->GetStyle();

         pfont->GetFamily(&fontFamily);
         //      Gdiplus::Status status;

         //Gdiplus::StringFormat format();

         format.SetFormatFlags(format.GetFormatFlags()
                               | Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
                               | Gdiplus::StringFormatFlagsLineLimit | Gdiplus::StringFormatFlagsNoWrap
                               | Gdiplus::StringFormatFlagsNoFitBlackBox);


         format.SetLineAlignment(Gdiplus::StringAlignmentNear);


         m_ppath->AddString(wstr, (INT)wstr.get_length(), &fontFamily, iStyle, dSize, Gdiplus::Point(x, y), &format);

      }
      catch (...)
      {

      }

      return true;

   }


   bool path::internal_add_draw_text(::draw2d::graphics * pgraphics, const ::rectangle_i32 & rectParam, const string & strText, ::write_text::font * pfont, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      ::rectangle_f64 rectangle(rectParam);

      auto estatus = gdiplus_draw_text(pgraphics, this, strText, rectangle, ealign, edrawtext, pfont, 1.0);

      return !estatus;

   }

   
   bool path::_set(::draw2d::graphics* pgraphics, const enum_shape& eshape)
   {

      if (eshape == e_shape_begin_figure)
      {

         return true;

      }
      else if(eshape == e_shape_close_figure)
      {

         internal_close_figure();

         return true;

      }
      else
      {

         return ::draw2d::path::_set(pgraphics, eshape);

      }


   }


   bool path::_set(::draw2d::graphics * pgraphics, const ::arc & arc)
   {

      ::rectangle_f64 rectangle;

      rectangle.left      = arc.m_pointCenter.x - arc.m_sizeRadius.cx;
      rectangle.right     = arc.m_pointCenter.x + arc.m_sizeRadius.cx;
      rectangle.top       = arc.m_pointCenter.y - arc.m_sizeRadius.cy;
      rectangle.bottom    = arc.m_pointCenter.y + arc.m_sizeRadius.cy;

      //if (!m_bHasPath && m_bHasPointInternal)
      //{

      //   internal_add_line(parc->m_pointBegin.x, parc->m_pointBegin.y);

      //}

      bool bOk = internal_add_arc(rectangle,arc.m_angleBeg, arc.m_angleEnd2);

      return bOk;

   }


   bool path::_set(::draw2d::graphics * pgraphics, const ::rectangle_i32 & rectangle)
   {

      return internal_add_rect(rectangle.left, rectangle.top,  rectangle.width(), rectangle.height());

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::rectangle_f64& rectangle)
   {

      return internal_add_rect(rectangle.left, rectangle.top, rectangle.width(), rectangle.height());

   }


   bool path::_set(::draw2d::graphics * pgraphics, const ::line & line)
   {

      return internal_add_line(line.m_p1.x, line.m_p1.y, line.m_p2.x, line.m_p2.y);

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::lined& line)
   {

      return internal_add_line(line.m_p1.x, line.m_p1.y, line.m_p2.x, line.m_p2.y);

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::lines & lines)
   {

      ::array < Gdiplus::PointF > pointa;
      
      pointa.set_size(lines.get_count());

      for (::index i = 0; i < pointa.get_size(); i++)
      {

         __copy(pointa[i], lines[i]);

      }

      m_ppath->AddLines(pointa.get_data(), (INT) pointa.get_count());

      return true;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::linesd& lines)
   {

      ::array < Gdiplus::PointF > pointa;

      pointa.set_size(lines.get_count());

      for (::index i = 0; i < pointa.get_size(); i++)
      {

         __copy(pointa[i], lines[i]);

      }

      m_ppath->AddLines(pointa.get_data(), (INT)pointa.get_count());

      return true;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::polygon_i32 & polygon_i32)
   {

      ::array < Gdiplus::PointF > pointa;

      pointa.set_size(polygon_i32.get_count());

      for (::index i = 0; i < pointa.get_size(); i++)
      {

         __copy(pointa[i], polygon_i32[i]);

      }

      m_ppath->AddPolygon(pointa.get_data(), (INT) pointa.get_count());

      return true;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::polygon_f64& polygon_i32)
   {

      ::array < Gdiplus::PointF > pointa;

      pointa.set_size(polygon_i32.get_count());

      for (::index i = 0; i < pointa.get_size(); i++)
      {

         __copy(pointa[i], polygon_i32[i]);

      }

      m_ppath->AddPolygon(pointa.get_data(), (INT)pointa.get_count());

      return true;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::text_out & textout)
   {

      return internal_add_text_out(
         pgraphics,
         (i32)textout.m_point.x,
         (i32)textout.m_point.y,
         textout.m_strText,
         textout.m_pfont);

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::draw_text & drawtext)
   {

      return internal_add_draw_text(
         pgraphics,
         drawtext.m_rectangle, 
         drawtext.m_strText, 
         drawtext.m_pfont, 
         drawtext.m_ealign,
         drawtext.m_edrawtext);

   }






   bool path::contains(::draw2d::graphics_pointer& pgraphics, const point_f64& point)
   {

      return ::draw2d::path::contains(pgraphics, point);

      auto pospath = get_os_data < Gdiplus::GraphicsPath *>(pgraphics);

      if (is_null(pospath))
      {

         return false;

      }

      Gdiplus::PointF p((FLOAT) point.x, (FLOAT) point.y);

      return pospath->IsVisible(p);

   }

} // namespace draw2d_gdiplus


