//
//  draw2d.inl
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 11/03/18.
//
#pragma once




inline color32_t get_pixel(const pixmap* ppixmap, int x, int y)
{

   return ::draw2d::get_pixel(ppixmap->colorref(), ppixmap->scan_size(), ppixmap->height(), x, y);

}


inline color32_t pixmap::get_pixel(int x, int y) const
{

   return ::get_pixel(this, x, y);

}



template < >
inline uptr uptr_hash<const ::image_header&>(const ::image_header& key)
{
   ::u32 u = (::u32)key.m_etype;
   if (key.m_etype == ::image_type_plain_color)
   {
      u |= key.m_cr;
   }
   u |= key.m_size.cx << 16;
   u |= key.m_size.cy << 24;
   return u;
}


inline image& image::operator = (const image& image)
{

   copy_from((::image*) & image);

   return *this;

}


//inline image * image::frame(iptr i) const
//{
//
//   auto frames = this->frames();
//
//   if (::is_null(frames) || frames->is_empty())
//   {
//
//      if (i == 0)
//      {
//
//         return m_pimpl;
//
//      }
//
//      return nullptr;
//
//   }
//
//   auto pointer = frames->ptr_at(i);
//
//   return ::is_null(pointer) ? nullptr : pointer->m_pimpl;
//
//}
//

inline bool image::operator == (const image& image) const
{

   return m_pcolorrefRaw == image.m_pcolorrefRaw;

}


inline bool image::operator != (const image& image) const
{

   return !operator ==(image);

}


inline int image::line(int line)
{

#if defined(APPLEOS)

   return height() - line - 1;

#else

   return line;

#endif

}


//inline ::size image::size() const
//{
//
//   return m_size;
//
//}


inline ::rect image::rect(const ::point& point)
{

   return ::rect(point, size() - point);

}


inline ::rect image::rect(const ::point& point) const
{

   return ::rect(point, size() - point);

}


inline color32_t image::pixel(int x, int y) const
{

   if (::is_null(this))
   {

      return 0;

   }

   return ::draw2d::get_pixel(colorref(), scan_size(), width(), x, y);

}


inline u64 image::area() const
{

   if (::is_null(this))
   {

      return 0;

   }

   return m_size.area();

}


inline int image::scan_size() const
{

   if (::is_null(this))
   {

      return 0;

   }

   return m_iScan;

}


inline int image::width() const
{

   if (::is_null(this))
   {

      return 0;

   }

   return m_size.cx;

}


inline int image::height() const
{

   if (::is_null(this))
   {

      return 0;

   }

   return m_size.cy;

}




inline bool image::is_null() const
{

   return ::is_null(this) || m_size.area() <= 0;

}


inline bool image::is_set() const
{

   return !is_null();

}


inline bool image::is_empty() const
{

   return is_null();

}


inline ::draw2d::graphics* image::g() const
{

   return get_graphics();

}


inline color32_t* image::colorref()
{

   return m_pcolorref1;

}


inline const color32_t* image::colorref() const
{


   return m_pcolorref1;

}


inline image::operator color32_t* ()
{

   return colorref();

}


inline image::operator const color32_t* () const
{

   return colorref();

}


inline ::pixmap* image::pixmap()
{

   return this;

}


inline const ::pixmap* image::pixmap() const
{

   return this;

}


inline image::operator ::pixmap* ()
{

   return this;

}


inline image::operator const ::pixmap* () const
{

   return this;

}


inline ::image_extension* image::extension()
{

   return m_pextension;

}


inline const ::image_extension* image::extension() const
{

   return m_pextension;

}


inline image::operator image_extension* ()
{

   return m_pextension;

}


inline image::operator const image_extension* () const
{

   return m_pextension;

}



inline __pointer(image_frame_array) image_meta::frames() { return m_pextension ? m_pextension->m_pframea : nullptr; }


inline ::rgb& rgb::operator =(const ::var& var)
{

   m_iR = var["red"];
   m_iG = var["green"];
   m_iB = var["blue"];

   return *this;

}


inline var& assign(var& var, const rgb& rgb)
{

   var["red"] = rgb.m_iR;
   var["green"] = rgb.m_iG;
   var["blue"] = rgb.m_iB;

   return var;

}



inline void __exchange(::stream& s, ::rgb& rgb)
{

   s.exchange("red", rgb.m_iR); s.exchange("green", rgb.m_iG); s.exchange("blue", rgb.m_iB);

}


inline ::rgba& rgba::operator =(const ::var& var)
{

   rgb::operator=(var);

   m_iA = var["opacity"];

   return *this;

}


inline var& assign(var& var, const ::rgba& rgba)
{

   assign(var, (const ::rgb&) rgba);

   var["opacity"] = rgba.m_iA;

   return var;

}



inline void __exchange(::stream& s, ::rgba& rgba)
{

   __exchange(s, (::rgb&) rgba); s.exchange("opacity", rgba.m_iA);

}


inline ::hls& hls::operator =(const ::var& var)
{

   m_dH = var["hue"];
   m_dL = var["lightness"];
   m_dS = var["saturation"];

   return *this;

}


inline var& assign(var& var, const ::hls& hls)
{

   var["hue"] = hls.m_dH;
   var["lightness"] = hls.m_dL;
   var["saturation"] = hls.m_dS;

   return var;

}


inline void __exchange(::stream& s, ::hls& hls)
{

   s.exchange("hue", hls.m_dH); s.exchange("lightness", hls.m_dL); s.exchange("saturation", hls.m_dS);

}


inline ::size image::get_size() const { return size(); }



namespace draw2d
{


   inline color32_t get_pixel(const color32_t * pdata, int iScan, int iHeight, int x, int y)
   {

#ifdef APPLEOS

      return ((color32_t *)&((u8 *)pdata)[iScan * (iHeight - y - 1)])[x];

#else

      return ((color32_t *)&((u8 *)pdata)[iScan * y])[x];

#endif

   }



   template < typename PRED >
   bool draw2d::emboss_pred(
   ::draw2d::graphics_pointer & pgraphics,
   const ::rect & rect,
   PRED pred,
   ::draw2d::fastblur & blur,
   ::image_pointer & pimageBlur,
   color32_t crGlow,
   int iSpreadRadius,
   int iBlurRadius,
   int iBlur,
   bool bUpdate,
   double dAlpha)
   {


      int iR = iSpreadRadius + iBlurRadius + iBlur + 1;

      ::rect rectEmboss = rect;


      rectEmboss.left -= (::i32)(iR * g_dEmboss);
      rectEmboss.top -= (::i32)(iR * g_dEmboss);
      rectEmboss.right += (::i32)(iR * g_dEmboss);
      rectEmboss.bottom += (::i32)(iR * g_dEmboss);

      if (bUpdate || !pimageBlur->is_ok())
      {

         int iEffectiveSpreadRadius = iSpreadRadius;

         int iEffectiveBlurRadius = iBlurRadius;

         const ::size & size = rectEmboss.size();

         pimageBlur->create(rectEmboss);

         pimageBlur->fill(0, 0, 0, 0);

         ::rect rectCache;

         rectCache.left = (::i32)(iR * g_dEmboss);
         rectCache.top = (::i32)(iR * g_dEmboss);
         rectCache.right = rectCache.left + rect.width();

         rectCache.bottom = rectCache.top + rect.height();


         ::image_pointer pimage;

         auto estatus = __construct(pimage);

         if (!estatus)
         {

            return false;

         }

         estatus = pimage->create(size);

         if (!estatus)
         {

            return false;

         }

         pimage->fill(0, 0, 0, 0);

         ::draw2d::brush_pointer brushText(e_create);

         brushText->create_solid(ARGB(255, 255, 255, 255));
         pimage->get_graphics()->set(brushText);


         pimage->get_graphics()->OffsetViewportOrg(rectCache.left - rect.left, rectCache.top - rect.top);


         pred(pimage->get_graphics());


         pimage->get_graphics()->OffsetViewportOrg(-rectCache.left + rect.left, -rectCache.top + rect.top);


         System.imaging().channel_spread_set_color(pimageBlur->g(), nullptr, size, pimage->g(), nullptr, ::color::channel_alpha, iEffectiveSpreadRadius, ARGB(255, 255, 255, 255));


         for (iptr i = 0; i < iBlur; i++)
         {

            blur.blur(pimageBlur, iEffectiveBlurRadius);

         }

         pimageBlur->set_rgb(crGlow);

         pimageBlur->mult_alpha();

      }

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      pgraphics->alpha_blend(rectEmboss, pimageBlur->g(), dAlpha);

      //::draw2d::brush_pointer brushText(e_create);
      //brushText->create_solid(crText);
      //pgraphics->set(brushText);
      //pgraphics->set(pfont);
      //pgraphics->_DrawText(strText, *pcrect, iDrawTextFlags);


      return true;

   }


   inline bool graphics::draw(::image * pimage) { return draw(rect(pimage->get_size()), pimage); }
   inline bool graphics::draw(const point & pDst, const ::size & size, ::image * pimage, const point & pSrc) { return draw(rect(pDst, size), pimage, pSrc); }

   inline bool graphics::draw(const ::size & size, ::image * pimage, const point & pSrc) { return draw(rect(size), pimage, pSrc); }

   inline bool graphics::draw_dim(i32 x, i32 y, i32 w, i32 h, ::image * pimage, i32 xSrc, i32 ySrc) { return draw(rect_dim(x, y, w, h), pimage, ::point(xSrc, ySrc)); }
   inline bool graphics::BitBlt (i32 x, i32 y, i32 w, i32 h, ::image * pimage, i32 xSrc, i32 ySrc) { return draw_dim(x, y, w, h, pimage, xSrc, ySrc); }


} // namespace draw2d



