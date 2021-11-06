/*
  TurboC, a library for porting Borland Turbo C to GNU gcc.
  Copyright 2002,2010 Ronald S. Burkey
 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
  
  Contact Ron Burkey at info@sandroid.org.

  Filename:		graphics.h
  Purpose:		Partial replacement for Borland Turbo C graphics.h.
  Mod history:	04/29/02 RSB	Created.
				05/10/02 RSB	... lotsa stuff on a continuing basis.
				05/20/02 RSB	Added fill-style stuff.
/*				05/23/02 RSB	Added getimage stuff.
				08/28/10 RSB	Now use macros for getmaxx() and
								getmaxy() to avoid namespace
								conflicts in newer Linux distros.
*/

#ifndef _INCLUDED_GRAPHICS_H
#define _INCLUDED_GRAPHICS_H

// You may notice nested "#ifdef WITH_X".  The reason for this is that
// the inner "#ifdef WITH_X" are present because I felt that I might want
// to implement a couple of different sets of graphics.h functions within
// the TurboC library -- some using X and some not X.  The  outer 
// "#ifdef WITH_X" is there because I realized afterward that graphics.h
// function sets already exist in some non-TurboC libraries (such as GRX).
// So it's not unintentional.  I simply haven't decided yet what's the
// best way to implement alternate graphics.h libraries.
#ifdef WITH_X

#include "TurboC.h"
#include "conio.h"

//----------------------------------------------------------------------------
// Constants.

// A conversion factor.
#define RADIANS_PER_DEGREE 0.017453292

// This is the maximum number of simultaneously usable image buffers for
/* putimage and getimage are allowed.
//#define MAX_TCIMAGEBUFS 32

// This actually a Turbo C constant (though it may look like one of mine).
// It refers to the maximum color index in a Turbo C palette, and shouldn't be
// messed with.  It has no relationship to the TurboC library palettes.
#define MAXCOLORS 15

// Colors.  We protect some of them with a conditional,
// because they're also defined (identically) in graphics.h, which
// may or may not have already been loaded.
#ifndef TC_COLORS_DEFINED
#define TC_COLORS_DEFINED
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15
#endif // TC_COLORS_DEFINED

#define CGA_LIGHTGREEN 1
#define CGA_LIGHTRED 2
#define CGA_YELLOW 3
#define CGA_LIGHTCYAN 1
#define CGA_LIGHTMAGENTA 2
#define CGA_WHITE 3
#define CGA_GREEN 1
#define CGA_RED 2
#define CGA_BROWN 3
#define CGA_CYAN 1
#define CGA_MAGENTA 2
#define CGA_LIGHTGRAY 3

#define EGA_BLACK 0
#define EGA_BLUE 1
#define EGA_GREEN 2
#define EGA_CYAN 3
#define EGA_RED 4
#define EGA_MAGENTA 5
#define EGA_BROWN 20
#define EGA_LIGHTGRAY 7
#define EGA_DARKGRAY 56
#define EGA_LIGHTBLUE 57
#define EGA_LIGHTGREEN 58
#define EGA_LIGHTCYAN 59
#define EGA_LIGHTRED 60
#define EGA_LIGHTMAGENTA 61
#define EGA_YELLOW 62
#define EGA_WHITE 63

// Error codes.
enum graphics_errors
{
  grOk = 0,
  grNoInitGraph = -1,
  grNotDetected = -2,
  grFileNotFound = -3,
  grInvalidDriver = -4,
  grNoLoadMem = -5,
  grNoScanMem = -6,
  grNoFloodMem = -7,
  grFontNotFound = -8,
  grNoFontMem = -9,
  grInvalidMode = -10,
  grError = -11,
  grIOerror = -12,
  grInvalidFont = -13,
  grInvalidFontNum = -14,
  grInvalidDeviceNum = -15,
  grInvalidVersion = -18
};

// Defines the allowed "graphics drivers" for initgraph.  Those up through
// 10 are available in Turbo C 2.0.  The others are present in Borland C++
// 5.0, but I don't know exactly what version they first appeared in.
// Oddly, graphics.h is completely missing from the free compiler Borland C++
// 5.5.
#define DETECT 0
#define CGA 1
#define MCGA 2
#define EGA 3
#define EGA64 4
#define EGAMONO 5
#define IBM8514 6
#define HERCMONO 7
#define ATT400 8
#define VGA 9
#define PC3270 10
#define VGA256 11
#define ATTDEB 12
#define TOSHIBA 13
#define SVGA16 14
#define SVGA256 15
#define SVGA32K 16
#define SVGA64K 17
#define VESA16 18
#define VESA256 19
#define VESA32K 20
#define VESA64K 21
#define VESA16M 22
#define ATI16 23
#define ATI256 24
#define ATI32K 25
#define COMPAQ 26
#define TSENG316 27
#define TSENG3256 28
#define TSENG416 29
#define TSENG4256 30
#define TSENG432K 31
#define GENOA5 32
#define GENOA6 33
#define OAK 34
#define PARADIS16 35
#define PARADIS256 36
#define TECMAR 37
#define TRIDENT16 38
#define TRIDENT256 39
#define VIDEO7 40
#define VIDEO7II 41
#define S3 42
#define ATIGUP 43
#define DETECTX 256

#if defined(WITH_X)

// Here are rgb definitions of the X equivalents (I hope) for the various
// Turbo C colors.  
#define XBLACK 		{ 0x0000, 0x0000, 0x0000 }
#define XBLUE 		{ 0x0000, 0x0000, 0x8000 }
#define XGREEN 		{ 0x0000, 0x8000, 0x0000 }
#define XCYAN 		{ 0x0000, 0x8000, 0x8000 }
#define XRED 		{ 0x8000, 0x0000, 0x0000 }
#define XMAGENTA 	{ 0x8000, 0x0000, 0x8000 }
#define XBROWN 		{ 0x8000, 0x4000, 0x4000 }
#define XLIGHTGRAY 	{ 0xd400, 0xd400, 0xd400 }
#define XDARKGRAY 	{ 0xa800, 0xa800, 0xa800 }
#define XLIGHTBLUE 	{ 0x0000, 0x0000, 0xff00 }
#define XLIGHTGREEN 	{ 0x0000, 0xff00, 0x0000 }
#define XLIGHTCYAN 	{ 0x0000, 0xff00, 0xff00 }
#define XLIGHTRED 	{ 0xff00, 0x0000, 0x0000 }
#define XLIGHTMAGENTA 	{ 0xff00, 0x0000, 0xff00 }
#define XYELLOW 	{ 0xff00, 0xff00, 0x0000 }
#define XWHITE 		{ 0xff00, 0xff00, 0xff00 }

// Here are all of the allowed graphics modes.  We encode the modes 
// differently (i.e., with different numerical constants) than Borland
// does, but *hopefully* this won't cause any problem.  This is done because
// we simulate the graphics screen within X, rather than using hardware
// modes of the graphics controller.  We define a set of allowed x-resolutions,
// y-resolutions, graphics-page counts, and palettes, and the modes are
// any combination of these.
//
// The constants beginning TC_xxxx are used only for *defining* the
// constants actually used by Turbo C.  If desirable, we can add new
// TC_xxxx constants later -- say, to go up to resolutions of 1600x1200 --
// as long as the number of x-resolutions times the number of y-resolutions,
// times the number of pages, times the number of palettes remains
// less than 65536.

// x-resolutions.
#define TC_X_320 0
#define TC_X_640 1
#define TC_X_720 2
#define TC_X_800 3
#define TC_X_1024 4
#define TC_X_1280 5
#define TCX 6			// Number of x-resolutions.

// y-resolutions.
#define TC_Y_200 0
#define TC_Y_348 1
#define TC_Y_350 2
#define TC_Y_400 3
#define TC_Y_480 4
#define TC_Y_600 5
#define TC_Y_768 6
#define TC_Y_1024 7
#define TCY 8			// Number of y-resolutions.
#define TCXY (TCX*TCY)

// graphics-page counts.
#define TC_PG_1 0
#define TC_PG_2 1
#define TC_PG_4 2
#define TCG 3			// Number of page-counts.
#define TCXYG (TCX*TCY*TCG)

// palettes. I don't actually know
// which palettes are used for the so-called "extended" modes associated
// with drivers 11 and up, so I give it the special name TC_PAL_X.
#define TC_PAL_2 0
#define TC_PAL_C0 1
#define TC_PAL_C1 2
#define TC_PAL_C2 3
#define TC_PAL_C3 4
#define TC_PAL_4 5
#define TC_PAL_16 6
#define TC_PAL_256 7
// #define TC_PAL_X TC_PAL_256
#define TCP 8			// Number of palettes.
#define TCXYGP (TCX*TCY*TCG*TCP)

// Okay, here are the actual constants used within Turbo C programs.  
// These are *not* the exact numbers used in true Borland Turbo C, 
// so programs that hard-code these numbers rather than using the 
// Borland-supplied constants are going to be in trouble.  (Too bad 
// for them, I say.)  
//
// Since it may not be obvious why the values are encoded the way they
// are -- instead, say, of providing a simple 4-bit field for each of 
// the 4 values being encoded (x-resolution, y-resolution, number of 
// graphics pages, and palette type) -- the reason has entirely to do
// with the Turbo C getmoderange function.  This function pre-supposes
// that the allowable graphics modes for any given graphics driver are
// in a range of integer values.  This requires that there be no *gaps*
// in the sequence, so that if we give a ranges of modes from n to n+N, 
// every one of the intervening values represents a legal mode.  By 
// encoding the modes in the way we have, all of the gaps are closed
// up, and every value from 0 to TCXYGP-1 is a legal mode -- though 
// not necessarily one which has been assigned a symbolic name below.
//
// Note that if we add new possibilities later -- say, 1600x1200 --
// then the values of the constants below could differ in different 
// versions of the TurboC library.
#define CGAC0 (TC_X_320 + TCX*TC_Y_200 + TCXY*TC_PG_1 + TCXYG*TC_PAL_C0)
#define CGAC1 (TC_X_320 + TCX*TC_Y_200 + TCXY*TC_PG_1 + TCXYG*TC_PAL_C1)
#define CGAC2 (TC_X_320 + TCX*TC_Y_200 + TCXY*TC_PG_1 + TCXYG*TC_PAL_C2)
#define CGAC3 (TC_X_320 + TCX*TC_Y_200 + TCXY*TC_PG_1 + TCXYG*TC_PAL_C3)
#define CGAHI (TC_X_640 + TCX*TC_Y_200 + TCXY*TC_PG_1 + TCXYG*TC_PAL_2)
#define MCGAC0 (TC_X_320 + TCX*TC_Y_200 + TCXY*TC_PG_1 + TCXYG*TC_PAL_C0)
#define MCGAC1 (TC_X_320 + TCX*TC_Y_200 + TCXY*TC_PG_1 + TCXYG*TC_PAL_C1)
#define MCGAC2 (TC_X_320 + TCX*TC_Y_200 + TCXY*TC_PG_1 + TCXYG*TC_PAL_C2)
#define MCGAC3 (TC_X_320 + TCX*TC_Y_200 + TCXY*TC_PG_1 + TCXYG*TC_PAL_C3)
#define MCGAMED (TC_X_640 + TCX*TC_Y_200 + TCXY*TC_PG_1 + TCXYG*TC_PAL_2)
#define MCGAHI (TC_X_640 + TCX*TC_Y_480 + TCXY*TC_PG_1 + TCXYG*TC_PAL_2)
#define EGALO (TC_X_640 + TCX*TC_Y_200 + TCXY*TC_PG_4 + TCXYG*TC_PAL_16)
#define EGAHI (TC_X_640 + TCX*TC_Y_350 + TCXY*TC_PG_2 + TCXYG*TC_PAL_16)
#define EGA64LO (TC_X_640 + TCX*TC_Y_200 + TCXY*TC_PG_1 + TCXYG*TC_PAL_16)
#define EGA64HI (TC_X_640 + TCX*TC_Y_350 + TCXY*TC_PG_1 + TCXYG*TC_PAL_4)
#define EGAMONOHI (TC_X_640 + TCX*TC_Y_350 + TCXY*TC_PG_2 + TCXYG*TC_PAL_2)
#define HERCMONOHI (TC_X_720 + TCX*TC_Y_348 + TCXY*TC_PG_2 + TCXYG*TC_PAL_2)
#define ATT400C0 (TC_X_320 + TCX*TC_Y_200 + TCXY*TC_PG_1 + TCXYG*TC_PAL_C0)
#define ATT400C1 (TC_X_320 + TCX*TC_Y_200 + TCXY*TC_PG_1 + TCXYG*TC_PAL_C1)
#define ATT400C2 (TC_X_320 + TCX*TC_Y_200 + TCXY*TC_PG_1 + TCXYG*TC_PAL_C2)
#define ATT400C3 (TC_X_320 + TCX*TC_Y_200 + TCXY*TC_PG_1 + TCXYG*TC_PAL_C3)
#define ATT400MED (TC_X_640 + TCX*TC_Y_200 + TCXY*TC_PG_1 + TCXYG*TC_PAL_2)
#define ATT400HI (TC_X_640 + TCX*TC_Y_480 + TCXY*TC_PG_1 + TCXYG*TC_PAL_2)
#define VGALO (TC_X_640 + TCX*TC_Y_200 + TCXY*TC_PG_2 + TCXYG*TC_PAL_16)
#define VGAMED (TC_X_640 + TCX*TC_Y_350 + TCXY*TC_PG_2 + TCXYG*TC_PAL_16)
#define VGAHI (TC_X_640 + TCX*TC_Y_480 + TCXY*TC_PG_1 + TCXYG*TC_PAL_16)
#define PC3270HI (TC_X_720 + TCX*TC_Y_350 + TCXY*TC_PG_1 + TCXYG*TC_PAL_2)
#define IBM8514LO (TC_X_640 + TCX*TC_Y_480 + TCXY*TC_PG_1 + TCXYG*TC_PAL_256)
#define IBM8514HI (TC_X_1024 + TCX*TC_Y_768 + TCXY*TC_PG_1 + TCXYG*TC_PAL_256)
//#define RES640x350 (TC_X_640 + TCX*TC_Y_350 + TCXY*TC_PG_1 + TCXYG*PC_PAL_X)
//#define RES640x480 (TC_X_640 + TCX*TC_Y_480 + TCXY*TC_PG_1 + TCXYG*PC_PAL_X)
//#define RES800x600 (TC_X_800 + TCX*TC_Y_600 + TCXY*TC_PG_1 + TCXYG*PC_PAL_X)
//#define RES1024x768 (TC_X_1024 + TCX*TC_Y_768 + TCXY*TC_PG_1 + TCXYG*PC_PAL_X)
//#define RES1280x1024 (TC_X_1280 + 0x10*TC_Y_1024 + TCXY*TC_PG_1 + TCXYG*PC_PAL_X)

#endif // defined(WITH_X)

// Write-modes.
#define COPY_PUT 0
#define XOR_PUT 1
#define OR_PUT 2
#define AND_PUT 3
#define NOT_PUT 4

// Line-style stuff.
#define SOLID_LINE 0
#define DOTTED_LINE 1
#define CENTER_LINE 2
#define DASHED_LINE 3
#define USERBIT_LINE 4
#define NORM_WIDTH 1
#define THICK_WIDTH 3

enum font_names
{
  DEFAULT_FONT = 0,
  TRIPLEX_FONT = 1,
  SMALL_FONT = 2,
  SANS_SERIF_FONT = 3,
  GOTHIC_FONT = 4,
  SCRIPT_FONT = 5,
  SIMPLEX_FONT = 6,
  TRIPLEX_SCR_FONT = 7,
  COMPLEX_FONT = 8,
  EUROPEAN_FONT = 9,
  BOLD_FONT = 10,
  MAX_FONT = 11
};

// Text directions.
#define HORIZ_DIR 0
#define VERT_DIR 1

// Text justification.
#define LEFT_TEXT 0
#define BOTTOM_TEXT 0
#define CENTER_TEXT 1
#define RIGHT_TEXT 2
#define TOP_TEXT 2

// Fill styles.
#define EMPTY_FILL 0
#define SOLID_FILL 1
#define LINE_FILL 2
#define LTSLASH_FILL 3
#define SLASH_FILL 4
#define BKSLASH_FILL 5
#define LTBKSLASH_FILL 6
#define HATCH_FILL 7
#define XHATCH_FILL 8
#define INTERLEAVE_FILL 9
#define WIDE_DOT_FILL 10
#define CLOSE_DOT_FILL 11
#define USER_FILL 12

////----------------------------------------------------------------------------
//// Data types.
//
//// A little toy of my own.
//typedef struct
//{
//  gint r, g, b;
//}
//RgbStruct;

// The following are all datatypes defined by true Turbo C.

struct arccoordstype
{
  int x, y;
  int xstart, ystart, xend, yend;
};

struct palettetype
{
  guchar size;
  gschar colors[MAXCOLORS + 1];
};

struct fillsettingstype
{
  int pattern;
  int color;
};

struct linesettingstype
{
  int linestyle;
  unsigned upattern;
  int thickness;
};

struct textsettingstype
{
  int font;
  int direction;
  int charsize;
  int horiz;
  int vert;
};

struct viewporttype
{
  int left, top, right, bottom;
  int clip;
};

/* This is the structure which holds data for the getimage/putimage
// functions.  It is not used explicitly (or even defined) by true Turbo C
// but it's convenient for us to define it!  We keep a pool of these
// in an array (TcImageBuffers). 
#ifdef WITH_X
struct TcImageBuffer
{
  gushort Width;
  gushort Height;
  Pixmap Handle;
};
#endif // WITH_X

//----------------------------------------------------------------------------
// Function prototypes.

__BEGIN_DECLS
  
//
CLASS_DECL_TURBOC void arc (int x, int y, int stangle, int endangle, int radius);
CLASS_DECL_TURBOC void bar (int left, int top, int right, int bottom);
CLASS_DECL_TURBOC void bar3d (int left, int top, int right, int bottom,
		   int depth, int topflag);
CLASS_DECL_TURBOC void circle (int x, int y, int radius);
CLASS_DECL_TURBOC void cleardevice (void);
CLASS_DECL_TURBOC void clearviewport (void);
CLASS_DECL_TURBOC void closegraph (void);
CLASS_DECL_TURBOC void detectgraph (int *graphdriver, int *graphmode);
CLASS_DECL_TURBOC void drawpoly (int numpoints, int *polypoints);
CLASS_DECL_TURBOC void ellipse (int x, int y, int stangle, int endangle,
		     int xradius, int yradius);
CLASS_DECL_TURBOC void fillellipse (int x, int y, int xradius, int yradius);
CLASS_DECL_TURBOC void fillpoly (int numpoints, int *polypoints);
CLASS_DECL_TURBOC void floodfill (int x, int y, int border);
CLASS_DECL_TURBOC void getarccoords (struct arccoordstype *arccoords);
CLASS_DECL_TURBOC void getaspectratio (int *xasp, int *yasp);
CLASS_DECL_TURBOC int getbkcolor (void);
CLASS_DECL_TURBOC int getcolor (void);
CLASS_DECL_TURBOC const struct palettetype *getdefaultpalette (void);
CLASS_DECL_TURBOC const char *getdrivername (void);
CLASS_DECL_TURBOC void getfillpattern (char *pattern);
CLASS_DECL_TURBOC void getfillsettings (struct fillsettingstype *fillinfo);
CLASS_DECL_TURBOC int getgraphmode (void);
/*CLASS_DECL_TURBOC void getimage (int left, int top, int right, int bottom, void *bitmap);
//CLASS_DECL_TURBOC void freeimage (void *bitmap);
CLASS_DECL_TURBOC void getlinesettings (struct linesettingstype *lineinfo);
CLASS_DECL_TURBOC int getmaxcolor (void);
CLASS_DECL_TURBOC int getmaxmode (void);
#ifdef getmaxx
#undef getmaxx
#endif
CLASS_DECL_TURBOC int turboc_getmaxx (void);
#define getmaxx() turboc_getmaxx()
#ifdef getmaxy
#undef getmaxy
#endif
CLASS_DECL_TURBOC int turboc_getmaxy (void);
#define getmaxy() turboc_getmaxy()
CLASS_DECL_TURBOC char *getmodename (int mode_number);
CLASS_DECL_TURBOC void getmoderange (int graphdriver, int *lomode, int *himode);
CLASS_DECL_TURBOC unsigned getpixel (int x, int y);
CLASS_DECL_TURBOC void getpalette (struct palettetype *palette);
CLASS_DECL_TURBOC int getpalettesize (void);
CLASS_DECL_TURBOC void gettextsettings (struct textsettingstype *texttypeinfo);
CLASS_DECL_TURBOC void getviewsettings (struct viewporttype *viewport);
CLASS_DECL_TURBOC int getx (void);
CLASS_DECL_TURBOC int gety (void);
CLASS_DECL_TURBOC void graphdefaults (void);
CLASS_DECL_TURBOC void TcGraphDefaults (void);
CLASS_DECL_TURBOC int TcDefaultColors (int Pal);
CLASS_DECL_TURBOC char *grapherrormsg (int errorcode);
CLASS_DECL_TURBOC void _graphfreemem (void *ptr, unsigned size_i32);
CLASS_DECL_TURBOC void *_graphgetmem (unsigned size_i32);
CLASS_DECL_TURBOC int graphresult (void);
CLASS_DECL_TURBOC unsigned imagesize (int left, int top, int right, int bottom);
CLASS_DECL_TURBOC void initgraph (int *graphdriver, int *graphmode, char *pathtodriver);
CLASS_DECL_TURBOC int installuserdriver (char *name, int (*detect) (void));
CLASS_DECL_TURBOC int installuserfont (char *name);
CLASS_DECL_TURBOC void line (int x1, int y1, int x2, int y2);
CLASS_DECL_TURBOC void linerel (int dx, int dy);
CLASS_DECL_TURBOC void lineto (int x, int y);
CLASS_DECL_TURBOC void moverel (int dx, int dy);
CLASS_DECL_TURBOC void moveto (int x, int y);
CLASS_DECL_TURBOC void outtext (char *textstring);
CLASS_DECL_TURBOC void outtextxy (int x, int y, char *textstring);
CLASS_DECL_TURBOC void pieslice (int x, int y, int stangle, int endangle, int radius);
/*CLASS_DECL_TURBOC void putimage (int left, int top, void *bitmap, int op);
CLASS_DECL_TURBOC void putpixel (int x, int y, int color);
CLASS_DECL_TURBOC void rectangle_i32 (int left, int top, int right, int bottom);
CLASS_DECL_TURBOC int registerbgidriver (void (*driver) (void));
CLASS_DECL_TURBOC int registerbgifont (void (*font) (void));
CLASS_DECL_TURBOC void restorecrtmode (void);
CLASS_DECL_TURBOC void sector (int X, int Y, int StAngle, int EndAngle,
		    int XRadius, int YRadius);
CLASS_DECL_TURBOC void setactivepage (int page);
CLASS_DECL_TURBOC void setallpalette (struct palettetype *palette);
CLASS_DECL_TURBOC void setaspectratio (int xasp, int yasp);
CLASS_DECL_TURBOC void setbkcolor (int color);
CLASS_DECL_TURBOC void setcolor (int color);
CLASS_DECL_TURBOC void setfillpattern (char *upattern, int color);
CLASS_DECL_TURBOC void setfillstyle (int pattern, int color);
CLASS_DECL_TURBOC unsigned setgraphbufsize (unsigned bufsize);
CLASS_DECL_TURBOC void setgraphmode (int mode);
CLASS_DECL_TURBOC void setlinestyle (int linestyle, unsigned upattern, int thickness);
CLASS_DECL_TURBOC void setpalette (int colornum, int color);
CLASS_DECL_TURBOC void setrgbpalette (int colornum, int red, int green, int blue);
CLASS_DECL_TURBOC void settextjustify (int horiz, int vert);
CLASS_DECL_TURBOC void settextstyle (int font, int direction, int charsize);
CLASS_DECL_TURBOC void setusercharsize (int multx, int divx, int multy, int divy);
CLASS_DECL_TURBOC void setviewport (int left, int top, int right, int bottom, int clip);
CLASS_DECL_TURBOC void setvisualpage (int page);
CLASS_DECL_TURBOC void setwritemode (int mode);
CLASS_DECL_TURBOC int textheight (char *textstring);
CLASS_DECL_TURBOC int textwidth (char *textstring);

// Non-user-callable functions.  Really, just names for use as function
// parameters in the registerbgidriver and registerbgifont functions.
CLASS_DECL_TURBOC void CGA_driver (void);
CLASS_DECL_TURBOC void EGAVGA_driver (void);
CLASS_DECL_TURBOC void IBM8514_driver (void);
CLASS_DECL_TURBOC void Herc_driver (void);
CLASS_DECL_TURBOC void ATT_driver (void);
CLASS_DECL_TURBOC void PC3270_driver (void);
CLASS_DECL_TURBOC void triplex_font (void);
CLASS_DECL_TURBOC void small_font (void);
CLASS_DECL_TURBOC void sansserif_font (void);
CLASS_DECL_TURBOC void gothic_font (void);

__END_DECLS
//--------------------------------------------------------------------------
// Variables.
#ifdef TURBOC_VARIABLES_C
#else // TURBOC_VARIABLES_C
extern volatile int TcGraphicsInitialized;
extern int TcCurrentGraphMode, TcGraphResult;
extern int TcXresolution, TcYresolution, TcPageCount, TcPaletteNum;
//extern int TcDriver, TcVisualPage, TcActivePage;
extern int TcForegroundColor, TcBackgroundColor, TcDriver;
extern int TcViewLeft, TcViewTop, TcViewRight, TcViewBottom, TcViewClip;
extern int Tcx, Tcy, TcViewMaxx, TcViewMaxy;
extern int TcLastArcX, TcLastArcY, TcLastStangle;
extern int TcLastEndangle, TcLastRadius;
extern int TcWritemode, TcTextHoriz, TcTextVert;
extern struct linesettingstype TcLinestyle;
extern RgbStruct TcColors[256];
extern const RgbStruct TcColors2[2];
extern const RgbStruct TcColorsC0[4];
extern const RgbStruct TcColorsC1[4];
extern const RgbStruct TcColorsC2[4];
extern const RgbStruct TcColorsC3[4];
extern const RgbStruct TcColors4[4];
extern const RgbStruct TcColors16[16];
extern const struct palettetype TcDefaultPalette2;
extern const struct palettetype TcDefaultPaletteC0;
extern const struct palettetype TcDefaultPaletteC1;
extern const struct palettetype TcDefaultPaletteC2;
extern const struct palettetype TcDefaultPaletteC3;
extern const struct palettetype TcDefaultPalette4;
extern const struct palettetype TcDefaultPalette16;
extern struct palettetype TcCurrentPalette;
extern int TcTextFont, TcTextDirection, TcTextCharsize;
extern int TcTextMultX, TcTextDivX, TcTextMultY, TcTextDivY;
extern int TcFillStyle, TcFillColor;
extern char TcUserFillPattern[8];
#ifdef WITH_X
//extern struct TcPixmapPoolRecord TcPixmapPool[MAX_TCIMAGEBUFS];
//extern Display *TcDisplay;
//extern Window TcWindow;
//extern Pixmap TcPixmaps[16];
//extern gint TcScreen;
//extern GC TcGc;
//extern Colormap TcColormap;
//extern XColor TcXforeground, TcXbackground;
//extern Pixmap TcTile;

#define TurboC_CTX (::get_turboc_context())

#define TcDisplay TurboC_CTX.Display()
#define TcWindow TurboC_CTX.Window()
#define TcPixmaps TurboC_CTX.Pixmaps()
#define TcScreen TurboC_CTX.Screen()
#define TcGc TurboC_CTX.Gc()
#define TcColormap TurboC_CTX.Colormap()
#define TcXforeground TurboC_CTX.Xforeground()
#define TcXbackground TurboC_CTX.Xbackground()
#define TcTile TurboC_CTX.Tile()

#define TcDriver TurboC_CTX.m_iDriver
#define TcVisualPage TurboC_CTX.m_iVisualPage
#define TcActivePage TurboC_CTX.m_iActivePage
//,TcVisualPage,TcActivePage;
//extern Window TcWindow;
//extern Pixmap TcPixmaps[16];
//extern gint TcScreen;
//extern GC TcGc;
//extern Colormap TcColormap;
//extern XColor TcXforeground, TcXbackground;
//extern Pixmap TcTile;

#endif // WITH_X
#endif // TURBOC_VARIABLES_C

#else // WITH_X

#include <graphics.h>

#endif // WITH_X

#endif // _INCLUDED_GRAPHICS_H
