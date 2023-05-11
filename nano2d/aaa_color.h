// From nano2d by camilo on 2023-02-05 01:42 <3ThomasBorregaardSorensen!!
//
// Copyright (c) 2013 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//
#pragma once


//namespace nano2d
//{
//
//	struct color
//	{
//
//		union
//		{
//
//			float rgba[4];
//
//			struct
//			{
//
//				float r, g, b, a;
//
//			};
//
//		};
//
//      color()
//      {
//         r = g= b= a= 0;
//      }
//      color(float l, float a)
//      {
//         r = g= b=l;
//         this->a= a;
//      }
//      color(float r, float g, float b, float a)
//      {
//         this->r = r;
//         this->g = g;
//         this->b = b;
//         this->a = a;
//      }
//      /**
//       * Computes the luminance as ``l = 0.299r + 0.587g + 0.144b + 0.0a``.  If
//       * the luminance is less than 0.5, white is returned.  If the luminance is
//       * greater than or equal to 0.5, black is returned.  Both returns will have
//       * an alpha component of 1.0.
//       */
//      color contrasting_color() const {
//         float luminance = 0.299f * r + 0.587f * g + 0.144f * b;
//         return color(luminance < 0.5f ? 1.f : 0.f, 1.f);
//      }
//
//
//	};
//
//
//	//
//// Color utils
////
//// Colors in NanoVG are stored as unsigned ints in ABGR format.
//
//// Returns a color value from red, green, blue values. Alpha will be set to 255 (1.0f).
//	CLASS_DECL_NANO2D	::color::color RGB_color(unsigned char r, unsigned char g, unsigned char b);
//
//	// Returns a color value from red, green, blue values. Alpha will be set to 1.0f.
//	CLASS_DECL_NANO2D ::color::color RGBf_color(float r, float g, float b);
//
//	// Returns a color value from red, green, blue and alpha values.
//	CLASS_DECL_NANO2D ::color::color RGBA_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
//
//	// Returns a color value from red, green, blue and alpha values.
//	CLASS_DECL_NANO2D::color::color RGBAf_color(float r, float g, float b, float a);
//
//	// Linearly interpolates from color c0 to c1, and returns resulting color value.
//	CLASS_DECL_NANO2D::color::color LerpRGBA_color(color c0, color c1, float u);
//
//	// Sets transparency of a color value.
//	CLASS_DECL_NANO2D::color::color TransRGBA_color(color c0, unsigned char a);
//
//	// Sets transparency of a color value.
//	CLASS_DECL_NANO2D::color::color TransRGBAf(color c0, float a);
//
//	// Returns color value specified by hue, saturation and lightness.
//	// HSL values are all in range [0..1], alpha will be set to 255.
//	CLASS_DECL_NANO2D::color::color HSL_color(float h, float s, float l);
//
//	// Returns color value specified by hue, saturation and lightness and alpha.
//	// HSL values are all in range [0..1], alpha in range [0..255]
//	CLASS_DECL_NANO2D::color::color HSLA_color(float h, float s, float l, unsigned char a);
//
//
//
//} // namespace nano2d


inline ::color::color as_color(::color::color color)
{

	return { color.r, color.g, color.b, color.a };

}


//inline ::color::color as_nano2d_color(const ::color::color& color)
//{
//
//	return { color.fr(), color.fg(), color.fb(), color.fa() };
//
//}





