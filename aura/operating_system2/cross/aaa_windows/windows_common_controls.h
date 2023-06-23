#pragma once


//====== TOOLBAR CONTROL ======================================================

#ifndef NOTOOLBAR

#ifdef _WIN32
#define TOOLBARCLASSNAMEW       L"ToolbarWindow32"
#define TOOLBARCLASSNAMEA       "ToolbarWindow32"

#ifdef  UNICODE
#define TOOLBARCLASSNAME        TOOLBARCLASSNAMEW
#else
#define TOOLBARCLASSNAME        TOOLBARCLASSNAMEA
#endif

#else
#define TOOLBARCLASSNAME        "ToolbarWindow"
#endif

typedef struct _TBBUTTON {
   int iBitmap;
   int idCommand;
   ::u8 fsState;
   ::u8 fsStyle;
#ifdef _WIN64
   ::u8 bReserved[6];          // padding for alignment
#elif defined(_WIN32)
   ::u8 bReserved[2];          // padding for alignment
#endif
   DWORD_PTR dwData;
   INT_PTR iString;
} TBBUTTON,* PTBBUTTON,*LPTBBUTTON;
typedef const TBBUTTON *LPCTBBUTTON;


typedef struct _COLORMAP {
   color32_t from;
   color32_t to;
} COLORMAP,*LPCOLORMAP;

/*
 
WINCOMMCTRLAPI oswindow WINAPI CreateToolbarEx(oswindow hwnd,::u32 ws,::u32 wID,int nBitmaps,
   HINSTANCE hBMInst,UINT_PTR wBMID,LPCTBBUTTON lpButtons,
   int iNumButtons,int dxButton,int dyButton,
   int dxBitmap,int dyBitmap,::u32 uStructSize);

WINCOMMCTRLAPI HBITMAP WINAPI CreateMappedBitmap(HINSTANCE hInstance,INT_PTR idBitmap,
   ::u32 wFlags,_In_opt_ LPCOLORMAP lpColorMap,
   int iNumMaps);
 
 */

#define CMB_MASKED              0x02
#define TBSTATE_CHECKED         0x01
#define TBSTATE_PRESSED         0x02
#define TBSTATE_ENABLED         0x04
#define e_toolbar_button_hidden          0x08
#define TBSTATE_INDETERMINATE   0x10
#define TBSTATE_WRAP            0x20
#define TBSTATE_ELLIPSES        0x40
#define TBSTATE_MARKED          0x80

// begin_r_commctrl

#define TBSTYLE_BUTTON          0x0000  // obsolete; use BTNS_BUTTON instead
#define TBSTYLE_SEP             0x0001  // obsolete; use BTNS_SEP instead
#define TBSTYLE_CHECK           0x0002  // obsolete; use BTNS_CHECK instead
#define TBSTYLE_GROUP           0x0004  // obsolete; use BTNS_GROUP instead
#define TBSTYLE_CHECKGROUP      (TBSTYLE_GROUP | TBSTYLE_CHECK)     // obsolete; use BTNS_CHECKGROUP instead
#define TBSTYLE_DROPDOWN        0x0008  // obsolete; use BTNS_DROPDOWN instead
#define TBSTYLE_AUTOSIZE        0x0010  // obsolete; use BTNS_AUTOSIZE instead
#define TBSTYLE_NOPREFIX        0x0020  // obsolete; use BTNS_NOPREFIX instead

#define TBSTYLE_TOOLTIPS        0x0100
#define TBSTYLE_WRAPABLE        0x0200
#define TBSTYLE_ALTDRAG         0x0400
#define TBSTYLE_FLAT            0x0800
#define TBSTYLE_LIST            0x1000
#define TBSTYLE_CUSTOMERASE     0x2000
#define TBSTYLE_REGISTERDROP    0x4000
#define TBSTYLE_TRANSPARENT     0x8000

// end_r_commctrl

#define TBSTYLE_EX_DRAWDDARROWS 0x00000001

// begin_r_commctrl

#define BTNS_BUTTON     TBSTYLE_BUTTON      // 0x0000
#define BTNS_SEP        TBSTYLE_SEP         // 0x0001
#define BTNS_CHECK      TBSTYLE_CHECK       // 0x0002
#define BTNS_GROUP      TBSTYLE_GROUP       // 0x0004
#define BTNS_CHECKGROUP TBSTYLE_CHECKGROUP  // (TBSTYLE_GROUP | TBSTYLE_CHECK)
#define BTNS_DROPDOWN   TBSTYLE_DROPDOWN    // 0x0008
#define BTNS_AUTOSIZE   TBSTYLE_AUTOSIZE    // 0x0010; automatically calculate the cx of the button
#define BTNS_NOPREFIX   TBSTYLE_NOPREFIX    // 0x0020; this button should not have accel prefix
#define BTNS_SHOWTEXT   0x0040              // ignored unless TBSTYLE_EX_MIXEDBUTTONS is set
#define BTNS_WHOLEDROPDOWN  0x0080          // draw drop-down arrow, but without split arrow section

// end_r_commctrl

#define TBSTYLE_EX_MIXEDBUTTONS             0x00000008
#define TBSTYLE_EX_HIDECLIPPEDBUTTONS       0x00000010  // don't show partially obscured buttons

#define TBSTYLE_EX_MULTICOLUMN              0x00000002 // conflicts w/ TBSTYLE_WRAPABLE
#define TBSTYLE_EX_VERTICAL                 0x00000004


#if (NTDDI_VERSION >= NTDDI_WINXP)
#define TBSTYLE_EX_DOUBLEBUFFER             0x00000080 // Double Buffer the toolbar
#endif

/*

// Custom Draw Structure
typedef struct _NMTBCUSTOMDRAW {
   NMCUSTOMDRAW nmcd;
   HBRUSH hbrMonoDither;
   HBRUSH hbrLines;                // For drawing lines on buttons
   HPEN hpenLines;                 // For drawing lines on buttons

   color32_t clrText;               // Color of text
   color32_t clrMark;               // Color of text bk when marked. (only if TBSTATE_MARKED)
   color32_t clrTextHighlight;      // Color of text when highlighted
   color32_t clrBtnFace;            // Background of the button
   color32_t clrBtnHighlight;       // 3D highlight
   color32_t clrHighlightHotTrack;  // In conjunction with fHighlightHotTrack
   // will cause button to highlight like a menu
   RECT32 rcText;                    // Rect for text

   int nStringBkMode;
   int nHLStringBkMode;
#if (NTDDI_VERSION >= NTDDI_WINXP)
   int iListGap;
#endif
} NMTBCUSTOMDRAW,* LPNMTBCUSTOMDRAW;
 
 */

// Toolbar custom draw return flags
#define TBCDRF_NOEDGES              0x00010000  // Don't draw button edges
#define TBCDRF_HILITEHOTTRACK       0x00020000  // Use color of the button bk when hottracked
#define TBCDRF_NOOFFSET             0x00040000  // Don't offset button if pressed
#define TBCDRF_NOMARK               0x00080000  // Don't draw default highlight of image/text for TBSTATE_MARKED
#define TBCDRF_NOETCHEDEFFECT       0x00100000  // Don't draw etched effect for disabled items

#define TBCDRF_BLENDICON            0x00200000  // Use ILD_BLEND50 on the icon image
#define TBCDRF_NOBACKGROUND         0x00400000  // Use ILD_BLEND50 on the icon image
#if (NTDDI_VERSION >= NTDDI_VISTA)
#define TBCDRF_USECDCOLORS          0x00800000  // Use CustomDrawColors to RenderText regardless of VisualStyle
#endif

#define TB_ENABLEBUTTON         (WM_USER + 1)
#define TB_CHECKBUTTON          (WM_USER + 2)
#define TB_PRESSBUTTON          (WM_USER + 3)
#define TB_HIDEBUTTON           (WM_USER + 4)
#define TB_INDETERMINATE        (WM_USER + 5)
#define TB_MARKBUTTON           (WM_USER + 6)
#define TB_ISBUTTONENABLED      (WM_USER + 9)
#define TB_ISBUTTONCHECKED      (WM_USER + 10)
#define TB_ISBUTTONPRESSED      (WM_USER + 11)
#define TB_ISBUTTONHIDDEN       (WM_USER + 12)
#define TB_ISBUTTONINDETERMINATE (WM_USER + 13)
#define TB_ISBUTTONHIGHLIGHTED  (WM_USER + 14)
#define TB_SETSTATE             (WM_USER + 17)
#define TB_GETSTATE             (WM_USER + 18)
#define TB_ADDBITMAP            (WM_USER + 19)

#ifdef _WIN32
typedef struct tagTBADDBITMAP {
   HINSTANCE       hInst;
   UINT_PTR        nID;
} TBADDBITMAP,*LPTBADDBITMAP;

#define HINST_COMMCTRL          ((HINSTANCE)-1)
#define IDB_STD_SMALL_COLOR     0
#define IDB_STD_LARGE_COLOR     1
#define IDB_VIEW_SMALL_COLOR    4
#define IDB_VIEW_LARGE_COLOR    5
#define IDB_HIST_SMALL_COLOR    8
#define IDB_HIST_LARGE_COLOR    9
#if (NTDDI_VERSION >= NTDDI_VISTA)
#define IDB_HIST_NORMAL         12
#define IDB_HIST_HOT            13
#define IDB_HIST_DISABLED       14
#define IDB_HIST_PRESSED        15
#endif // (NTDDI_VERSION >= NTDDI_VISTA)

// icon indexes for standard bitmap

#define STD_CUT                 0
#define STD_COPY                1
#define STD_PASTE               2
#define STD_UNDO                3
#define STD_REDOW               4
#define STD_DELETE              5
#define STD_FILENEW             6
#define STD_FILEOPEN            7
#define STD_FILESAVE            8
#define STD_PRINTPRE            9
#define STD_PROPERTIES          10
#define STD_HELP                11
#define STD_FIND                12
#define STD_REPLACE             13
#define STD_PRINT               14

// icon indexes for standard impact bitmap

#define VIEW_LARGEICONS         0
#define VIEW_SMALLICONS         1
#define VIEW_LIST               2
#define VIEW_DETAILS            3
#define VIEW_SORTNAME           4
#define VIEW_SORTSIZE           5
#define VIEW_SORTDATE           6
#define VIEW_SORTTYPE           7
#define VIEW_PARENTFOLDER       8
#define VIEW_NETCONNECT         9
#define VIEW_NETDISCONNECT      10
#define VIEW_NEWFOLDER          11
#define VIEW_VIEWMENU           12

#define HIST_BACK               0
#define HIST_FORWARD            1
#define HIST_FAVORITES          2
#define HIST_ADDTOFAVORITES     3
#define HIST_VIEWTREE           4

#endif

#define TB_ADDBUTTONSA          (WM_USER + 20)
#define TB_INSERTBUTTONA        (WM_USER + 21)

#define TB_DELETEBUTTON         (WM_USER + 22)
#define TB_GETBUTTON            (WM_USER + 23)
#define TB_BUTTONCOUNT          (WM_USER + 24)
#define TB_COMMANDTOINDEX       (WM_USER + 25)

#ifdef _WIN32

typedef struct tagTBSAVEPARAMSA {
   HKEY hkr;
   const ::scoped_string & scopedstrSubKey;
   const ::scoped_string & scopedstrValueName;
} TBSAVEPARAMSA,*LPTBSAVEPARAMSA;

typedef struct tagTBSAVEPARAMSW {
   HKEY hkr;
   const ::wide_character * pszSubKey;
   const ::wide_character * pszValueName;
} TBSAVEPARAMSW,*LPTBSAVEPARAMW;

#ifdef UNICODE
#define TBSAVEPARAMS            TBSAVEPARAMSW
#define LPTBSAVEPARAMS          LPTBSAVEPARAMSW
#else
#define TBSAVEPARAMS            TBSAVEPARAMSA
#define LPTBSAVEPARAMS          LPTBSAVEPARAMSA
#endif

#endif  // _WIN32

#define TB_SAVERESTOREA         (WM_USER + 26)
#define TB_SAVERESTOREW         (WM_USER + 76)
#define TB_CUSTOMIZE            (WM_USER + 27)
#define TB_ADDSTRINGA           (WM_USER + 28)
#define TB_ADDSTRINGW           (WM_USER + 77)
#define TB_GETITEMRECT          (WM_USER + 29)
#define TB_BUTTONSTRUCTSIZE     (WM_USER + 30)
#define TB_SETBUTTONSIZE        (WM_USER + 31)
#define TB_SETBITMAPSIZE        (WM_USER + 32)
#define TB_AUTOSIZE             (WM_USER + 33)
#define TB_GETTOOLTIPS          (WM_USER + 35)
#define TB_SETTOOLTIPS          (WM_USER + 36)
#define TB_SETPARENT            (WM_USER + 37)
#define TB_SETROWS              (WM_USER + 39)
#define TB_GETROWS              (WM_USER + 40)
#define TB_SETCMDID             (WM_USER + 42)
#define TB_CHANGEBITMAP         (WM_USER + 43)
#define TB_GETBITMAP            (WM_USER + 44)
#define TB_GETBUTTONTEXTA       (WM_USER + 45)
#define TB_GETBUTTONTEXTW       (WM_USER + 75)
#define TB_REPLACEBITMAP        (WM_USER + 46)
#define TB_SETINDENT            (WM_USER + 47)
#define TB_SETIMAGELIST         (WM_USER + 48)
#define TB_GETIMAGELIST         (WM_USER + 49)
#define TB_LOADIMAGES           (WM_USER + 50)
#define TB_GETRECT              (WM_USER + 51) // wParam is the Cmd instead of index
#define TB_SETHOTIMAGELIST      (WM_USER + 52)
#define TB_GETHOTIMAGELIST      (WM_USER + 53)
#define TB_SETDISABLEDIMAGELIST (WM_USER + 54)
#define TB_GETDISABLEDIMAGELIST (WM_USER + 55)
#define TB_SETSTYLE             (WM_USER + 56)
#define TB_GETSTYLE             (WM_USER + 57)
#define TB_GETBUTTONSIZE        (WM_USER + 58)
#define TB_SETBUTTONWIDTH       (WM_USER + 59)
#define TB_SETMAXTEXTROWS       (WM_USER + 60)
#define TB_GETTEXTROWS          (WM_USER + 61)

#ifdef UNICODE
#define TB_GETBUTTONTEXT        TB_GETBUTTONTEXTW
#define TB_SAVERESTORE          TB_SAVERESTOREW
#define TB_ADDSTRING            TB_ADDSTRINGW
#else
#define TB_GETBUTTONTEXT        TB_GETBUTTONTEXTA
#define TB_SAVERESTORE          TB_SAVERESTOREA
#define TB_ADDSTRING            TB_ADDSTRINGA
#endif
#define TB_GETOBJECT            (WM_USER + 62)  // wParam == IID, lParam void **ppv
#define TB_GETHOTITEM           (WM_USER + 71)
#define TB_SETHOTITEM           (WM_USER + 72)  // wParam == iHotItem
#define TB_SETANCHORHIGHLIGHT   (WM_USER + 73)  // wParam == true/false
#define TB_GETANCHORHIGHLIGHT   (WM_USER + 74)
#define TB_MAPACCELERATORA      (WM_USER + 78)  // wParam == ch, lParam int * pidBtn

typedef struct {
   int   iButton;
   ::u32 dwFlags;
} TBINSERTMARK,* LPTBINSERTMARK;
#define TBIMHT_AFTER      0x00000001 // true = insert After iButton, otherwise before
#define TBIMHT_BACKGROUND 0x00000002 // true iff missed buttons completely

#define TB_GETINSERTMARK        (WM_USER + 79)  // lParam == LPTBINSERTMARK
#define TB_SETINSERTMARK        (WM_USER + 80)  // lParam == LPTBINSERTMARK
#define TB_INSERTMARKHITTEST    (WM_USER + 81)  // wParam == POINT32 * lParam == LPTBINSERTMARK
#define TB_MOVEBUTTON           (WM_USER + 82)
#define TB_GETMAXSIZE           (WM_USER + 83)  // lParam == LPSIZE32
#define TB_SETEXTENDEDSTYLE     (WM_USER + 84)  // For TBSTYLE_EX_*
#define TB_GETEXTENDEDSTYLE     (WM_USER + 85)  // For TBSTYLE_EX_*
#define TB_GETPADDING           (WM_USER + 86)
#define TB_SETPADDING           (WM_USER + 87)
#define TB_SETINSERTMARKCOLOR   (WM_USER + 88)
#define TB_GETINSERTMARKCOLOR   (WM_USER + 89)

#define TB_SETCOLORSCHEME       CCM_SETCOLORSCHEME  // lParam is color scheme
#define TB_GETCOLORSCHEME       CCM_GETCOLORSCHEME      // fills in COLORSCHEME pointed to by lParam

#define TB_SETUNICODEFORMAT     CCM_SETUNICODEFORMAT
#define TB_GETUNICODEFORMAT     CCM_GETUNICODEFORMAT

#define TB_MAPACCELERATORW      (WM_USER + 90)  // wParam == ch, lParam int * pidBtn
#ifdef UNICODE
#define TB_MAPACCELERATOR       TB_MAPACCELERATORW
#else
#define TB_MAPACCELERATOR       TB_MAPACCELERATORA
#endif

typedef struct {
   HINSTANCE       hInstOld;
   UINT_PTR        nIDOld;
   HINSTANCE       hInstNew;
   UINT_PTR        nIDNew;
   int             nButtons;
} TBREPLACEBITMAP,*LPTBREPLACEBITMAP;

#ifdef _WIN32

#define TBBF_LARGE              0x0001

#define TB_GETBITMAPFLAGS       (WM_USER + 41)

#define TBIF_IMAGE              0x00000001
#define TBIF_TEXT               0x00000002
#define TBIF_STATE              0x00000004
#define TBIF_STYLE              0x00000008
#define TBIF_LPARAM             0x00000010
#define TBIF_COMMAND            0x00000020
#define TBIF_SIZE               0x00000040

#define TBIF_BYINDEX            0x80000000 // this specifies that the wparam in Get/SetButtonInfo is an index, not atom

typedef struct {
   ::u32 cbSize;
   ::u32 dwMask;
   int idCommand;
   int iImage;
   ::u8 fsState;
   ::u8 fsStyle;
   ::u16 cx;
   DWORD_PTR lParam;
   char * pszText;
   int cchText;
} TBBUTTONINFOA,*LPTBBUTTONINFOA;

typedef struct {
   ::u32 cbSize;
   ::u32 dwMask;
   int idCommand;
   int iImage;
   ::u8 fsState;
   ::u8 fsStyle;
   ::u16 cx;
   DWORD_PTR lParam;
   LPWSTR pszText;
   int cchText;
} TBBUTTONINFOW,*LPTBBUTTONINFOW;

#ifdef UNICODE
#define TBBUTTONINFO TBBUTTONINFOW
#define LPTBBUTTONINFO LPTBBUTTONINFOW
#else
#define TBBUTTONINFO TBBUTTONINFOA
#define LPTBBUTTONINFO LPTBBUTTONINFOA
#endif

// BUTTONINFO APIs do NOT support the string pool.
#define TB_GETBUTTONINFOW        (WM_USER + 63)
#define TB_SETBUTTONINFOW        (WM_USER + 64)
#define TB_GETBUTTONINFOA        (WM_USER + 65)
#define TB_SETBUTTONINFOA        (WM_USER + 66)
#ifdef UNICODE
#define TB_GETBUTTONINFO        TB_GETBUTTONINFOW
#define TB_SETBUTTONINFO        TB_SETBUTTONINFOW
#else
#define TB_GETBUTTONINFO        TB_GETBUTTONINFOA
#define TB_SETBUTTONINFO        TB_SETBUTTONINFOA
#endif


#define TB_INSERTBUTTONW        (WM_USER + 67)
#define TB_ADDBUTTONSW          (WM_USER + 68)

#define TB_HITTEST              (WM_USER + 69)

// New post Win95/NT4 for InsertButton and AddButton.  if iString member
// is a pointer to a string, it will be handled as a string like listview
// (although LPSTR_TEXTCALLBACK is not supported).
#ifdef UNICODE
#define TB_INSERTBUTTON         TB_INSERTBUTTONW
#define TB_ADDBUTTONS           TB_ADDBUTTONSW
#else
#define TB_INSERTBUTTON         TB_INSERTBUTTONA
#define TB_ADDBUTTONS           TB_ADDBUTTONSA
#endif

#define TB_SETDRAWTEXTFLAGS     (WM_USER + 70)  // wParam == mask lParam == bit values

#define TB_GETSTRINGW           (WM_USER + 91)
#define TB_GETSTRINGA           (WM_USER + 92)
#ifdef UNICODE
#define TB_GETSTRING            TB_GETSTRINGW
#else
#define TB_GETSTRING            TB_GETSTRINGA
#endif

#define TB_SETBOUNDINGSIZE      (WM_USER + 93)
#define TB_SETHOTITEM2          (WM_USER + 94)  // wParam == iHotItem,  lParam = dwFlags
#define TB_HASACCELERATOR       (WM_USER + 95)  // wParam == char, lParam = &iCount
#define TB_SETLISTGAP           (WM_USER + 96)
#define TB_GETIMAGELISTCOUNT    (WM_USER + 98)
#define TB_GETIDEALSIZE         (WM_USER + 99)  // wParam == fHeight, lParam = psize
// before using WM_USER + 103, recycle old space above (WM_USER + 97)
#define TB_TRANSLATEACCELERATOR     CCM_TRANSLATEACCELERATOR

#if (NTDDI_VERSION >= NTDDI_WINXP)
#define TBMF_PAD                0x00000001
#define TBMF_BARPAD             0x00000002
#define TBMF_BUTTONSPACING      0x00000004

typedef struct {
   ::u32 cbSize;
   ::u32 dwMask;

   int cxPad;        // PAD
   int cyPad;
   int cxBarPad;     // BARPAD
   int cyBarPad;
   int cxButtonSpacing;   // BUTTONSPACING
   int cyButtonSpacing;
} TBMETRICS,* LPTBMETRICS;

#define TB_GETMETRICS           (WM_USER + 101)
#define TB_SETMETRICS           (WM_USER + 102)
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
#define TB_GETITEMDROPDOWNRECT  (WM_USER + 103)  // Rect of item's drop down button
#define TB_SETPRESSEDIMAGELIST  (WM_USER + 104)
#define TB_GETPRESSEDIMAGELIST  (WM_USER + 105)
#endif // (NTDDI_VERSION >= NTDDI_VISTA)

#if (NTDDI_VERSION >= NTDDI_WINXP)
#define TB_SETWINDOWTHEME       CCM_SETWINDOWTHEME
#endif

#define TBN_GETBUTTONINFOA      (TBN_FIRST-0)
#define TBN_BEGINDRAG           (TBN_FIRST-1)
#define TBN_ENDDRAG             (TBN_FIRST-2)
#define TBN_BEGINADJUST         (TBN_FIRST-3)
#define TBN_ENDADJUST           (TBN_FIRST-4)
#define TBN_RESET               (TBN_FIRST-5)
#define TBN_QUERYINSERT         (TBN_FIRST-6)
#define TBN_QUERYDELETE         (TBN_FIRST-7)
#define TBN_TOOLBARCHANGE       (TBN_FIRST-8)
#define TBN_CUSTHELP            (TBN_FIRST-9)
#define TBN_DROPDOWN            (TBN_FIRST - 10)
#define TBN_GETOBJECT           (TBN_FIRST - 12)

// Structure for TBN_HOTITEMCHANGE notification
//
typedef struct tagNMTBHOTITEM
{
   NMHDR   hdr;
   int     idOld;
   int     idNew;
   ::u32   dwFlags;           // HICF_*
} NMTBHOTITEM,* LPNMTBHOTITEM;

// Hot item change flags
#define HICF_OTHER          0x00000000
#define HICF_MOUSE          0x00000001          // Triggered by mouse
#define HICF_ARROWKEYS      0x00000002          // Triggered by arrow keys
#define HICF_ACCELERATOR    0x00000004          // Triggered by accelerator
#define HICF_DUPACCEL       0x00000008          // This accelerator is not unique
#define HICF_ENTERING       0x00000010          // idOld is invalid
#define HICF_LEAVING        0x00000020          // idNew is invalid
#define HICF_RESELECT       0x00000040          // hot item reselected
#define HICF_LMOUSE         0x00000080          // left mouse button selected
#define HICF_TOGGLEDROPDOWN 0x00000100          // Toggle button's dropdown state


#define TBN_HOTITEMCHANGE       (TBN_FIRST - 13)
#define TBN_DRAGOUT             (TBN_FIRST - 14) // this is sent when the user clicks down on a button then drags off the button
#define TBN_DELETINGBUTTON      (TBN_FIRST - 15) // uses TBNOTIFY
#define TBN_GETDISPINFOA        (TBN_FIRST - 16) // This is sent when the  toolbar needs  some display information
#define TBN_GETDISPINFOW        (TBN_FIRST - 17) // This is sent when the  toolbar needs  some display information
#define TBN_GETINFOTIPA         (TBN_FIRST - 18)
#define TBN_GETINFOTIPW         (TBN_FIRST - 19)
#define TBN_GETBUTTONINFOW      (TBN_FIRST - 20)
#define TBN_RESTORE             (TBN_FIRST - 21)
#define TBN_SAVE                (TBN_FIRST - 22)
#define TBN_INITCUSTOMIZE       (TBN_FIRST - 23)
#define    TBNRF_HIDEHELP       0x00000001
#define    TBNRF_ENDCUSTOMIZE   0x00000002
#define TBN_WRAPHOTITEM         (TBN_FIRST - 24)
#define TBN_DUPACCELERATOR      (TBN_FIRST - 25)
#define TBN_WRAPACCELERATOR     (TBN_FIRST - 26)
#define TBN_DRAGOVER            (TBN_FIRST - 27)
#define TBN_MAPACCELERATOR      (TBN_FIRST - 28)



typedef struct tagNMTBSAVE
{
   NMHDR hdr;
   ::u32* pData;
   ::u32* pCurrent;
   ::u32 cbData;
   int iItem;
   int cButtons;
   TBBUTTON tbButton;
} NMTBSAVE,*LPNMTBSAVE;

typedef struct tagNMTBRESTORE
{
   NMHDR hdr;
   ::u32* pData;
   ::u32* pCurrent;
   ::u32 cbData;
   int iItem;
   int cButtons;
   int cbBytesPerRecord;
   TBBUTTON tbButton;
} NMTBRESTORE,*LPNMTBRESTORE;

typedef struct tagNMTBGETINFOTIPA
{
   NMHDR hdr;
   char * pszText;
   int cchTextMax;
   int iItem;
   LPARAM lParam;
} NMTBGETINFOTIPA,*LPNMTBGETINFOTIPA;

typedef struct tagNMTBGETINFOTIPW
{
   NMHDR hdr;
   LPWSTR pszText;
   int cchTextMax;
   int iItem;
   LPARAM lParam;
} NMTBGETINFOTIPW,*LPNMTBGETINFOTIPW;

#ifdef UNICODE
#define TBN_GETINFOTIP          TBN_GETINFOTIPW
#define NMTBGETINFOTIP          NMTBGETINFOTIPW
#define LPNMTBGETINFOTIP        LPNMTBGETINFOTIPW
#else
#define TBN_GETINFOTIP          TBN_GETINFOTIPA
#define NMTBGETINFOTIP          NMTBGETINFOTIPA
#define LPNMTBGETINFOTIP        LPNMTBGETINFOTIPA
#endif

#define TBNF_IMAGE              0x00000001
#define TBNF_TEXT               0x00000002
#define TBNF_DI_SETITEM         0x10000000

typedef struct {
   NMHDR  hdr;
   ::u32 dwMask;     // [in] Specifies the values requested .[out] Client ask the data to be set for future use
   int idCommand;    // [in] atom of button we're requesting info for
   DWORD_PTR lParam;  // [in] lParam of button
   int iImage;       // [out] image index
   char * pszText;    // [out] memory_new text for item
   int cchText;      // [in] size of buffer pointed to by pszText
} NMTBDISPINFOA,*LPNMTBDISPINFOA;

typedef struct {
   NMHDR hdr;
   ::u32 dwMask;      //[in] Specifies the values requested .[out] Client ask the data to be set for future use
   int idCommand;    // [in] atom of button we're requesting info for
   DWORD_PTR lParam;  // [in] lParam of button
   int iImage;       // [out] image index
   LPWSTR pszText;   // [out] memory_new text for item
   int cchText;      // [in] size of buffer pointed to by pszText
} NMTBDISPINFOW,*LPNMTBDISPINFOW;


#ifdef UNICODE
#define TBN_GETDISPINFO       TBN_GETDISPINFOW
#define NMTBDISPINFO          NMTBDISPINFOW
#define LPNMTBDISPINFO        LPNMTBDISPINFOW
#else
#define TBN_GETDISPINFO       TBN_GETDISPINFOA
#define NMTBDISPINFO          NMTBDISPINFOA
#define LPNMTBDISPINFO        LPNMTBDISPINFOA
#endif

// Return codes for TBN_DROPDOWN
#define TBDDRET_DEFAULT         0
#define TBDDRET_NODEFAULT       1
#define TBDDRET_TREATPRESSED    2       // Treat as a standard press button


#ifdef UNICODE
#define TBN_GETBUTTONINFO       TBN_GETBUTTONINFOW
#else
#define TBN_GETBUTTONINFO       TBN_GETBUTTONINFOA
#endif

#define TBNOTIFYA NMTOOLBARA
#define TBNOTIFYW NMTOOLBARW
#define LPTBNOTIFYA LPNMTOOLBARA
#define LPTBNOTIFYW LPNMTOOLBARW

#define TBNOTIFY       NMTOOLBAR
#define LPTBNOTIFY     LPNMTOOLBAR

typedef struct tagNMTOOLBARA {
   NMHDR   hdr;
   int     iItem;
   TBBUTTON tbButton;
   int     cchText;
   char *   pszText;
   RECT32    rcButton;
} NMTOOLBARA,*LPNMTOOLBARA;

typedef struct tagNMTOOLBARW {
   NMHDR   hdr;
   int     iItem;
   TBBUTTON tbButton;
   int     cchText;
   LPWSTR   pszText;
   RECT32    rcButton;
} NMTOOLBARW,*LPNMTOOLBARW;

#ifdef UNICODE
#define NMTOOLBAR               NMTOOLBARW
#define LPNMTOOLBAR             LPNMTOOLBARW
#else
#define NMTOOLBAR               NMTOOLBARA
#define LPNMTOOLBAR             LPNMTOOLBARA
#endif

#endif

#endif      // NOTOOLBAR


//====== REBAR CONTROL ========================================================

#ifndef NOREBAR

#ifdef _WIN32
#define REBARCLASSNAMEW         L"ReBarWindow32"
#define REBARCLASSNAMEA         "ReBarWindow32"

#ifdef  UNICODE
#define REBARCLASSNAME          REBARCLASSNAMEW
#else
#define REBARCLASSNAME          REBARCLASSNAMEA
#endif

#else
#define REBARCLASSNAME          "ReBarWindow"
#endif

#define RBIM_IMAGELIST   0x00000001

// begin_r_commctrl

#define RBS_TOOLTIPS                  0x00000100
#define RBS_VARHEIGHT                 0x00000200
#define RBS_BANDBORDERS               0x00000400
#define RBS_FIXEDORDER                0x00000800
#define RBS_REGISTERDROP              0x00001000
#define RBS_AUTOSIZE                  0x00002000
#define RBS_VERTICALGRIPPER           0x00004000  // this always has the vertical gripper (default for horizontal mode)
#define RBS_DBLCLKTOGGLE              0x00008000
// end_r_commctrl

typedef struct tagREBARINFO
{
   ::u32        cbSize;
   ::u32        fMask;
//#ifndef NOIMAGEAPIS
  // HIMAGELIST  himl;
//#else
   HANDLE      himl;
//#endif
}   REBARINFO,*LPREBARINFO;


#define RBBS_BREAK          0x00000001  // break to memory_new line
#define RBBS_FIXEDSIZE      0x00000002  // band can't be size_f64
#define RBBS_CHILDEDGE      0x00000004  // edge around top & bottom of child window
#define RBBS_HIDDEN         0x00000008  // don't show
#define RBBS_NOVERT         0x00000010  // don't show when vertical
#define RBBS_FIXEDBMP       0x00000020  // bitmap doesn't transfer during band resize
#define RBBS_VARIABLEHEIGHT 0x00000040  // allow autosizing of this child vertically
#define RBBS_GRIPPERALWAYS  0x00000080  // always show the gripper
#define RBBS_NOGRIPPER      0x00000100  // never show the gripper
#define RBBS_USECHEVRON     0x00000200  // display drop-down button for this band if it's size_f64 smaller than ideal width
#define RBBS_HIDETITLE      0x00000400  // keep band title hidden
#define RBBS_TOPALIGN       0x00000800  // keep band in top row
#if (NTDDI_VERSION >= NTDDI_VISTA)
#endif



#define RBBIM_STYLE         0x00000001
#define RBBIM_COLORS        0x00000002
#define RBBIM_TEXT          0x00000004
#define RBBIM_IMAGE         0x00000008
#define RBBIM_CHILD         0x00000010
#define RBBIM_CHILDSIZE     0x00000020
#define RBBIM_SIZE          0x00000040
#define RBBIM_BACKGROUND    0x00000080
#define RBBIM_ID            0x00000100
#define RBBIM_IDEALSIZE     0x00000200
#define RBBIM_LPARAM        0x00000400
#define RBBIM_HEADERSIZE    0x00000800  // control the size of the header
#if (NTDDI_VERSION >= NTDDI_VISTA)
#define RBBIM_CHEVRONLOCATION 0x00001000
#define RBBIM_CHEVRONSTATE    0x00002000
#endif

typedef struct tagREBARBANDINFOA
{
   ::u32        cbSize;
   ::u32        fMask;
   ::u32        fStyle;
   color32_t    clrFore;
   color32_t    clrBack;
   char *       lpText;
   ::u32        cch;
   int         iImage;
   oswindow        hwndChild;
   ::u32        cxMinChild;
   ::u32        cyMinChild;
   ::u32        cx;
   HBITMAP     hbmBack;
   ::u32        wID;
   ::u32        cyChild;
   ::u32        cyMaxChild;
   ::u32        cyIntegral;
   ::u32        cxIdeal;
   LPARAM      lParam;
   ::u32        cxHeader;
#if (NTDDI_VERSION >= NTDDI_VISTA)
   RECT32        rcChevronLocation;  // the rectangle is in client co-ord wrt hwndChild
   ::u32        uChevronState;      // STATE_SYSTEM_*
#endif
}   REBARBANDINFOA,*LPREBARBANDINFOA;
typedef REBARBANDINFOA const *LPCREBARBANDINFOA;

#define REBARBANDINFOA_V3_SIZE CCSIZEOF_STRUCT(REBARBANDINFOA, wID)
#define REBARBANDINFOW_V3_SIZE CCSIZEOF_STRUCT(REBARBANDINFOW, wID)

#define REBARBANDINFOA_V6_SIZE CCSIZEOF_STRUCT(REBARBANDINFOA, cxHeader)
#define REBARBANDINFOW_V6_SIZE CCSIZEOF_STRUCT(REBARBANDINFOW, cxHeader)

typedef struct tagREBARBANDINFOW
{
   ::u32        cbSize;
   ::u32        fMask;
   ::u32        fStyle;
   color32_t    clrFore;
   color32_t    clrBack;
   LPWSTR      lpText;
   ::u32        cch;
   int         iImage;
   oswindow        hwndChild;
   ::u32        cxMinChild;
   ::u32        cyMinChild;
   ::u32        cx;
   HBITMAP     hbmBack;
   ::u32        wID;
   ::u32        cyChild;
   ::u32        cyMaxChild;
   ::u32        cyIntegral;
   ::u32        cxIdeal;
   LPARAM      lParam;
   ::u32        cxHeader;
#if (NTDDI_VERSION >= NTDDI_VISTA)
   RECT32        rcChevronLocation;    // the rectangle is in client co-ord wrt hwndChild
   ::u32        uChevronState; // STATE_SYSTEM_*
#endif
}   REBARBANDINFOW,*LPREBARBANDINFOW;
typedef REBARBANDINFOW const *LPCREBARBANDINFOW;

#ifdef UNICODE
#define REBARBANDINFO       REBARBANDINFOW
#define LPREBARBANDINFO     LPREBARBANDINFOW
#define LPCREBARBANDINFO    LPCREBARBANDINFOW
#define REBARBANDINFO_V3_SIZE REBARBANDINFOW_V3_SIZE
#define REBARBANDINFO_V6_SIZE REBARBANDINFOW_V6_SIZE
#else
#define REBARBANDINFO       REBARBANDINFOA
#define LPREBARBANDINFO     LPREBARBANDINFOA
#define LPCREBARBANDINFO    LPCREBARBANDINFOA
#define REBARBANDINFO_V3_SIZE REBARBANDINFOA_V3_SIZE
#define REBARBANDINFO_V6_SIZE REBARBANDINFOA_V6_SIZE
#endif

#define RB_INSERTBANDA  (WM_USER +  1)
#define RB_DELETEBAND   (WM_USER +  2)
#define RB_GETBARINFO   (WM_USER +  3)
#define RB_SETBARINFO   (WM_USER +  4)
#define RB_SETBANDINFOA (WM_USER +  6)
#define RB_SETPARENT    (WM_USER +  7)
#define RB_HITTEST      (WM_USER +  8)
#define RB_GETRECT      (WM_USER +  9)
#define RB_INSERTBANDW  (WM_USER +  10)
#define RB_SETBANDINFOW (WM_USER +  11)
#define RB_GETBANDCOUNT (WM_USER +  12)
#define RB_GETROWCOUNT  (WM_USER +  13)
#define RB_GETROWHEIGHT (WM_USER +  14)
#define RB_IDTOINDEX    (WM_USER +  16) // wParam == atom
#define RB_GETTOOLTIPS  (WM_USER +  17)
#define RB_SETTOOLTIPS  (WM_USER +  18)
#define RB_SETBKCOLOR   (WM_USER +  19) // sets the default BK color
#define RB_GETBKCOLOR   (WM_USER +  20) // defaults to CLR_NONE
#define RB_SETTEXTCOLOR (WM_USER +  21)
#define RB_GETTEXTCOLOR (WM_USER +  22) // defaults to 0x00000000

#if (NTDDI_VERSION >= NTDDI_WINXP)
#define RBSTR_CHANGERECT            0x0001   // flags for RB_SIZETORECT
#endif

#define RB_SIZETORECT   (WM_USER +  23) // resize the rebar/break bands and such to this rectangle (lparam)

#define RB_SETCOLORSCHEME   CCM_SETCOLORSCHEME  // lParam is color scheme
#define RB_GETCOLORSCHEME   CCM_GETCOLORSCHEME  // fills in COLORSCHEME pointed to by lParam

#ifdef UNICODE
#define RB_INSERTBAND   RB_INSERTBANDW
#define RB_SETBANDINFO   RB_SETBANDINFOW
#else
#define RB_INSERTBAND   RB_INSERTBANDA
#define RB_SETBANDINFO   RB_SETBANDINFOA
#endif

// for manual drag control
// lparam == cursor pos
// -1 means do it yourself.
// -2 means use what you had saved before
#define RB_BEGINDRAG    (WM_USER + 24)
#define RB_ENDDRAG      (WM_USER + 25)
#define RB_DRAGMOVE     (WM_USER + 26)
#define RB_GETBARHEIGHT (WM_USER + 27)
#define RB_GETBANDINFOW (WM_USER + 28)
#define RB_GETBANDINFOA (WM_USER + 29)

#ifdef UNICODE
#define RB_GETBANDINFO   RB_GETBANDINFOW
#else
#define RB_GETBANDINFO   RB_GETBANDINFOA
#endif

#define RB_MINIMIZEBAND (WM_USER + 30)
#define RB_MAXIMIZEBAND (WM_USER + 31)

#define RB_GETDROPTARGET (CCM_GETDROPTARGET)

#define RB_GETBANDBORDERS (WM_USER + 34)  // returns in lparam = lprc the amount of edges added to band wparam

#define RB_SHOWBAND     (WM_USER + 35)      // show/hide band
#define RB_SETPALETTE   (WM_USER + 37)
#define RB_GETPALETTE   (WM_USER + 38)
#define RB_MOVEBAND     (WM_USER + 39)

#define RB_SETUNICODEFORMAT     CCM_SETUNICODEFORMAT
#define RB_GETUNICODEFORMAT     CCM_GETUNICODEFORMAT

#if (NTDDI_VERSION >= NTDDI_WINXP)
#define RB_GETBANDMARGINS   (WM_USER + 40)
#define RB_SETWINDOWTHEME       CCM_SETWINDOWTHEME
#endif

#if (_WIN32_IE >= 0x0600)
#define RB_SETEXTENDEDSTYLE (WM_USER + 41)
#define RB_GETEXTENDEDSTYLE (WM_USER + 42)
#endif      // _WIN32_IE >= 0x0600

#define RB_PUSHCHEVRON      (WM_USER + 43)

#if (NTDDI_VERSION >= NTDDI_VISTA)
#define RB_SETBANDWIDTH     (WM_USER + 44)   // set width for docked band
#endif      // (NTDDI_VERSION >= NTDDI_VISTA)

#define RBN_HEIGHTCHANGE    (RBN_FIRST - 0)

#define RBN_GETOBJECT       (RBN_FIRST - 1)
#define RBN_LAYOUTCHANGED   (RBN_FIRST - 2)
#define RBN_AUTOSIZE        (RBN_FIRST - 3)
#define RBN_BEGINDRAG       (RBN_FIRST - 4)
#define RBN_ENDDRAG         (RBN_FIRST - 5)
#define RBN_DELETINGBAND    (RBN_FIRST - 6)     // Uses NMREBAR
#define RBN_DELETEDBAND     (RBN_FIRST - 7)     // Uses NMREBAR
#define RBN_CHILDSIZE       (RBN_FIRST - 8)

#define RBN_CHEVRONPUSHED   (RBN_FIRST - 10)

#if (_WIN32_IE >= 0x0600)
#define RBN_SPLITTERDRAG    (RBN_FIRST - 11)
#endif      // _WIN32_IE >= 0x0600


#define RBN_MINMAX          (RBN_FIRST - 21)

#if (NTDDI_VERSION >= NTDDI_WINXP)
#define RBN_AUTOBREAK       (RBN_FIRST - 22)
#endif

typedef struct tagNMREBARCHILDSIZE
{
   NMHDR hdr;
   ::u32 uBand;
   ::u32 wID;
   RECT32 rcChild;
   RECT32 rcBand;
} NMREBARCHILDSIZE,*LPNMREBARCHILDSIZE;

typedef struct tagNMREBAR
{
   NMHDR   hdr;
   ::u32   dwMask;           // RBNM_*
   ::u32    uBand;
   ::u32    fStyle;
   ::u32    wID;
   LPARAM  lParam;
} NMREBAR,*LPNMREBAR;

// Mask flags for NMREBAR
#define RBNM_ID         0x00000001
#define RBNM_STYLE      0x00000002
#define RBNM_LPARAM     0x00000004


typedef struct tagNMRBAUTOSIZE
{
   NMHDR hdr;
   int_bool fChanged;
   RECT32 rcTarget;
   RECT32 rcActual;
} NMRBAUTOSIZE,*LPNMRBAUTOSIZE;

typedef struct tagNMREBARCHEVRON
{
   NMHDR hdr;
   ::u32 uBand;
   ::u32 wID;
   LPARAM lParam;
   RECT32 rc;
   LPARAM lParamNM;
} NMREBARCHEVRON,*LPNMREBARCHEVRON;

#if (_WIN32_IE >= 0x0600)
typedef struct tagNMREBARSPLITTER
{
   NMHDR hdr;
   RECT32  rcSizing;
} NMREBARSPLITTER,*LPNMREBARSPLITTER;
#endif

#if (NTDDI_VERSION >= NTDDI_WINXP)
#define RBAB_AUTOSIZE   0x0001   // These are not flags and are all mutually exclusive
#define RBAB_ADDBAND    0x0002

typedef struct tagNMREBARAUTOBREAK
{
   NMHDR hdr;
   ::u32 uBand;
   ::u32 wID;
   LPARAM lParam;
   ::u32 uMsg;
   ::u32 fStyleCurrent;
   int_bool fAutoBreak;
} NMREBARAUTOBREAK,*LPNMREBARAUTOBREAK;
#endif

#define RBHT_NOWHERE    0x0001
#define RBHT_CAPTION    0x0002
#define RBHT_CLIENT     0x0003
#define RBHT_GRABBER    0x0004
#define RBHT_CHEVRON    0x0008
#if (_WIN32_IE >= 0x0600)
#define RBHT_SPLITTER   0x0010
#endif

typedef struct _RB_HITTESTINFO
{
   POINT32 pt;
   ::u32 flags;
   int iBand;
} RBHITTESTINFO,*LPRBHITTESTINFO;

#endif      // NOREBAR

//====== TOOLTIPS CONTROL =====================================================

#ifndef NOTOOLTIPS

#ifdef _WIN32

#define TOOLTIPS_CLASSW         L"tooltips_class32"
#define TOOLTIPS_CLASSA         "tooltips_class32"

#ifdef UNICODE
#define TOOLTIPS_CLASS          TOOLTIPS_CLASSW
#else
#define TOOLTIPS_CLASS          TOOLTIPS_CLASSA
#endif

#else
#define TOOLTIPS_CLASS          "tooltips_class"
#endif

#define LPTOOLINFOA   LPTTTOOLINFOA
#define LPTOOLINFOW   LPTTTOOLINFOW
#define TOOLINFOA       TTTOOLINFOA
#define TOOLINFOW       TTTOOLINFOW

#define LPTOOLINFO    LPTTTOOLINFO
#define TOOLINFO        TTTOOLINFO

#define TTTOOLINFOA_V1_SIZE CCSIZEOF_STRUCT(TTTOOLINFOA, lpszText)
#define TTTOOLINFOW_V1_SIZE CCSIZEOF_STRUCT(TTTOOLINFOW, lpszText)
#define TTTOOLINFOA_V2_SIZE CCSIZEOF_STRUCT(TTTOOLINFOA, lParam)
#define TTTOOLINFOW_V2_SIZE CCSIZEOF_STRUCT(TTTOOLINFOW, lParam)
#define TTTOOLINFOA_V3_SIZE CCSIZEOF_STRUCT(TTTOOLINFOA, lpReserved)
#define TTTOOLINFOW_V3_SIZE CCSIZEOF_STRUCT(TTTOOLINFOW, lpReserved)

typedef struct tagTOOLINFOA {
   ::u32 cbSize;
   ::u32 uFlags;
   oswindow hwnd;
   UINT_PTR uId;
   RECT32 rectangle;
   HINSTANCE hinst;
   char * lpszText;
   LPARAM lParam;
#if (NTDDI_VERSION >= NTDDI_WINXP)
   void *lpReserved;
#endif
} TTTOOLINFOA,*PTOOLINFOA,*LPTTTOOLINFOA;

typedef struct tagTOOLINFOW {
   ::u32 cbSize;
   ::u32 uFlags;
   oswindow hwnd;
   UINT_PTR uId;
   RECT32 rectangle;
   HINSTANCE hinst;
   LPWSTR lpszText;
   LPARAM lParam;
#if (NTDDI_VERSION >= NTDDI_WINXP)
   void *lpReserved;
#endif
} TTTOOLINFOW,*PTOOLINFOW,*LPTTTOOLINFOW;

#ifdef UNICODE
#define TTTOOLINFO              TTTOOLINFOW
#define PTOOLINFO               PTOOLINFOW
#define LPTTTOOLINFO            LPTTTOOLINFOW
#define TTTOOLINFO_V1_SIZE TTTOOLINFOW_V1_SIZE
#else
#define PTOOLINFO               PTOOLINFOA
#define TTTOOLINFO              TTTOOLINFOA
#define LPTTTOOLINFO            LPTTTOOLINFOA
#define TTTOOLINFO_V1_SIZE TTTOOLINFOA_V1_SIZE
#endif

// begin_r_commctrl

#define TTS_ALWAYSTIP           0x01
#define TTS_NOPREFIX            0x02
#define TTS_NOANIMATE           0x10
#define TTS_NOFADE              0x20
#define TTS_BALLOON             0x40
#define TTS_CLOSE               0x80
#if (NTDDI_VERSION >= NTDDI_VISTA)
#define TTS_USEVISUALSTYLE      0x100  // Use themed hyperlinks

#endif

// end_r_commctrl

#define TTF_IDISHWND            0x0001

// Use this to center around trackpoint in trackmode
// -OR- to center around tool in normal mode.
// Use TTF_ABSOLUTE to place the tip exactly at the track coords when
// in tracking mode.  TTF_ABSOLUTE can be used in conjunction with TTF_CENTERTIP
// to center the tip absolutely about the track point.

#define TTF_CENTERTIP           0x0002
#define TTF_RTLREADING          0x0004
#define TTF_SUBCLASS            0x0010
#define TTF_TRACK               0x0020
#define TTF_ABSOLUTE            0x0080
#define TTF_TRANSPARENT         0x0100
#define TTF_PARSELINKS          0x1000
#define TTF_DI_SETITEM          0x8000       // valid only on the TTN_NEEDTEXT callback


#define TTDT_AUTOMATIC          0
#define TTDT_RESHOW             1
#define TTDT_AUTOPOP            2
#define TTDT_INITIAL            3

// ToolTip Icons (Set with TTM_SETTITLE)
#define TTI_NONE                0
#define TTI_INFO                1
#define TTI_WARNING             2
#define TTI_ERROR               3
#if (NTDDI_VERSION >= NTDDI_VISTA)
#define TTI_INFO_LARGE          4
#define TTI_WARNING_LARGE       5
#define TTI_ERROR_LARGE         6
#endif  // (NTDDI_VERSION >= NTDDI_VISTA)

// Tool Tip Messages
#define TTM_ACTIVATE            (WM_USER + 1)
#define TTM_SETDELAYTIME        (WM_USER + 3)
#define TTM_ADDTOOLA            (WM_USER + 4)
#define TTM_ADDTOOLW            (WM_USER + 50)
#define TTM_DELTOOLA            (WM_USER + 5)
#define TTM_DELTOOLW            (WM_USER + 51)
#define TTM_NEWTOOLRECTA        (WM_USER + 6)
#define TTM_NEWTOOLRECTW        (WM_USER + 52)
#define TTM_RELAYEVENT          (WM_USER + 7) // Win7: wParam = GetMessageExtraInfo() when relaying e_message_mouse_move

#define TTM_GETTOOLINFOA        (WM_USER + 8)
#define TTM_GETTOOLINFOW        (WM_USER + 53)

#define TTM_SETTOOLINFOA        (WM_USER + 9)
#define TTM_SETTOOLINFOW        (WM_USER + 54)

#define TTM_HITTESTA            (WM_USER +10)
#define TTM_HITTESTW            (WM_USER +55)
#define TTM_GETTEXTA            (WM_USER +11)
#define TTM_GETTEXTW            (WM_USER +56)
#define TTM_UPDATETIPTEXTA      (WM_USER +12)
#define TTM_UPDATETIPTEXTW      (WM_USER +57)
#define TTM_GETTOOLCOUNT        (WM_USER +13)
#define TTM_ENUMTOOLSA          (WM_USER +14)
#define TTM_ENUMTOOLSW          (WM_USER +58)
#define TTM_GETCURRENTTOOLA     (WM_USER + 15)
#define TTM_GETCURRENTTOOLW     (WM_USER + 59)
#define TTM_WINDOWFROMPOINT     (WM_USER + 16)
#define TTM_TRACKACTIVATE       (WM_USER + 17)  // wParam = true/false start end  lparam = LPTOOLINFO
#define TTM_TRACKPOSITION       (WM_USER + 18)  // lParam = dwPos
#define TTM_SETTIPBKCOLOR       (WM_USER + 19)
#define TTM_SETTIPTEXTCOLOR     (WM_USER + 20)
#define TTM_GETDELAYTIME        (WM_USER + 21)
#define TTM_GETTIPBKCOLOR       (WM_USER + 22)
#define TTM_GETTIPTEXTCOLOR     (WM_USER + 23)
#define TTM_SETMAXTIPWIDTH      (WM_USER + 24)
#define TTM_GETMAXTIPWIDTH      (WM_USER + 25)
#define TTM_SETMARGIN           (WM_USER + 26)  // lParam = lprc
#define TTM_GETMARGIN           (WM_USER + 27)  // lParam = lprc
#define TTM_POP                 (WM_USER + 28)
#define TTM_UPDATE              (WM_USER + 29)
#define TTM_GETBUBBLESIZE       (WM_USER + 30)
#define TTM_ADJUSTRECT          (WM_USER + 31)
#define TTM_SETTITLEA           (WM_USER + 32)  // wParam = TTI_*, lParam = char* szTitle
#define TTM_SETTITLEW           (WM_USER + 33)  // wParam = TTI_*, lParam = wchar* szTitle

#if (NTDDI_VERSION >= NTDDI_WINXP)
#define TTM_POPUP               (WM_USER + 34)
#define TTM_GETTITLE            (WM_USER + 35) // wParam = 0, lParam = TTGETTITLE*

typedef struct _TTGETTITLE
{
   ::u32 dwSize;
   ::u32 uTitleBitmap;
   ::u32 cch;
   WCHAR* pszTitle;
} TTGETTITLE,*PTTGETTITLE;
#endif

#ifdef UNICODE
#define TTM_ADDTOOL             TTM_ADDTOOLW
#define TTM_DELTOOL             TTM_DELTOOLW
#define TTM_NEWTOOLRECT         TTM_NEWTOOLRECTW
#define TTM_GETTOOLINFO         TTM_GETTOOLINFOW
#define TTM_SETTOOLINFO         TTM_SETTOOLINFOW
#define TTM_HITTEST             TTM_HITTESTW
#define TTM_GETTEXT             TTM_GETTEXTW
#define TTM_UPDATETIPTEXT       TTM_UPDATETIPTEXTW
#define TTM_ENUMTOOLS           TTM_ENUMTOOLSW
#define TTM_GETCURRENTTOOL      TTM_GETCURRENTTOOLW
#define TTM_SETTITLE            TTM_SETTITLEW
#else
#define TTM_ADDTOOL             TTM_ADDTOOLA
#define TTM_DELTOOL             TTM_DELTOOLA
#define TTM_NEWTOOLRECT         TTM_NEWTOOLRECTA
#define TTM_GETTOOLINFO         TTM_GETTOOLINFOA
#define TTM_SETTOOLINFO         TTM_SETTOOLINFOA
#define TTM_HITTEST             TTM_HITTESTA
#define TTM_GETTEXT             TTM_GETTEXTA
#define TTM_UPDATETIPTEXT       TTM_UPDATETIPTEXTA
#define TTM_ENUMTOOLS           TTM_ENUMTOOLSA
#define TTM_GETCURRENTTOOL      TTM_GETCURRENTTOOLA
#define TTM_SETTITLE            TTM_SETTITLEA
#endif

#if (NTDDI_VERSION >= NTDDI_WINXP)
#define TTM_SETWINDOWTHEME      CCM_SETWINDOWTHEME
#endif


#define LPHITTESTINFOW    LPTTHITTESTINFOW
#define LPHITTESTINFOA    LPTTHITTESTINFOA
#define LPHITTESTINFO     LPTTHITTESTINFO

typedef struct _TT_HITTESTINFOA {
   oswindow hwnd;
   POINT32 pt;
   TTTOOLINFOA ti;
} TTHITTESTINFOA,*LPTTHITTESTINFOA;

typedef struct _TT_HITTESTINFOW {
   oswindow hwnd;
   POINT32 pt;
   TTTOOLINFOW ti;
} TTHITTESTINFOW,*LPTTHITTESTINFOW;

#ifdef UNICODE
#define TTHITTESTINFO           TTHITTESTINFOW
#define LPTTHITTESTINFO         LPTTHITTESTINFOW
#else
#define TTHITTESTINFO           TTHITTESTINFOA
#define LPTTHITTESTINFO         LPTTHITTESTINFOA
#endif

#define TTN_GETDISPINFOA        (TTN_FIRST - 0)
#define TTN_GETDISPINFOW        (TTN_FIRST - 10)
#define TTN_SHOW                (TTN_FIRST - 1)
#define TTN_POP                 (TTN_FIRST - 2)
#define TTN_LINKCLICK           (TTN_FIRST - 3)

#ifdef UNICODE
#define TTN_GETDISPINFO         TTN_GETDISPINFOW
#else
#define TTN_GETDISPINFO         TTN_GETDISPINFOA
#endif

#define TTN_NEEDTEXT            TTN_GETDISPINFO
#define TTN_NEEDTEXTA           TTN_GETDISPINFOA
#define TTN_NEEDTEXTW           TTN_GETDISPINFOW


#define TOOLTIPTEXTW NMTTDISPINFOW
#define TOOLTIPTEXTA NMTTDISPINFOA
#define LPTOOLTIPTEXTA LPNMTTDISPINFOA
#define LPTOOLTIPTEXTW LPNMTTDISPINFOW

#define TOOLTIPTEXT    NMTTDISPINFO
#define LPTOOLTIPTEXT  LPNMTTDISPINFO

#define NMTTDISPINFOA_V1_SIZE CCSIZEOF_STRUCT(NMTTDISPINFOA, uFlags)
#define NMTTDISPINFOW_V1_SIZE CCSIZEOF_STRUCT(NMTTDISPINFOW, uFlags)

typedef struct tagNMTTDISPINFOA {
   NMHDR hdr;
   char * lpszText;
   char szText[80];
   HINSTANCE hinst;
   ::u32 uFlags;
   LPARAM lParam;
} NMTTDISPINFOA,*LPNMTTDISPINFOA;

typedef struct tagNMTTDISPINFOW {
   NMHDR hdr;
   LPWSTR lpszText;
   WCHAR szText[80];
   HINSTANCE hinst;
   ::u32 uFlags;
   LPARAM lParam;
} NMTTDISPINFOW,*LPNMTTDISPINFOW;

#ifdef UNICODE
#define NMTTDISPINFO            NMTTDISPINFOW
#define LPNMTTDISPINFO          LPNMTTDISPINFOW
#define NMTTDISPINFO_V1_SIZE NMTTDISPINFOW_V1_SIZE
#else
#define NMTTDISPINFO            NMTTDISPINFOA
#define LPNMTTDISPINFO          LPNMTTDISPINFOA
#define NMTTDISPINFO_V1_SIZE NMTTDISPINFOA_V1_SIZE
#endif

#endif      // NOTOOLTIPS



//====== STATUS BAR CONTROL ===================================================

#ifndef NOSTATUSBAR

// begin_r_commctrl

#define SBARS_SIZEGRIP          0x0100
#define SBARS_TOOLTIPS          0x0800

// this is a status bar flag, preference to SBARS_TOOLTIPS
#define SBT_TOOLTIPS            0x0800

// end_r_commctrl

//WINCOMMCTRLAPI void WINAPI DrawStatusTextA(HDC hDC,LPCRECT32 lprc, const ::string & pszText,::u32 uFlags);
//WINCOMMCTRLAPI void WINAPI DrawStatusTextW(HDC hDC,LPCRECT32 lprc,const ::wide_character * pszText,::u32 uFlags);

//WINCOMMCTRLAPI oswindow WINAPI CreateStatusWindowA(::i32 style, const ::string & lpszText,oswindow hwndParent,::u32 wID);
//WINCOMMCTRLAPI oswindow WINAPI CreateStatusWindowW(::i32 style,const ::wide_character * lpszText,oswindow hwndParent,::u32 wID);

#ifdef UNICODE
#define CreateStatusWindow      CreateStatusWindowW
#define DrawStatusText          DrawStatusTextW
#else
#define CreateStatusWindow      CreateStatusWindowA
#define DrawStatusText          DrawStatusTextA
#endif

#ifdef _WIN32
#define STATUSCLASSNAMEW        L"msctls_statusbar32"
#define STATUSCLASSNAMEA        "msctls_statusbar32"

#ifdef UNICODE
#define STATUSCLASSNAME         STATUSCLASSNAMEW
#else
#define STATUSCLASSNAME         STATUSCLASSNAMEA
#endif

#else
#define STATUSCLASSNAME         "msctls_statusbar"
#endif

#define SB_SETTEXTA             (WM_USER+1)
#define SB_SETTEXTW             (WM_USER+11)
#define SB_GETTEXTA             (WM_USER+2)
#define SB_GETTEXTW             (WM_USER+13)
#define SB_GETTEXTLENGTHA       (WM_USER+3)
#define SB_GETTEXTLENGTHW       (WM_USER+12)

#ifdef UNICODE
#define SB_GETTEXT              SB_GETTEXTW
#define SB_SETTEXT              SB_SETTEXTW
#define SB_GETTEXTLENGTH        SB_GETTEXTLENGTHW
#define SB_SETTIPTEXT           SB_SETTIPTEXTW
#define SB_GETTIPTEXT           SB_GETTIPTEXTW
#else
#define SB_GETTEXT              SB_GETTEXTA
#define SB_SETTEXT              SB_SETTEXTA
#define SB_GETTEXTLENGTH        SB_GETTEXTLENGTHA
#define SB_SETTIPTEXT           SB_SETTIPTEXTA
#define SB_GETTIPTEXT           SB_GETTIPTEXTA
#endif


#define SB_SETPARTS             (WM_USER+4)
#define SB_GETPARTS             (WM_USER+6)
#define SB_GETBORDERS           (WM_USER+7)
#define SB_SETMINHEIGHT         (WM_USER+8)
#define SB_SIMPLE               (WM_USER+9)
#define SB_GETRECT              (WM_USER+10)
#define SB_ISSIMPLE             (WM_USER+14)
#define SB_SETICON              (WM_USER+15)
#define SB_SETTIPTEXTA          (WM_USER+16)
#define SB_SETTIPTEXTW          (WM_USER+17)
#define SB_GETTIPTEXTA          (WM_USER+18)
#define SB_GETTIPTEXTW          (WM_USER+19)
#define SB_GETICON              (WM_USER+20)
#define SB_SETUNICODEFORMAT     CCM_SETUNICODEFORMAT
#define SB_GETUNICODEFORMAT     CCM_GETUNICODEFORMAT

#define SBT_OWNERDRAW            0x1000
#define SBT_NOBORDERS            0x0100
#define SBT_POPOUT               0x0200
#define SBT_RTLREADING           0x0400
#define SBT_NOTABPARSING         0x0800

#define SB_SETBKCOLOR           CCM_SETBKCOLOR      // lParam = bkColor

// status bar notifications
#define SBN_SIMPLEMODECHANGE    (SBN_FIRST - 0)

// refers to the data saved for simple mode
#define SB_SIMPLEID  0x00ff

#endif      // NOSTATUSBAR

//====== MENU HELP ============================================================

#ifndef NOMENUHELP

//WINCOMMCTRLAPI void WINAPI MenuHelp(::u32 uMsg,WPARAM wParam,LPARAM lParam,HMENU hMainMenu,HINSTANCE hInst,oswindow hwndStatus,_In_reads_(_Inexpressible_(2 + 2n && n >= 1)) ::u32 *lpwIDs);
//WINCOMMCTRLAPI int_bool WINAPI ShowHideMenuCtl(_In_ oswindow hWnd,_In_ UINT_PTR uFlags,_In_z_ LPINT lpInfo);
//WINCOMMCTRLAPI void WINAPI GetEffectiveClientRect(_In_ oswindow hWnd,_Out_ ::rectangle_i32 * lprc,_In_z_ const ::i32 *lpInfo);

#define MINSYSCOMMAND   SC_SIZE

#endif



#define CMB_MASKED              0x02
#define TBSTATE_CHECKED         0x01
#define TBSTATE_PRESSED         0x02
#define TBSTATE_ENABLED         0x04
#define e_toolbar_button_hidden          0x08
#define TBSTATE_INDETERMINATE   0x10
#define TBSTATE_WRAP            0x20
#define TBSTATE_ELLIPSES        0x40
#define TBSTATE_MARKED          0x80

// begin_r_commctrl

#define TBSTYLE_BUTTON          0x0000  // obsolete; use BTNS_BUTTON instead
#define TBSTYLE_SEP             0x0001  // obsolete; use BTNS_SEP instead
#define TBSTYLE_CHECK           0x0002  // obsolete; use BTNS_CHECK instead
#define TBSTYLE_GROUP           0x0004  // obsolete; use BTNS_GROUP instead
#define TBSTYLE_CHECKGROUP      (TBSTYLE_GROUP | TBSTYLE_CHECK)     // obsolete; use BTNS_CHECKGROUP instead
#define TBSTYLE_DROPDOWN        0x0008  // obsolete; use BTNS_DROPDOWN instead
#define TBSTYLE_AUTOSIZE        0x0010  // obsolete; use BTNS_AUTOSIZE instead
#define TBSTYLE_NOPREFIX        0x0020  // obsolete; use BTNS_NOPREFIX instead

#define TBSTYLE_TOOLTIPS        0x0100
#define TBSTYLE_WRAPABLE        0x0200
#define TBSTYLE_ALTDRAG         0x0400
#define TBSTYLE_FLAT            0x0800
#define TBSTYLE_LIST            0x1000
#define TBSTYLE_CUSTOMERASE     0x2000
#define TBSTYLE_REGISTERDROP    0x4000
#define TBSTYLE_TRANSPARENT     0x8000
