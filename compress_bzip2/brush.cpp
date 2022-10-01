#include "framework.h"





namespace draw2d_gdiplus
{


   brush::brush()
   {

      m_pthis = this;
      m_pbrush = nullptr;

   }

   brush::~brush()
   {

      destroy();

   }


#ifdef DEBUG

   void brush::dump(dump_context & dumpcontext) const
   {

      ::draw2d::object::dump(dumpcontext);

   }

#endif

   bool brush::create(::draw2d::graphics * pgraphics, ::i8 iCreate)
   {

      if(m_etype == type_solid)
      {

         try
         {

            m_pbrush = normal_new Gdiplus::SolidBrush(gdiplus_color(m_color));

         }
         catch(...)
         {

         }

      }
      else if(m_etype == type_linear_gradient_point_color)
      {

         try
         {

            m_pbrush = normal_new Gdiplus::LinearGradientBrush(
            Gdiplus::PointF((Gdiplus::REAL) m_point1.x,(Gdiplus::REAL) m_point1.y),
            Gdiplus::PointF((Gdiplus::REAL) m_point2.x,(Gdiplus::REAL) m_point2.y),
            gdiplus_color(m_color1),
               gdiplus_color(m_color2));

         }
         catch(...)
         {
         }
      }
      else if(m_etype == type_radial_gradient_color)
      {

         try
         {

            Gdiplus::GraphicsPath * ppath = normal_new Gdiplus::GraphicsPath();

            ppath->AddEllipse((Gdiplus::REAL) (m_point.x - m_size.cx / 2),(Gdiplus::REAL)(m_point.y - m_size.cy / 2),(Gdiplus::REAL) (m_size.cx),(Gdiplus::REAL) (m_size.cy));

            Gdiplus::PathGradientBrush * pgradientbrush = normal_new Gdiplus::PathGradientBrush(ppath);

            auto c1 = gdiplus_color(m_color1);
            auto c2 = gdiplus_color(m_color2);

            INT c = 1;

            pgradientbrush->SetCenterPoint(Gdiplus::PointF((Gdiplus::REAL) m_point.x,(Gdiplus::REAL) m_point.y));
            pgradientbrush->SetCenterColor(c1);
            pgradientbrush->SetSurroundColors(&c2,&c);

            m_pbrush = pgradientbrush;

         }
         catch(...)
         {
         }
      }
      else if (m_etype == type_pattern)
      {

         try
         {

            if (m_pimage->is_ok())
            {

               Gdiplus::Image * pimage = m_pimage->get_bitmap()->get_os_data < Gdiplus::Bitmap * >();

               if (::is_set(pimage))
               {

                  Gdiplus::TextureBrush* ptexturebrush = normal_new Gdiplus::TextureBrush(pimage);

                  m_pbrush = ptexturebrush;

               }

            }

         }
         catch (...)
         {

         }

      }
      else
      {

         try
         {

            m_pbrush = normal_new Gdiplus::SolidBrush(gdiplus_color(m_color));

         }
         catch(...)
         {

         }

      }

      m_osdata[0] = m_pbrush;

      return m_pbrush != nullptr;

   }


   void brush::destroy()
   {

      ::acme::del(m_pbrush);

      ::draw2d::brush::destroy();

   }




} // namespace draw2d_gdiplus



