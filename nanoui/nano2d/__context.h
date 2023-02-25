#pragma once


#include NANO2D_INCLUDE
#include "../vector.h"


namespace nano2d
{


   class CLASS_DECL_NANOUI context :
      virtual public ::particle,
		public ::nano2d::context
	{
	public:
		

		context();
		virtual ~context();


		virtual void save();
		virtual void restore();


		virtual void begin_path();
		virtual void path_winding(int dir);
		virtual void close_path();


		virtual void translate(float x, float y);
		virtual void rotate(float angle);


		virtual void rounded_rect(float x, float y, float w, float h, float r);

		virtual void fill();
		virtual void stroke();


		virtual ::nano2d::paint linear_gradient(float sx, float sy, float ex, float ey,
			::nano2d::color icol, ::nano2d::color ocol);
		virtual ::nano2d::paint box_gradient(float x, float y, float w, float h, float r, float f,
			::nano2d::color icol, ::nano2d::color ocol);
		virtual ::nano2d::paint radial_gradient(float cx, float cy, float inr, float outr,
			::nano2d::color icol, ::nano2d::color ocol);
		virtual ::nano2d::paint image_pattern(float cx, float cy, float w, float h, float angle,
			int image, float alpha);


		virtual void font_face(const char * font);
		virtual void font_size(float size);
      virtual void font_blur(float blur);
		virtual void fill_color(::nano2d::color color);
		virtual void stroke_color(::nano2d::color color);
      virtual void global_alpha(float alpha);
		virtual void stroke_width(float width);
		virtual void text_align(int align);


		virtual void fill_paint(::nano2d::paint paint);
		virtual void stroke_paint(::nano2d::paint paint);

		virtual void scissor(float x, float y, float w, float h);
		virtual void intersect_scissor(float x, float y, float w, float h);
		virtual void reset_scissor();



		virtual float text(float x, float y, const char * string, const char * end);
		virtual int text_glyph_positions(float x, float y, const char * string, const char * end, ::nano2d::glyphPosition * positions, int maxPositions);
		virtual float text_bounds(float x, float y, const char * string, const char * end, float * bounds);
      virtual void text_line_height(float lineHeight);


		virtual void move_to(float x, float y);
		virtual void line_to(float x, float y);


		virtual void rect(float x, float y, float w, float h);
		virtual void ellipse(float cx, float cy, float rx, float ry);
		virtual void circle(float cx, float cy, float r);
		virtual void arc(float cx, float cy, float r, float a0, float a1, int dir);


		virtual int create_image(const char * filename, int imageFlags);
		virtual int create_image_rgba(int w, int h, int imageFlags, const void * data, int iScan);
		virtual void image_size(int image, int * w, int * h);


		virtual void update_image(int image, const void * data);
		virtual void _draw_image(float x, float y, float w, float h, ::image * pimage);

	};


} // namespace nano2d




