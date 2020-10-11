#include "framework.h"


#undef new


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


   pointd path::internal_last_point()
   {

      if(m_bHasPointInternal)
      {

         //return pointd((LONG) m_pointInternal.X, (LONG) m_pointInternal.Y);

         return pointd(0, 0);

      }
      else
      {

         __throw(::exception::exception("path does not have last point"));

      }

   }


   bool path::internal_begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode)
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

      //plusplus::Rect rect(x,y,cx,cy);

      //bool bOk2 = m_ppath->AddRectangle(rect) == plusplus::Status::Ok;


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


   pointd path::internal_current_point()
   {

      return m_pointLast;

   }


   bool path::internal_add_move(i32 x, i32 y)
   {

      m_pointLast.x = x;

      m_pointLast.y = y;

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



   bool path::internal_add_arc(const ::rect & rect, double iStart, double iAngle)
   {

      return true;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::arc& parc)
   {

      __throw(todo("::opengl::path"));

      return false;

   }

        
   bool path::_set(::draw2d::graphics* pgraphics, const ::line& pline)
   {

      __throw(todo("::opengl::path"));

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::lined& pline)
   {

      __throw(todo("::opengl::path"));

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::lines& pline)
   {

      __throw(todo("::opengl::path"));

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::linesd& pline)
   {

      __throw(todo("::opengl::path"));

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::rect& prect)
   {

      __throw(todo("::opengl::path"));

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::rectd& prect)
   {

      __throw(todo("::opengl::path"));

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::polygon& ppolygon)
   {

      __throw(todo("::opengl::path"));

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::polygond& ppolygond)
   {

      __throw(todo("::opengl::path"));

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::text_out& ptextout)
   {

      __throw(todo("::opengl::path"));

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::draw_text& pdrawtext)
   {

      __throw(todo("::opengl::path"));

      return false;

   }


} // namespace draw2d_opengl


#define new ACME_NEW



