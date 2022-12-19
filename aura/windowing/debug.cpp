// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#include "framework.h"
//#include "_windowing.h"
////#include "sn/sn.h"


//extern ::particle * user_synchronization();


int g_iIgnoreXDisplayError = 0;


//void x_display_error_trap_push(SnDisplay * sndisplay, Display * display)
//{
//
//   g_iIgnoreXDisplayError++;
//
//}


//void x_display_error_trap_pop(SnDisplay * sndisplay, Display * display)
//{
//
//   synchronous_lock synchronouslock(x11_mutex());
//
//   g_iIgnoreXDisplayError--;
//
//   if(g_iIgnoreXDisplayError == 0)
//   {
//
//      XSync(display, false);
//
//   }
//
//}
//
//
//
//
//i32 _c_XErrorHandler(Display * display, XErrorEvent * perrorevent)
//{
//
//   const scoped_string & strError;
//
//   if(perrorevent->error_code == BadRequest)
//   {
//
//      pszError = "BadRequest";
//
//   }
//   else if(perrorevent->error_code == BadValue)
//   {
//
//      pszError = "BadValue";
//
//   }
//   else if(perrorevent->error_code == BadWindow)
//   {
//
//      pszError = "BadWindow";
//
//   }
//   else if(perrorevent->error_code == BadPixmap)
//   {
//
//      pszError = "BadPixmap";
//
//   }
//   else if(perrorevent->error_code == BadAtom)
//   {
//
//      pszError = "BadAtom";
//
//   }
//   else if(perrorevent->error_code == BadCursor)
//   {
//
//      pszError = "BadCursor";
//
//   }
//   else if(perrorevent->error_code == BadFont)
//   {
//
//      pszError = "BadFont";
//
//   }
//   else if(perrorevent->error_code == BadMatch)
//   {
//
//      pszError = "BadMatch";
//
//   }
//   else if(perrorevent->error_code == BadDrawable)
//   {
//
//      pszError = "BadDrawable";
//
//   }
//   else if(perrorevent->error_code == BadAccess)
//   {
//
//      pszError = "BadAccess";
//
//   }
//   else if(perrorevent->error_code == BadAlloc)
//   {
//
//      pszError = "BadAlloc";
//
//   }
//   else if(perrorevent->error_code == BadColor)
//   {
//
//      pszError = "BadColor";
//
//   }
//   else if(perrorevent->error_code == BadGC)
//   {
//
//      pszError = "BadGC";
//
//   }
//   else if(perrorevent->error_code == BadIDChoice)
//   {
//
//      pszError = "BadIDChoice";
//
//   }
//   else if(perrorevent->error_code == BadName)
//   {
//
//      pszError = "BadName";
//
//   }
//   else if(perrorevent->error_code == BadLength)
//   {
//
//      pszError = "BadLength";
//
//   }
//   else if(perrorevent->error_code == BadImplementation)
//   {
//
//      pszError = "BadImplementation";
//
//   }
//   else
//   {
//
//      pszError = " ( Unknown ) ";
//
//   }
//
//const scoped_string & strRequest;
//   if(perrorevent->request_code == 1)
//   {
//
//      pszRequest = "X_CreateWindow";
//
//   }
//   else if(perrorevent->request_code == 2)
//   {
//
//      pszRequest = "X_ChangeWindowAttributes";
//
//   }
//   else if(perrorevent->request_code == 3)
//   {
//
//      pszRequest = "X_GetWindowAttributes";
//
//   }
//   else if(perrorevent->request_code == 4)
//   {
//
//      pszRequest = "X_DestroyWindow";
//
//   }
//   else if(perrorevent->request_code == 5)
//   {
//
//      pszRequest = "X_DestroySubwindows";
//
//   }
//   else if(perrorevent->request_code == 6)
//   {
//
//      pszRequest = "X_ChangeSaveSet";
//
//   }
//   else if(perrorevent->request_code == 7)
//   {
//
//      pszRequest = "X_ReparentWindow";
//
//   }
//   else if(perrorevent->request_code == 8)
//   {
//
//      pszRequest = "X_MapWindow";
//
//   }
//   else if(perrorevent->request_code == 9)
//   {
//
//      pszRequest = "X_MapSubwindows";
//
//   }
//   else if(perrorevent->request_code == 10)
//   {
//
//      pszRequest = "X_UnmapWindow";
//
//   }
//   else if(perrorevent->request_code == 11)
//   {
//
//      pszRequest = "X_UnmapSubwindows";
//
//   }
//   else if(perrorevent->request_code == 12)
//   {
//
//      pszRequest = "X_ConfigureWindow";
//
//   }
//
//
//      #define X_CreateWindow                  1
//#define X_ChangeWindowAttributes        2
//#define X_GetWindowAttributes           3
//#define X_DestroyWindow                 4
//#define X_DestroySubwindows             5
//#define X_ChangeSaveSet                 6
//#define X_ReparentWindow                7
//#define X_MapWindow                     8
//#define X_MapSubwindows                 9
//#define X_UnmapWindow                  10
//#define X_UnmapSubwindows              11
//#define X_ConfigureWindow              12
//#define X_CirculateWindow              13
//#define X_GetGeometry                  14
//#define X_QueryTree                    15
//#define X_InternAtom                   16
//#define X_GetAtomName                  17
//#define X_ChangeProperty               18
//#define X_DeleteProperty               19
//#define X_GetProperty                  20
//#define X_ListProperties               21
//#define X_SetSelectionOwner            22
//#define X_GetSelectionOwner            23
//#define X_ConvertSelection             24
//#define X_SendEvent                    25
//#define X_GrabPointer                  26
//#define X_UngrabPointer                27
//#define X_GrabButton                   28
//#define X_UngrabButton                 29
//#define X_ChangeActivePointerGrab      30
//#define X_GrabKeyboard                 31
//#define X_UngrabKeyboard               32
//#define X_GrabKey                      33
//#define X_UngrabKey                    34
//#define X_AllowEvents                  35
//#define X_GrabServer                   36
//#define X_UngrabServer                 37
//#define X_QueryPointer                 38
//#define X_GetMotionEvents              39
//#define X_TranslateCoords              40
//#define X_WarpPointer                  41
//#define X_SetInputFocus                42
//#define X_GetInputFocus                43
//#define X_QueryKeymap                  44
//#define X_OpenFont                     45
//#define X_CloseFont                    46
//#define X_QueryFont                    47
//#define X_QueryTextExtents             48
//#define X_ListFonts                    49
//#define X_ListFontsWithInfo    	       50
//#define X_SetFontPath                  51
//#define X_GetFontPath                  52
//#define X_CreatePixmap                 53
//#define X_FreePixmap                   54
//#define X_CreateGC                     55
//#define X_ChangeGC                     56
//#define X_CopyGC                       57
//#define X_SetDashes                    58
//#define X_SetClipRectangles            59
//#define X_FreeGC                       60
//#define X_ClearArea                    61
//#define X_CopyArea                     62
//#define X_CopyPlane                    63
//#define X_PolyPoint                    64
//#define X_PolyLine                     65
//#define X_PolySegment                  66
//#define X_PolyRectangle                67
//#define X_PolyArc                      68
//#define X_FillPoly                     69
//#define X_PolyFillRectangle            70
//#define X_PolyFillArc                  71
//#define X_PutImage                     72
//#define X_GetImage                     73
//#define X_PolyText8                    74
//#define X_PolyText16                   75
//#define X_ImageText8                   76
//#define X_ImageText16                  77
//#define X_CreateColormap               78
//#define X_FreeColormap                 79
//#define X_CopyColormapAndFree          80
//#define X_InstallColormap              81
//#define X_UninstallColormap            82
//#define X_ListInstalledColormaps       83
//#define X_AllocColor                   84
//#define X_AllocNamedColor              85
//#define X_AllocColorCells              86
//#define X_AllocColorPlanes             87
//#define X_FreeColors                   88
//#define X_StoreColors                  89
//#define X_StoreNamedColor              90
//#define X_QueryColors                  91
//#define X_LookupColor                  92
//#define X_CreateCursor                 93
//#define X_CreateGlyphCursor            94
//#define X_FreeCursor                   95
//#define X_RecolorCursor                96
//#define X_QueryBestSize                97
//#define X_QueryExtension               98
//#define X_ListExtensions               99
//#define X_ChangeKeyboardMapping        100
//#define X_GetKeyboardMapping           101
//#define X_ChangeKeyboardControl        102
//#define X_GetKeyboardControl           103
//#define X_Bell                         104
//#define X_ChangePointerControl         105
//#define X_GetPointerControl            106
//#define X_SetScreenSaver               107
//#define X_GetScreenSaver               108
//#define X_ChangeHosts                  109
//#define X_ListHosts                    110
//#define X_SetAccessControl             111
//#define X_SetCloseDownMode             112
//#define X_KillClient                   113
//#define X_RotateProperties	       114
//#define X_ForceScreenSaver	       115
//#define X_SetPointerMapping            116
//#define X_GetPointerMapping            117
//#define X_SetModifierMapping	       118
//#define X_GetModifierMapping	       119
//#define X_NoOperation                  127
//
//   else
//   {
//
//      pszRequest = " ( Unknown ) ";
//
//   }
//
//   fprintf(stderr, "_c_XErrorHandler error=%d (%s) request =%d (%s)\n", perrorevent->error_code, pszError, perrorevent->request_code, pszRequest);
//
//   return 0;
//
//}
