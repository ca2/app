#pragma once


namespace draw2d_quartz2d
{

   
   class CLASS_DECL_DRAW2D_QUARTZ2D brush : 
      virtual public ::draw2d_quartz2d::object,
      virtual public ::draw2d::brush
   {
   public:
      
      
      CGGradientRef     m_gradientref;
      CGColorRef        m_colorref;
      CGColorSpaceRef   m_colorspaceref;
      
      
      brush();
      virtual ~brush();
      
      
      //virtual void * get_os_data() const;
      
      virtual bool create(::draw2d::graphics * pgraphics) override;

      virtual void destroy() override;
     
      virtual void dump(dump_context & dumpcontext) const override;

   };


} // namespace draw2d_quartz2d





