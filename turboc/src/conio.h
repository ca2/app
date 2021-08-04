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

  Filename:	conio.h
  Purpose:	Partial replacement for Borland Turbo C conio.h.
  Mod history:	02/03/02 RSB	Created.
  		03/02/02 RSB	Added TurboC.h.
		03/18/02 RSB	Adapted for C++.
		03/21/02 RSB	Added getpass.
		03/23/02 RSB	Added directvideo, _directvideo.
				Added _wscroll.  Added
				_setcursortype et al.
		03/24/02 RSB	Added ConioRefreshOkay.	
		04/19/02 RSB	Added RawResizeTurboC.	
		05/09/02 RSB	Added stuff related to 
				graphics-window keyboard FIFO.	
		11/02/03 RSB	gettext renamed to gettextTurboC to
				avoid conflicts with the internationalization
				library's gettext function.  A macro called
				gettext has been introduced to allow access
				to gettextTurboC, while the internationalization
				library's gettext can be accessed as
				gettextIntl.
		08/28/10 RSB    Now makes sure that if there's a gettext()
                                macro it gets undefined.
*/

#ifndef _INCLUDED_CONIO_H
#define _INCLUDED_CONIO_H

////#include <sys/cdefs.h>
#include "TurboC.h"
#include "graphics.h"

//----------------------------------------------------------------------------
// Constants.

// Supported text modes for conio.h.  The free Borland C++ 5.5 compiler has
// lots of video modes that aren't present in Turbo C 2.0, so I've thrown them
// in also.  EXITMODE is a new constant I've invented so that textmode(EXITMODE) 
// can be called at the end of the program to turn off ncurses.
#define EXITMODE -2
#define LASTMODE -1
#define BW40 0
#define C40 1
#define BW80 2
#define C80 3
#define MONO 7
#define C40X14 8
#define C40X21 9
#define C40X28 10
#define C40X43 11
#define C40X50 12
#define C40X60 13
#define C80X14 14
#define C80X21 15
#define C80X28 16
#define C80X43 17
#define C80X50 18
#define C80X60 19
#define BW40X14 20
#define BW40X21 21
#define BW40X28 22
#define BW40X43 23
#define BW40X50 24
#define BW40X60 25
#define BW80X14 26
#define BW80X21 27
#define BW80X28 28
#define BW80X43 29
#define BW80X50 30
#define BW80X60 31
#define MONO14 32
#define MONO21 33
#define MONO28 34
#define MONO43 35
#define MONO50 36
#define MONO60 37
#define C4350 64
//#define CCUSTOM(x,y) (0xffff + 0x10000*(x) + 0x1000000*(y))

// Colors, exactly as in Turbo C.  We protect them with a conditional,
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
#define BLINK 128

// Cursor shapes.
#define _NOCURSOR 0
#define _SOLIDCURSOR 1
#define _NORMALCURSOR 2

// Size of the keyboard buffer of the graphics window, used
// for feeding into getch.
#define TC_KEYBUF_SIZE 256

//----------------------------------------------------------------------------
// Data types.

struct text_info
{
  u32 currmode;		// Is only a char in conio.
  u8 winleft;
  u8 wintop;
  u8 winright;
  u8 winbottom;
  u8 attribute;
  u8 normattr;
  //u8 currmode;
  u8 screenheight;
  u8 screenwidth;
  u8 curx;
  u8 cury;
};

//----------------------------------------------------------------------------
// Function prototypes.

__BEGIN_DECLS
// It might seem that various of these functions (like
// clrscr) could just be renamed to use the similar ncurses functions.
// I think not, but I could be wrong.  Important point_i32:  the textmode 
// function is optional in Turbo C, but must be used in all cases for us
// because otherwise we can't guarantee that the necessary initialization
// of ncurses has occurred.
CLASS_DECL_TURBOC void textattr (int newattr);
CLASS_DECL_TURBOC void textbackground (int newcolor);
CLASS_DECL_TURBOC void textcolor (int newcolor);
CLASS_DECL_TURBOC void lowvideo (void);
CLASS_DECL_TURBOC void highvideo (void);
CLASS_DECL_TURBOC void normvideo (void);
CLASS_DECL_TURBOC void gettextinfo (struct text_info *r);
CLASS_DECL_TURBOC int wherex (void);
CLASS_DECL_TURBOC int wherey (void);
CLASS_DECL_TURBOC void gotoxy (int x, int y);
CLASS_DECL_TURBOC void window (int left, int top, int right, int bottom);
CLASS_DECL_TURBOC void clreol (void);
CLASS_DECL_TURBOC void clrscr (void);
CLASS_DECL_TURBOC void textmode (int newmode);
CLASS_DECL_TURBOC int putch (int c);
CLASS_DECL_TURBOC int getche (void);
CLASS_DECL_TURBOC int cputs (const ::string &str);
CLASS_DECL_TURBOC int cprintf (const ::string &format, ...);
CLASS_DECL_TURBOC void delline (void);
CLASS_DECL_TURBOC void insline (void);

// The following is used to access the internationalization library's gettext
// (presumably with #include <libintl.h>).
#ifdef gettext
#undef gettext
#endif
static inline char *
gettextIntl (const ::string &msgid) { 
  extern char *gettext (const ::string &msgid);
  return (gettext (msgid)); 
}
// The following is used to access the TurboC-library's gettext.
CLASS_DECL_TURBOC int gettextTurboC (int left, int top, int right, int bottom, void *destin);
#define gettext gettextTurboC

CLASS_DECL_TURBOC int puttext (int left, int top, int right, int bottom, void *destin);
CLASS_DECL_TURBOC int movetext (int left, int top, int right, int bottom, int dleft,
		     int dtop);
CLASS_DECL_TURBOC int kbhit (void);
CLASS_DECL_TURBOC char *cgets (char *s);
CLASS_DECL_TURBOC char *getpass (const ::string &prompt);
CLASS_DECL_TURBOC void _setcursortype (int cur_t);

// Implementing getch/ungetch is a little tricky, since functions of the same
// names, but slightly different behavior, are available in ncurses.  We
// still need to USE the ncurses getch to implement the Turbo C getch/ungetch.
// So we want to use macros to redefine what they mean when encountered
// in the Turbo C code.  However, we provide NEW functions (getchNcurses
// and ungetchNcurses) to provide the ncurses functionality.
static inline int
getchNcurses (void)
{
  return (getch ());
}
CLASS_DECL_TURBOC int getchTurbo (void);
#ifdef getch
#undef getch
#endif
#define getch getchTurbo
static inline void
ungetchNcurses (int c)
{
  ungetch (c);
}
CLASS_DECL_TURBOC int ungetchTurbo (int c);
#ifdef ungetch
#undef ungetch
#endif
#define ungetch ungetchTurbo

// Signal-handling stuff.
//CLASS_DECL_TURBOC void ExitTurboC (gint);
CLASS_DECL_TURBOC void ResizeTurboC (gint);
CLASS_DECL_TURBOC void RawResizeTurboC (gint Rows, gint Columns);
CLASS_DECL_TURBOC void ConioResizeCallback (void);

// Graphics-window keyboard buffer.
int TcAddKeybuf (char c);
int TcExtractKeybuf (char *c);

__END_DECLS
//--------------------------------------------------------------------------
// Variables.
#ifdef TURBOC_VARIABLES_C
//int directvideo = 1, _directvideo = 1, _wscroll = 1;
//char TcKeybuf[TC_KEYBUF_SIZE];
//gint TcKeybufStart = 0, TcKeybufSize = 0;
//pthread_mutex_t TcMutex = PTHREAD_MUTEX_INITIALIZER;
//int ConioInitialized = 0;	// Becomes 1 after initialization.
//struct text_info CurrentAttributes;
//// CurrentWindow is NULL prior to initialization.  After initialization,
//// it begins as the ncurses stdscr.  After the window function is used, it
//// becomes something else.
//WINDOW *CurrentWindow = NULL;
//int ColorPairsUsed;
//int ConioRefreshOkay = 1;
#else // TURBOC_VARIABLES_C
extern int directvideo, _directvideo, _wscroll;
extern char TcKeybuf[TC_KEYBUF_SIZE];
extern gint TcKeybufStart, TcKeybufSize;
//extern pthread_mutex_t TcMutex;
extern int ConioInitialized;
extern struct text_info CurrentAttributes;
//extern WINDOW *CurrentWindow;
extern int ColorPairsUsed;
extern int ConioRefreshOkay;
#endif // TURBOC_VARIABLES_C

#endif // _INCLUDED_CONIO_H
