#pragma once





struct CLASS_DECL_AURA gdi_object
{


   enum enum_type
   {
      type_undefined,
      type_pen,
      ::draw2d::e_pen_brush,
      type_bitmap,
      type_font,
   };

   enum enum_type      m_etype;

/*   gdi_object(enum_type etype = type_undefined) :
      m_etype(etype)
   {
   }*/

};



struct tag_WINDOW
{

   oswindow   m_window;

};

class CLASS_DECL_AURA device_context
{
public:


   //cairo_t *      m_pdc;

   device_context();


};



struct tagEXTLOGPEN :
   public gdi_object
{
    ::u32       elpPenStyle;
    ::u32       elpWidth;
    ::u32        elpBrushStyle;
    color32_t    elpColor;
    ulong_ptr   elpHatch;
    ::u32       elpNumEntries;
    ::u32       elpStyleEntry[1];
};


struct tagEXTLOGBRUSH :
   public gdi_object
{
	::u32        lbStyle;
	color32_t    lbColor;
	ulong_ptr   lbHatch;
};



struct tagLOGRGN :
   public gdi_object
{
	::u32        m_uiSize;
	byte *      m_puchData;
};




struct  tagFONTA :
   public gdi_object,
   public tagLOGFONTA
{

};




