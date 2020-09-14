#pragma once



struct gdi_object;


struct gdi_enhanced_meta_file;


typedef struct gdi_enhanced_meta_file * HENHMETAFILE;


struct tagEXTLOGPEN;


struct tagLOGBRUSH;


struct tagLOGRGN;


//typedef struct tagPOINT
//{
//   LONG  x;
//   LONG  y;
//} POINT,*PPOINT,NEAR *NPPOINT,FAR *LPPOINT;
//
//


/* Ternary raster operations */
#define SRCCOPY             (DWORD)0x00CC0020 /* dest = source                   */
#define SRCPAINT            (DWORD)0x00EE0086 /* dest = source OR dest           */
#define SRcaND              (DWORD)0x008800C6 /* dest = source AND dest          */
#define SRCINVERT           (DWORD)0x00660046 /* dest = source XOR dest          */
#define SRCERASE            (DWORD)0x00440328 /* dest = source AND (NOT dest )   */
#define NOTSRCCOPY          (DWORD)0x00330008 /* dest = (NOT source)             */
#define NOTSRCERASE         (DWORD)0x001100A6 /* dest = (NOT src) AND (NOT dest) */
#define MERGECOPY           (DWORD)0x00C000ca /* dest = (source AND pattern)     */
#define MERGEPAINT          (DWORD)0x00BB0226 /* dest = (NOT source) OR dest     */
#define PATCOPY             (DWORD)0x00F00021 /* dest = pattern                  */
#define PATPAINT            (DWORD)0x00FB0A09 /* dest = DPSnoo                   */
#define PATINVERT           (DWORD)0x005A0049 /* dest = pattern XOR dest         */
#define DSTINVERT           (DWORD)0x00550009 /* dest = (NOT dest)               */
#define BLACKNESS           (DWORD)0x00000042 /* dest = BLACK                    */
#define WHITENESS           (DWORD)0x00FF0062 /* dest = WHITE                    */
#if(WINVER >= 0x0500)

#define NOMIRRORBITMAP               (DWORD)0x80000000 /* Do not Mirror the bitmap in this call */
#define caPTUREBLT                   (DWORD)0x40000000 /* Include layered windows */
#endif /* WINVER >= 0x0500 */



/* Logcolorspace lcsType values */

#define LCS_sRGB                'sRGB'
#define LCS_WINDOWS_COLOR_SPACE 'Win '  // Windows default color space

typedef LONG   LCSCSTYPE;
#define LCS_caLIBRATED_RGB              0x00000000L

typedef LONG    LCSGAMUTMATCH;
#define LCS_GM_BUSINESS                 0x00000001L
#define LCS_GM_GRAPHICS                 0x00000002L
#define LCS_GM_IMAGES                   0x00000004L
#define LCS_GM_ABS_COLORIMETRIC         0x00000008L

/* ICM Defines for results from CheckColorInGamut() */
#define CM_OUT_OF_GAMUT                 255
#define CM_IN_GAMUT                     0

/* UpdateICMRegKey Constants               */
#define ICM_ADDPROFILE                  1
#define ICM_DELETEPROFILE               2
#define ICM_QUERYPROFILE                3
#define ICM_SETDEFAULTPROFILE           4
#define ICM_REGISTERICMATCHER           5
#define ICM_UNREGISTERICMATCHER         6
#define ICM_QUERYMATCH                  7

/* Macros to retrieve CMYK values from a COLORREF */
#define GetKValue(cmyk)      ((BYTE)(cmyk))
#define GetYValue(cmyk)      ((BYTE)((cmyk)>> 8))
#define GetMValue(cmyk)      ((BYTE)((cmyk)>>16))
#define GetCValue(cmyk)      ((BYTE)((cmyk)>>24))

#define CMYK(c,m,y,k)       ((COLORREF)((((BYTE)(k)|((WORD)((BYTE)(y))<<8))|(((DWORD)(BYTE)(m))<<16))|(((DWORD)(BYTE)(c))<<24)))

typedef long            FXPT16DOT16,FAR *LPFXPT16DOT16;
typedef long            FXPT2DOT30,FAR *LPFXPT2DOT30;




/* xform stuff */
#define MWT_IDENTITY        1
#define MWT_LEFTMULTIPLY    2
#define MWT_RIGHTMULTIPLY   3

#define MWT_MIN             MWT_IDENTITY
#define MWT_MAX             MWT_RIGHTMULTIPLY

#define _XFORM_
//typedef struct  tagXFORM
//{
//   FLOAT   eM11;
//   FLOAT   eM12;
//   FLOAT   eM21;
//   FLOAT   eM22;
//   FLOAT   eDx;
//   FLOAT   eDy;
//} XFORM,*PXFORM,FAR *LPXFORM;

/* Bitmap Header Definition */
//typedef struct tagBITMAP
//{
//   LONG        bmType;
//   LONG        bmWidth;
//   LONG        bmHeight;
//   LONG        bmWidthBytes;
//   WORD        bmPlanes;
//   WORD        bmBitsPixel;
//   LPVOID      bmBits;
//} BITMAP,*PBITMAP,NEAR *NPBITMAP,FAR *LPBITMAP;

////#include <pshpack1.h>
//typedef struct tagRGBTRIPLE {
//   BYTE    rgbtBlue;
//   BYTE    rgbtGreen;
//   BYTE    rgbtRed;
//} RGBTRIPLE,*PRGBTRIPLE,NEAR *NPRGBTRIPLE,FAR *LPRGBTRIPLE;
////#include "poppack.h"


/* ICM Color Definitions */
// The following two structures are used for defining RGB's in terms of CIEXYZ.

//typedef struct tagCIEXYZ
//{
//   FXPT2DOT30 ciexyzX;
//   FXPT2DOT30 ciexyzY;
//   FXPT2DOT30 ciexyzZ;
//} CIEXYZ;
//typedef CIEXYZ  FAR *LPCIEXYZ;

//typedef struct tagICEXYZTRIPLE
//{
//   CIEXYZ  ciexyzRed;
//   CIEXYZ  ciexyzGreen;
//   CIEXYZ  ciexyzBlue;
//} CIEXYZTRIPLE;
//typedef CIEXYZTRIPLE    FAR *LPCIEXYZTRIPLE;

//#ifdef LINUX
//#define BOOL int
//#endif

//typedef DWORD   COLORREF;
//typedef DWORD   *LPCOLORREF;
//
//typedef struct tagRGBQUAD {
//   BYTE    rgbBlue;
//   BYTE    rgbGreen;
//   BYTE    rgbRed;
//   BYTE    rgbReserved;
//} RGBQUAD, FAR* LPRGBQUAD;
//
//typedef struct tagPALETTEENTRY {
//   BYTE        peRed;
//   BYTE        peGreen;
//   BYTE        peBlue;
//   BYTE        peFlags;
//} PALETTEENTRY,*PPALETTEENTRY,FAR *LPPALETTEENTRY;

///* Logical Palette */
//typedef struct tagLOGPALETTE {
//   WORD                palVersion;
//   WORD                palNumEntries;
//   PALETTEENTRY        palPalEntry[1];
//} LOGPALETTE,*PLOGPALETTE,NEAR *NPLOGPALETTE,FAR *LPLOGPALETTE;
//

/* Logical Font */
#define LF_FACESIZE         32

//
//struct  tagLOGFONTA
//{
//   LONG      lfHeight;
//   LONG      lfWidth;
//   LONG      lfEscapement;
//   LONG      lfOrientation;
//   LONG      lfWeight;
//   BYTE      lfItalic;
//   BYTE      lfUnderline;
//   BYTE      lfStrikeOut;
//   BYTE      lfCharSet;
//   BYTE      lfOutPrecision;
//   BYTE      lfClipPrecision;
//   BYTE      lfQuality;
//   BYTE      lfPitchAndFamily;
//   char      lfFaceName[LF_FACESIZE];
//};


//struct tagLOGFONTW
//{
//   LONG      lfHeight;
//   LONG      lfWidth;
//   LONG      lfEscapement;
//   LONG      lfOrientation;
//   LONG      lfWeight;
//   BYTE      lfItalic;
//   BYTE      lfUnderline;
//   BYTE      lfStrikeOut;
//   BYTE      lfCharSet;
//   BYTE      lfOutPrecision;
//   BYTE      lfClipPrecision;
//   BYTE      lfQuality;
//   BYTE      lfPitchAndFamily;
//   unichar   lfFaceName[LF_FACESIZE];
//};


typedef struct tagLOGFONTA LOGFONTA,*PLOGFONTA,NEAR *NPLOGFONTA,FAR *LPLOGFONTA;


typedef struct tagLOGFONTW LOGFONTW,*PLOGFONTW,NEAR *NPLOGFONTW,FAR *LPLOGFONTW;


struct tagFONTA;


struct tagFONTW;


typedef struct tagFONTA FONTA,* PFONTA,NEAR * NPFONTA,FAR * LPFONTA;


typedef struct tagFONTW FONTW,* PFONTW,NEAR * NPFONTW,FAR * LPFONTW;


#ifdef UNICODE
typedef LOGFONTW LOGFONT;
typedef PLOGFONTW PLOGFONT;
typedef NPLOGFONTW NPLOGFONT;
typedef LPLOGFONTW LPLOGFONT;
typedef FONTW FONT;
typedef PFONTW PFONT;
typedef NPFONTW NPFONT;
typedef LPFONTW LPFONT;
#else
typedef LOGFONTA LOGFONT;
typedef PLOGFONTA PLOGFONT;
typedef NPLOGFONTA NPLOGFONT;
typedef LPLOGFONTA LPLOGFONT;
typedef FONTA FONT;
typedef PFONTA PFONT;
typedef NPFONTA NPFONT;
typedef LPFONTA LPFONT;
#endif // UNICODE



typedef LPFONT HFONT;




#define ANSI_CHARSET            0
#define DEFAULT_CHARSET         1
#define SYMBOL_CHARSET          2
#define SHIFTJIS_CHARSET        128
#define HANGEUL_CHARSET         129
#define HANGUL_CHARSET          129
#define GB2312_CHARSET          134
#define CHINESEBIG5_CHARSET     136
#define OEM_CHARSET             255

#define JOHAB_CHARSET           130
#define HEBREW_CHARSET          177
#define ARABIC_CHARSET          178
#define GREEK_CHARSET           161
#define TURKISH_CHARSET         162
#define VIETNAMESE_CHARSET      163
#define THAI_CHARSET            222
#define EASTEUROPE_CHARSET      238
#define RUSSIAN_CHARSET         204


/* Font Weights */
#define FW_DONTcaRE         0
#define FW_THIN             100
#define FW_EXTRALIGHT       200
#define FW_LIGHT            300
#define FW_NORMAL           400
#define FW_MEDIUM           500
#define FW_SEMIBOLD         600
#define FW_BOLD             700
#define FW_EXTRABOLD        800
#define FW_HEAVY            900

#define FW_ULTRALIGHT       FW_EXTRALIGHT
#define FW_REGULAR          FW_NORMAL
#define FW_DEMIBOLD         FW_SEMIBOLD
#define FW_ULTRABOLD        FW_EXTRABOLD
#define FW_BLACK            FW_HEAVY



//typedef struct tagTEXTMETRIca
//{
//   LONG        tmHeight;
//   LONG        tmAscent;
//   LONG        tmDescent;
//   LONG        tmInternalLeading;
//   LONG        tmExternalLeading;
//   LONG        tmAveCharWidth;
//   LONG        tmMaxCharWidth;
//   LONG        tmWeight;
//   LONG        tmOverhang;
//   LONG        tmDigitizedAspectX;
//   LONG        tmDigitizedAspectY;
//   BYTE        tmFirstChar;
//   BYTE        tmLastChar;
//   BYTE        tmDefaultChar;
//   BYTE        tmBreakChar;
//   BYTE        tmItalic;
//   BYTE        tmUnderlined;
//   BYTE        tmStruckOut;
//   BYTE        tmPitchAndFamily;
//   BYTE        tmCharSet;
//} TEXTMETRIca,*PTEXTMETRIca,NEAR *NPTEXTMETRIca,FAR *LPTEXTMETRIca;
//typedef struct tagTEXTMETRICW
//{
//   LONG        tmHeight;
//   LONG        tmAscent;
//   LONG        tmDescent;
//   LONG        tmInternalLeading;
//   LONG        tmExternalLeading;
//   LONG        tmAveCharWidth;
//   LONG        tmMaxCharWidth;
//   LONG        tmWeight;
//   LONG        tmOverhang;
//   LONG        tmDigitizedAspectX;
//   LONG        tmDigitizedAspectY;
//   WCHAR       tmFirstChar;
//   WCHAR       tmLastChar;
//   WCHAR       tmDefaultChar;
//   WCHAR       tmBreakChar;
//   BYTE        tmItalic;
//   BYTE        tmUnderlined;
//   BYTE        tmStruckOut;
//   BYTE        tmPitchAndFamily;
//   BYTE        tmCharSet;
//} TEXTMETRICW,*PTEXTMETRICW,NEAR *NPTEXTMETRICW,FAR *LPTEXTMETRICW;
//#ifdef UNICODE
//typedef TEXTMETRICW TEXTMETRIC;
//typedef PTEXTMETRICW PTEXTMETRIC;
//typedef NPTEXTMETRICW NPTEXTMETRIC;
//typedef LPTEXTMETRICW LPTEXTMETRIC;
//#else
//typedef TEXTMETRIca TEXTMETRIC;
//typedef PTEXTMETRIca PTEXTMETRIC;
//typedef NPTEXTMETRIca NPTEXTMETRIC;
//typedef LPTEXTMETRIca LPTEXTMETRIC;
//#endif // UNICODE
//
//
//
///* Pel Array */
//typedef struct tagPELARRAY
//{
//   LONG        paXCount;
//   LONG        paYCount;
//   LONG        paXExt;
//   LONG        paYExt;
//   BYTE        paRGBs;
//} PELARRAY,*PPELARRAY,NEAR *NPPELARRAY,FAR *LPPELARRAY;
//
///* Logical Brush (or Pattern) */
//typedef struct tagLOGBRUSH
//{
//   UINT        lbStyle;
//   COLORREF    lbColor;
//   ulong_ptr   lbHatch;
//} LOGBRUSH,*PLOGBRUSH,NEAR *NPLOGBRUSH,FAR *LPLOGBRUSH;
//
//typedef struct tagLOGBRUSH32
//{
//   UINT        lbStyle;
//   COLORREF    lbColor;
//   WINULONG       lbHatch;
//} LOGBRUSH32,*PLOGBRUSH32,NEAR *NPLOGBRUSH32,FAR *LPLOGBRUSH32;
//
//
//typedef LOGBRUSH            PATTERN;
//typedef PATTERN             *PPATTERN;
//typedef PATTERN NEAR        *NPPATTERN;
//typedef PATTERN FAR         *LPPATTERN;
//
//
///* Logical Pen */
//typedef struct tagLOGPEN
//{
//   UINT        lopnStyle;
//   POINT       lopnWidth;
//   COLORREF    lopnColor;
//} LOGPEN,*PLOGPEN,NEAR *NPLOGPEN,FAR *LPLOGPEN;
//
//
//
//struct tagEXTLOGPEN;
//
//typedef struct tagEXTLOGPEN  EXTLOGPEN,*PEXTLOGPEN,NEAR *NPEXTLOGPEN,FAR *LPEXTLOGPEN;
//
//typedef LPEXTLOGPEN HPEN;
//
///* Pen Styles */
//#define PS_SOLID            0
//#define PS_DASH             1       /* -------  */
//#define PS_DOT              2       /* .......  */
//#define PS_DASHDOT          3       /* _._._._  */
//#define PS_DASHDOTDOT       4       /* _.._.._  */
//#define PS_NULL             5
//#define PS_INSIDEFRAME      6
//#define PS_USERSTYLE        7
//#define PS_ALTERNATE        8
//#define PS_STYLE_MASK       0x0000000F
//
//#define PS_ENDcaP_ROUND     0x00000000
//#define PS_ENDcaP_SQUARE    0x00000100
//#define PS_ENDcaP_FLAT      0x00000200
//#define PS_ENDcaP_MASK      0x00000F00
//
//#define PS_JOIN_ROUND       0x00000000
//#define PS_JOIN_BEVEL       0x00001000
//#define PS_JOIN_MITER       0x00002000
//#define PS_JOIN_MASK        0x0000F000
//
//#define PS_COSMETIC         0x00000000
//#define PS_GEOMETRIC        0x00010000
//#define PS_TYPE_MASK        0x000F0000
//
//#define AD_COUNTERCLOCKWISE 1
//#define AD_CLOCKWISE        2
//
//#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
//
//#define GetRValue(rgb)      (LOBYTE(rgb))
//#define GetGValue(rgb)      (LOBYTE(((WORD)(rgb)) >> 8))
//#define GetBValue(rgb)      (LOBYTE((rgb)>>16))
//
///* Background Modes */
//#define TRANSPARENT         1
//#define OPAQUE              2
//#define BKMODE_LAST         2
//
//
//
//struct tagEXTLOGBRUSH;
//
//typedef struct tagEXTLOGBRUSH  EXTLOGBRUSH,*PEXTLOGBRUSH,NEAR *NPEXTLOGBRUSH,FAR *LPEXTLOGBRUSH;
//
//typedef LPEXTLOGBRUSH HBRUSH;
//

/* Stock Logical Objects */
#define WHITE_BRUSH         0
#define LTGRAY_BRUSH        1
#define GRAY_BRUSH          2
#define DKGRAY_BRUSH        3
#define BLACK_BRUSH         4
#define NULL_BRUSH          5
#define HOLLOW_BRUSH        NULL_BRUSH
#define WHITE_PEN           6
#define BLACK_PEN           7
#define NULL_PEN            8
#define OEM_FIXED_FONT      10
#define ANSI_FIXED_FONT     11
#define ANSI_VAR_FONT       12
#define SYSTEM_FONT         13
#define DEVICE_DEFAULT_FONT 14
#define DEFAULT_PALETTE     15
#define SYSTEM_FIXED_FONT   16

#if(WINVER >= 0x0400)
#define DEFAULT_GUI_FONT    17
#endif /* WINVER >= 0x0400 */

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN2K)
#define DC_BRUSH            18
#define DC_PEN              19
#endif

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN2K)
#define STOCK_LAST          19
#elif (WINVER >= 0x0400)
#define STOCK_LAST          17
#else
#define STOCK_LAST          16
#endif

#define CLR_INVALID     0xFFFFFFFF
//
///* structures for defining DIBs */
//typedef struct tagBITMAPCOREHEADER {
//   DWORD   bcSize;                 /* used to get to color table */
//   WORD    bcWidth;
//   WORD    bcHeight;
//   WORD    bcPlanes;
//   WORD    bcBitCount;
//} BITMAPCOREHEADER,FAR *LPBITMAPCOREHEADER,*PBITMAPCOREHEADER;
//
//typedef struct tagBITMAPINFOHEADER{
//   DWORD      biSize;
//   LONG       biWidth;
//   LONG       biHeight;
//   WORD       biPlanes;
//   WORD       biBitCount;
//   DWORD      biCompression;
//   DWORD      biSizeImage;
//   LONG       biXPelsPerMeter;
//   LONG       biYPelsPerMeter;
//   DWORD      biClrUsed;
//   DWORD      biClrImportant;
//} BITMAPINFOHEADER,FAR *LPBITMAPINFOHEADER,*PBITMAPINFOHEADER;
//
//typedef struct tagBITMAPINFO {
//   BITMAPINFOHEADER bmiHeader;
//   RGBQUAD          bmiColors[1];
//} BITMAPINFO,*PBITMAPINFO;
//
//
//#if(WINVER >= 0x0400)
//typedef struct {
//   DWORD        bV4Size;
//   LONG         bV4Width;
//   LONG         bV4Height;
//   WORD         bV4Planes;
//   WORD         bV4BitCount;
//   DWORD        bV4V4Compression;
//   DWORD        bV4SizeImage;
//   LONG         bV4XPelsPerMeter;
//   LONG         bV4YPelsPerMeter;
//   DWORD        bV4ClrUsed;
//   DWORD        bV4ClrImportant;
//   DWORD        bV4RedMask;
//   DWORD        bV4GreenMask;
//   DWORD        bV4BlueMask;
//   DWORD        bV4AlphaMask;
//   DWORD        bV4CSType;
//   CIEXYZTRIPLE bV4Endpoints;
//   DWORD        bV4GammaRed;
//   DWORD        bV4GammaGreen;
//   DWORD        bV4GammaBlue;
//} BITMAPV4HEADER,FAR *LPBITMAPV4HEADER,*PBITMAPV4HEADER;
//#endif /* WINVER >= 0x0400 */
//
//#if (WINVER >= 0x0500)
//typedef struct {
//   DWORD        bV5Size;
//   LONG         bV5Width;
//   LONG         bV5Height;
//   WORD         bV5Planes;
//   WORD         bV5BitCount;
//   DWORD        bV5Compression;
//   DWORD        bV5SizeImage;
//   LONG         bV5XPelsPerMeter;
//   LONG         bV5YPelsPerMeter;
//   DWORD        bV5ClrUsed;
//   DWORD        bV5ClrImportant;
//   DWORD        bV5RedMask;
//   DWORD        bV5GreenMask;
//   DWORD        bV5BlueMask;
//   DWORD        bV5AlphaMask;
//   DWORD        bV5CSType;
//   CIEXYZTRIPLE bV5Endpoints;
//   DWORD        bV5GammaRed;
//   DWORD        bV5GammaGreen;
//   DWORD        bV5GammaBlue;
//   DWORD        bV5Intent;
//   DWORD        bV5ProfileData;
//   DWORD        bV5ProfileSize;
//   DWORD        bV5Reserved;
//} BITMAPV5HEADER,FAR *LPBITMAPV5HEADER,*PBITMAPV5HEADER;
//
//
//
//typedef struct tagBITMAPINFOHEADER{
//   DWORD biSize;
//   LONG  biWidth;
//   LONG  biHeight;
//   WORD  biPlanes;
//   WORD  biBitCount;
//   DWORD biCompression;
//   DWORD biSizeImage;
//   LONG  biXPelsPerMeter;
//   LONG  biYPelsPerMeter;
//   DWORD biClrUsed;
//   DWORD biClrImportant;
//} BITMAPINFOHEADER,*PBITMAPINFOHEADER;
//
//typedef struct tagBITMAPINFO {
//   BITMAPINFOHEADER bmiHeader;
//   RGBQUAD          bmiColors[1];
//} BITMAPINFO,*PBITMAPINFO;
//

//
//// Values for bV5CSType
//#define PROFILE_LINKED          'LINK'
//#define PROFILE_EMBEDDED        'MBED'
//#endif

/* constants for the biCompression field */
#define BI_RGB        0L
#define BI_RLE8       1L
#define BI_RLE4       2L
#define BI_BITFIELDS  3L
#define BI_JPEG       4L
#define BI_PNG        5L
#if (_WIN32_WINNT >= _WIN32_WINNT_NT4)
#endif


struct tagBITMAPINFO;


typedef struct tagBITMAPINFO  FAR *LPBITMAPINFO;


typedef LPBITMAPINFO HBITMAP;

/* DIB color table identifiers */

#define DIB_RGB_COLORS      0 /* color table in RGBs */
#define DIB_PAL_COLORS      1 /* color table in palette indices */


//
// image blt
//

//typedef WINUSHORT COLOR16;
//
//typedef struct _TRIVERTEX
//{
//   LONG    x;
//   LONG    y;
//   COLOR16 Red;
//   COLOR16 Green;
//   COLOR16 Blue;
//   COLOR16 Alpha;
//}TRIVERTEX,*PTRIVERTEX,*LPTRIVERTEX;
//
//typedef struct _GRADIENT_TRIANGLE
//{
//   WINULONG Vertex1;
//   WINULONG Vertex2;
//   WINULONG Vertex3;
//} GRADIENT_TRIANGLE,*PGRADIENT_TRIANGLE,*LPGRADIENT_TRIANGLE;
//
//typedef struct _GRADIENT_RECT
//{
//   WINULONG UpperLeft;
//   WINULONG LowerRight;
//}GRADIENT_RECT,*PGRADIENT_RECT,*LPGRADIENT_RECT;
//
//
//typedef struct _BLENDFUNCTION
//{
//   BYTE   BlendOp;
//   BYTE   BlendFlags;
//   BYTE   SourceConstantAlpha;
//   BYTE   AlphaFormat;
//}BLENDFUNCTION,*PBLENDFUNCTION;


//
// currentlly defined blend function
//

#define AC_SRC_OVER                 0x00

//
// alpha format flags
//

#define AC_SRC_ALPHA                0x01





struct tagLOGRGN;


typedef struct tagLOGRGN  LOGRGN,*PLOGRGN,NEAR *NPLOGRGN,FAR *LPLOGRGN;


typedef LPLOGRGN HRGN;


HBITMAP CreateCompatibleBitmap(HDC hdc,i32 cx,i32 cy);


WINBOOL BitBlt(HDC hdcDest,i32 nXDest,i32 nYDest,i32 nWidth,i32 nHeight,HDC hdcSrc,i32 nXSrc,i32 nYSrc,DWORD dwRop);


//WINBOOL SetViewportOrgEx(HDC hdc, i32 X, i32 Y, LPPOINT lpPoint);



WINBOOL get_client_rect(oswindow hwnd,LPRECT lprect);

WINBOOL get_window_rect(oswindow hwnd,LPRECT lprect);

i32 FillRect(HDC hDC,const RECT *lprc,HBRUSH hbr);

//WINBOOL ReleaseDC(oswindow hwnd,HDC hdc);

//HDC GetWindowDC(oswindow hwnd);


HBRUSH CreateSolidBrush(COLORREF color);

//
///* Enhanced Metafile structures */
//typedef struct tagENHMETARECORD
//{
//   DWORD   iType;              // Record type EMR_XXX
//   DWORD   nSize;              // Record size in bytes
//   DWORD   dParm[1];           // Parameters
//} ENHMETARECORD,*PENHMETARECORD,*LPENHMETARECORD;
//
//typedef struct tagENHMETAHEADER
//{
//   DWORD   iType;              // Record typeEMR_HEADER
//   DWORD   nSize;              // Record size in bytes.  This may be greater
//   // than the sizeof(ENHMETAHEADER).
//   RECTL   rclBounds;          // Inclusive-inclusive bounds in device units
//   RECTL   rclFrame;           // Inclusive-inclusive Picture Frame of metafile in .01 mm units
//   DWORD   dSignature;         // Signature.  Must be ENHMETA_SIGNATURE.
//   DWORD   nVersion;           // Version number
//   DWORD   nBytes;             // Size of the metafile in bytes
//   DWORD   nRecords;           // Number of records in the metafile
//   WORD    nHandles;           // Number of handles in the handle table
//   // Handle index zero is reserved.
//   WORD    sReserved;          // Reserved.  Must be zero.
//   DWORD   nDescription;       // Number of chars in the unicode description string
//   // This is 0 if there is no description string
//   DWORD   offDescription;     // Offset to the metafile description record.
//   // This is 0 if there is no description string
//   DWORD   nPalEntries;        // Number of entries in the metafile palette.
//   SIZEL   szlDevice;          // Size of the context_object device in pels
//   SIZEL   szlMillimeters;     // Size of the context_object device in millimeters
//#if(WINVER >= 0x0400)
//   DWORD   cbPixelFormat;      // Size of PIXELFORMATDESCRIPTOR information
//   // This is 0 if no pixel format is set
//   DWORD   offPixelFormat;     // Offset to PIXELFORMATDESCRIPTOR
//   // This is 0 if no pixel format is set
//   DWORD   bOpenGL;            // TRUE if OpenGL commands are present in
//   // the metafile, otherwise FALSE
//#endif /* WINVER >= 0x0400 */
//#if(WINVER >= 0x0500)
//   SIZEL   szlMicrometers;     // Size of the context_object device in micrometers
//#endif /* WINVER >= 0x0500 */
//
//} ENHMETAHEADER,*PENHMETAHEADER,*LPENHMETAHEADER;
//
//
//


/* Region Flags */
#define ERROR               0
#define NULLREGION          1
#define SIMPLEREGION        2
#define COMPLEXREGION       3
#define RGN_ERROR ERROR

/* CombineRgn() Styles */
#define RGN_AND             1
#define RGN_OR              2
#define RGN_XOR             3
#define RGN_DIFF            4
#define RGN_COPY            5
#define RGN_MIN             RGN_AND
#define RGN_MAX             RGN_COPY

/* StretchBlt() Modes */
#define BLACKONWHITE                 1
#define WHITEONBLACK                 2
#define COLORONCOLOR                 3
#define HALFTONE                     4
#define MAXSTRETCHBLTMODE            4


/* StretchBlt() Modes */
#define BLACKONWHITE                 1
#define WHITEONBLACK                 2
#define COLORONCOLOR                 3
#define HALFTONE                     4
#define MAXSTRETCHBLTMODE            4


