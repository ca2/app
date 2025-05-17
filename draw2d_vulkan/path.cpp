#include "framework.h"
#include "_vulkan.h"
#include "path.h"


namespace draw2d_vulkan
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


   double_point path::internal_last_point()
   {

      if(m_bHasPointInternal)
      {

         //return double_point((int) m_pointInternal.X, (int) m_pointInternal.Y);

         return double_point(0, 0);

      }
      else
      {

         throw ::exception(error_failed, "path does not have last int_point");

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

   bool path::internal_add_line(int x1, int y1, int x2, int y2)
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


   bool path::internal_add_rect(int x,int y,int cx,int cy)
   {

      //plusplus::int_rectangle int_rectangle(x,y,cx,cy);

      //bool bOk2 = m_ppath->AddRectangle(rectangle) == plusplus::Status::Ok;


      //return bOk2;

      return true;
   }

   bool path::internal_add_line(int x, int y)
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


   double_point path::internal_current_point()
   {

      return m_pointLast;

   }


   bool path::internal_add_move(int x, int y)
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



   bool path::internal_add_arc(const ::int_rectangle & rectangle, double iStart, double iAngle)
   {

      return true;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::double_arc& parc)
   {

      throw ::exception(todo, "::vulkan::path");

      return false;

   }

        
   bool path::_set(::draw2d::graphics* pgraphics, const ::double_line& pline)
   {

      throw ::exception(todo, "::vulkan::path");

      return false;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, const ::lined& pline)
   //{

   //   throw ::exception(todo("::vulkan::path"));

   //   return false;

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const ::double_lines& pline)
   {

      throw ::exception(todo, "::vulkan::path");

      return false;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, const ::linesd& pline)
   //{

   //   throw ::exception(todo("::vulkan::path"));

   //   return false;

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const ::double_rectangle & prectangle)
   {

      throw ::exception(todo, "::vulkan::path");

      return false;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, const ::double_rectangle& prectangle)
   //{

   //   throw ::exception(todo("::vulkan::path"));

   //   return false;

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const ::double_polygon& ppolygon)
   {

      throw ::exception(todo, "::vulkan::path");

      return false;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, const ::double_polygon& ppolygond)
   //{

   //   throw ::exception(todo("::vulkan::path"));

   //   return false;

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const ::write_text::text_out& ptextout)
   {

      throw ::exception(todo, "::vulkan::path");

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::write_text::draw_text& pdrawtext)
   {

      throw ::exception(todo, "::vulkan::path");

      return false;

   }


} // namespace draw2d_vulkan






