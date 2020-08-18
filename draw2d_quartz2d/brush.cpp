#include "framework.h"


namespace draw2d_quartz2d
{
   
   
   brush::brush()
   {
      
      m_colorspaceref = nullptr;
      
      m_colorref = nullptr;
      
      m_gradientref = nullptr;
      
   }
   
   
   brush::~brush()
   {
   }
   

   void brush::dump(dump_context & dumpcontext) const
   {
      
      ::draw2d::object::dump(dumpcontext);
      
   }

   
   void brush::destroy()
   {
      
      if(m_gradientref != nullptr)
      {
         
         CGGradientRelease(m_gradientref);
         
         m_gradientref = nullptr;
         
      }
      
      if(m_colorref != nullptr)
      {
         
         CGColorRelease(m_colorref);
         
         m_colorref = nullptr;
         
      }
      
      if(m_colorspaceref != nullptr)
      {
         
         CGColorSpaceRelease(m_colorspaceref);
         
         m_colorspaceref = nullptr;
         
      }
      
      ::draw2d::brush::destroy();
      
   }

   
   bool brush::create(::draw2d::graphics * pgraphics, i8 iCreate)
   {
      
      if(m_etype == type_linear_gradient_point_color || m_etype == type_radial_gradient_color)
      {
         
         CGFloat locations[2];
         CGFloat components[8];
         
         //      CGColorSpaceRef colorspace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
         
         if(m_colorspaceref == nullptr)
         {
         
            m_colorspaceref = CGColorSpaceCreateDeviceRGB();
            
         }
         
         components[0] = m_color1.m_iR / 255.f;
         components[1] = m_color1.m_iG / 255.f;
         components[2] = m_color1.m_iB / 255.f;
         components[3] = m_color1.m_iA / 255.f;
         components[4] = m_color2.m_iR / 255.f;
         components[5] = m_color2.m_iG / 255.f;
         components[6] = m_color2.m_iB / 255.f;
         components[7] = m_color2.m_iA / 255.f;
         
         locations[0] = 0.0;
         locations[1] = 1.0;
         
         m_gradientref = CGGradientCreateWithColorComponents(m_colorspaceref, components, locations, 2);
         
         m_osdata[0] = m_gradientref;
         
      }
      else if(m_etype == type_solid)
      {

         CGFloat components[4];
         
         //      CGColorSpaceRef colorspace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
         
         if(m_colorspaceref == nullptr)
         {
            
            m_colorspaceref = CGColorSpaceCreateDeviceRGB();
            
         }

         components[0] = m_color.m_iR / 255.f;
         components[1] = m_color.m_iG / 255.f;
         components[2] = m_color.m_iB / 255.f;
         components[3] = m_color.m_iA / 255.f;
         
         m_colorref = CGColorCreate(m_colorspaceref, components);
         
         m_osdata[0] = m_colorref;
         
      }
      
      return true;
      
   }
   

} // namespace draw2d_quartz2d



