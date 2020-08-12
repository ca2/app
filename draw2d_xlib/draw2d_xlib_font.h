#pragma once

typedef struct _XftFont XftFont;



namespace draw2d_xlib
{


   class CLASS_DECL_DRAW2D_XLIB font :
      virtual public ::draw2d::font
   {
   public:

      Display * m_pdisplay;
      XFontStruct * m_pfont;
      XFontSet m_fontset;
      XftFont *      m_pft;

      font(::object * pobject);
      virtual ~font();


      virtual void * get_os_data() const;

      virtual void dump(dump_context & dumpcontext) const;


   };


} // namespace draw2d_xlib



