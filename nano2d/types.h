	//
// Copyright (c) 2013 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no happening will the authors be held liable for any damages
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


#include "acme/prototype/geometry2d/matrix.h"


namespace nano2d
{

//
//	constexpr ::f32 f_pi = 3.14159265358979323846264338327f;
//
//#ifdef _MSC_VER
//#pragma warning(push)
//#pragma warning(disable: 4201)  // nonstandard extension used : nameless struct/union
//#endif

	
	class context;

//
//#define _INIT_FONTIMAGE_SIZE  512
//#define _MAX_FONTIMAGE_SIZE   2048
//
//#define _INIT_COMMANDS_SIZE 256
//#define _INIT_POINTS_SIZE 128
//#define _INIT_PATHS_SIZE 16
//#define _INIT_VERTS_SIZE 256
//
//
//#define NANO2D_KAPPA90 0.5522847493f	// Length proportional to radius of a cubic bezier handle for 90deg arcs.
//
//#define NANO2D_COUNTOF(arr) (sizeof(arr) / sizeof(0[arr]))
//
//	enum enum_command {
//		e_command_move_to = 0,
//		e_command_line_to = 1,
//		e_command_bezier_to = 2,
//		e_command_close = 3,
//		e_command_winding = 4,
//	};
//
//	enum enum_pointer
//	{
//		e_point_corner = 0x01,
//		e_point_left = 0x02,
//		e_point_bevel = 0x04,
//		e_point_inner_bevel = 0x08,
//	};
//
//
//	struct color {
//		union {
//			::f32 rgba[4];
//			struct {
//				::f32 r, g, b, a;
//			};
//		};
//	};

	struct paint {
		::f32 xform[6];
		::f32 extent[2];
		::f32 radius;
		::f32 feather;
      ::color::color innerColor;
		::color::color outerColor;
		::i32 image;
	};
	typedef struct paint paint;

	//enum enum_winding {
	//	e_winding_ccw = 1,			// Winding for solid shapes
	//	e_winding_cw = 2,				// Winding for holes
	//};

	//enum enum_solidity {
	//	e_solidity_solid = 1,			// CCW
	//	e_solidity_hole = 2,			// CW
	//};

	//enum enum_line_cap {
	//	e_line_cap_butt,
	//	e_line_cap_round,
	//	e_line_cap_square,
	//};

	//enum enum_line_join {
	//	e_line_join_bevel,
	//	e_line_join_miter
	//};


	//enum enum_align {
	//	// Horizontal align
	//	e_align_left = 1 << 0,	// Default, align text horizontally to left.
	//	e_align_center = 1 << 1,	// Align text horizontally to center.
	//	e_align_right = 1 << 2,	// Align text horizontally to right.
	//	// Vertical align
	//	e_align_top = 1 << 3,	// Align text vertically to top.
	//	e_align_middle = 1 << 4,	// Align text vertically to middle.
	//	e_align_bottom = 1 << 5,	// Align text vertically to bottom.
	//	e_align_baseline = 1 << 6, // Default, align text vertically to baseline.
	//};

	//enum enum_blend_factor {
	//	e_blend_factor_zero = 1 << 0,
	//	e_blend_factor_one = 1 << 1,
	//	e_blend_factor_src_color = 1 << 2,
	//	e_blend_factor_one_minus_src_color = 1 << 3,
	//	e_blend_factor_dst_color = 1 << 4,
	//	e_blend_factor_one_minus_dst_color = 1 << 5,
	//	e_blend_factor_src_alpha = 1 << 6,
	//	e_blend_factor_one_minus_src_alpha = 1 << 7,
	//	e_blend_factor_dst_alpha = 1 << 8,
	//	e_blend_factor_one_minus_dst_alpha = 1 << 9,
	//	e_blend_factor_src_alpha_saturate = 1 << 10,
	//};

	//enum enum_composite_operation {
	//	e_composite_operation_source_over,
	//	e_composite_operation_source_in,
	//	e_composite_operation_source_out,
	//	e_composite_operation_atop,
	//	e_composite_operation_destination_over,
	//	e_composite_operation_destination_in,
	//	e_composite_operation_destination_out,
	//	e_composite_operation_destination_atop,
	//	e_composite_operation_lighter,
	//	e_composite_operation_copy,
	//	e_composite_operation_xor,
	//};

	struct compositeOperationState {
		::i32 srcRGB;
		::i32 dstRGB;
		::i32 srcAlpha;
		::i32 dstAlpha;
	};
	typedef struct compositeOperationState compositeOperationState;

	struct glyphPosition {
		const_char_pointer str;	// Position of the glyph in the input string.
		::f32 x;			// The x-coordinate of the logical glyph position.
		::f32 minx, maxx;	// The bounds of the glyph shape.
	};
	

	//enum imageFlags {
	//	_IMAGE_GENERATE_MIPMAPS = 1 << 0,     // Generate mipmaps during creation of the image.
	//	_IMAGE_REPEATX = 1 << 1,		// Repeat image in X direction.
	//	_IMAGE_REPEATY = 1 << 2,		// Repeat image in Y direction.
	//	_IMAGE_FLIPY = 1 << 3,		// Flips (inverses) image in Y direction when rendered.
	//	_IMAGE_PREMULTIPLIED = 1 << 4,		// Image data has premultiplied alpha.
	//	_IMAGE_NEAREST = 1 << 5,		// Image interpolation is Nearest instead Linear
	//};


	// The following functions can be used to make calculations on 2x3 transformation matrices.
	// A 2x3 matrix is represented as ::f32[6].

	// Sets the transform to identity matrix.
	CLASS_DECL_NANO2D void TransformIdentity(::f32* dst);

	// Sets the transform to translation matrix matrix.
	CLASS_DECL_NANO2D void TransformTranslate(::f32* dst, ::f32 tx, ::f32 ty);

	// Sets the transform to scale matrix.
	CLASS_DECL_NANO2D void TransformScale(::f32* dst, ::f32 sx, ::f32 sy);

	// Sets the transform to rotate matrix. Angle is specified in radians.
	CLASS_DECL_NANO2D void TransformRotate(::f32* dst, ::f32 a);

	// Sets the transform to skew-x matrix. Angle is specified in radians.
	CLASS_DECL_NANO2D void TransformSkewX(::f32* dst, ::f32 a);

	// Sets the transform to skew-y matrix. Angle is specified in radians.
	CLASS_DECL_NANO2D void TransformSkewY(::f32* dst, ::f32 a);

	// Sets the transform to the result of multiplication of two transforms, of A = A*B.
	CLASS_DECL_NANO2D void TransformMultiply(::f32* dst, const ::f32* src);

	// Sets the transform to the result of multiplication of two transforms, of A = B*A.
	CLASS_DECL_NANO2D void TransformPremultiply(::f32* dst, const ::f32* src);

	// Sets the destination to inverse of specified transform.
	// Returns 1 if the inverse could be calculated, else 0.
	CLASS_DECL_NANO2D ::i32 TransformInverse(::f32* dst, const ::f32* src);

	// Transform a point by given transform.
	CLASS_DECL_NANO2D void TransformPoint(::f32* dstx, ::f32* dsty, const ::f32* xform, ::f32 srcx, ::f32 srcy);

	// Converts degrees to radians and vice versa.
	CLASS_DECL_NANO2D	::f32 DegToRad(::f32 deg);
	CLASS_DECL_NANO2D	::f32 RadToDeg(::f32 rad);



	////
	//// Internal Render API
	////
	//enum texture {
	//	_TEXTURE_ALPHA = 0x01,
	//	_TEXTURE_RGBA = 0x02,
	//};

	struct scissor {
		::f32 xform[6];
		::f32 extent[2];
	};

	struct vertex {
		::f32 x, y, u, v;
	};

	struct path {
		::i32 first;
		::i32 count;
		::u8 closed;
		::i32 nbevel;
		vertex* fill;
		::i32 nfill;
		vertex* stroke;
		::i32 nstroke;
		::i32 winding;
		::i32 convex;
	};

	struct params {
		void* userPtr;
		::i32 edgeAntiAlias;
		::i32 (*renderCreate)(void* uptr);
		::i32 (*renderCreateTexture)(void* uptr, ::i32 type, ::i32 w, ::i32 h, ::i32 imageFlags, const ::u8* data);
		::i32 (*renderDeleteTexture)(void* uptr, ::i32 image);
		::i32 (*renderUpdateTexture)(void* uptr, ::i32 image, ::i32 x, ::i32 y, ::i32 w, ::i32 h, const ::u8* data);
		::i32 (*renderGetTextureSize)(void* uptr, ::i32 image, ::i32* w, ::i32* h);
		void (*renderContext)(void* uptr, ::f32 width, ::f32 height, ::f32 devicePixelRatio);
		void (*renderCancel)(void* uptr);
		void (*renderFlush)(void* uptr);
		void (*renderFill)(void* uptr, paint* paint, compositeOperationState compositeOperation, scissor* scissor, ::f32 fringe, const ::f32* bounds, const path* paths, ::i32 npaths);
		void (*renderStroke)(void* uptr, paint* paint, compositeOperationState compositeOperation, scissor* scissor, ::f32 fringe, ::f32 strokeWidth, const path* paths, ::i32 npaths);
		void (*renderTriangles)(void* uptr, paint* paint, compositeOperationState compositeOperation, scissor* scissor, const vertex* verts, ::i32 nverts, ::f32 fringe);
		void (*renderDelete)(void* uptr);
	};

	// Constructor and destructor, called by the render back-end.
	CLASS_DECL_NANO2D context * CreateInternal(params* params);
	CLASS_DECL_NANO2D void DeleteInternal(context* pcontext);


	struct state :
		virtual public ::particle
	{
		compositeOperationState compositeOperation;
		::i32 shapeAntiAlias;
		paint fill;
		paint stroke;
		::f32 strokeWidth;
		::f32 miterLimit;
		::i32 lineJoin;
		::i32 lineCap;
		::f32 alpha;
		::f32 xform[6];
		scissor m_scissor;
		//::f32 fontSize;
		::f32 letterSpacing;
		::f32 lineHeight;
		::f32 fontBlur;
		//::i32 textAlign;
		::i32 fontId;
   
   
   ::i32                         m_iSavedContext;

   string                        m_strFontFace;
	bool                        m_bDiacritics = true;
   ::f32                         m_fFontSize;

   ::e_align                     m_ealignText;

   ::f64_point                   m_pointCurrent;

   ::geometry2d::matrix          m_matrix;

   bool                          m_bHasCurrentPoint;

   state()
   {

      m_fFontSize = 0.f;

   }

	};


	typedef struct state state;

	struct point {
		::f32 x, y;
		::f32 Δx, Δy;
		::f32 len;
		::f32 dmx, dmy;
		::u8 flags;
	};
	typedef struct point point;


	struct pathCache {
		point* points;
		::i32 npoints;
		::i32 cpoints;
		path* paths;
		::i32 npaths;
		::i32 cpaths;
		vertex* verts;
		::i32 nverts;
		::i32 cverts;
		::f32 bounds[4];
	};
	typedef struct pathCache pathCache;
//#define _MAX_STATES 32
//#define _MAX_FONTIMAGES       4

//	struct CONTEXT
//	{
//
//		params params;
//		::f32* commands;
//		::i32 ccommands;
//		::i32 ncommands;
//		::f32 commandx, commandy;
//		state states[_MAX_STATES];
//		::i32 nstates;
//		pathCache* cache;
//		::f32 tessTol;
//		::f32 distTol;
//		::f32 fringeWidth;
//		::f32 devicePxRatio;
//		struct FONScontext* fs;
//		::i32 fontImages[_MAX_FONTIMAGES];
//		::i32 fontImageIdx;
//		::i32 drawCallCount;
//		::i32 fillTriCount;
//		::i32 strokeTriCount;
//		::i32 textTriCount;
//		void* p;
//
//
//		  state* __getState();
//
//
//		params* InternalParams(  CONTEXT* pcontext);
//
//		// Debug function to dump cached path data.
//		CLASS_DECL_NANO2D void debug_dump_path_cache(  CONTEXT* pcontext);
//		// Begin drawing a ___new frame
//// Calls to nanovg drawing API should be wrapped in BeginFrame() & EndFrame()
//// BeginFrame() defines the size of the window to render to in relation currently
//// set viewport (i.e. glContext on GL backends). Device pixel ration allows to
//// control the rendering on Hi-DPI devices.
//// For example, GLFW returns two dimension for an opened window: window size and
//// frame buffer size. In that case you would set windowWidth/Height to the window size
//// devicePixelRatio to: framebufferWidth / windowWidth.
//		void begin_frame(::f32 windowWidth, ::f32 windowHeight, ::f32 devicePixelRatio);
//
//		// Cancels drawing the current frame.
//		void cancel_frame();
//
//		// Ends drawing flushing remaining render state.
//		void end_frame();
//
//		//
//		// Composite operation
//		//
//		// The composite operations in NanoVG are modeled after HTML Canvas API, and
//		// the blend func is based on OpenGL (see corresponding manuals for more info).
//		// The colors in the blending state have premultiplied alpha.
//
//		// Sets the composite operation. The op parameter should be one of compositeOperation.
//		void global_composite_operation(::i32 op);
//
//		// Sets the composite operation with custom pixel arithmetic. The parameters should be one of blendFactor.
//		void global_composite_blend_func(::i32 sfactor, ::i32 dfactor);
//
//		// Sets the composite operation with custom pixel arithmetic for RGB and alpha components separately. The parameters should be one of blendFactor.
//		void global_composite_blend_func_separate(::i32 srcRGB, ::i32 dstRGB, ::i32 srcAlpha, ::i32 dstAlpha);
//
//		//
//		// State Handling
//		//
//		// NanoVG contains state which represents how paths will be rendered.
//		// The state contains transform, fill and stroke styles, text and font styles,
//		// and scissor clipping.
//
//		// Pushes and saves the current render state into a state stack.
//		// A matching Restore() must be used to restore the state.
//		virtual void save();
//
//		// Pops and restores current render state.
//		virtual void restore();
//
//		// Resets current render state to default values. Does not affect the render state stack.
//		virtual void reset();
//
//		//
//		// Render styles
//		//
//		// Fill and stroke render style can be either a solid color or a paint which is a gradient or a pattern.
//		// Solid color is simply defined as a color value, different kinds of paints can be created
//		// using LinearGradient(), BoxGradient(), RadialGradient() and ImagePattern().
//		//
//		// Current render style can be saved and restored using Save() and Restore().
//
//		// Sets whether to draw antialias for Stroke() and Fill(). It's enabled by default.
//		void shape_anti_alias(::i32 enabled);
//
//		// Sets current stroke style to a solid color.
//		void stroke_color(  color color);
//
//		// Sets current stroke style to a paint, which can be a one of the gradients or a pattern.
//		void stroke_paint(paint paint);
//
//		// Sets current fill style to a solid color.
//		void fill_color(  color color);
//
//		// Sets current fill style to a paint, which can be a one of the gradients or a pattern.
//		void fill_paint(paint paint);
//
//		// Sets the miter limit of the stroke style.
//		// Miter limit controls when a sharp corner is beveled.
//		virtual void miter_limit(::f32 limit);
//
//		// Sets the stroke width of the stroke style.
//		virtual void stroke_width(::f32 size);
//
//		// Sets how the end of the line (cap) is drawn,
//		// Can be one of: _BUTT (default), _ROUND, _SQUARE.
//		virtual void line_cap(::i32 cap);
//
//		// Sets how sharp path corners are drawn.
//		// Can be one of _MITER (default), _ROUND, _BEVEL.
//		virtual void line_join(::i32 join);
//
//		// Sets the transparency applied to all rendered shapes.
//		// Already transparent paths will get proportionally more transparent as well.
//		virtual void global_alpha(::f32 alpha);
//
//
//		//
//		// Transforms
//		//
//		// The paths, gradients, patterns and scissor region are transformed by an transformation
//		// matrix at the time when they are passed to the API.
//		// The current transformation matrix is a affine matrix:
//		//   [sx kx tx]
//		//   [ky sy ty]
//		//   [ 0  0  1]
//		// Where: sx,sy define scaling, kx,ky skewing, and tx,ty translation.
//		// The last row is assumed to be 0,0,1 and is not stored.
//		//
//		// Apart from ResetTransform(), each transformation function first creates
//		// specific transformation matrix and pre-multiplies the current transformation by it.
//		//
//		// Current coordinate system (transformation) can be saved and restored using Save() and Restore().
//
//		// Resets current transform to a identity matrix.
//		void reset_transform();
//
//		// Premultiplies current coordinate system by specified matrix.
//		// The parameters are interpreted as matrix as follows:
//		//   [a c e]
//		//   [b d f]
//		//   [0 0 1]
//		void transform(::f32 a, ::f32 b, ::f32 c, ::f32 d, ::f32 e, ::f32 f);
//
//		// Translates current coordinate system.
//		//void Translate(::f32 x, ::f32 y);
//		virtual void translate(::f32 x, ::f32 y);
//
//		// Rotates current coordinate system. Angle is specified in radians.
//		void rotate(::f32 angle);
//
//		// Skews the current coordinate system along X axis. Angle is specified in radians.
//		void skew_x(::f32 angle);
//
//		// Skews the current coordinate system along Y axis. Angle is specified in radians.
//		void skew_y(::f32 angle);
//
//		// Scales the current coordinate system.
//		void scale(::f32 x, ::f32 y);
//
//		// Stores the top part (a-f) of the current transformation matrix in to the specified buffer.
//		//   [a c e]
//		//   [b d f]
//		//   [0 0 1]
//		// There should be space for 6 f32s in the return buffer for the values a-f.
//		void current_transform(::f32* xform);
//
//		//
//		// Images
//		//
//		// NanoVG allows you to load jpg, png, psd, tga, pic and gif files to be used for rendering.
//		// In addition you can upload your own image. The image loading is provided by stb_image.
//		// The parameter imageFlags is combination of flags defined in imageFlags.
//
//		// Creates image by loading it from the disk from specified file name.
//		// Returns handle to the image.
//		::i32 create_image(const ::scoped_string& scopedstrFilename, ::i32 imageFlags);
//
//		// Creates image by loading it from the specified chunk of memory.
//		// Returns handle to the image.
//		::i32 create_image_mem(::i32 imageFlags, ::u8* data, ::i32 ndata);
//
//		// Creates image from specified image data.
//		// Returns handle to the image.
//		::i32 create_image_rgba(::i32 w, ::i32 h, ::i32 imageFlags, const void* data, ::i32 iScan);
//
//		// Updates image data specified by image handle.
//		void update_image(::i32 image, const void* data);
//
//		// Returns the dimensions of a created image.
//		void image_size(::i32 image, ::i32* w, ::i32* h);
//
//		// Deletes created image.
//		void delete_image(::i32 image);
//
//		//
//		// Paints
//		//
//		// NanoVG supports four types of paints: linear gradient, box gradient, radial gradient and image pattern.
//		// These can be used as paints for strokes and fills.
//
//		// Creates and returns a linear gradient. Parameters (sx,sy)-(ex,ey) specify the start and end coordinates
//		// of the linear gradient, icol specifies the start color and ocol the end color.
//		// The gradient is transformed by the current transform when it is passed to FillPaint() or StrokePaint().
//		  paint linear_gradient(::f32 sx, ::f32 sy, ::f32 ex, ::f32 ey,
//			  color icol,   color ocol);
//
//		// Creates and returns a box gradient. Box gradient is a feathered rounded rectangle, it is useful for rendering
//		// drop shadows or highlights for boxes. Parameters (x,y) define the top-left corner of the rectangle,
//		// (w,h) define the size of the rectangle, r defines the corner radius, and f feather. Feather defines how blurry
//		// the border of the rectangle is. Parameter icol specifies the inner color and ocol the outer color of the gradient.
//		// The gradient is transformed by the current transform when it is passed to FillPaint() or StrokePaint().
//		  paint box_gradient(::f32 x, ::f32 y, ::f32 w, ::f32 h,
//			::f32 r, ::f32 f,   color icol,   color ocol);
//
//		// Creates and returns a radial gradient. Parameters (cx,cy) specify the center, inr and outr specify
//		// the inner and outer radius of the gradient, icol specifies the start color and ocol the end color.
//		// The gradient is transformed by the current transform when it is passed to FillPaint() or StrokePaint().
//		  paint radial_gradient(::f32 cx, ::f32 cy, ::f32 inr, ::f32 outr,
//			  color icol,   color ocol);
//
//		// Creates and returns an image pattern. Parameters (ox,oy) specify the left-top location of the image pattern,
//		// (ex,ey) the size of one image, angle rotation around the top-left corner, image is handle to the image to render.
//		// The gradient is transformed by the current transform when it is passed to FillPaint() or StrokePaint().
//		  paint image_pattern(::f32 ox, ::f32 oy, ::f32 ex, ::f32 ey,
//			::f32 angle, ::i32 image, ::f32 alpha);
//
//		//
//		// Scissoring
//		//
//		// Scissoring allows you to clip the rendering into a rectangle. This is useful for various
//		// user interface cases like rendering a text edit or a timeline.
//
//		// Sets the current scissor rectangle.
//		// The scissor rectangle is transformed by the current transform.
//		void scissor(::f32 x, ::f32 y, ::f32 w, ::f32 h);
//
//		// Intersects current scissor rectangle with the specified rectangle.
//		// The scissor rectangle is transformed by the current transform.
//		// Note: in case the rotation of previous scissor rect differs from
//		// the current one, the intersection will be done between the specified
//		// rectangle and the previous scissor rectangle transformed in the current
//		// transform space. The resulting shape is always rectangle.
//		void intersect_scissor(::f32 x, ::f32 y, ::f32 w, ::f32 h);
//
//		// Reset and disables scissoring.
//		void reset_scissor();
//
//		//
//		// Paths
//		//
//		// Drawing a ___new shape starts with BeginPath(), it clears all the currently defined paths.
//		// Then you define one or more paths and sub-paths which describe the shape. The are functions
//		// to draw common shapes like rectangles and circles, and lower level step-by-step functions,
//		// which allow to define a path curve by curve.
//		//
//		// NanoVG uses even-odd fill rule to draw the shapes. Solid shapes should have counter clockwise
//		// winding and holes should have counter clockwise order. To specify winding of a path you can
//		// call PathWinding(). This is useful especially for the common shapes, which are drawn CCW.
//		//
//		// Finally you can fill the path using current fill style by calling Fill(), and stroke it
//		// with current stroke style by calling Stroke().
//		//
//		// The curve segments and sub-paths are transformed by the current transform.
//
//		// Clears the current path and sub-paths.
//		void begin_path();
//
//		// Starts ___new sub-path with specified point as first point.
//		void move_to(::f32 x, ::f32 y);
//
//		// Adds line segment from the last point in the path to the specified point.
//		void line_to(::f32 x, ::f32 y);
//
//		// Adds cubic bezier segment from last point in the path via two control points to the specified point.
//		void bezier_to(::f32 c1x, ::f32 c1y, ::f32 c2x, ::f32 c2y, ::f32 x, ::f32 y);
//
//		// Adds quadratic bezier segment from last point in the path via a control point to the specified point.
//		void quad_to(::f32 cx, ::f32 cy, ::f32 x, ::f32 y);
//
//		// Adds an arc segment at the corner defined by the last path point, and two specified points.
//		void arc_to(::f32 x1, ::f32 y1, ::f32 x2, ::f32 y2, ::f32 radius);
//
//		// Closes current sub-path with a line segment.
//		void close_path();
//
//		// Sets the current sub-path winding, see winding and solidity.
//		void path_winding(::i32 dir);
//
//		// Creates ___new circle arc shaped sub-path. The arc center is at cx,cy, the arc radius is r,
//		// and the arc is drawn from angle a0 to a1, and swept in direction dir (_CCW, or _CW).
//		// Angles are specified in radians.
//		void arc(::f32 cx, ::f32 cy, ::f32 r, ::f32 a0, ::f32 a1, ::i32 dir);
//
//		// Creates ___new rectangle shaped sub-path.
//		void rectangle(::f32 x, ::f32 y, ::f32 w, ::f32 h);
//
//		// Creates ___new rounded rectangle shaped sub-path.
//		void rounded_rectangle(::f32 x, ::f32 y, ::f32 w, ::f32 h, ::f32 r);
//
//		// Creates ___new rounded rectangle shaped sub-path with varying radii for each corner.
//		void rounded_rectangle_varying(::f32 x, ::f32 y, ::f32 w, ::f32 h, ::f32 radTopLeft, ::f32 radTopRight, ::f32 radBottomRight, ::f32 radBottomLeft);
//
//		// Creates ___new ellipse shaped sub-path.
//		void ellipse(::f32 cx, ::f32 cy, ::f32 rx, ::f32 ry);
//
//		// Creates ___new circle shaped sub-path.
//		void circle(::f32 cx, ::f32 cy, ::f32 r);
//
//		// Fills the current path with current fill style.
//		void fill();
//
//		// Fills the current path with current stroke style.
//		void stroke();
//
//		//
//		// Text
//		//
//		// NanoVG allows you to load .ttf files and use the font to render text.
//		//
//		// The appearance of the text can be defined by setting the current text style
//		// and by specifying the fill color. Common text and font settings such as
//		// font size, letter spacing and text align are supported. Font blur allows you
//		// to create simple text effects such as drop shadows.
//		//
//		// At render time the font face can be set based on the font handles or name.
//		//
//		// Font measure functions return values in local space, the calculations are
//		// carried in the same resolution as the final rendering. This is done because
//		// the text glyph positions are snapped to the nearest pixels sharp rendering.
//		//
//		// The local space means that values are not rotated or scale as per the current
//		// transformation. For example if you set font size to 12, which would mean that
//		// line height is 16, then regardless of the current scaling and rotation, the
//		// returned line height is always 16. Some measures may vary because of the scaling
//		// since aforementioned pixel snapping.
//		//
//		// While this may sound a little odd, the setup allows you to always render the
//		// same way regardless of scaling. I.e. following works regardless of scaling:
//		//
//		//		const_char_pointer txt = "Text me up.";
//		//		TextBounds(vg, x,y, txt, NULL, bounds);
//		//		BeginPath(vg);
//		//		RoundedRect(vg, bounds[0],bounds[1], bounds[2]-bounds[0], bounds[3]-bounds[1]);
//		//		Fill(vg);
//		//
//		// Note: currently only solid color fill is supported for text.
//
//		// Creates font by loading it from the disk from specified file name.
//		// Returns handle to the font.
//		//::i32 CreateFont(  CONTEXT * pcontext, const ::scoped_string & name, const ::scoped_string & filename);
//
//		// fontIndex specifies which font face to load from a .ttf/.ttc file.
//		::i32 create_font_at_index(const ::scoped_string& name, const ::scoped_string& filename, const ::i32 fontIndex);
//
//		// Creates font by loading it from the specified memory chunk.
//		// Returns handle to the font.
//		::i32 create_font_mem(const ::scoped_string& name, ::u8* data, ::i32 ndata, ::i32 freeData);
//
//		// fontIndex specifies which font face to load from a .ttf/.ttc file.
//		::i32 create_font_mem_at_index(const ::scoped_string& name, ::u8* data, ::i32 ndata, ::i32 freeData, const ::i32 fontIndex);
//
//		// Finds a loaded font of specified name, and returns handle to it, or -1 if the font is not found.
//		::i32 find_font(const ::scoped_string& name);
//
//		// Adds a fallback font by handle.
//		::i32 add_fallback_font_id(::i32 baseFont, ::i32 fallbackFont);
//
//		// Adds a fallback font by name.
//		::i32 add_fallback_font(const ::scoped_string& baseFont, const ::scoped_string& fallbackFont);
//
//		// Resets fallback fonts by handle.
//		void reset_fallback_fonts_id(::i32 baseFont);
//
//		// Resets fallback fonts by name.
//		void reset_fallback_fonts(const ::scoped_string& baseFont);
//
//		// Sets the font size of current text style.
//		void font_size(::f32 size);
//
//		// Sets the blur of current text style.
//		void font_blur(::f32 blur);
//
//		// Sets the letter spacing of current text style.
//		void text_letter_spacing(::f32 spacing);
//
//		// Sets the proportional line height of current text style. The line height is specified as multiple of font size.
//		void text_line_height(::f32 lineHeight);
//
//		// Sets the text align of current text style, see align for options.
//		void text_align(::i32 align);
//
//		// Sets the font face based on specified id of current text style.
//		void font_face_id(::i32 font);
//
//		// Sets the font face based on specified name of current text style.
//		void font_face(const ::scoped_string& font);
//
//		// Draws text string at specified location. If end is specified only the sub-string up to the end is drawn.
//		::f32 text(::f32 x, ::f32 y, const ::scoped_string& string, const ::scoped_string& end);
//
//		// Draws multi-line text string at specified location wrapped at the specified width. If end is specified only the sub-string up to the end is drawn.
//		// White space is stripped at the beginning of the rows, the text is split at word boundaries or when ___new-line characters are encountered.
//		// Words longer than the max width are slit at nearest character (i.e. no hyphenation).
//		void text_box(::f32 x, ::f32 y, ::f32 breakRowWidth, const ::scoped_string& string, const ::scoped_string& end);
//
//		// Measures the specified text string. Parameter bounds should be a pointer to ::f32[4],
//		// if the bounding box of the text should be returned. The bounds value are [xmin,ymin, xmax,ymax]
//		// Returns the horizontal advance of the measured text (i.e. where the next character should drawn).
//		// Measured values are returned in local coordinate space.
//		::f32 text_bounds(::f32 x, ::f32 y, const ::scoped_string& string, const ::scoped_string& end, ::f32* bounds);
//
//		// Measures the specified multi-text string. Parameter bounds should be a pointer to ::f32[4],
//		// if the bounding box of the text should be returned. The bounds value are [xmin,ymin, xmax,ymax]
//		// Measured values are returned in local coordinate space.
//		void text_box_bounds(::f32 x, ::f32 y, ::f32 breakRowWidth, const ::scoped_string& string, const ::scoped_string& end, ::f32* bounds);
//
//		// Calculates the glyph x positions of the specified text. If end is specified only the sub-string will be used.
//		// Measured values are returned in local coordinate space.
//		::i32 text_glyph_positions(::f32 x, ::f32 y, const ::scoped_string& string, const ::scoped_string& end, glyphPosition* positions, ::i32 maxPositions);
//
//		// Returns the vertical metrics based on the current text style.
//		// Measured values are returned in local coordinate space.
//		void text_metrics(::f32* ascender, ::f32* descender, ::f32* lineh);
//
//		// Breaks the specified text into lines. If end is specified only the sub-string will be used.
//		// White space is stripped at the beginning of the rows, the text is split at word boundaries or when ___new-line characters are encountered.
//		// Words longer than the max width are slit at nearest character (i.e. no hyphenation).
//		::i32 text_break_lines(const ::scoped_string& string, const ::scoped_string& end, ::f32 breakRowWidth, text_row* rows, ::i32 maxRows);
//
//		void __append_commands(::f32* vals, ::i32 nvals);
//
//	};
//
//#ifdef _MSC_VER
//#pragma warning(pop)
//#endif
//
//#define _NOTUSED(v) for (;;) { (void(1 ? (void)0 : ( (void(v) ) ); break; }
//
	//#ifdef __cplusplus
	//}
	//#endif

} // namespace nano2d

