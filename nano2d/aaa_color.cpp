// From nano2d by camilo on 2023-02-05 04:11 <3ThomasBorregaardSorensen!!
#include "framework.h"
//#include "color.h"


//namespace nano2d
//{
//
//
//   //::color::color context::RGB(unsigned char r, unsigned char g, unsigned char b)
//   ::color::color RGB_color(unsigned char r, unsigned char g, unsigned char b)
//   {
//      ///return context::RGBA)(r, g, b, 255);
//      return { r / 255.f, g / 255.f, b / 255.f, 1.0f };
//   }
//
//   //::color::color context::RGBf)(float r, float g, float b)
//   ::color::color RGBf_color(float r, float g, float b)
//   {
//      //return context::RGBAf)(r, g, b, 1.0f);
//      return { r , g, b, 1.0f };
//   }
//
//   //::color::color context::RGBA)(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
//   ::color::color RGBA_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
//   {
//      ::color::color color;
//      // Use longer initialization to suppress warning.
//      color.r = r / 255.0f;
//      color.g = g / 255.0f;
//      color.b = b / 255.0f;
//      color.a = a / 255.0f;
//      return color;
//   }
//
//   //::color::color context::RGBAf)(float r, float g, float b, float a)
//   ::color::color RGBAf_color(float r, float g, float b, float a)
//   {
//      ::color::color color;
//      // Use longer initialization to suppress warning.
//      color.r = r;
//      color.g = g;
//      color.b = b;
//      color.a = a;
//      return color;
//   }
//
//   //::color::color context::TransRGBA)(::color::color c, unsigned char a)
//   ::color::color TransRGBA_color(::color::color c, unsigned char a)
//   {
//      c.a = a / 255.0f;
//      return c;
//   }
//
//   //::color::color context::TransRGBAf)(::color::color c, float a)
//   ::color::color TransRGBAf_color(::color::color c, float a)
//   {
//      c.a = a;
//      return c;
//   }
//
//   //::color::color context::LerpRGBA)(::color::color c0, ::color::color c1, float u)
//   //{
//   //	int i;
//   //	float oneminu;
//   //	::color::color cint = { {{0}} };
//   //
//   //	u = context::__clampf)(u, 0.0f, 1.0f);
//   //	oneminu = 1.0f - u;
//   //	for (i = 0; i < 4; i++)
//   //	{
//   //		cint.rgba[i] = c0.rgba[i] * oneminu + c1.rgba[i] * u;
//   //	}
//   //
//   //	return cint;
//   //}
//
//   //::color::color context::HSL)(float h, float s, float l)
//   ::color::color HSL_color(float h, float s, float l)
//   {
//      //return context::HSLA)(h, s, l, 255);
//      ::color::color color;
//
//      color.set_hls(h, l, s);
//      return { color.fr(), color.fg(), color.fb(), color.fa() };
//
//   }
//
//   //static float context::__hue)(float h, float m1, float m2)
//   //{
//   //	if (h < 0) h += 1;
//   //	if (h > 1) h -= 1;
//   //	if (h < 1.0f / 6.0f)
//   //		return m1 + (m2 - m1) * h * 6.0f;
//   //	else if (h < 3.0f / 6.0f)
//   //		return m2;
//   //	else if (h < 4.0f / 6.0f)
//   //		return m1 + (m2 - m1) * (2.0f / 3.0f - h) * 6.0f;
//   //	return m1;
//   //}
//
//   //::color::color context::HSLA)(float h, float s, float l, unsigned char a)
//   ::color::color HSLA_color(float h, float s, float l, unsigned char a)
//   {
//      //float m1, m2;
//      //::color::color col;
//      //h = context::__modf)(h, 1.0f);
//      //if (h < 0.0f) h += 1.0f;
//      //s = context::__clampf)(s, 0.0f, 1.0f);
//      //l = context::__clampf)(l, 0.0f, 1.0f);
//      //m2 = l <= 0.5f ? (l * (1 + s)) : (l + s - l * s);
//      //m1 = 2 * l - m2;
//      //col.r = context::__clampf)(context::__hue)(h + 1.0f / 3.0f, m1, m2), 0.0f, 1.0f);
//      //col.g = context::__clampf)(context::__hue)(h, m1, m2), 0.0f, 1.0f);
//      //col.b = context::__clampf)(context::__hue)(h - 1.0f / 3.0f, m1, m2), 0.0f, 1.0f);
//      ::color::color color;
//
//      color.set_hls(h, l, s);
//      color.alpha = a;
//      return { color.fr(), color.fg(), color.fb(), color.fa() };
//   }
//
//
//} // namespace nano2d
//
//
//
