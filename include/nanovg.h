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

#ifndef NANOVG_H
#define NANOVG_H


#ifdef __cplusplus
extern "C" {
#endif

#define NVG_PI 3.14159265358979323846264338327f

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4201)  // nonstandard extension used : nameless struct/union
#endif

	typedef struct NVGcontext NVGcontext;




#define NVG_INIT_FONTIMAGE_SIZE  512
#define NVG_MAX_FONTIMAGE_SIZE   2048

#define NVG_INIT_COMMANDS_SIZE 256
#define NVG_INIT_POINTS_SIZE 128
#define NVG_INIT_PATHS_SIZE 16
#define NVG_INIT_VERTS_SIZE 256


#define NVG_KAPPA90 0.5522847493f	// Length proportional to radius of a cubic bezier handle for 90deg arcs.

#define NVG_COUNTOF(arr) (sizeof(arr) / sizeof(0[arr]))

	enum NVGcommands {
		NVG_MOVETO = 0,
		NVG_LINETO = 1,
		NVG_BEZIERTO = 2,
		NVG_CLOSE = 3,
		NVG_WINDING = 4,
	};

	enum NVGpointFlags
	{
		NVG_PT_CORNER = 0x01,
		NVG_PT_LEFT = 0x02,
		NVG_PT_BEVEL = 0x04,
		NVG_PR_INNERBEVEL = 0x08,
	};


	struct NVGcolor {
		union {
			float rgba[4];
			struct {
				float r, g, b, a;
			};
		};
	};
	typedef struct NVGcolor NVGcolor;

	struct NVGpaint {
		float xform[6];
		float extent[2];
		float radius;
		float feather;
		NVGcolor innerColor;
		NVGcolor outerColor;
		int image;
	};
	typedef struct NVGpaint NVGpaint;

	enum NVGwinding {
		NVG_CCW = 1,			// Winding for solid shapes
		NVG_CW = 2,				// Winding for holes
	};

	enum NVGsolidity {
		NVG_SOLID = 1,			// CCW
		NVG_HOLE = 2,			// CW
	};

	enum NVGlineCap {
		NVG_BUTT,
		NVG_ROUND,
		NVG_SQUARE,
		NVG_BEVEL,
		NVG_MITER,
	};

	enum NVGalign {
		// Horizontal align
		NVG_ALIGN_LEFT = 1 << 0,	// Default, align text horizontally to left.
		NVG_ALIGN_CENTER = 1 << 1,	// Align text horizontally to center.
		NVG_ALIGN_RIGHT = 1 << 2,	// Align text horizontally to right.
		// Vertical align
		NVG_ALIGN_TOP = 1 << 3,	// Align text vertically to top.
		NVG_ALIGN_MIDDLE = 1 << 4,	// Align text vertically to middle.
		NVG_ALIGN_BOTTOM = 1 << 5,	// Align text vertically to bottom.
		NVG_ALIGN_BASELINE = 1 << 6, // Default, align text vertically to baseline.
	};

	enum NVGblendFactor {
		NVG_ZERO = 1 << 0,
		NVG_ONE = 1 << 1,
		NVG_SRC_COLOR = 1 << 2,
		NVG_ONE_MINUS_SRC_COLOR = 1 << 3,
		NVG_DST_COLOR = 1 << 4,
		NVG_ONE_MINUS_DST_COLOR = 1 << 5,
		NVG_SRC_ALPHA = 1 << 6,
		NVG_ONE_MINUS_SRC_ALPHA = 1 << 7,
		NVG_DST_ALPHA = 1 << 8,
		NVG_ONE_MINUS_DST_ALPHA = 1 << 9,
		NVG_SRC_ALPHA_SATURATE = 1 << 10,
	};

	enum NVGcompositeOperation {
		NVG_SOURCE_OVER,
		NVG_SOURCE_IN,
		NVG_SOURCE_OUT,
		NVG_ATOP,
		NVG_DESTINATION_OVER,
		NVG_DESTINATION_IN,
		NVG_DESTINATION_OUT,
		NVG_DESTINATION_ATOP,
		NVG_LIGHTER,
		NVG_COPY,
		NVG_XOR,
	};

	struct NVGcompositeOperationState {
		int srcRGB;
		int dstRGB;
		int srcAlpha;
		int dstAlpha;
	};
	typedef struct NVGcompositeOperationState NVGcompositeOperationState;

	struct NVGglyphPosition {
		const char * str;	// Position of the glyph in the input string.
		float x;			// The x-coordinate of the logical glyph position.
		float minx, maxx;	// The bounds of the glyph shape.
	};
	typedef struct NVGglyphPosition NVGglyphPosition;

	struct NVGtextRow {
		const char * start;	// Pointer to the input text where the row starts.
		const char * end;	// Pointer to the input text where the row ends (one past the last character).
		const char * next;	// Pointer to the beginning of the next row.
		float width;		// Logical width of the row.
		float minx, maxx;	// Actual bounds of the row. Logical with and bounds can differ because of kerning and some parts over extending.
	};
	typedef struct NVGtextRow NVGtextRow;

	enum NVGimageFlags {
		NVG_IMAGE_GENERATE_MIPMAPS = 1 << 0,     // Generate mipmaps during creation of the image.
		NVG_IMAGE_REPEATX = 1 << 1,		// Repeat image in X direction.
		NVG_IMAGE_REPEATY = 1 << 2,		// Repeat image in Y direction.
		NVG_IMAGE_FLIPY = 1 << 3,		// Flips (inverses) image in Y direction when rendered.
		NVG_IMAGE_PREMULTIPLIED = 1 << 4,		// Image data has premultiplied alpha.
		NVG_IMAGE_NEAREST = 1 << 5,		// Image interpolation is Nearest instead Linear
	};

	// Begin drawing a memory_new frame
	// Calls to nanovg drawing API should be wrapped in __NANO2D_API(BeginFrame)() & __NANO2D_API(EndFrame)()
	// __NANO2D_API(BeginFrame)() defines the size of the window to render to in relation currently
	// set viewport (i.e. glContext on GL backends). Device pixel ration allows to
	// control the rendering on Hi-DPI devices.
	// For example, GLFW returns two dimension for an opened window: window size and
	// frame buffer size. In that case you would set windowWidth/Height to the window size
	// devicePixelRatio to: frameBufferWidth / windowWidth.
NANO2D_EXPORT void __NANO2D_API(BeginFrame)(NVGcontext * ctx, float windowWidth, float windowHeight, float devicePixelRatio);

	// Cancels drawing the current frame.
NANO2D_EXPORT void __NANO2D_API(CancelFrame)(NVGcontext * ctx);

	// Ends drawing flushing remaining render state.
NANO2D_EXPORT void __NANO2D_API(EndFrame)(NVGcontext * ctx);

	//
	// Composite operation
	//
	// The composite operations in NanoVG are modeled after HTML Canvas API, and
	// the blend func is based on OpenGL (see corresponding manuals for more info).
	// The colors in the blending state have premultiplied alpha.

	// Sets the composite operation. The op parameter should be one of NVGcompositeOperation.
NANO2D_EXPORT void __NANO2D_API(GlobalCompositeOperation)(NVGcontext * ctx, int op);

	// Sets the composite operation with custom pixel arithmetic. The parameters should be one of NVGblendFactor.
NANO2D_EXPORT void __NANO2D_API(GlobalCompositeBlendFunc)(NVGcontext * ctx, int sfactor, int dfactor);

	// Sets the composite operation with custom pixel arithmetic for RGB and alpha components separately. The parameters should be one of NVGblendFactor.
NANO2D_EXPORT void __NANO2D_API(GlobalCompositeBlendFuncSeparate)(NVGcontext * ctx, int srcRGB, int dstRGB, int srcAlpha, int dstAlpha);

	//
	// Color utils
	//
	// Colors in NanoVG are stored as unsigned ints in ABGR format.

	// Returns a color value from red, green, blue values. Alpha will be set to 255 (1.0f).
NANO2D_EXPORT	NVGcolor __NANO2D_API(RGB)(unsigned char r, unsigned char g, unsigned char b);

	// Returns a color value from red, green, blue values. Alpha will be set to 1.0f.
NANO2D_EXPORT	NVGcolor __NANO2D_API(RGBf)(float r, float g, float b);


	// Returns a color value from red, green, blue and alpha values.
NANO2D_EXPORT	NVGcolor __NANO2D_API(RGBA)(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	// Returns a color value from red, green, blue and alpha values.
NANO2D_EXPORT	NVGcolor __NANO2D_API(RGBAf)(float r, float g, float b, float a);


	// Linearly interpolates from color c0 to c1, and returns resulting color value.
NANO2D_EXPORT	NVGcolor __NANO2D_API(LerpRGBA)(NVGcolor c0, NVGcolor c1, float u);

	// Sets transparency of a color value.
NANO2D_EXPORT	NVGcolor __NANO2D_API(TransRGBA)(NVGcolor c0, unsigned char a);

	// Sets transparency of a color value.
NANO2D_EXPORT	NVGcolor __NANO2D_API(TransRGBAf)(NVGcolor c0, float a);

	// Returns color value specified by hue, saturation and lightness.
	// HSL values are all in range [0..1], alpha will be set to 255.
NANO2D_EXPORT	NVGcolor __NANO2D_API(HSL)(float h, float s, float l);

	// Returns color value specified by hue, saturation and lightness and alpha.
	// HSL values are all in range [0..1], alpha in range [0..255]
NANO2D_EXPORT	NVGcolor __NANO2D_API(HSLA)(float h, float s, float l, unsigned char a);

	//
	// State Handling
	//
	// NanoVG contains state which represents how paths will be rendered.
	// The state contains transform, fill and stroke styles, text and font styles,
	// and scissor clipping.

	// Pushes and saves the current render state into a state stack.
	// A matching __NANO2D_API(Restore)() must be used to restore the state.
NANO2D_EXPORT void __NANO2D_API(Save)(NVGcontext * ctx);

	// Pops and restores current render state.
NANO2D_EXPORT void __NANO2D_API(Restore)(NVGcontext * ctx);

	// Resets current render state to default values. Does not affect the render state stack.
NANO2D_EXPORT void __NANO2D_API(Reset)(NVGcontext * ctx);

	//
	// Render styles
	//
	// Fill and stroke render style can be either a solid color or a paint which is a gradient or a pattern.
	// Solid color is simply defined as a color value, different kinds of paints can be created
	// using __NANO2D_API(LinearGradient)(), __NANO2D_API(BoxGradient)(), __NANO2D_API(RadialGradient)() and __NANO2D_API(ImagePattern)().
	//
	// Current render style can be saved and restored using __NANO2D_API(Save)() and __NANO2D_API(Restore)().

	// Sets whether to draw antialias for __NANO2D_API(Stroke)() and __NANO2D_API(Fill)(). It's enabled by default.
NANO2D_EXPORT void __NANO2D_API(ShapeAntiAlias)(NVGcontext * ctx, int enabled);

	// Sets current stroke style to a solid color.
NANO2D_EXPORT void __NANO2D_API(StrokeColor)(NVGcontext * ctx, NVGcolor color);

	// Sets current stroke style to a paint, which can be a one of the gradients or a pattern.
NANO2D_EXPORT void __NANO2D_API(StrokePaint)(NVGcontext * ctx, NVGpaint paint);

	// Sets current fill style to a solid color.
NANO2D_EXPORT void __NANO2D_API(FillColor)(NVGcontext * ctx, NVGcolor color);

	// Sets current fill style to a paint, which can be a one of the gradients or a pattern.
NANO2D_EXPORT void __NANO2D_API(FillPaint)(NVGcontext * ctx, NVGpaint paint);

	// Sets the miter limit of the stroke style.
	// Miter limit controls when a sharp corner is beveled.
NANO2D_EXPORT void __NANO2D_API(MiterLimit)(NVGcontext * ctx, float limit);

	// Sets the stroke width of the stroke style.
NANO2D_EXPORT void __NANO2D_API(StrokeWidth)(NVGcontext * ctx, float size);

	// Sets how the end of the line (cap) is drawn,
	// Can be one of: NVG_BUTT (default), NVG_ROUND, NVG_SQUARE.
NANO2D_EXPORT void __NANO2D_API(LineCap)(NVGcontext * ctx, int cap);

	// Sets how sharp path corners are drawn.
	// Can be one of NVG_MITER (default), NVG_ROUND, NVG_BEVEL.
NANO2D_EXPORT void __NANO2D_API(LineJoin)(NVGcontext * ctx, int join);

	// Sets the transparency applied to all rendered shapes.
	// Already transparent paths will get proportionally more transparent as well.
NANO2D_EXPORT void __NANO2D_API(GlobalAlpha)(NVGcontext * ctx, float alpha);

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
	// Apart from __NANO2D_API(ResetTransform)(), each transformation function first creates
	// specific transformation matrix and pre-multiplies the current transformation by it.
	//
	// Current coordinate system (transformation) can be saved and restored using __NANO2D_API(Save)() and __NANO2D_API(Restore)().

	// Resets current transform to a identity matrix.
NANO2D_EXPORT void __NANO2D_API(ResetTransform)(NVGcontext * ctx);

	// Premultiplies current coordinate system by specified matrix.
	// The parameters are interpreted as matrix as follows:
	//   [a c e]
	//   [b d f]
	//   [0 0 1]
NANO2D_EXPORT void __NANO2D_API(Transform)(NVGcontext * ctx, float a, float b, float c, float d, float e, float f);

	// Translates current coordinate system.
NANO2D_EXPORT void __NANO2D_API(Translate)(NVGcontext * ctx, float x, float y);

	// Rotates current coordinate system. Angle is specified in radians.
NANO2D_EXPORT void __NANO2D_API(Rotate)(NVGcontext * ctx, float angle);

	// Skews the current coordinate system along X axis. Angle is specified in radians.
NANO2D_EXPORT void __NANO2D_API(SkewX)(NVGcontext * ctx, float angle);

	// Skews the current coordinate system along Y axis. Angle is specified in radians.
NANO2D_EXPORT void __NANO2D_API(SkewY)(NVGcontext * ctx, float angle);

	// Scales the current coordinate system.
NANO2D_EXPORT void __NANO2D_API(Scale)(NVGcontext * ctx, float x, float y);

	// Stores the top part (a-f) of the current transformation matrix in to the specified buffer.
	//   [a c e]
	//   [b d f]
	//   [0 0 1]
	// There should be space for 6 floats in the return buffer for the values a-f.
NANO2D_EXPORT void __NANO2D_API(CurrentTransform)(NVGcontext * ctx, float * xform);


	// The following functions can be used to make calculations on 2x3 transformation matrices.
	// A 2x3 matrix is represented as float[6].

	// Sets the transform to identity matrix.
NANO2D_EXPORT void __NANO2D_API(TransformIdentity)(float * dst);

	// Sets the transform to translation matrix matrix.
NANO2D_EXPORT void __NANO2D_API(TransformTranslate)(float * dst, float tx, float ty);

	// Sets the transform to scale matrix.
NANO2D_EXPORT void __NANO2D_API(TransformScale)(float * dst, float sx, float sy);

	// Sets the transform to rotate matrix. Angle is specified in radians.
NANO2D_EXPORT void __NANO2D_API(TransformRotate)(float * dst, float a);

	// Sets the transform to skew-x matrix. Angle is specified in radians.
NANO2D_EXPORT void __NANO2D_API(TransformSkewX)(float * dst, float a);

	// Sets the transform to skew-y matrix. Angle is specified in radians.
NANO2D_EXPORT void __NANO2D_API(TransformSkewY)(float * dst, float a);

	// Sets the transform to the result of multiplication of two transforms, of A = A*B.
NANO2D_EXPORT void __NANO2D_API(TransformMultiply)(float * dst, const float * src);

	// Sets the transform to the result of multiplication of two transforms, of A = B*A.
NANO2D_EXPORT void __NANO2D_API(TransformPremultiply)(float * dst, const float * src);

	// Sets the destination to inverse of specified transform.
	// Returns 1 if the inverse could be calculated, else 0.
NANO2D_EXPORT int __NANO2D_API(TransformInverse)(float * dst, const float * src);

	// Transform a point by given transform.
NANO2D_EXPORT void __NANO2D_API(TransformPoint)(float * dstx, float * dsty, const float * xform, float srcx, float srcy);

	// Converts degrees to radians and vice versa.
NANO2D_EXPORT	float __NANO2D_API(DegToRad)(float deg);
NANO2D_EXPORT	float __NANO2D_API(RadToDeg)(float rad);

	//
	// Images
	//
	// NanoVG allows you to load jpg, png, psd, tga, pic and gif files to be used for rendering.
	// In addition you can upload your own image. The image loading is provided by stb_image.
	// The parameter imageFlags is combination of flags defined in NVGimageFlags.

	// Creates image by loading it from the disk from specified file name.
	// Returns handle to the image.
NANO2D_EXPORT int __NANO2D_API(CreateImage)(NVGcontext * ctx, const char * filename, int imageFlags);

	// Creates image by loading it from the specified chunk of memory.
	// Returns handle to the image.
NANO2D_EXPORT int __NANO2D_API(CreateImageMem)(NVGcontext * ctx, int imageFlags, unsigned char * data, int ndata);

	// Creates image from specified image data.
	// Returns handle to the image.
	NANO2D_EXPORT int __NANO2D_API(CreateImageRGBA)(NVGcontext * ctx, int w, int h, int imageFlags, const void * data, int iScan);

	// Updates image data specified by image handle.
	NANO2D_EXPORT void __NANO2D_API(UpdateImage)(NVGcontext * ctx, int image, const void* data);

	// Returns the dimensions of a created image.
	NANO2D_EXPORT void __NANO2D_API(ImageSize)(NVGcontext * ctx, int image, int * w, int * h);

	// Deletes created image.
	NANO2D_EXPORT void __NANO2D_API(DeleteImage)(NVGcontext * ctx, int image);

	//
	// Paints
	//
	// NanoVG supports four types of paints: linear gradient, box gradient, radial gradient and image pattern.
	// These can be used as paints for strokes and fills.

	// Creates and returns a linear gradient. Parameters (sx,sy)-(ex,ey) specify the start and end coordinates
	// of the linear gradient, icol specifies the start color and ocol the end color.
	// The gradient is transformed by the current transform when it is passed to __NANO2D_API(FillPaint)() or __NANO2D_API(StrokePaint)().
	NANO2D_EXPORT NANO2D_PAINT __NANO2D_API(LinearGradient)(NVGcontext * ctx, float sx, float sy, float ex, float ey,
		NVGcolor icol, NVGcolor ocol);

	// Creates and returns a box gradient. Box gradient is a feathered rounded rectangle, it is useful for rendering
	// drop shadows or highlights for boxes. Parameters (x,y) define the top-left corner of the rectangle,
	// (w,h) define the size of the rectangle, r defines the corner radius, and f feather. Feather defines how blurry
	// the border of the rectangle is. Parameter icol specifies the inner color and ocol the outer color of the gradient.
	// The gradient is transformed by the current transform when it is passed to __NANO2D_API(FillPaint)() or __NANO2D_API(StrokePaint)().
	NANO2D_EXPORT NANO2D_PAINT __NANO2D_API(BoxGradient)(NVGcontext * ctx, float x, float y, float w, float h,
		float r, float f, NVGcolor icol, NVGcolor ocol);

	// Creates and returns a radial gradient. Parameters (cx,cy) specify the center, inr and outr specify
	// the inner and outer radius of the gradient, icol specifies the start color and ocol the end color.
	// The gradient is transformed by the current transform when it is passed to __NANO2D_API(FillPaint)() or __NANO2D_API(StrokePaint)().
	NANO2D_EXPORT NANO2D_PAINT __NANO2D_API(RadialGradient)(NVGcontext * ctx, float cx, float cy, float inr, float outr,
		NVGcolor icol, NVGcolor ocol);

	// Creates and returns an image pattern. Parameters (ox,oy) specify the left-top location of the image pattern,
	// (ex,ey) the size of one image, angle rotation around the top-left corner, image is handle to the image to render.
	// The gradient is transformed by the current transform when it is passed to __NANO2D_API(FillPaint)() or __NANO2D_API(StrokePaint)().
	NANO2D_EXPORT NANO2D_PAINT __NANO2D_API(ImagePattern)(NVGcontext * ctx, float ox, float oy, float ex, float ey,
		float angle, int image, float alpha);

	//
	// Scissoring
	//
	// Scissoring allows you to clip the rendering into a rectangle. This is useful for various
	// user interface cases like rendering a text edit or a timeline.

	// Sets the current scissor rectangle.
	// The scissor rectangle is transformed by the current transform.
	NANO2D_EXPORT void __NANO2D_API(Scissor)(NVGcontext * ctx, float x, float y, float w, float h);

	// Intersects current scissor rectangle with the specified rectangle.
	// The scissor rectangle is transformed by the current transform.
	// Note: in case the rotation of previous scissor rect differs from
	// the current one, the intersection will be done between the specified
	// rectangle and the previous scissor rectangle transformed in the current
	// transform space. The resulting shape is always rectangle.
	NANO2D_EXPORT void __NANO2D_API(IntersectScissor)(NVGcontext * ctx, float x, float y, float w, float h);

	// Reset and disables scissoring.
	NANO2D_EXPORT void __NANO2D_API(ResetScissor)(NVGcontext * ctx);

	//
	// Paths
	//
	// Drawing a memory_new shape starts with __NANO2D_API(BeginPath)(), it clears all the currently defined paths.
	// Then you define one or more paths and sub-paths which describe the shape. The are functions
	// to draw common shapes like rectangles and circles, and lower level step-by-step functions,
	// which allow to define a path curve by curve.
	//
	// NanoVG uses even-odd fill rule to draw the shapes. Solid shapes should have counter clockwise
	// winding and holes should have counter clockwise order. To specify winding of a path you can
	// call __NANO2D_API(PathWinding)(). This is useful especially for the common shapes, which are drawn CCW.
	//
	// Finally you can fill the path using current fill style by calling __NANO2D_API(Fill)(), and stroke it
	// with current stroke style by calling __NANO2D_API(Stroke)().
	//
	// The curve segments and sub-paths are transformed by the current transform.

	// Clears the current path and sub-paths.
	NANO2D_EXPORT void __NANO2D_API(BeginPath)(NVGcontext * ctx);

	// Starts memory_new sub-path with specified point as first point.
	NANO2D_EXPORT void __NANO2D_API(MoveTo)(NVGcontext * ctx, float x, float y);

	// Adds line segment from the last point in the path to the specified point.
	NANO2D_EXPORT void __NANO2D_API(LineTo)(NVGcontext * ctx, float x, float y);

	// Adds cubic bezier segment from last point in the path via two control points to the specified point.
	NANO2D_EXPORT void __NANO2D_API(BezierTo)(NVGcontext * ctx, float c1x, float c1y, float c2x, float c2y, float x, float y);

	// Adds quadratic bezier segment from last point in the path via a control point to the specified point.
	NANO2D_EXPORT void __NANO2D_API(QuadTo)(NVGcontext * ctx, float cx, float cy, float x, float y);

	// Adds an arc segment at the corner defined by the last path point, and two specified points.
	NANO2D_EXPORT void __NANO2D_API(ArcTo)(NVGcontext * ctx, float x1, float y1, float x2, float y2, float radius);

	// Closes current sub-path with a line segment.
	NANO2D_EXPORT void __NANO2D_API(ClosePath)(NVGcontext * ctx);

	// Sets the current sub-path winding, see NVGwinding and NVGsolidity.
	NANO2D_EXPORT void __NANO2D_API(PathWinding)(NVGcontext * ctx, int dir);

	// Creates memory_new circle arc shaped sub-path. The arc center is at cx,cy, the arc radius is r,
	// and the arc is drawn from angle a0 to a1, and swept in direction dir (NVG_CCW, or NVG_CW).
	// Angles are specified in radians.
	NANO2D_EXPORT void __NANO2D_API(Arc)(NVGcontext * ctx, float cx, float cy, float r, float a0, float a1, int dir);

	// Creates memory_new rectangle shaped sub-path.
	NANO2D_EXPORT void __NANO2D_API(Rect)(NVGcontext * ctx, float x, float y, float w, float h);

	// Creates memory_new rounded rectangle shaped sub-path.
	NANO2D_EXPORT void __NANO2D_API(RoundedRect)(NVGcontext * ctx, float x, float y, float w, float h, float r);

	// Creates memory_new rounded rectangle shaped sub-path with varying radii for each corner.
	NANO2D_EXPORT void __NANO2D_API(RoundedRectVarying)(NVGcontext * ctx, float x, float y, float w, float h, float radTopLeft, float radTopRight, float radBottomRight, float radBottomLeft);

	// Creates memory_new ellipse shaped sub-path.
	NANO2D_EXPORT void __NANO2D_API(Ellipse)(NVGcontext * ctx, float cx, float cy, float rx, float ry);

	// Creates memory_new circle shaped sub-path.
	NANO2D_EXPORT void __NANO2D_API(Circle)(NVGcontext * ctx, float cx, float cy, float r);

	// Fills the current path with current fill style.
	NANO2D_EXPORT void __NANO2D_API(Fill)(NVGcontext * ctx);

	// Fills the current path with current stroke style.
	NANO2D_EXPORT void __NANO2D_API(Stroke)(NVGcontext * ctx);


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
	//		__NANO2D_API(TextBounds)(vg, x,y, txt, NULL, bounds);
	//		__NANO2D_API(BeginPath)(vg);
	//		__NANO2D_API(RoundedRect)(vg, bounds[0],bounds[1], bounds[2]-bounds[0], bounds[3]-bounds[1]);
	//		__NANO2D_API(Fill)(vg);
	//
	// Note: currently only solid color fill is supported for text.

	// Creates font by loading it from the disk from specified file name.
	// Returns handle to the font.
	//NANO2D_EXPORT int __NANO2D_API(CreateFont)(NVGcontext * ctx, const char * name, const char * filename);

	// fontIndex specifies which font face to load from a .ttf/.ttc file.
	NANO2D_EXPORT int __NANO2D_API(CreateFontAtIndex)(NVGcontext * ctx, const char * name, const char * filename, const int fontIndex);

	// Creates font by loading it from the specified memory chunk.
	// Returns handle to the font.
	NANO2D_EXPORT int __NANO2D_API(CreateFontMem)(NVGcontext * ctx, const char * name, unsigned char * data, int ndata, int freeData);

	// fontIndex specifies which font face to load from a .ttf/.ttc file.
	NANO2D_EXPORT int __NANO2D_API(CreateFontMemAtIndex)(NVGcontext * ctx, const char * name, unsigned char * data, int ndata, int freeData, const int fontIndex);

	// Finds a loaded font of specified name, and returns handle to it, or -1 if the font is not found.
	NANO2D_EXPORT int __NANO2D_API(FindFont)(NVGcontext * ctx, const char * name);

	// Adds a fallback font by handle.
	NANO2D_EXPORT int __NANO2D_API(AddFallbackFontId)(NVGcontext * ctx, int baseFont, int fallbackFont);

	// Adds a fallback font by name.
	NANO2D_EXPORT int __NANO2D_API(AddFallbackFont)(NVGcontext * ctx, const char * baseFont, const char * fallbackFont);

	// Resets fallback fonts by handle.
	NANO2D_EXPORT void __NANO2D_API(ResetFallbackFontsId)(NVGcontext * ctx, int baseFont);

	// Resets fallback fonts by name.
	NANO2D_EXPORT void __NANO2D_API(ResetFallbackFonts)(NVGcontext * ctx, const char * baseFont);

	// Sets the font size of current text style.
	NANO2D_EXPORT void __NANO2D_API(FontSize)(NVGcontext * ctx, float size);

	// Sets the blur of current text style.
	NANO2D_EXPORT void __NANO2D_API(FontBlur)(NVGcontext * ctx, float blur);

	// Sets the letter spacing of current text style.
	NANO2D_EXPORT void __NANO2D_API(TextLetterSpacing)(NVGcontext * ctx, float spacing);

	// Sets the proportional line height of current text style. The line height is specified as multiple of font size.
	NANO2D_EXPORT void __NANO2D_API(TextLineHeight)(NVGcontext * ctx, float lineHeight);

	// Sets the text align of current text style, see NVGalign for options.
	NANO2D_EXPORT void __NANO2D_API(TextAlign)(NVGcontext * ctx, int align);

	// Sets the font face based on specified id of current text style.
	NANO2D_EXPORT void __NANO2D_API(FontFaceId)(NVGcontext * ctx, int font);

	// Sets the font face based on specified name of current text style.
	NANO2D_EXPORT void __NANO2D_API(FontFace)(NVGcontext * ctx, const char * font);

	// Draws text string at specified location. If end is specified only the sub-string up to the end is drawn.
	NANO2D_EXPORT float __NANO2D_API(Text)(NVGcontext * ctx, float x, float y, const char * string, const char * end);

	// Draws multi-line text string at specified location wrapped at the specified width. If end is specified only the sub-string up to the end is drawn.
	// White space is stripped at the beginning of the rows, the text is split at word boundaries or when memory_new-line characters are encountered.
	// Words longer than the max width are slit at nearest character (i.e. no hyphenation).
	NANO2D_EXPORT void __NANO2D_API(TextBox)(NVGcontext * ctx, float x, float y, float breakRowWidth, const char * string, const char * end);

	// Measures the specified text string. Parameter bounds should be a pointer to float[4],
	// if the bounding box of the text should be returned. The bounds value are [xmin,ymin, xmax,ymax]
	// Returns the horizontal advance of the measured text (i.e. where the next character should drawn).
	// Measured values are returned in local coordinate space.
	NANO2D_EXPORT float __NANO2D_API(TextBounds)(NVGcontext * ctx, float x, float y, const char * string, const char * end, float * bounds);

	// Measures the specified multi-text string. Parameter bounds should be a pointer to float[4],
	// if the bounding box of the text should be returned. The bounds value are [xmin,ymin, xmax,ymax]
	// Measured values are returned in local coordinate space.
	NANO2D_EXPORT void __NANO2D_API(TextBoxBounds)(NVGcontext * ctx, float x, float y, float breakRowWidth, const char * string, const char * end, float * bounds);

	// Calculates the glyph x positions of the specified text. If end is specified only the sub-string will be used.
	// Measured values are returned in local coordinate space.
	NANO2D_EXPORT int __NANO2D_API(TextGlyphPositions)(NVGcontext * ctx, float x, float y, const char * string, const char * end, NVGglyphPosition * positions, int maxPositions);

	// Returns the vertical metrics based on the current text style.
	// Measured values are returned in local coordinate space.
	NANO2D_EXPORT void __NANO2D_API(TextMetrics)(NVGcontext * ctx, float * ascender, float * descender, float * lineh);

	// Breaks the specified text into lines. If end is specified only the sub-string will be used.
	// White space is stripped at the beginning of the rows, the text is split at word boundaries or when memory_new-line characters are encountered.
	// Words longer than the max width are slit at nearest character (i.e. no hyphenation).
	NANO2D_EXPORT int __NANO2D_API(TextBreakLines)(NVGcontext * ctx, const char * string, const char * end, float breakRowWidth, NVGtextRow * rows, int maxRows);

	//
	// Internal Render API
	//
	enum NVGtexture {
		NVG_TEXTURE_ALPHA = 0x01,
		NVG_TEXTURE_RGBA = 0x02,
	};

	struct NVGscissor {
		float xform[6];
		float extent[2];
	};
	typedef struct NVGscissor NVGscissor;

	struct NVGvertex {
		float x, y, u, v;
	};
	typedef struct NVGvertex NVGvertex;

	struct NVGpath {
		int first;
		int count;
		unsigned char closed;
		int nbevel;
		NVGvertex * fill;
		int nfill;
		NVGvertex * stroke;
		int nstroke;
		int winding;
		int convex;
	};
	typedef struct NVGpath NVGpath;

	struct NVGparams {
		void * userPtr;
		int edgeAntiAlias;
		int (*renderCreate)(void * uptr);
		int (*renderCreateTexture)(void * uptr, int type, int w, int h, int imageFlags, const unsigned char * data);
		int (*renderDeleteTexture)(void * uptr, int image);
		int (*renderUpdateTexture)(void * uptr, int image, int x, int y, int w, int h, const unsigned char * data);
		int (*renderGetTextureSize)(void * uptr, int image, int * w, int * h);
		void (*renderContext)(void * uptr, float width, float height, float devicePixelRatio);
		void (*renderCancel)(void * uptr);
		void (*renderFlush)(void * uptr);
		void (*renderFill)(void * uptr, NVGpaint * paint, NVGcompositeOperationState compositeOperation, NVGscissor * scissor, float fringe, const float * bounds, const NVGpath * paths, int npaths);
		void (*renderStroke)(void * uptr, NVGpaint * paint, NVGcompositeOperationState compositeOperation, NVGscissor * scissor, float fringe, float strokeWidth, const NVGpath * paths, int npaths);
		void (*renderTriangles)(void * uptr, NVGpaint * paint, NVGcompositeOperationState compositeOperation, NVGscissor * scissor, const NVGvertex * verts, int nverts, float fringe);
		void (*renderDelete)(void * uptr);
	};
	typedef struct NVGparams NVGparams;

	// Constructor and destructor, called by the render back-end.
	NVGcontext * __NANO2D_API(CreateInternal)(NVGparams * params);
	NANO2D_EXPORT void __NANO2D_API(DeleteInternal)(NVGcontext * ctx);

	NVGparams * __NANO2D_API(InternalParams)(NVGcontext * ctx);

	// Debug function to dump cached path data.
	NANO2D_EXPORT void __NANO2D_API(DebugDumpPathCache)(NVGcontext * ctx);


	struct NVGstate {
		NVGcompositeOperationState compositeOperation;
		int shapeAntiAlias;
		NVGpaint fill;
		NVGpaint stroke;
		float strokeWidth;
		float miterLimit;
		int lineJoin;
		int lineCap;
		float alpha;
		float xform[6];
		NVGscissor scissor;
		float fontSize;
		float letterSpacing;
		float lineHeight;
		float fontBlur;
		int textAlign;
		int fontId;
	};


	typedef struct NVGstate NVGstate;

	struct NVGpoint {
		float x, y;
		float Δx, Δy;
		float len;
		float dmx, dmy;
		unsigned char flags;
	};
	typedef struct NVGpoint NVGpoint;


	struct NVGpathCache {
		NVGpoint * points;
		int npoints;
		int cpoints;
		NVGpath * paths;
		int npaths;
		int cpaths;
		NVGvertex * verts;
		int nverts;
		int cverts;
		float bounds[4];
	};
	typedef struct NVGpathCache NVGpathCache;
#define NVG_MAX_STATES 32
#define NVG_MAX_FONTIMAGES       4

	struct NVGcontext
	{

		NVGparams params;
		float * commands;
		int ccommands;
		int ncommands;
		float commandx, commandy;
		NVGstate states[NVG_MAX_STATES];
		int nstates;
		NVGpathCache * cache;
		float tessTol;
		float distTol;
		float fringeWidth;
		float devicePxRatio;
		struct FONScontext * fs;
		int fontImages[NVG_MAX_FONTIMAGES];
		int fontImageIdx;
		int drawCallCount;
		int fillTriCount;
		int strokeTriCount;
		int textTriCount;
		void * p;
	};

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#define NVG_NOTUSED(v) for (;;) { (void)(1 ? (void)0 : ( (void)(v) ) ); break; }

#ifdef __cplusplus
}
#endif


#endif



