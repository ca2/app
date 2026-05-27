#pragma once


#include NANO2D_INCLUDE
#include "../vector.h"


namespace nano2d
{


   class NANOUI_EXPORT context :
      virtual public ::particle,
		public ::nano2d::context 
	{
	public:
		

		context();
		virtual ~context();


		virtual void save();
		virtual void restore();


		virtual void begin_path();
		virtual void path_winding(::i32 dir);
		virtual void close_path();


		virtual void translate(::f32 x, ::f32 y);
		virtual void rotate(::f32 angle);


		virtual void rounded_rect(::f32 x, ::f32 y, ::f32 w, ::f32 h, ::f32 r);

		virtual void fill();
		virtual void stroke();


		virtual ::nano2d::paint linear_gradient(::f32 sx, ::f32 sy, ::f32 ex, ::f32 ey,
			::nano2d::color icol, ::nano2d::color ocol);
		virtual ::nano2d::paint box_gradient(::f32 x, ::f32 y, ::f32 w, ::f32 h, ::f32 r, ::f32 f,
			::nano2d::color icol, ::nano2d::color ocol);
		virtual ::nano2d::paint radial_gradient(::f32 cx, ::f32 cy, ::f32 inr, ::f32 outr,
			::nano2d::color icol, ::nano2d::color ocol);
		virtual ::nano2d::paint image_pattern(::f32 cx, ::f32 cy, ::f32 w, ::f32 h, ::f32 angle,
			::i32 image, ::f32 alpha);


		virtual void font_face(const_char_pointer font);
		virtual void font_size(::f32 size);
      virtual void font_blur(::f32 blur);
		virtual void fill_color(::nano2d::color color);
		virtual void stroke_color(::nano2d::color color);
      virtual void global_alpha(::f32 alpha);
		virtual void stroke_width(::f32 width);
		virtual void text_align(::i32 align);


		virtual void fill_paint(::nano2d::paint paint);
		virtual void stroke_paint(::nano2d::paint paint);

		virtual void scissor(::f32 x, ::f32 y, ::f32 w, ::f32 h);
		virtual void intersect_scissor(::f32 x, ::f32 y, ::f32 w, ::f32 h);
		virtual void reset_scissor();



		virtual ::f32 text(::f32 x, ::f32 y, const_char_pointer string, const_char_pointer end);
		virtual ::i32 text_glyph_positions(::f32 x, ::f32 y, const_char_pointer string, const_char_pointer end, ::nano2d::glyphPosition * positions, ::i32 maxPositions);
		virtual ::f32 text_bounds(::f32 x, ::f32 y, const_char_pointer string, const_char_pointer end, ::f32 * bounds);
      virtual void text_line_height(::f32 lineHeight);


		virtual void move_to(::f32 x, ::f32 y);
		virtual void line_to(::f32 x, ::f32 y);


		virtual void rect(::f32 x, ::f32 y, ::f32 w, ::f32 h);
		virtual void ellipse(::f32 cx, ::f32 cy, ::f32 rx, ::f32 ry);
		virtual void circle(::f32 cx, ::f32 cy, ::f32 r);
		virtual void arc(::f32 cx, ::f32 cy, ::f32 r, ::f32 a0, ::f32 a1, ::i32 dir);


		virtual ::i32 create_image(const_char_pointer pszFilename, ::i32 imageFlags);
		virtual ::i32 create_image_rgba(::i32 w, ::i32 h, ::i32 imageFlags, const void * data, ::i32 iScan);
		virtual void image_size(::i32 image, ::i32 * w, ::i32 * h);


		virtual void update_image(::i32 image, const void * data);
		virtual void _draw_image(::f32 x, ::f32 y, ::f32 w, ::f32 h, ::image::image *pimage);

	};


} // namespace nano2d




