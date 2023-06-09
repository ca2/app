//
// Alignment and Orientation From Layout.h by camilo on 2022-09-08 23:57 <3ThomasBorregaardSorensen!!
//
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



namespace nano2d
{


	constexpr float f_pi = 3.14159265358979323846264338327f;


	constexpr int INIT_FONTIMAGE_SIZE = 512;
	constexpr int MAX_FONTIMAGE_SIZE = 2048;

	constexpr int INIT_COMMANDS_SIZE = 256;
	constexpr int INIT_POINTS_SIZE = 128;
	constexpr int INIT_PATHS_SIZE = 16;
	constexpr int INIT_VERTS_SIZE = 256;


	constexpr float KAPPA90 = 0.5522847493f;	// Length proportional to radius of a cubic bezier handle for 90deg arcs.

	#define NANO2D_COUNTOF(arr) (sizeof(arr) / sizeof(0[arr]))



	enum enum_codepoint 
	{

		e_codepoint_none = 0,
		e_codepoint_space,
		e_codepoint_new_line,
		e_codepoint_character,
		e_codepoint_cjk_character,

	};


	enum enum_command 
	{
		e_command_move_to = 0,
		e_command_line_to = 1,
		e_command_bezier_to = 2,
		e_command_close = 3,
		e_command_winding = 4,
	};

	enum enum_pointer
	{
		e_point_corner = 0x01,
		e_point_left = 0x02,
		e_point_bevel = 0x04,
		e_point_inner_bevel = 0x08,
	};


	enum enum_winding {
		e_winding_ccw = 1,			// Winding for solid shapes
		e_winding_cw = 2,				// Winding for holes
	};

	enum enum_solidity {
		e_solidity_solid = 1,			// CCW
		e_solidity_hole = 2,			// CW
	};

	enum enum_line_cap {
		e_line_cap_butt,
		e_line_cap_round,
		e_line_cap_square,
	};

	enum enum_line_join {
		e_line_join_bevel,
		e_line_join_miter
	};


	enum enum_align {
		// Horizontal align
		e_align_left = 1 << 0,	// Default, align text horizontally to left.
		e_align_center = 1 << 1,	// Align text horizontally to center.
		e_align_right = 1 << 2,	// Align text horizontally to right.
		// Vertical align
		e_align_top = 1 << 3,	// Align text vertically to top.
		e_align_middle = 1 << 4,	// Align text vertically to middle.
		e_align_bottom = 1 << 5,	// Align text vertically to bottom.
		e_align_baseline = 1 << 6, // Default, align text vertically to baseline.
	};

	enum enum_blend_factor {
		e_blend_factor_zero = 1 << 0,
		e_blend_factor_one = 1 << 1,
		e_blend_factor_src_color = 1 << 2,
		e_blend_factor_one_minus_src_color = 1 << 3,
		e_blend_factor_dst_color = 1 << 4,
		e_blend_factor_one_minus_dst_color = 1 << 5,
		e_blend_factor_src_alpha = 1 << 6,
		e_blend_factor_one_minus_src_alpha = 1 << 7,
		e_blend_factor_dst_alpha = 1 << 8,
		e_blend_factor_one_minus_dst_alpha = 1 << 9,
		e_blend_factor_src_alpha_saturate = 1 << 10,
	};

	enum enum_composite_operation {
		e_composite_operation_source_over,
		e_composite_operation_source_in,
		e_composite_operation_source_out,
		e_composite_operation_atop,
		e_composite_operation_destination_over,
		e_composite_operation_destination_in,
		e_composite_operation_destination_out,
		e_composite_operation_destination_atop,
		e_composite_operation_lighter,
		e_composite_operation_copy,
		e_composite_operation_xor,
	};

	enum enum_image {
		e_image_generate_mipmaps = 1 << 0,     // Generate mipmaps during creation of the image.
		e_image_repeat_x = 1 << 1,		// Repeat image in X direction.
		e_image_repeat_y = 1 << 2,		// Repeat image in Y direction.
		e_image_flip_y = 1 << 3,		// Flips (inverses) image in Y direction when rendered.
		e_image_premultiplied = 1 << 4,		// Image data has premultiplied alpha.
		e_image_nearest = 1 << 5,		// Image interpolation is Nearest instead Linear
	};

	////
	//// Color utils
	////
	//// Colors in NanoVG are stored as unsigned ints in ABGR format.

	//// Returns a color value from red, green, blue values. Alpha will be set to 255 (1.0f).
	//CLASS_DECL_NANO2D   color RGB(unsigned char r, unsigned char g, unsigned char b);

	//// Returns a color value from red, green, blue values. Alpha will be set to 1.0f.
	//CLASS_DECL_NANO2D  color RGBf(float r, float g, float b);


	//// Returns a color value from red, green, blue and alpha values.
	//CLASS_DECL_NANO2D  color RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	//// Returns a color value from red, green, blue and alpha values.
	//CLASS_DECL_NANO2D  color RGBAf(float r, float g, float b, float a);


	//// Linearly interpolates from color c0 to c1, and returns resulting color value.
	//CLASS_DECL_NANO2D  color LerpRGBA(color c0, color c1, float u);

	//// Sets transparency of a color value.
	//CLASS_DECL_NANO2D  color TransRGBA(color c0, unsigned char a);

	//// Sets transparency of a color value.
	//CLASS_DECL_NANO2D  color TransRGBAf(color c0, float a);

	//// Returns color value specified by hue, saturation and lightness.
	//// HSL values are all in range [0..1], alpha will be set to 255.
	//CLASS_DECL_NANO2D  color HSL(float h, float s, float l);

	//// Returns color value specified by hue, saturation and lightness and alpha.
	//// HSL values are all in range [0..1], alpha in range [0..255]
	//CLASS_DECL_NANO2D  color HSLA(float h, float s, float l, unsigned char a);


	//// The following functions can be used to make calculations on 2x3 transformation matrices.
	//// A 2x3 matrix is represented as float[6].

	//// Sets the transform to identity matrix.
	//CLASS_DECL_NANO2D void TransformIdentity(float* dst);

	//// Sets the transform to translation matrix matrix.
	//CLASS_DECL_NANO2D void TransformTranslate(float* dst, float tx, float ty);

	//// Sets the transform to scale matrix.
	//CLASS_DECL_NANO2D void TransformScale(float* dst, float sx, float sy);

	//// Sets the transform to rotate matrix. Angle is specified in radians.
	//CLASS_DECL_NANO2D void TransformRotate(float* dst, float a);

	//// Sets the transform to skew-x matrix. Angle is specified in radians.
	//CLASS_DECL_NANO2D void TransformSkewX(float* dst, float a);

	//// Sets the transform to skew-y matrix. Angle is specified in radians.
	//CLASS_DECL_NANO2D void TransformSkewY(float* dst, float a);

	//// Sets the transform to the result of multiplication of two transforms, of A = A*B.
	//CLASS_DECL_NANO2D void TransformMultiply(float* dst, const float* src);

	//// Sets the transform to the result of multiplication of two transforms, of A = B*A.
	//CLASS_DECL_NANO2D void TransformPremultiply(float* dst, const float* src);

	//// Sets the destination to inverse of specified transform.
	//// Returns 1 if the inverse could be calculated, else 0.
	//CLASS_DECL_NANO2D int TransformInverse(float* dst, const float* src);

	//// Transform a point by given transform.
	//CLASS_DECL_NANO2D void TransformPoint(float* dstx, float* dsty, const float* xform, float srcx, float srcy);

	//// Converts degrees to radians and vice versa.
	//CLASS_DECL_NANO2D	float DegToRad(float deg);
	//CLASS_DECL_NANO2D	float RadToDeg(float rad);



	//
	// Internal Render API
	//
	enum enum_texture {
		e_texture_alpha = 0x01,
		e_texture_rgba = 0x02,
	};

	//struct scissor {
	//	float xform[6];
	//	float extent[2];
	//};
	//typedef struct scissor scissor;

	//struct vertex {
	//	float x, y, u, v;
	//};
	//typedef struct vertex vertex;

	//struct path {
	//	int first;
	//	int count;
	//	unsigned char closed;
	//	int nbevel;
	//	vertex* fill;
	//	int nfill;
	//	vertex* stroke;
	//	int nstroke;
	//	int winding;
	//	int convex;
	//};
	//typedef struct path path;

	//struct params {
	//	void* userPtr;
	//	int edgeAntiAlias;
	//	int (*renderCreate)(void* uptr);
	//	int (*renderCreateTexture)(void* uptr, int type, int w, int h, int imageFlags, const unsigned char* data);
	//	int (*renderDeleteTexture)(void* uptr, int image);
	//	int (*renderUpdateTexture)(void* uptr, int image, int x, int y, int w, int h, const unsigned char* data);
	//	int (*renderGetTextureSize)(void* uptr, int image, int* w, int* h);
	//	void (*renderContext)(void* uptr, float width, float height, float devicePixelRatio);
	//	void (*renderCancel)(void* uptr);
	//	void (*renderFlush)(void* uptr);
	//	void (*renderFill)(void* uptr, paint* paint, compositeOperationState compositeOperation, scissor* scissor, float fringe, const float* bounds, const path* paths, int npaths);
	//	void (*renderStroke)(void* uptr, paint* paint, compositeOperationState compositeOperation, scissor* scissor, float fringe, float strokeWidth, const path* paths, int npaths);
	//	void (*renderTriangles)(void* uptr, paint* paint, compositeOperationState compositeOperation, scissor* scissor, const vertex* verts, int nverts, float fringe);
	//	void (*renderDelete)(void* uptr);
	//};
	//typedef struct params params;

	//// Constructor and destructor, called by the render back-end.
	//CLASS_DECL_NANO2D context* CreateInternal(params* params);
	//CLASS_DECL_NANO2D void DeleteInternal(context* pcontext);


	//struct state {
	//	compositeOperationState compositeOperation;
	//	int shapeAntiAlias;
	//	paint fill;
	//	paint stroke;
	//	float strokeWidth;
	//	float miterLimit;
	//	int lineJoin;
	//	int lineCap;
	//	float alpha;
	//	float xform[6];
	//	scissor scissor;
	//	float fontSize;
	//	float letterSpacing;
	//	float lineHeight;
	//	float fontBlur;
	//	int textAlign;
	//	int fontId;
	//};


	//typedef struct state state;

	//struct point {
	//	float x, y;
	//	float greekdeltax, greekdeltay;
	//	float len;
	//	float dmx, dmy;
	//	unsigned char flags;
	//};
	//typedef struct point point;


	//struct pathCache {
	//	point* points;
	//	int npoints;
	//	int cpoints;
	//	path* paths;
	//	int npaths;
	//	int cpaths;
	//	vertex* verts;
	//	int nverts;
	//	int cverts;
	//	float bounds[4];
	//};
	//typedef struct pathCache pathCache;
	constexpr int CONTEXT_MAX_STATES = 32;
	constexpr int CONTEXT_MAX_FONT_IMAGES = 4;

	//	struct CONTEXT
	//	{
	//
	//		params params;
	//		float* commands;
	//		int ccommands;
	//		int ncommands;
	//		float commandx, commandy;
	//		state states[_MAX_STATES];
	//		int nstates;
	//		pathCache* cache;
	//		float tessTol;
	//		float distTol;
	//		float fringeWidth;
	//		float devicePxRatio;
	//		struct FONScontext* fs;
	//		int fontImages[_MAX_FONTIMAGES];
	//		int fontImageIdx;
	//		int drawCallCount;
	//		int fillTriCount;
	//		int strokeTriCount;
	//		int textTriCount;
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
	//
	//
	//
	//
	//		// Begin drawing a new frame
	//// Calls to nanovg drawing API should be wrapped in BeginFrame() & EndFrame()
	//// BeginFrame() defines the size of the window to render to in relation currently
	//// set viewport (i.e. glContext on GL backends). Device pixel ration allows to
	//// control the rendering on Hi-DPI devices.
	//// For example, GLFW returns two dimension for an opened window: window size and
	//// frame buffer size. In that case you would set windowWidth/Height to the window size
	//// devicePixelRatio to: frameBufferWidth / windowWidth.
	//		void begin_frame(float windowWidth, float windowHeight, float devicePixelRatio);
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
	//		void global_composite_operation(int op);
	//
	//		// Sets the composite operation with custom pixel arithmetic. The parameters should be one of blendFactor.
	//		void global_composite_blend_func(int sfactor, int dfactor);
	//
	//		// Sets the composite operation with custom pixel arithmetic for RGB and alpha components separately. The parameters should be one of blendFactor.
	//		void global_composite_blend_func_separate(int srcRGB, int dstRGB, int srcAlpha, int dstAlpha);
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
	//		void shape_anti_alias(int enabled);
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
	//		virtual void miter_limit(float limit);
	//
	//		// Sets the stroke width of the stroke style.
	//		virtual void stroke_width(float size);
	//
	//		// Sets how the end of the line (cap) is drawn,
	//		// Can be one of: _BUTT (default), _ROUND, _SQUARE.
	//		virtual void line_cap(int cap);
	//
	//		// Sets how sharp path corners are drawn.
	//		// Can be one of _MITER (default), _ROUND, _BEVEL.
	//		virtual void line_join(int join);
	//
	//		// Sets the transparency applied to all rendered shapes.
	//		// Already transparent paths will get proportionally more transparent as well.
	//		virtual void global_alpha(float alpha);
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
	//		void transform(float a, float b, float c, float d, float e, float f);
	//
	//		// Translates current coordinate system.
	//		//void Translate(float x, float y);
	//		virtual void translate(float x, float y);
	//
	//		// Rotates current coordinate system. Angle is specified in radians.
	//		void rotate(float angle);
	//
	//		// Skews the current coordinate system along X axis. Angle is specified in radians.
	//		void skew_x(float angle);
	//
	//		// Skews the current coordinate system along Y axis. Angle is specified in radians.
	//		void skew_y(float angle);
	//
	//		// Scales the current coordinate system.
	//		void scale(float x, float y);
	//
	//		// Stores the top part (a-f) of the current transformation matrix in to the specified buffer.
	//		//   [a c e]
	//		//   [b d f]
	//		//   [0 0 1]
	//		// There should be space for 6 floats in the return buffer for the values a-f.
	//		void current_transform(float* xform);
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
	//		int create_image(const ::scoped_string& scopedstrFilename, int imageFlags);
	//
	//		// Creates image by loading it from the specified chunk of memory.
	//		// Returns handle to the image.
	//		int create_image_mem(int imageFlags, unsigned char* data, int ndata);
	//
	//		// Creates image from specified image data.
	//		// Returns handle to the image.
	//		int create_image_rgba(int w, int h, int imageFlags, const void* data, int iScan);
	//
	//		// Updates image data specified by image handle.
	//		void update_image(int image, const void* data);
	//
	//		// Returns the dimensions of a created image.
	//		void image_size(int image, int* w, int* h);
	//
	//		// Deletes created image.
	//		void delete_image(int image);
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
	//		  paint linear_gradient(float sx, float sy, float ex, float ey,
	//			  color icol,   color ocol);
	//
	//		// Creates and returns a box gradient. Box gradient is a feathered rounded rectangle, it is useful for rendering
	//		// drop shadows or highlights for boxes. Parameters (x,y) define the top-left corner of the rectangle,
	//		// (w,h) define the size of the rectangle, r defines the corner radius, and f feather. Feather defines how blurry
	//		// the border of the rectangle is. Parameter icol specifies the inner color and ocol the outer color of the gradient.
	//		// The gradient is transformed by the current transform when it is passed to FillPaint() or StrokePaint().
	//		  paint box_gradient(float x, float y, float w, float h,
	//			float r, float f,   color icol,   color ocol);
	//
	//		// Creates and returns a radial gradient. Parameters (cx,cy) specify the center, inr and outr specify
	//		// the inner and outer radius of the gradient, icol specifies the start color and ocol the end color.
	//		// The gradient is transformed by the current transform when it is passed to FillPaint() or StrokePaint().
	//		  paint radial_gradient(float cx, float cy, float inr, float outr,
	//			  color icol,   color ocol);
	//
	//		// Creates and returns an image pattern. Parameters (ox,oy) specify the left-top location of the image pattern,
	//		// (ex,ey) the size of one image, angle rotation around the top-left corner, image is handle to the image to render.
	//		// The gradient is transformed by the current transform when it is passed to FillPaint() or StrokePaint().
	//		  paint image_pattern(float ox, float oy, float ex, float ey,
	//			float angle, int image, float alpha);
	//
	//		//
	//		// Scissoring
	//		//
	//		// Scissoring allows you to clip the rendering into a rectangle. This is useful for various
	//		// user interface cases like rendering a text edit or a timeline.
	//
	//		// Sets the current scissor rectangle.
	//		// The scissor rectangle is transformed by the current transform.
	//		void scissor(float x, float y, float w, float h);
	//
	//		// Intersects current scissor rectangle with the specified rectangle.
	//		// The scissor rectangle is transformed by the current transform.
	//		// Note: in case the rotation of previous scissor rect differs from
	//		// the current one, the intersection will be done between the specified
	//		// rectangle and the previous scissor rectangle transformed in the current
	//		// transform space. The resulting shape is always rectangle.
	//		void intersect_scissor(float x, float y, float w, float h);
	//
	//		// Reset and disables scissoring.
	//		void reset_scissor();
	//
	//		//
	//		// Paths
	//		//
	//		// Drawing a new shape starts with BeginPath(), it clears all the currently defined paths.
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
	//		// Starts new sub-path with specified point as first point.
	//		void move_to(float x, float y);
	//
	//		// Adds line segment from the last point in the path to the specified point.
	//		void line_to(float x, float y);
	//
	//		// Adds cubic bezier segment from last point in the path via two control points to the specified point.
	//		void bezier_to(float c1x, float c1y, float c2x, float c2y, float x, float y);
	//
	//		// Adds quadratic bezier segment from last point in the path via a control point to the specified point.
	//		void quad_to(float cx, float cy, float x, float y);
	//
	//		// Adds an arc segment at the corner defined by the last path point, and two specified points.
	//		void arc_to(float x1, float y1, float x2, float y2, float radius);
	//
	//		// Closes current sub-path with a line segment.
	//		void close_path();
	//
	//		// Sets the current sub-path winding, see winding and solidity.
	//		void path_winding(int dir);
	//
	//		// Creates new circle arc shaped sub-path. The arc center is at cx,cy, the arc radius is r,
	//		// and the arc is drawn from angle a0 to a1, and swept in direction dir (_CCW, or _CW).
	//		// Angles are specified in radians.
	//		void arc(float cx, float cy, float r, float a0, float a1, int dir);
	//
	//		// Creates new rectangle shaped sub-path.
	//		void rectangle(float x, float y, float w, float h);
	//
	//		// Creates new rounded rectangle shaped sub-path.
	//		void rounded_rectangle(float x, float y, float w, float h, float r);
	//
	//		// Creates new rounded rectangle shaped sub-path with varying radii for each corner.
	//		void rounded_rectangle_varying(float x, float y, float w, float h, float radTopLeft, float radTopRight, float radBottomRight, float radBottomLeft);
	//
	//		// Creates new ellipse shaped sub-path.
	//		void ellipse(float cx, float cy, float rx, float ry);
	//
	//		// Creates new circle shaped sub-path.
	//		void circle(float cx, float cy, float r);
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
	//		//		const char* txt = "Text me up.";
	//		//		TextBounds(vg, x,y, txt, NULL, bounds);
	//		//		BeginPath(vg);
	//		//		RoundedRect(vg, bounds[0],bounds[1], bounds[2]-bounds[0], bounds[3]-bounds[1]);
	//		//		Fill(vg);
	//		//
	//		// Note: currently only solid color fill is supported for text.
	//
	//		// Creates font by loading it from the disk from specified file name.
	//		// Returns handle to the font.
	//		//int CreateFont(  CONTEXT * pcontext, const ::scoped_string & name, const ::scoped_string & filename);
	//
	//		// fontIndex specifies which font face to load from a .ttf/.ttc file.
	//		int create_font_at_index(const ::scoped_string& name, const ::scoped_string& filename, const int fontIndex);
	//
	//		// Creates font by loading it from the specified memory chunk.
	//		// Returns handle to the font.
	//		int create_font_mem(const ::scoped_string& name, unsigned char* data, int ndata, int freeData);
	//
	//		// fontIndex specifies which font face to load from a .ttf/.ttc file.
	//		int create_font_mem_at_index(const ::scoped_string& name, unsigned char* data, int ndata, int freeData, const int fontIndex);
	//
	//		// Finds a loaded font of specified name, and returns handle to it, or -1 if the font is not found.
	//		int find_font(const ::scoped_string& name);
	//
	//		// Adds a fallback font by handle.
	//		int add_fallback_font_id(int baseFont, int fallbackFont);
	//
	//		// Adds a fallback font by name.
	//		int add_fallback_font(const ::scoped_string& baseFont, const ::scoped_string& fallbackFont);
	//
	//		// Resets fallback fonts by handle.
	//		void reset_fallback_fonts_id(int baseFont);
	//
	//		// Resets fallback fonts by name.
	//		void reset_fallback_fonts(const ::scoped_string& baseFont);
	//
	//		// Sets the font size of current text style.
	//		void font_size(float size);
	//
	//		// Sets the blur of current text style.
	//		void font_blur(float blur);
	//
	//		// Sets the letter spacing of current text style.
	//		void text_letter_spacing(float spacing);
	//
	//		// Sets the proportional line height of current text style. The line height is specified as multiple of font size.
	//		void text_line_height(float lineHeight);
	//
	//		// Sets the text align of current text style, see align for options.
	//		void text_align(int align);
	//
	//		// Sets the font face based on specified id of current text style.
	//		void font_face_id(int font);
	//
	//		// Sets the font face based on specified name of current text style.
	//		void font_face(const ::scoped_string& font);
	//
	//		// Draws text string at specified location. If end is specified only the sub-string up to the end is drawn.
	//		float text(float x, float y, const ::scoped_string& string, const ::scoped_string& end);
	//
	//		// Draws multi-line text string at specified location wrapped at the specified width. If end is specified only the sub-string up to the end is drawn.
	//		// White space is stripped at the beginning of the rows, the text is split at word boundaries or when new-line characters are encountered.
	//		// Words longer than the max width are slit at nearest character (i.e. no hyphenation).
	//		void text_box(float x, float y, float breakRowWidth, const ::scoped_string& string, const ::scoped_string& end);
	//
	//		// Measures the specified text string. Parameter bounds should be a pointer to float[4],
	//		// if the bounding box of the text should be returned. The bounds value are [xmin,ymin, xmax,ymax]
	//		// Returns the horizontal advance of the measured text (i.e. where the next character should drawn).
	//		// Measured values are returned in local coordinate space.
	//		float text_bounds(float x, float y, const ::scoped_string& string, const ::scoped_string& end, float* bounds);
	//
	//		// Measures the specified multi-text string. Parameter bounds should be a pointer to float[4],
	//		// if the bounding box of the text should be returned. The bounds value are [xmin,ymin, xmax,ymax]
	//		// Measured values are returned in local coordinate space.
	//		void text_box_bounds(float x, float y, float breakRowWidth, const ::scoped_string& string, const ::scoped_string& end, float* bounds);
	//
	//		// Calculates the glyph x positions of the specified text. If end is specified only the sub-string will be used.
	//		// Measured values are returned in local coordinate space.
	//		int text_glyph_positions(float x, float y, const ::scoped_string& string, const ::scoped_string& end, glyphPosition* positions, int maxPositions);
	//
	//		// Returns the vertical metrics based on the current text style.
	//		// Measured values are returned in local coordinate space.
	//		void text_metrics(float* ascender, float* descender, float* lineh);
	//
	//		// Breaks the specified text into lines. If end is specified only the sub-string will be used.
	//		// White space is stripped at the beginning of the rows, the text is split at word boundaries or when new-line characters are encountered.
	//		// Words longer than the max width are slit at nearest character (i.e. no hyphenation).
	//		int text_break_lines(const ::scoped_string& string, const ::scoped_string& end, float breakRowWidth, text_row* rows, int maxRows);
	//
	//		void __append_commands(float* vals, int nvals);
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



//namespace nanoui
//{
//
//
///// The different kinds of alignments a layout can perform.
//   enum class Alignment : uint8_t
//   {
//      Minimum = 0, ///< Take only as much space as is required.
//      Middle,      ///< Center align.
//      Maximum,     ///< Take as much space as is allowed.
//      Fill         ///< Fill according to preferred sizes.
//   };
//
///// The direction of data flow for a layout.
//   enum class Orientation
//   {
//      Horizontal = 0, ///< Layout expands on horizontal axis.
//      Vertical        ///< Layout expands on vertical axis.
//   };
//
//
//} // namespace nanoui
//
//
//
