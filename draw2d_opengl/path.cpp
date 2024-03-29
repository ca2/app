#include "framework.h"
#include "_opengl.h"
#include "path.h"


namespace draw2d_opengl
{



   path::path()
   {

//      m_ppath = nullptr;


   }


   path::~path()
   {

      destroy();

   }


   //plusplus::GraphicsPath * path::get_os_path(plusplus::Graphics * pgraphics)
   //{

   //   if(m_bUpdated)
   //      return m_ppath;

   //   destroy();

   //   create(pgraphics);

   //   return m_ppath;

   //}


   point_f64 path::internal_last_point()
   {

      if(m_bHasPointInternal)
      {

         //return point_f64((::i32) m_pointInternal.X, (::i32) m_pointInternal.Y);

         return point_f64(0, 0);

      }
      else
      {

         throw ::exception(error_failed, "path does not have last point_i32");

      }

   }


   bool path::internal_begin_figure(bool bFill, ::draw2d::enum_fill_mode efillmode)
   {

      //return m_ppath->StartFigure() == plusplus::Status::Ok;

      return true;

   }

   bool path::internal_end_figure(bool bClose)
   {

      //if(bClose)
      //{

      //   m_bHasPointInternal = false;
      //   return m_ppath->CloseFigure() == plusplus::Status::Ok;

      //}
      //else
      //{
      //   m_bHasPointInternal = false;
      //   return true;

      //}

      return true;
   }

   bool path::internal_add_line(i32 x1, i32 y1, i32 x2, i32 y2)
   {

      ////bool bOk1 = true;

      ////if(m_bHasPointInternal)
      ////{

      ////   bOk1 = m_ppath->AddLine(m_pointInternal.X, m_pointInternal.Y, (FLOAT) x1, (FLOAT) y1) == plusplus::Status::Ok;

      ////}

      ////bool bOk2 = m_ppath->AddLine(x1, y1, x2, y2) == plusplus::Status::Ok;

      ////m_pointInternal.X = (plusplus::REAL) x2;
      ////m_pointInternal.Y = (plusplus::REAL) y2;

      ////m_bHasPointInternal = true;

      //return bOk1 && bOk2;

      return true;
   }


   bool path::internal_add_rect(i32 x,i32 y,i32 cx,i32 cy)
   {

      //plusplus::rectangle_i32 rectangle_i32(x,y,cx,cy);

      //bool bOk2 = m_ppath->AddRectangle(rectangle) == plusplus::Status::Ok;


      //return bOk2;

      return true;
   }

   bool path::internal_add_line(i32 x, i32 y)
   {

      //bool bOk1 = true;

      //if(m_bHasPointInternal)
      //{

      //   bOk1 = m_ppath->AddLine(m_pointInternal.X, m_pointInternal.Y, (FLOAT) x, (FLOAT) y) == plusplus::Status::Ok;

      //}

      //m_bHasPointInternal = true;

      //m_pointInternal.X = (plusplus::REAL) x;
      //m_pointInternal.Y = (plusplus::REAL) y;

      //return bOk1;

      return true;
   }


   point_f64 path::internal_current_point()
   {

      return m_pointLast;

   }


   bool path::internal_add_move(i32 x, i32 y)
   {

      m_pointLast.x() = x;

      m_pointLast.y() = y;

      return true;

   }


   bool path::internal_add_rect(double x,double y,double cx,double cy)
   {

      return true;

   }


   bool path::internal_add_move(double x,double y)
   {

      return true;

   }


   void path::destroy()
   {


   }



   bool path::internal_add_arc(const ::rectangle_i32 & rectangle, double iStart, double iAngle)
   {

      return true;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::arc_f64& parc)
   {

      throw ::exception(todo, "::opengl::path");

      return false;

   }

        
   bool path::_set(::draw2d::graphics* pgraphics, const ::line_f64& pline)
   {

      throw ::exception(todo, "::opengl::path");

      return false;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, const ::lined& pline)
   //{

   //   throw ::exception(todo("::opengl::path"));

   //   return false;

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const ::lines_f64& pline)
   {

      throw ::exception(todo, "::opengl::path");

      return false;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, const ::linesd& pline)
   //{

   //   throw ::exception(todo("::opengl::path"));

   //   return false;

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const ::rectangle_f64 & prectangle)
   {

      throw ::exception(todo, "::opengl::path");

      return false;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, const ::rectangle_f64& prectangle)
   //{

   //   throw ::exception(todo("::opengl::path"));

   //   return false;

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const ::polygon_f64& ppolygon)
   {

      throw ::exception(todo, "::opengl::path");

      return false;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, const ::polygon_f64& ppolygond)
   //{

   //   throw ::exception(todo("::opengl::path"));

   //   return false;

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const ::write_text::text_out& ptextout)
   {

      throw ::exception(todo, "::opengl::path");

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::write_text::draw_text& pdrawtext)
   {

      throw ::exception(todo, "::opengl::path");

      return false;

   }


} // namespace draw2d_opengl






