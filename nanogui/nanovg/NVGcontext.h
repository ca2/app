#pragma once


#include "nanovg.h"
#include "../vector.h"






#define NVG_INIT_FONTIMAGE_SIZE  512
#define NVG_MAX_FONTIMAGE_SIZE   2048
#define NVG_MAX_FONTIMAGES       4

#define NVG_INIT_COMMANDS_SIZE 256
#define NVG_INIT_POINTS_SIZE 128
#define NVG_INIT_PATHS_SIZE 16
#define NVG_INIT_VERTS_SIZE 256
#define NVG_MAX_STATES 32

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
	float dx, dy;
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


struct NVGcontext
{
public:
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


		virtual void font_face(const char * font);
		virtual void font_size(float size);
		virtual void fill_color(NVGcolor color);
		virtual void text_align(int align);
		virtual float text(float x, float y, const char * string, const char * end);
		virtual float text_bounds(float x, float y, const char * string, const char * end, float * bounds);


};


