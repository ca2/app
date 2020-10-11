#pragma once


namespace draw2d_opengl
{


   class CLASS_DECL_DRAW2D_OPENGL font : 
      virtual public ::draw2d::font
   {
   public:

      
      HDC                           m_hdcFont;
      HFONT                         m_hfont;
      GLuint	                     m_baseFont;				// Base Display List For The Font Set

#ifdef WINDOWS
      GLYPHMETRICSFLOAT             m_gmf[256];	// Storage For Information About Our Outline Font Characters
#endif



      font();
      virtual ~font();


      virtual void construct(const ::draw2d::font & fontParam);

      
      virtual void dump(dump_context & dumpcontext) const;


      virtual bool create(::draw2d::graphics* pgraphics, i8 iCreate) override;
      virtual void destroy() override;


   };


} // namespace draw2d_opengl



