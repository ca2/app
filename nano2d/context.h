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


#include "_constant.h"
#include "types.h"


namespace nano2d
{


	class CLASS_DECL_NANO2D context :
		virtual public ::particle
	{
	public:

		params						m_params;
		float*						m_faCommands;
		int							m_ccommands;
		int							m_ncommands;
		float							m_fCommandX;
		float							m_fCommandY;
		state							m_statea[CONTEXT_MAX_STATES];
		int							m_nStates;
		pathCache*					m_ppathcache;
		float							m_fTessTol;
		float							m_fDistTol;
		float							m_fFringeWidth;
		float							m_fDevicePxRatio;
		struct FONScontext *		m_pfonscontext;
		int							m_iaFontImages[CONTEXT_MAX_FONT_IMAGES];
		int							m_iFontImageIdx;
		int							m_iDrawCallCount;
		int							m_iFillTriCount;
		int							m_iStrokeTriCount;
		int							m_iTextTriCount;
		//void* p;


		virtual ::nano2d::state* __getState();


		virtual params* internal_params();

		// Debug function to dump cached path data.
		virtual void debug_dump_path_cache();




		// Begin drawing a new frame
// Calls to nanovg drawing API should be wrapped in __NANO2D_API(BeginFrame)() & __NANO2D_API(EndFrame)()
// __NANO2D_API(BeginFrame)() defines the size of the window to render to in relation currently
// set viewport (i.e. glContext on GL backends). Device pixel ration allows to
// control the rendering on Hi-DPI devices.
// For example, GLFW returns two dimension for an opened window: window size and
// frame buffer size. In that case you would set windowWidth/Height to the window size
// devicePixelRatio to: frameBufferWidth / windowWidth.
		virtual void begin_frame(float windowWidth, float windowHeight, float devicePixelRatio);

		// Cancels drawing the current frame.
		virtual void cancel_frame();

		// Ends drawing flushing remaining render state.
		virtual void end_frame();

		//
		// Composite operation
		//
		// The composite operations in NanoVG are modeled after HTML Canvas API, and
		// the blend func is based on OpenGL (see corresponding manuals for more info).
		// The colors in the blending state have premultiplied alpha.

		// Sets the composite operation. The op parameter should be one of compositeOperation.
		virtual void global_composite_operation(int op);

		// Sets the composite operation with custom pixel arithmetic. The parameters should be one of blendFactor.
		virtual void global_composite_blend_func(int sfactor, int dfactor);

		// Sets the composite operation with custom pixel arithmetic for RGB and alpha components separately. The parameters should be one of blendFactor.
		virtual void global_composite_blend_func_separate(int srcRGB, int dstRGB, int srcAlpha, int dstAlpha);

		//
		// State Handling
		//
		// NanoVG contains state which represents how paths will be rendered.
		// The state contains transform, fill and stroke styles, text and font styles,
		// and scissor clipping.

		// Pushes and saves the current render state into a state stack.
		// A matching Restore)() must be used to restore the state.
		virtual void save();

		// Pops and restores current render state.
		virtual void restore();

		// Resets current render state to default values. Does not affect the render state stack.
		virtual void reset();

		//
		// Render styles
		//
		// Fill and stroke render style can be either a solid color or a paint which is a gradient or a pattern.
		// Solid color is simply defined as a color value, different kinds of paints can be created
		// using LinearGradient)(), BoxGradient)(), RadialGradient)() and ImagePattern)().
		//
		// Current render style can be saved and restored using Save)() and Restore)().

		// Sets whether to draw antialias for Stroke)() and Fill)(). It's enabled by default.
		virtual void shape_anti_alias(int enabled);

		// Sets current stroke style to a solid color.
		virtual void stroke_color(::nano2d::color color);

		// Sets current stroke style to a paint, which can be a one of the gradients or a pattern.
		virtual void stroke_paint(paint paint);

		// Sets current fill style to a solid color.
		virtual void fill_color(::nano2d::color color);

		// Sets current fill style to a paint, which can be a one of the gradients or a pattern.
		virtual void fill_paint(paint paint);

		// Sets the miter limit of the stroke style.
		// Miter limit controls when a sharp corner is beveled.
		virtual void miter_limit(float limit);

		// Sets the stroke width of the stroke style.
		virtual void stroke_width(float size);

		// Sets how the end of the line (cap) is drawn,
		// Can be one of: _BUTT (default), _ROUND, _SQUARE.
		virtual void line_cap(int cap);

		// Sets how sharp path corners are drawn.
		// Can be one of _MITER (default), _ROUND, _BEVEL.
		virtual void line_join(int join);

		// Sets the transparency applied to all rendered shapes.
		// Already transparent paths will get proportionally more transparent as well.
		virtual void global_alpha(float alpha);


		//
		// Transforms
		//
		// The paths, gradients, patterns and scissor region are transformed by an transformation
		// matrix at the time when they are passed to the API.
		// The current transformation matrix is a affine matrix:
		//   [sx kx tx]
		//   [ky sy ty]
		//   [ 0  0  1]
		// Where: sx,sy define scaling, kx,ky skewing, and tx,ty translation.
		// The last row is assumed to be 0,0,1 and is not stored.
		//
		// Apart from ResetTransform)(), each transformation function first creates
		// specific transformation matrix and pre-multiplies the current transformation by it.
		//
		// Current coordinate system (transformation) can be saved and restored using Save)() and Restore)().

		// Resets current transform to a identity matrix.
		virtual void reset_transform();

		// Premultiplies current coordinate system by specified matrix.
		// The parameters are interpreted as matrix as follows:
		//   [a c e]
		//   [b d f]
		//   [0 0 1]
		virtual void transform(float a, float b, float c, float d, float e, float f);

		// Translates current coordinate system.
		//void Translate(float x, float y);
		virtual void translate(float x, float y);

		// Rotates current coordinate system. Angle is specified in radians.
		virtual void rotate(float angle);

		// Skews the current coordinate system along X axis. Angle is specified in radians.
		virtual void skew_x(float angle);

		// Skews the current coordinate system along Y axis. Angle is specified in radians.
		virtual void skew_y(float angle);

		// Scales the current coordinate system.
		virtual void scale(float x, float y);

		// Stores the top part (a-f) of the current transformation matrix in to the specified buffer.
		//   [a c e]
		//   [b d f]
		//   [0 0 1]
		// There should be space for 6 floats in the return buffer for the values a-f.
		virtual void current_transform(float* xform);

		//
		// Images
		//
		// NanoVG allows you to load jpg, png, psd, tga, pic and gif files to be used for rendering.
		// In addition you can upload your own image. The image loading is provided by stb_image.
		// The parameter imageFlags is combination of flags defined in imageFlags.

		// Creates image by loading it from the disk from specified file name.
		// Returns handle to the image.
		virtual int create_image(const ::scoped_string& scopedstrFilename, int imageFlags);

		// Creates image by loading it from the specified chunk of memory.
		// Returns handle to the image.
		virtual int create_image_mem(int imageFlags, unsigned char* data, int ndata);

		// Creates image from specified image data.
		// Returns handle to the image.
		virtual int create_image_rgba(int w, int h, int imageFlags, const void* data, int iScan);

		// Updates image data specified by image handle.
		virtual void update_image(int image, const void* data);

		// Returns the dimensions of a created image.
		virtual void image_size(int image, int* w, int* h);

		// Deletes created image.
		virtual void delete_image(int image);

		//
		// Paints
		//
		// NanoVG supports four types of paints: linear gradient, box gradient, radial gradient and image pattern.
		// These can be used as paints for strokes and fills.

		// Creates and returns a linear gradient. Parameters (sx,sy)-(ex,ey) specify the start and end coordinates
		// of the linear gradient, icol specifies the start color and ocol the end color.
		// The gradient is transformed by the current transform when it is passed to FillPaint)() or StrokePaint)().
		virtual ::nano2d::paint linear_gradient(float sx, float sy, float ex, float ey, ::nano2d::color icol, ::nano2d::color ocol);

		// Creates and returns a box gradient. Box gradient is a feathered rounded rectangle, it is useful for rendering
		// drop shadows or highlights for boxes. Parameters (x,y) define the top-left corner of the rectangle,
		// (w,h) define the size of the rectangle, r defines the corner radius, and f feather. Feather defines how blurry
		// the border of the rectangle is. Parameter icol specifies the inner color and ocol the outer color of the gradient.
		// The gradient is transformed by the current transform when it is passed to FillPaint)() or StrokePaint)().
		virtual ::nano2d::paint box_gradient(float x, float y, float w, float h, float r, float f, ::nano2d::color icol, ::nano2d::color ocol);

		// Creates and returns a radial gradient. Parameters (cx,cy) specify the center, inr and outr specify
		// the inner and outer radius of the gradient, icol specifies the start color and ocol the end color.
		// The gradient is transformed by the current transform when it is passed to FillPaint)() or StrokePaint)().
		virtual ::nano2d::paint radial_gradient(float cx, float cy, float inr, float outr, ::nano2d::color icol, ::nano2d::color ocol);

		// Creates and returns an image pattern. Parameters (ox,oy) specify the left-top location of the image pattern,
		// (ex,ey) the size of one image, angle rotation around the top-left corner, image is handle to the image to render.
		// The gradient is transformed by the current transform when it is passed to FillPaint)() or StrokePaint)().
		virtual ::nano2d::paint image_pattern(float ox, float oy, float ex, float ey, float angle, int image, float alpha);

		//
		// Scissoring
		//
		// Scissoring allows you to clip the rendering into a rectangle. This is useful for various
		// user interface cases like rendering a text edit or a timeline.

		// Sets the current scissor rectangle.
		// The scissor rectangle is transformed by the current transform.
		virtual void scissor(float x, float y, float w, float h);

		// Intersects current scissor rectangle with the specified rectangle.
		// The scissor rectangle is transformed by the current transform.
		// Note: in case the rotation of previous scissor rect differs from
		// the current one, the intersection will be done between the specified
		// rectangle and the previous scissor rectangle transformed in the current
		// transform space. The resulting shape is always rectangle.
		virtual void intersect_scissor(float x, float y, float w, float h);

		// Reset and disables scissoring.
		virtual void reset_scissor();

		//
		// Paths
		//
		// Drawing a new shape starts with BeginPath)(), it clears all the currently defined paths.
		// Then you define one or more paths and sub-paths which describe the shape. The are functions
		// to draw common shapes like rectangles and circles, and lower level step-by-step functions,
		// which allow to define a path curve by curve.
		//
		// NanoVG uses even-odd fill rule to draw the shapes. Solid shapes should have counter clockwise
		// winding and holes should have counter clockwise order. To specify winding of a path you can
		// call PathWinding)(). This is useful especially for the common shapes, which are drawn CCW.
		//
		// Finally you can fill the path using current fill style by calling Fill)(), and stroke it
		// with current stroke style by calling Stroke)().
		//
		// The curve segments and sub-paths are transformed by the current transform.

		// Clears the current path and sub-paths.
		virtual void begin_path();

		// Starts new sub-path with specified point as first point.
		virtual void move_to(float x, float y);

		// Adds line segment from the last point in the path to the specified point.
		virtual void line_to(float x, float y);

		// Adds cubic bezier segment from last point in the path via two control points to the specified point.
		virtual void bezier_to(float c1x, float c1y, float c2x, float c2y, float x, float y);

		// Adds quadratic bezier segment from last point in the path via a control point to the specified point.
		virtual void quad_to(float cx, float cy, float x, float y);

		// Adds an arc segment at the corner defined by the last path point, and two specified points.
		virtual void arc_to(float x1, float y1, float x2, float y2, float radius);

		// Closes current sub-path with a line segment.
		virtual void close_path();

		// Sets the current sub-path winding, see winding and solidity.
		virtual void path_winding(int dir);

		// Creates new circle arc shaped sub-path. The arc center is at cx,cy, the arc radius is r,
		// and the arc is drawn from angle a0 to a1, and swept in direction dir (_CCW, or _CW).
		// Angles are specified in radians.
		virtual void arc(float cx, float cy, float r, float a0, float a1, int dir);

		// Creates new rectangle shaped sub-path.
		virtual void rectangle(float x, float y, float w, float h);

		// Creates new rounded rectangle shaped sub-path.
		virtual void rounded_rectangle(float x, float y, float w, float h, float r);

		// Creates new rounded rectangle shaped sub-path with varying radii for each corner.
		virtual void rounded_rectangle_varying(float x, float y, float w, float h, float radTopLeft, float radTopRight, float radBottomRight, float radBottomLeft);

		// Creates new ellipse shaped sub-path.
		virtual void ellipse(float cx, float cy, float rx, float ry);

		// Creates new circle shaped sub-path.
		virtual void circle(float cx, float cy, float r);

		// Fills the current path with current fill style.
		virtual void fill();

		// Fills the current path with current stroke style.
		virtual void stroke();

		//
		// Text
		//
		// NanoVG allows you to load .ttf files and use the font to render text.
		//
		// The appearance of the text can be defined by setting the current text style
		// and by specifying the fill color. Common text and font settings such as
		// font size, letter spacing and text align are supported. Font blur allows you
		// to create simple text effects such as drop shadows.
		//
		// At render time the font face can be set based on the font handles or name.
		//
		// Font measure functions return values in local space, the calculations are
		// carried in the same resolution as the final rendering. This is done because
		// the text glyph positions are snapped to the nearest pixels sharp rendering.
		//
		// The local space means that values are not rotated or scale as per the current
		// transformation. For example if you set font size to 12, which would mean that
		// line height is 16, then regardless of the current scaling and rotation, the
		// returned line height is always 16. Some measures may vary because of the scaling
		// since aforementioned pixel snapping.
		//
		// While this may sound a little odd, the setup allows you to always render the
		// same way regardless of scaling. I.e. following works regardless of scaling:
		//
		//		const char* txt = "Text me up.";
		//		TextBounds)(vg, x,y, txt, NULL, bounds);
		//		BeginPath)(vg);
		//		RoundedRect)(vg, bounds[0],bounds[1], bounds[2]-bounds[0], bounds[3]-bounds[1]);
		//		Fill)(vg);
		//
		// Note: currently only solid color fill is supported for text.

		// Creates font by loading it from the disk from specified file name.
		// Returns handle to the font.
		//int CreateFont)(::nano2d::context * pcontext, const ::scoped_string & name, const ::scoped_string & filename);

		// fontIndex specifies which font face to load from a .ttf/.ttc file.
		virtual int create_font_at_index(const ::scoped_string& name, const ::scoped_string& filename, const int fontIndex);

		// Creates font by loading it from the specified memory chunk.
		// Returns handle to the font.
		virtual int create_font_mem(const ::scoped_string& name, unsigned char* data, int ndata, int freeData);

		// fontIndex specifies which font face to load from a .ttf/.ttc file.
		virtual int create_font_mem_at_index(const ::scoped_string& name, unsigned char* data, int ndata, int freeData, const int fontIndex);

		// Finds a loaded font of specified name, and returns handle to it, or -1 if the font is not found.
		virtual int find_font(const ::scoped_string& name);

		// Adds a fallback font by handle.
		virtual int add_fallback_font_id(int baseFont, int fallbackFont);

		// Adds a fallback font by name.
		virtual int add_fallback_font(const ::scoped_string& baseFont, const ::scoped_string& fallbackFont);

		// Resets fallback fonts by handle.
		virtual void reset_fallback_fonts_id(int baseFont);

		// Resets fallback fonts by name.
		virtual void reset_fallback_fonts(const ::scoped_string& baseFont);

		// Sets the font size of current text style.
		virtual void font_size(float size);

		// Sets the blur of current text style.
		virtual void font_blur(float blur);

		// Sets the letter spacing of current text style.
		virtual void text_letter_spacing(float spacing);

		// Sets the proportional line height of current text style. The line height is specified as multiple of font size.
		virtual void text_line_height(float lineHeight);

		// Sets the text align of current text style, see align for options.
		virtual void text_align(int align);

		// Sets the font face based on specified id of current text style.
		virtual void font_face_id(int font);

		// Sets the font face based on specified name of current text style.
		virtual void font_face(const ::scoped_string& font);

		// Draws text string at specified location. If end is specified only the sub-string up to the end is drawn.
		virtual float text(float x, float y, const ::scoped_string& scopedstr);

		// Draws multi-line text string at specified location wrapped at the specified width. If end is specified only the sub-string up to the end is drawn.
		// White space is stripped at the beginning of the rows, the text is split at word boundaries or when new-line characters are encountered.
		// Words longer than the max width are slit at nearest character (i.e. no hyphenation).
		virtual void text_box(float x, float y, float breakRowWidth, const ::scoped_string& scopedstr);

		// Measures the specified text string. Parameter bounds should be a pointer to float[4],
		// if the bounding box of the text should be returned. The bounds value are [xmin,ymin, xmax,ymax]
		// Returns the horizontal advance of the measured text (i.e. where the next character should drawn).
		// Measured values are returned in local coordinate space.
		virtual float text_bounds(float x, float y, const ::scoped_string& scopedstr, float* bounds);

		// Measures the specified multi-text string. Parameter bounds should be a pointer to float[4],
		// if the bounding box of the text should be returned. The bounds value are [xmin,ymin, xmax,ymax]
		// Measured values are returned in local coordinate space.
		virtual void text_box_bounds(float x, float y, float breakRowWidth, const ::scoped_string& scopedstr, float* bounds);

		// Calculates the glyph x positions of the specified text. If end is specified only the sub-string will be used.
		// Measured values are returned in local coordinate space.
		virtual int text_glyph_positions(float x, float y, const ::scoped_string& scopedstr, glyphPosition* positions, int maxPositions);

		// Returns the vertical metrics based on the current text style.
		// Measured values are returned in local coordinate space.
		virtual void text_metrics(float* ascender, float* descender, float* lineh);

		// Breaks the specified text into lines. If end is specified only the sub-string will be used.
		// White space is stripped at the beginning of the rows, the text is split at word boundaries or when new-line characters are encountered.
		// Words longer than the max width are slit at nearest character (i.e. no hyphenation).
		virtual int text_break_lines(const ::scoped_string& scopedstr, float breakRowWidth, text_row* rows, int maxRows);

		virtual void __append_commands(float* vals, int nvals);

		virtual void _draw_image(float x, float y, float w, float h, ::image* pimage);

	};

   class guard
   {
   public:

      
      context * m_pcontext;


      guard(context * pcontext) :
         m_pcontext(pcontext) 
      {
         
         m_pcontext->save(); 
      
      }

      
      ~guard()
      {
         
         m_pcontext->restore(); 
      
      }


   };


} // namespace nano2d



