#pragma once



class CLASS_DECL_AURA image :
   virtual public image_base
{
public:


   ::image_pointer        m_pimpl;
   image_dynamic        m_dynamic;
   static ::mutex *     s_pmutex;


   image();
   image(std::nullptr_t);
   image(::object * pobject);
   image(::image * pimage);
   image(const ::image_pointer & pimpl);
   image(::image_pointer && pimpl);
   image(const image & image);
   image(image && image);
   virtual ~image();



   inline bool is_traited(::u64 u, ::u64 uTrait)
   {

      return is_set() && m_pimpl->is_traited(u, uTrait);

   }


   static ::mutex * ::mutex();

   virtual bool create_thumbnail(const char * pszPath) override;

   virtual bool create(::object * pobject, color32_t * pcolorref, int w, int h, int scan);

   //virtual void defer_save_to_cache() override;


   virtual ::image_pointer get_image(enum_image eimage);

   inline ::image_pointer operator + (enum_image eimage)
   {

      return get_image(eimage);

   }

   //virtual bool save_to_image(const ::file::path & pathDib) override;
   //virtual bool load_from_image(const ::file::path & pathDib) override;



//   virtual bool dispose_current_frame() override;
//   virtual bool overlay_frame(int iFrame) override;
   virtual void defer_update()  override;


   inline ::image_pointer frame() const { return m_pimpl; }

   inline image_frame_array * frames() const
   {

      if (m_pimpl.is_null())
      {

         return nullptr;

      }

      return m_pimpl->m_pimagepointera;

   }

   inline ::image_pointer frame(iptr i) const;

   virtual image get_image(::payload varFile, bool bSync = false) override;
   virtual image matter_image(string strMatter, bool bSync = false) override;
   virtual image load_image(::payload varFile, bool bCreateHelperMaps = false) override;
   virtual image load_matter_image(const char * pszMatter, bool bCache = true, bool bCreateHelperMaps = false) override;
   virtual image load_matter_icon(string_array & straMatter, string strIcon) override;
   virtual image load_thumbnail(::payload varFile, int w, int h) override;
   virtual image load_thumbnail(const char * pszPath) override;
   virtual image load_dib(const ::file::path & pathDib) override;


   virtual bool save_image(::payload varFile, ::save_image * psaveimage = nullptr) override;
   virtual bool save_dib(const ::file::path & pathDib) override;



   virtual ::draw2d::graphics * get_graphics() const override; // is semantically const (besides may not be implementationly constant)
   virtual ::draw2d::bitmap_pointer get_bitmap() const  override;// is semantically const (besides may not be implementationly constant)
   virtual ::draw2d::bitmap_pointer detach_bitmap() override;

   virtual ::count get_image_count() const override;
   virtual ::image_pointer get_image(iptr i) override;

   virtual bool set_mipmap(::draw2d::e_mipmap emipmap) override;
   virtual bool _set_mipmap(::draw2d::e_mipmap emipmap) override;

   //virtual bool add_next(double dRate)
   virtual bool create_isotropic(::image * pimage) override;
   virtual bool create_isotropic(double_array & daRate, ::e_priority epriority) override;

   virtual bool SetViewportOrg(const ::point & point) override;
   virtual bool set_font_factor(double dFactor) override;
   virtual bool set_alpha_mode(::draw2d::enum_alpha_mode enum_alpha_mode) override;


   virtual bool create_helper_map() override;

   virtual bool on_load_image() override;
   virtual bool on_exif_orientation() override;


   virtual ::size get_size() const override;


   virtual bool rate_rgb(int iMul, int iDiv) override;
   virtual bool dc_select(bool bSelect = true) override;

   virtual color32_t GetAverageColor() override;
   virtual color32_t GetAverageOpaqueColor() override;
   virtual bool blend(::image * pimage, ::image * pimageRate) override;
   virtual bool Blend(::image * pimage, ::image * pimageA, i32 A) override;
   virtual bool Blend(::image * pimage, ::image * pimageA) override;
   virtual bool blend(const ::point & pointDst, ::image * pimageSrc, const ::point & pointSrc, ::image * pimageAlf, const ::point & pointDstAlf, const ::size & size) override;
   virtual bool precision_blend(const ::point & pointDst, ::image * pimageAlf, const ::point & pointAlf, const ::size & size) override;
   virtual bool precision_blend(const ::point & pointDst, ::image * pimageAlf, const ::point & pointAlf, const ::size & size, byte bA) override;
   virtual bool blend(const ::point & pointDst, ::image * pimageAlf, const ::point & pointAlf, const ::size & size) override;
   virtual bool blend(const ::point & pointDst, ::image * pimageAlf, const ::point & pointAlf, const ::size & size, byte bA) override;
   virtual bool blend2(const ::point & pointDst, ::image * pimageSrc, const ::point & pointSrc, const ::size & size, byte bA) override;
   virtual bool fork_blend(const ::point & pointDst, ::image * pimageAlf, const ::point & pointAlf, const ::size & size) override;
   virtual bool fork_blend(const ::point & pointDst, ::image * pimageAlf, const ::point & pointAlf, const ::size & size, byte bA) override;
   virtual bool bitmap_blend(::draw2d::graphics_pointer & pgraphics, const ::rect & rect) override;

   virtual bool color_blend(color32_t cr, byte bAlpha) override;
   virtual bool BitBlt(::image * pimage, i32 op) override;
   virtual bool BitBlt(int cxParam, int cyParam, ::image * pimage, i32 op) override;
   virtual i32 cos(i32 i, i32 iAngle) override;
   virtual i32 sin(i32 i, i32 iAngle) override;
   virtual i32 cos10(i32 i, i32 iAngle) override;
   virtual i32 sin10(i32 i, i32 iAngle) override;
   virtual bool hue_offset(double dRate) override;


   virtual bool map(bool bApplyAlphaTransform = true) const override; // some implementations may requrire to map to m_pcolorref before manipulate it
   virtual bool unmap() const  override;// some implementations may require to unmap from m_pcolorref to update *os* bitmap
   virtual bool set_mapped() override;

   virtual bool flip_vertical(::image * pimage) override;
   virtual bool flip_horizontal(::image * pimage) override;
   virtual bool flipx(::image * pimage) override;
   virtual bool flipy(::image * pimage) override;
   virtual ::image_pointer flipx() override;
   virtual ::image_pointer flipy() override;

   virtual bool is_rgb_black() override;
   virtual bool do_xor(::image * pimage) override;

   virtual bool ToAlpha(i32 i) override;
   virtual bool ToAlphaAndFill(i32 i, color32_t cr) override;
   virtual bool GrayToARGB(color32_t cr) override;

   virtual bool from_alpha() override;
   virtual bool mult_alpha(::image * pimageWork, bool bPreserveAlpha = true) override;

   virtual bool mult_alpha() override;
   virtual bool mult_alpha_fast() override;
   virtual bool div_alpha() override;

   virtual bool mult_alpha(const ::point & point, const ::size & size) override;
   virtual bool div_alpha(const ::point & point, const ::size & size) override;

   virtual bool rotate(::image * pimage, const ::rect & rect, double dAngle, double dScale) override;

   virtual bool rotate(::image * pimage, double dAngle, double dScale) override;
   virtual bool rotate(::image * pimage, double dAngle) override;
   virtual bool Rotate034(::image * pimage, double dAngle, double dScale) override;

   virtual bool rotate90(::image * pimage) override;
   virtual bool rotate180(::image * pimage) override;
   virtual bool rotate270(::image * pimage) override;
   virtual bool rotate90() override;
   virtual bool rotate180() override;
   virtual bool rotate270() override;
   virtual bool rotate90flipx(::image * pimage) override;
   virtual bool rotate180flipx(::image * pimage) override;
   virtual bool rotate270flipx(::image * pimage) override;
   virtual bool rotate90flipx() override;
   virtual bool rotate180flipx() override;
   virtual bool rotate270flipx() override;


   virtual bool set_rgb(color32_t cr) override;
   virtual bool set_rgb(i32 R, i32 G, i32 B) override;
   virtual bool tint(::image * pimage, const rgb & rgb) override;
   virtual bool set_rgb_pre_alpha(i32 R, i32 G, i32 B, i32 A) override;
   virtual bool rgb_from(::image * pimage) override;
   virtual bool paint_rgb(::color::color color) override;


   virtual bool saturation(double dRate) override;
   virtual bool lightness(double dRate) override;
   virtual bool opacity(double dRate) override;


   virtual bool SetIconMask(::draw2d::icon * picon, i32 cx, i32 cy) override;
   virtual bool RadialFill(byte a, byte rect, byte g, byte b, i32 x, i32 y, i32 iRadius) override;
   virtual bool RadialFill(
   byte a1, byte r1, byte g1, byte b1, // center colors
   byte a2, byte r2, byte g2, byte b2, // border colors
   i32 x, i32 y, i32 iRadius) override;

   virtual bool gradient_fill(color32_t clr1, color32_t clr2, const point & point1, const point & point2) override;
   virtual bool gradient_horizontal_fill(color32_t clr1, color32_t clr2, int start, int end) override;
   virtual bool gradient_vertical_fill(color32_t clr1, color32_t clr2, int start, int end) override;
   virtual bool gradient_horizontal_fill(color32_t clr1, color32_t clr2) override;
   virtual bool gradient_vertical_fill(color32_t clr1, color32_t clr2) override;

   virtual u32 GetPixel(i32 x, i32 y) override;
   inline u32 GetPixel(const ::point & point) { return GetPixel(point.x, point.y); }
   virtual bool Mask(color32_t crMask, color32_t crInMask, color32_t crOutMask) override;
   virtual bool channel_mask(byte uchFind, byte uchSet, byte uchUnset, color::e_channel echannel) override;
   virtual bool transparent_color(::color::color color) override;

   virtual bool create(const ::size & size, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1) override;
   virtual bool create(i32 iWidth, i32 iHeight, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1) override;
   virtual bool host(const pixmap * ppixmap) override;
   virtual bool on_host_read_pixels(const pixmap* ppixmap) override;
   virtual bool create(::draw2d::graphics_pointer & pgraphics) override;
   virtual bool destroy() override;
   //virtual bool detach(::image * pimage) override;
   //{
   //   return m_pimpl->detach(pimage);
   //}

   // realization is semantically const
   // image keeps an image and image will be the same,
   // besides the way the Device Context associated with the image (m_spgraphics)
   // interprets or deals with it, may change
   virtual bool realize(::draw2d::graphics_pointer & pgraphics) const override;
   virtual bool unrealize() const override;
   virtual bool is_realized() const override;
   virtual bool defer_realize(::draw2d::graphics_pointer & pgraphics) const override;

   virtual bool DivideRGB(i32 iDivide) override;
   virtual bool DivideARGB(i32 iDivide) override;
   virtual bool DivideA(i32 iDivide) override;


   virtual bool stretch_image(::image * pimage) override;


   virtual bool to(::image * pimage) const override;
   virtual bool from(const ::image * pimage) override;
   virtual bool from(::draw2d::graphics_pointer & pgraphics) override;
   virtual bool from(const ::point & pointDst, ::draw2d::graphics_pointer & pgraphics, const ::point & pointSrc, const ::size & size) override;
   virtual bool from(const ::point & pointDst, ::image * pimage, const ::point & pointSrc, const ::size & size) override;
   virtual bool from(const ::point & pointDst, ::image * pimage, const ::point & pointSrc, const ::size & size, byte bA) override;
   //virtual bool blend(const ::point & pointDst, ::image * pimage, const ::point & pointSrc, const ::size & size)
   virtual bool from_ignore_alpha(const ::point & pointDst, ::image * pimage, const ::point & pointSrc, const ::size & size) override;

   virtual bool to(::draw2d::graphics_pointer & pgraphics) override;
   virtual bool to(::draw2d::graphics_pointer & pgraphics, const ::point & point) override;
   virtual bool to(::draw2d::graphics_pointer & pgraphics, const ::size & size) override;
   virtual bool to(::draw2d::graphics_pointer & pgraphics, const ::point & point, const ::size & size) override;
   virtual bool to(::draw2d::graphics_pointer & pgraphics, const ::rect & rect) override;

   virtual bool to(::draw2d::graphics_pointer & pgraphics, const ::point & point, const ::size & size, const ::point & pointSrc) override;


   virtual bool pixelate(i32 iSize) override;




   virtual bool fill_channel(i32 C, color::e_channel echannel) override;
   virtual bool white_fill_channel(i32 C, color::e_channel echannel) override;
   virtual bool fill_byte(uchar uch) override;
   virtual bool fill(color32_t level) override;
   virtual bool fill(i32 A, i32 R, i32 G, i32 B) override;
   //      virtual bool Fill(i32 R, i32 G, i32 B)
   //virtual bool set(i32 R, i32 G, i32 B) override;
   virtual bool fill_glass(i32 R, i32 G, i32 B, i32 A) override;
   virtual bool fill_stippled_glass(i32 R, i32 G, i32 B) override;
   virtual bool invert() override;
   virtual bool channel_invert(color::e_channel echannel) override;
   virtual bool channel_multiply(double dRate, color::e_channel echannel, bool bIfAlphaIgnorePreDivPosMult = false) override;
   virtual bool channel_multiply(color::e_channel echannel, ::image * pimage, bool bIfAlphaIgnorePreDivPosMult = false) override;
   virtual bool channel_lighten(color::e_channel echannel, ::image * pimage) override;
   virtual bool channel_darken(color::e_channel echannel, ::image * pimage) override;
   virtual bool channel_from(color::e_channel echannel, ::image * pimage) override;
   virtual bool channel_multiply(color::e_channel echannel, ::image * pimage, const ::rect & rect, bool bIfAlphaIgnorePreDivPosMult = false) override;

   virtual bool channel_from(color::e_channel echannel, ::image * pimage, const ::rect & rect) override;

   virtual bool channel_copy(color::e_channel echannelDst, color::e_channel echannelSrc) override;
   virtual bool channel_copy(color::e_channel echannelDst, color::e_channel echannelSrc, ::image * pimage) override;

   virtual bool Map(i32 ToRgb, i32 FromRgb) override;

   virtual bool create_nanosvg(char * pszXml, double dDpi = 0.0) override;
   virtual bool nanosvg(char * pszXml, double dDpi = 0.0) override;

   virtual bool op(string str) override;

   //virtual bool from( ::image * pimage)

   virtual bool Blend(::image * pimage, i32 A) override;
   virtual bool Darken(::image * pimage) override;
   virtual bool Difference(::image * pimage) override;
   virtual bool Lighten(::image * pimage) override;
   virtual bool Multiply(::image * pimage) override;
   virtual bool Screen(::image * pimage) override;

   virtual bool lighten(double dRate) override;

   virtual bool copy(::image * pimage, i32 x, i32 y) override;
   virtual bool PasteRect(::image * pimage, i32 x, i32 y) override;

   virtual bool fill_rectangle(const ::rect & rect, color32_t cr) override;

   virtual bool fill_rectangle(const ::rect & rect, i32 R, i32 G, i32 B) override;


   virtual bool fill_glass_rect(const ::rect & rect, i32 R, i32 G, i32 B, i32 A) override;

   virtual bool fill_stippled_glass_rect(const ::rect & rect, i32 R, i32 G, i32 B) override;


   virtual bool BlendRect(::image * pimage, i32 x, i32 y, i32 A) override;
   virtual bool DarkenRect(::image * pimage, i32 x, i32 y) override;
   virtual bool DifferenceRect(::image * pimage, i32 x, i32 y) override;
   virtual bool LightenRect(::image * pimage, i32 x, i32 y) override;
   virtual bool MultiplyRect(::image * pimage, i32 x, i32 y) override;
   virtual bool ScreenRect(::image * pimage, i32 x, i32 y) override;

   virtual bool horizontal_line(i32 y, i32 R, i32 G, i32 B, i32 A = 0, i32 x1 = 0, i32 x2 = -1) override;
   virtual bool Line(i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B) override;
   virtual bool LineGlass(i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B, i32 A) override;

   virtual bool create_frame(const ::size & size, i32 iFrameCount) override;
   virtual bool set_frame2(void * pdata, i32 iFrame, i32 iFrameCount) override;

   virtual bool set_frame1(void * pdata, i32 iFrame, i32 iFrameCount) override;

   virtual bool get_frame(void * pdata, i32 iFrame, i32 iFrameCount) override;

   virtual bool xor_image_frame2(void * pdata, i32 iFrame, i32 iFrameCount) override;


   virtual bool create_circle(::image * pimage, int diameter) override;
   virtual bool create_framed_square(::image * pimage, int inner, int outer, color32_t cr) override;


   virtual bool invert_rgb(const ::rect & rect) override;
   virtual bool invert_rgb() override;


   virtual __pointer(::object) clone() const override;


   void _create_image(::object * pobject, const ::size & size, ::eobject eobjectCreate, int iGoodStride = -1);
   void _create(const ::size & size, ::eobject eobjectCreate, int iGoodStride = -1);



   static void static_initialize();


   inline image & operator = (const image & image);
   inline bool operator == (const image & image) const;
   bool operator != (const image & image) const;


   inline color32_t * get_data() const;
   inline color32_t * colorref() const;

   inline int line(int line);

   inline ::size size() const;

   inline ::rect rect(const ::point & point = nullptr);
   inline const ::rect rect(const ::point & point = nullptr) const;


   inline color32_t pixel(int x, int y);
   inline i64 area() const;
   inline int scan_size() const;
   inline int width() const;
   inline int height() const;
   inline ::i32 scan_area() override;


   inline bool is_ok() const
   {

      return m_pimpl.is_set() && m_pimpl->is_ok();

   }


   inline bool is_null() const;
   inline bool is_set() const;
   inline bool is_empty() const;
   //inline void alloc(::object * pobject);
   //inline void defer_alloc(::object * pobject);


   inline ::draw2d::graphics * g() const;

   inline operator ::pixmap *();
   inline operator const ::pixmap *() const;

   inline operator image_data *();
   inline operator const image_data *() const;

   inline operator image_impl *();
   inline operator const image_impl *() const;


   inline class ::pixmap * pixmap() { return m_pimpl; }
   inline const class ::pixmap * pixmap() const { return m_pimpl; }
   inline ::image_data * imagedata() { return m_pimpl; }
   inline const ::image_data * imagedata() const { return m_pimpl; }


   inline i64 release() override { return m_pimpl.release(); }

//   virtual ::stream & write(::stream & stream) const override;
//virtual ::stream & read(::stream & stream) override;

   inline bool operator !() { return !is_ok(); }
   inline bool operator !() const { return !is_ok(); }

   inline operator bool() { return is_ok(); }
   inline operator bool() const { return is_ok(); }

   inline void set_ok() { m_pimpl->set_ok(); }
   inline void set_nok() { m_pimpl->set_nok(); }


   inline bool create_image(::object * pobject, const ::size & size, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1);


   inline bool has_flag(e_object eobject) const { return m_pimpl && m_pimpl->has_flag(eobject); }
   inline void set_flag(e_object eobject) { m_pimpl->set_flag(eobject); }
   inline void clear_flag(e_object eobject) { m_pimpl->clear_flag(eobject); }

   inline bool has_id(::u64 u) const { return m_pimpl && m_pimpl->has_id(u); }
   inline void set_id(::u64 u) { m_pimpl->set_id(u); }
   inline void clear_id(::u64 u) { m_pimpl->clear_id(u); }


   inline bool has_property(id id) const { return m_pimpl.is_set() && m_pimpl->has_property(id); }
   inline bool erase_key(id id) { return m_pimpl.is_set() && m_pimpl->erase_key(id); }
   inline ::payload value(id id) { return m_pimpl->payload(id); }
   inline ::payload value(id id) const { return m_pimpl->payload(id); }
   inline property & set(id id) { return m_pimpl->set(id); }
   inline ::payload find_property(id id) const { return m_pimpl->find_property(id); }
   inline property_set & propset() { return m_pimpl->propset(); }

   inline void clear_color_transform() { m_pimpl->m_bColorMatrix = false; }
   inline ::draw2d::color_matrix & colormatrix() { m_pimpl->m_bColorMatrix = true;  return m_pimpl->m_colormatrix; }

   inline image & clone(::image * pimage)
   {
      if (::is_null(pimpl))
      {
         m_pimpl.release();
      }
      else
      {
         m_pimpl = pimpl->clone();
      }
      return *this;
   }

   inline image & fork()
   {
      if (is_set())
      {
         clone(m_pimpl);
      }
      return *this;

   }
   

   inline image & operator = (const ::trait & traitPayload)
   {
      
      if (::is_null(this) || is_null())
      {
         
         return *this;
         
      }
      
      m_pimpl->set_action(traitPayload);
      
      return *this;
      
   }


   inline image & operator += (const ::trait & traitPayload)
   {

      if (::is_null(this) || is_null())
      {

         return *this;

      }

      m_pimpl->add_notification(traitPayload);

      return *this;

   }


};




class CLASS_DECL_AURA work_image :
   virtual public image
{
public:


   ::rect       m_rectMap;


   work_image(::object * pobject, const ::size & size);
   virtual ~work_image();




};


inline bool image::create_image(::object * pobject, const ::size & size, ::eobject eobjectCreate, int iGoodStride)
{

   if (m_pimpl.is_null())
   {

      _create_image(pobject, size, uidCreateImage, iGoodStride);

   }
   else if (size != m_pimpl->get_size())
   {

      _create(size, uidCreateImage, iGoodStride);

   }

   return is_ok();

}



inline stream &  operator >>(stream & istream, image & image)
{

   return istream >> *pimage;

}


inline stream &  operator <<(stream & ostream, const image & image)
{

   return ostream << *pimage;

}
