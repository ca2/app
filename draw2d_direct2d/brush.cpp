#include "framework.h"


namespace draw2d_direct2d
{


   brush::brush()
   {
      
      m_pthis = this;

   }


   brush::~brush()
   {

      destroy();

   }


   void brush::dump(dump_context & dumpcontext) const
   {

      ::draw2d::object::dump(dumpcontext);

   }


   bool brush::create(::draw2d::graphics* pgraphicsParam, ::i8 iCreate)
   {

      auto pgraphics = __graphics(pgraphicsParam);

      ::draw2d::lock draw2dlock;

      if (pgraphics->m_prendertarget == nullptr)
      {

         return false;

      }

      if(m_etype == type_solid)
      {

         if(m_psolidbrush == nullptr)
         {

            D2D1_COLOR_F color;

            __copy(color, m_color);

            pgraphics->m_prendertarget->CreateSolidColorBrush(color, &m_psolidbrush);

            if(m_psolidbrush != nullptr)
            {

               m_osdata[0] = (ID2D1Brush*)m_psolidbrush.Get();
               
               set_updated();

            }

         }

         return m_psolidbrush.Get();

      }
      else if(m_etype == type_linear_gradient_point_color)
      {

         if(m_plineargradientbrush == nullptr)
         {

            D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES prop{};

            //auto pointViewport = pgraphics->GetViewportOrg();
            ::point pointViewport(0, 0);

            prop.startPoint.x    = (FLOAT) m_point1.x + pointViewport.x;
            prop.startPoint.y    = (FLOAT) m_point1.y + pointViewport.y;
            prop.endPoint.x      = (FLOAT) m_point2.x + pointViewport.x;
            prop.endPoint.y      = (FLOAT) m_point2.y + pointViewport.y;

            // Create an array of gradient stops to put in the gradient stop
            // collection that will be used in the gradient brush.
            ::comptr<ID2D1GradientStopCollection> pstopcollection;

            D2D1_GRADIENT_STOP gradientstops[2] = {};

            __copy(gradientstops[0].color, m_color1);
            gradientstops[0].position = 0.0f;

            __copy(gradientstops[1].color, m_color2);
            gradientstops[1].position = 1.0f;

            // Create the ID2D1GradientStopCollection from a previously
            // declared array of D2D1_GRADIENT_STOP structs.
            HRESULT hr = pgraphics->m_prendertarget->CreateGradientStopCollection(gradientstops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &pstopcollection);

            D2D1_BRUSH_PROPERTIES brushproperties;

            brushproperties.opacity = 1.0f;
            brushproperties.transform =  D2D1::IdentityMatrix();

            hr = pgraphics->m_prendertarget->CreateLinearGradientBrush(&prop, &brushproperties, pstopcollection, &m_plineargradientbrush);

            if(m_plineargradientbrush != nullptr)
            {
               
               m_osdata[0] = (ID2D1Brush*)m_plineargradientbrush.Get();

               set_updated();

            }

         }

         return (ID2D1Brush *) m_plineargradientbrush.Get();

      }
      else if(m_etype == type_radial_gradient_color)
      {

         if(m_plineargradientbrush == nullptr)
         {

            // Create an array of gradient stops to put in the gradient stop
            // collection that will be used in the gradient brush.
            ID2D1GradientStopCollection *pgradientstops = nullptr;

            D2D1_GRADIENT_STOP gradientstops[2];

            __copy(gradientstops[0].color, m_color1);
            gradientstops[0].position = 0.0f;

            __copy(gradientstops[1].color, m_color1);
               gradientstops[1].position = 1.0f;

            // Create the ID2D1GradientStopCollection from a previously
            // declared array of D2D1_GRADIENT_STOP structs.
            HRESULT hr = pgraphics->m_prendertarget->CreateGradientStopCollection(
                         gradientstops,
                         2,
                         D2D1_GAMMA_2_2,
                         D2D1_EXTEND_MODE_CLAMP,
                         &pgradientstops
                         );

            // The center of the gradient is in the center of the box.
            // The gradient origin offset was set to zero(0, 0) or center in this case.
            if(SUCCEEDED(hr))
            {

               double centerx = m_size.cx - m_point.x;
               double centery = m_size.cy - m_point.y;
               double originx = m_size.cx / 2 -m_point.x;
               double originy = m_size.cy / 2 -m_point.y;
               double radiusx = m_size.cx / 2;
               double radiusy = m_size.cy / 2;

               hr = pgraphics->m_prendertarget->CreateRadialGradientBrush(
                    D2D1::RadialGradientBrushProperties(
                    D2D1::Point2F((FLOAT) (centerx), (FLOAT)(centery)),
                    D2D1::Point2F((FLOAT)(originx), (FLOAT)(originy)),
                    (FLOAT)(radiusx), (FLOAT)(radiusy)),
                    pgradientstops,
                    &m_pradialgradientbrush
                    );

            }

            pgradientstops->Release();

            if(m_pradialgradientbrush != nullptr)
            {

               m_osdata[0] = (ID2D1Brush*)m_pradialgradientbrush.Get();

               set_updated();

            }

         }

         return (ID2D1Brush *)m_pradialgradientbrush.Get();

      }
      else if (m_etype == type_pattern)
      {

         if (!::is_ok(m_pimage))
         {

            // succeeded and resume if and/or when there is a valid image.

            return false;

         }

         if (m_pimagebrush == nullptr)
         {

            auto imagebrushproperties = D2D1::ImageBrushProperties(
               D2D1::RectF(0, 0,(float) m_pimage->width(),(float) m_pimage->height()),
               D2D1_EXTEND_MODE_WRAP,
               D2D1_EXTEND_MODE_WRAP,
               D2D1_INTERPOLATION_MODE_LINEAR
            );

            m_pimage->unmap();

            ID2D1Image* pimage = m_pimage->m_pbitmap->get_os_data < ID2D1Bitmap * >();

            HRESULT hr = pgraphics->m_pdevicecontext->CreateImageBrush(
               pimage,
               imagebrushproperties,
               &m_pimagebrush);

            if (SUCCEEDED(hr) && m_pimagebrush != nullptr)
            {

               m_osdata[0] = (ID2D1Brush*)m_pimagebrush.Get();

               set_updated();

            }

         }

         return (ID2D1Brush*) m_pimagebrush.Get();

      }
      else
      {

         return (ID2D1Brush *) m_pbrush.Get();

      }

      return false;

   }


   void brush::destroy()
   {

      if(m_psolidbrush != nullptr)
      {

         m_psolidbrush = nullptr;

      }

      if(m_plineargradientbrush != nullptr)
      {

         m_plineargradientbrush = nullptr;

      }

      if(m_pbrush != nullptr)
      {

         m_pbrush = nullptr;

      }

      if (m_pimagebrush)
      {

         m_pimagebrush = nullptr;

      }

   }


} // namespace draw2d_direct2d



