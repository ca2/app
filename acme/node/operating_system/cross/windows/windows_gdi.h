#pragma once



struct gdi_object;


struct gdi_enhanced_meta_file;


typedef struct gdi_enhanced_meta_file * HENHMETAFILE;


struct tagEXTLOGPEN;


struct tagLOGBRUSH;


struct tagLOGRGN;

//
//struct POINT_I32
//{
//
//   ::i32  x;
//   ::i32  y;
//
//};
//
//
//typedef POINT_I32 * LPPOINT32;


/* Ternary raster operations */
#define SRCCOPY             (::u32)0x00CC0020 /* dest = source                   */
#define SRCPAINT            (::u32)0x00EE0086 /* dest = source OR dest           */
#define SRcaND              (::u32)0x008800C6 /* dest = source AND dest          */
#define SRCINVERT           (::u32)0x00660046 /* dest = source XOR dest          */
#define SRCERASE            (::u32)0x00440328 /* dest = source AND (NOT dest )   */
#define NOTSRCCOPY          (::u32)0x00330008 /* dest = (NOT source)             */
#define NOTSRCERASE         (::u32)0x001100A6 /* dest = (NOT src) AND (NOT dest) */
#define MERGECOPY           (::u32)0x00C000ca /* dest = (source AND pattern)     */
#define MERGEPAINT          (::u32)0x00BB0226 /* dest = (NOT source) OR dest     */
#define PATCOPY             (::u32)0x00F00021 /* dest = pattern                  */
#define PATPAINT            (::u32)0x00FB0A09 /* dest = DPSnoo                   */
#define PATINVERT           (::u32)0x005A0049 /* dest = pattern XOR dest         */
#define DSTINVERT           (::u32)0x00550009 /* dest = (NOT dest)               */
#define BLACKNESS           (::u32)0x00000042 /* dest = BLACK                    */
#define WHITENESS           (::u32)0x00FF0062 /* dest = WHITE                    */
#if(WINVER >= 0x0500)

#define NOMIRRORBITMAP               (::u32)0x80000000 /* Do not Mirror the bitmap in this call */
#define caPTUREBLT                   (::u32)0x40000000 /* Include layered windows */
#endif /* WINVER >= 0x0500 */



/* Logcolorspace lcsType values */

#define LCS_sRGB                'sRGB'
#define LCS_WINDOWS_COLOR_SPACE 'Win '  // Windows default color space

typedef ::i32   LCSCSTYPE;
#define LCS_caLIBRATED_RGB              0x00000000L

typedef ::i32    LCSGAMUTMATCH;
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

/* Macros to retrieve CMYK values from a color32_t */
#define GetKValue(cmyk)      ((byte)(cmyk))
#define GetYValue(cmyk)      ((byte)((cmyk)>> 8))
#define GetMValue(cmyk)      ((byte)((cmyk)>>16))
#define GetCValue(cmyk)      ((byte)((cmyk)>>24))

#define CMYK(c,m,y,k)       ((color32_t)((((byte)(k)|((::u16)((byte)(y))<<8))|(((::u32)(byte)(m))<<16))|(((::u32)(byte)(c))<<24)))

typedef long            FXPT16DOT16,*LPFXPT16DOT16;
typedef long            FXPT2DOT30,*LPFXPT2DOT30;




/* xform stuff */
#define MWT_IDENTITY        1
#define MWT_LEFTMULTIPLY    2
#define MWT_RIGHTMULTIPLY   3

#define MWT_MIN             MWT_IDENTITY
#define MWT_MAX             MWT_RIGHTMULTIPLY

#define _XFORM_
typedef struct  tagXFORM
{
   FLOAT   eM11;
   FLOAT   eM12;
   FLOAT   eM21;
   FLOAT   eM22;
   FLOAT   eDx;
   FLOAT   eDy;
} XFORM,*PXFORM,*LPXFORM;

/* Bitmap Header Definition */
typedef struct tagBITMAP
{
   ::i32        bmType;
   ::i32        bmWidth;
   ::i32        bmHeight;
   ::i32        bmWidthBytes;
   ::u16        bmPlanes;
   ::u16        bmBitsPixel;
   LPVOID      bmBits;
} BITMAP,*PBITMAP,*NPBITMAP,*LPBITMAP;

////#include <pshpack1.h>
//typedef struct tagRGBTRIPLE {
//   byte    rgbtBlue;
//   byte    rgbtGreen;
//   byte    rgbtRed;
//} RGBTRIPLE,*PRGBTRIPLE,*NPRGBTRIPLE,*LPRGBTRIPLE;
////#include "poppack.h"


/* ICM Color Definitions */
// The following two structures are used for defining rgb's in terms of CIEXYZ.

typedef struct tagCIEXYZ
{
   FXPT2DOT30 ciexyzX;
   FXPT2DOT30 ciexyzY;
   FXPT2DOT30 ciexyzZ;
} CIEXYZ;
typedef CIEXYZ  *LPCIEXYZ;

typedef struct tagICEXYZTRIPLE
{
   CIEXYZ  ciexyzRed;
   CIEXYZ  ciexyzGreen;
   CIEXYZ  ciexyzBlue;
} CIEXYZTRIPLE;
typedef CIEXYZTRIPLE    *LPCIEXYZTRIPLE;

//#ifdef LINUX
//#define BOOL int
//#endif

//typedef ::u32   color32_t;
//typedef ::u32   *LPCOLORREF;



typedef struct tagPALETTEENTRY {
   byte        peRed;
   byte        peGreen;
   byte        peBlue;
   byte        peFlags;
} PALETTEENTRY,*PPALETTEENTRY,*LPPALETTEENTRY;

/* Logical Palette */
typedef struct tagLOGPALETTE {
   ::u16                palVersion;
   ::u16                palNumEntries;
   PALETTEENTRY        palPalEntry[1];
} LOGPALETTE,*PLOGPALETTE,*NPLOGPALETTE,*LPLOGPALETTE;


/* Logical Font */
#define LF_FACESIZE         32


struct  tagLOGFONTA
{
   ::i32      lfHeight;
   ::i32      lfWidth;
   ::i32      lfEscapement;
   ::i32      lfOrientation;
   ::i32      lfWeight;
   byte      lfItalic;
   byte      lfUnderline;
   byte      lfStrikeOut;
   byte      lfCharSet;
   byte      lfOutPrecision;
   byte      lfClipPrecision;
   byte      lfQuality;
   byte      lfPitchAndFamily;
   char      lfFaceName[LF_FACESIZE];
};


//struct tagLOGFONTW
//{
//   ::i32      lfHeight;
//   ::i32      lfWidth;
//   ::i32      lfEscapement;
//   ::i32      lfOrientation;
//   ::i32      lfWeight;
//   byte      lfItalic;
//   byte      lfUnderline;
//   byte      lfStrikeOut;
//   byte      lfCharSet;
//   byte      lfOutPrecision;
//   byte      lfClipPrecision;
//   byte      lfQuality;
//   byte      lfPitchAndFamily;
//   unichar   lfFaceName[LF_FACESIZE];
//};


typedef struct tagLOGFONTA LOGFONTA,*PLOGFONTA,*NPLOGFONTA,*LPLOGFONTA;


typedef struct tagLOGFONTW LOGFONTW,*PLOGFONTW,*NPLOGFONTW,*LPLOGFONTW;


struct tagFONTA;


struct tagFONTW;


typedef struct tagFONTA FONTA,* PFONTA,* NPFONTA,* LPFONTA;


typedef struct tagFONTW FONTW,* PFONTW,* NPFONTW,* LPFONTW;


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
#define e_font_weight_normal           400
#define FW_MEDIUM           500
#define FW_SEMIBOLD         600
#define e_font_weight_bold             700
#define FW_EXTRABOLD        800
#define FW_HEAVY            900

#define FW_ULTRALIGHT       FW_EXTRALIGHT
#define FW_REGULAR          e_font_weight_normal
#define FW_DEMIBOLD         FW_SEMIBOLD
#define FW_ULTRABOLD        FW_EXTRABOLD
#define FW_BLACK            FW_HEAVY



typedef struct tagTEXTMETRIca
{
   ::i32        tmHeight;
   ::i32        tmAscent;
   ::i32        tmDescent;
   ::i32        tmInternalLeading;
   ::i32        tmExternalLeading;
   ::i32        tmAveCharWidth;
   ::i32        tmMaxCharWidth;
   ::i32        tmWeight;
   ::i32        tmOverhang;
   ::i32        tmDigitizedAspectX;
   ::i32        tmDigitizedAspectY;
   byte        tmFirstChar;
   byte        tmLastChar;
   byte        tmDefaultChar;
   byte        tmBreakChar;
   byte        tmItalic;
   byte        tmUnderlined;
   byte        tmStruckOut;
   byte        tmPitchAndFamily;
   byte        tmCharSet;
} TEXTMETRIca,*PTEXTMETRIca,*NPTEXTMETRIca,*LPTEXTMETRIca;
typedef struct tagTEXTMETRICW
{
   ::i32        tmHeight;
   ::i32        tmAscent;
   ::i32        tmDescent;
   ::i32        tmInternalLeading;
   ::i32        tmExternalLeading;
   ::i32        tmAveCharWidth;
   ::i32        tmMaxCharWidth;
   ::i32        tmWeight;
   ::i32        tmOverhang;
   ::i32        tmDigitizedAspectX;
   ::i32        tmDigitizedAspectY;
   WCHAR       tmFirstChar;
   WCHAR       tmLastChar;
   WCHAR       tmDefaultChar;
   WCHAR       tmBreakChar;
   byte        tmItalic;
   byte        tmUnderlined;
   byte        tmStruckOut;
   byte        tmPitchAndFamily;
   byte        tmCharSet;
} TEXTMETRICW,*PTEXTMETRICW,*NPTEXTMETRICW,*LPTEXTMETRICW;
#ifdef UNICODE
typedef TEXTMETRICW TEXTMETRIC;
typedef PTEXTMETRICW PTEXTMETRIC;
typedef NPTEXTMETRICW NPTEXTMETRIC;
typedef LPTEXTMETRICW LPTEXTMETRIC;
#else
typedef TEXTMETRIca TEXTMETRIC;
typedef PTEXTMETRIca PTEXTMETRIC;
typedef NPTEXTMETRIca NPTEXTMETRIC;
typedef LPTEXTMETRIca LPTEXTMETRIC;
#endif // UNICODE



/* Pel Array */
typedef struct tagPELARRAY
{
   ::i32        paXCount;
   ::i32        paYCount;
   ::i32        paXExt;
   ::i32        paYExt;
   byte        paRGBs;
} PELARRAY,*PPELARRAY,*NPPELARRAY,*LPPELARRAY;

/* Logical Brush (or Pattern) */
typedef struct tagLOGBRUSH
{
   ::u32        lbStyle;
   color32_t    lbColor;
   ulong_ptr   lbHatch;
} LOGBRUSH,*PLOGBRUSH,*NPLOGBRUSH,*LPLOGBRUSH;

//typedef struct tagLOGBRUSH32
//{
//   ::u32        lbStyle;
//   color32_t    lbColor;
//   WINULONG       lbHatch;
//} LOGBRUSH32,*PLOGBRUSH32,*NPLOGBRUSH32,*LPLOGBRUSH32;
//

typedef LOGBRUSH            PATTERN;
typedef PATTERN             *PPATTERN;
typedef PATTERN         *NPPATTERN;
typedef PATTERN          *LPPATTERN;


/* Logical Pen */
typedef struct tagLOGPEN
{
   ::u32        lopnStyle;
   POINT_I32       lopnWidth;
   color32_t    lopnColor;
} LOGPEN,*PLOGPEN,*NPLOGPEN,*LPLOGPEN;



struct tagEXTLOGPEN;

typedef struct tagEXTLOGPEN  EXTLOGPEN,*PEXTLOGPEN,*NPEXTLOGPEN,*LPEXTLOGPEN;

typedef LPEXTLOGPEN HPEN;

/* Pen Styles */
#define PS_SOLID            0
#define PS_DASH             1       /* -------  */
#define PS_DOT              2       /* .......  */
#define PS_DASHDOT          3       /* _._._._  */
#define PS_DASHDOTDOT       4       /* _.._.._  */
#define PS_NULL             5
#define PS_INSIDEFRAME      6
#define PS_USERSTYLE        7
#define PS_ALTERNATE        8
#define PS_STYLE_MASK       0x0000000F

#define PS_ENDcaP_ROUND     0x00000000
#define PS_ENDcaP_SQUARE    0x00000100
#define PS_ENDcaP_FLAT      0x00000200
#define PS_ENDcaP_MASK      0x00000F00

#define PS_JOIN_ROUND       0x00000000
#define PS_JOIN_BEVEL       0x00001000
#define PS_JOIN_MITER       0x00002000
#define PS_JOIN_MASK        0x0000F000

#define PS_COSMETIC         0x00000000
#define PS_GEOMETRIC        0x00010000
#define PS_TYPE_MASK        0x000F0000

#define AD_COUNTERCLOCKWISE 1
#define AD_CLOCKWISE        2

//#define rgb(r,g,b)          ((color32_t)(((byte)(r)|((::u16)((byte)(g))<<8))|(((::u32)(byte)(b))<<16)))

//#define GetRValue(rgb)      (__LOBYTE(rgb))
//#define GetGValue(rgb)      (__LOBYTE(((::u16)(rgb)) >> 8))
//#define GetBValue(rgb)      (__LOBYTE((rgb)>>16))

/* Background Modes */
#define TRANSPARENT         1
#define OPAQUE              2
#define BKMODE_LAST         2



struct tagEXTLOGBRUSH;

typedef struct tagEXTLOGBRUSH  EXTLOGBRUSH,*PEXTLOGBRUSH,*NPEXTLOGBRUSH,*LPEXTLOGBRUSH;

typedef LPEXTLOGBRUSH HBRUSH;


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

/* structures for defining DIBs */
typedef struct tagBITMAPCOREHEADER {
   ::u32   bcSize;                 /* used to get to color table */
   ::u16    bcWidth;
   ::u16    bcHeight;
   ::u16    bcPlanes;
   ::u16    bcBitCount;
} BITMAPCOREHEADER,*LPBITMAPCOREHEADER,*PBITMAPCOREHEADER;

typedef struct tagBITMAPINFOHEADER{
   ::u32      biSize;
   ::i32       biWidth;
   ::i32       biHeight;
   ::u16       biPlanes;
   ::u16       biBitCount;
   ::u32      biCompression;
   ::u32      biSizeImage;
   ::i32       biXPelsPerMeter;
   ::i32       biYPelsPerMeter;
   ::u32      biClrUsed;
   ::u32      biClrImportant;
} BITMAPINFOHEADER,*LPBITMAPINFOHEADER,*PBITMAPINFOHEADER;

typedef struct tagBITMAPINFO {
   BITMAPINFOHEADER bmiHeader;
   WINRGBQUAD       bmiColors[1];
} BITMAPINFO,*PBITMAPINFO;


#if(WINVER >= 0x0400)
typedef struct {
   ::u32        bV4Size;
   ::i32         bV4Width;
   ::i32         bV4Height;
   ::u16         bV4Planes;
   ::u16         bV4BitCount;
   ::u32        bV4V4Compression;
   ::u32        bV4SizeImage;
   ::i32         bV4XPelsPerMeter;
   ::i32         bV4YPelsPerMeter;
   ::u32        bV4ClrUsed;
   ::u32        bV4ClrImportant;
   ::u32        bV4RedMask;
   ::u32        bV4GreenMask;
   ::u32        bV4BlueMask;
   ::u32        bV4AlphaMask;
   ::u32        bV4CSType;
   CIEXYZTRIPLE bV4Endpoints;
   ::u32        bV4GammaRed;
   ::u32        bV4GammaGreen;
   ::u32        bV4GammaBlue;
} BITMAPV4HEADER,*LPBITMAPV4HEADER,*PBITMAPV4HEADER;
#endif /* WINVER >= 0x0400 */

#if (WINVER >= 0x0500)
typedef struct {
   ::u32        bV5Size;
   ::i32         bV5Width;
   ::i32         bV5Height;
   ::u16         bV5Planes;
   ::u16         bV5BitCount;
   ::u32        bV5Compression;
   ::u32        bV5SizeImage;
   ::i32         bV5XPelsPerMeter;
   ::i32         bV5YPelsPerMeter;
   ::u32        bV5ClrUsed;
   ::u32        bV5ClrImportant;
   ::u32        bV5RedMask;
   ::u32        bV5GreenMask;
   ::u32        bV5BlueMask;
   ::u32        bV5AlphaMask;
   ::u32        bV5CSType;
   CIEXYZTRIPLE bV5Endpoints;
   ::u32        bV5GammaRed;
   ::u32        bV5GammaGreen;
   ::u32        bV5GammaBlue;
   ::u32        bV5Intent;
   ::u32        bV5ProfileData;
   ::u32        bV5ProfileSize;
   ::u32        bV5Reserved;
} BITMAPV5HEADER,*LPBITMAPV5HEADER,*PBITMAPV5HEADER;



typedef struct tagBITMAPINFOHEADER{
   ::u32 biSize;
   ::i32  biWidth;
   ::i32  biHeight;
   ::u16  biPlanes;
   ::u16  biBitCount;
   ::u32 biCompression;
   ::u32 biSizeImage;
   ::i32  biXPelsPerMeter;
   ::i32  biYPelsPerMeter;
   ::u32 biClrUsed;
   ::u32 biClrImportant;
} BITMAPINFOHEADER,*PBITMAPINFOHEADER;

typedef struct tagBITMAPINFO {
   BITMAPINFOHEADER bmiHeader;
   RGBQUAD          bmiColors[1];
} BITMAPINFO,*PBITMAPINFO;



// Values for bV5CSType
#define PROFILE_LINKED          'LINK'
#define PROFILE_EMBEDDED        'MBED'
#endif

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


typedef struct tagBITMAPINFO  *LPBITMAPINFO;


typedef LPBITMAPINFO HBITMAP;

/* DIB color table identifiers */

#define DIB_RGB_COLORS      0 /* color table in RGBs */
#define DIB_PAL_COLORS      1 /* color table in palette indices */


//
// image blt
//

typedef WINUSHORT COLOR16;

typedef struct _TRIVERTEX
{
   ::i32    x;
   ::i32    y;
   COLOR16 Red;
   COLOR16 Green;
   COLOR16 Blue;
   COLOR16 Alpha;
}TRIVERTEX,*PTRIVERTEX,*LPTRIVERTEX;

typedef struct _GRADIENT_TRIANGLE
{
   WINULONG Vertex1;
   WINULONG Vertex2;
   WINULONG Vertex3;
} GRADIENT_TRIANGLE,*PGRADIENT_TRIANGLE,*LPGRADIENT_TRIANGLE;

typedef struct _GRADIENT_RECT
{
   WINULONG UpperLeft;
   WINULONG LowerRight;
}GRADIENT_RECT,*PGRADIENT_RECT,*LPGRADIENT_RECT;


typedef struct _BLENDFUNCTION
{
   byte   BlendOp;
   byte   BlendFlags;
   byte   SourceConstantAlpha;
   byte   AlphaFormat;
}BLENDFUNCTION,*PBLENDFUNCTION;


//
// currentlly defined blend function
//

#define AC_SRC_OVER                 0x00

//
// alpha format flags
//

#define AC_SRC_ALPHA                0x01





struct tagLOGRGN;


typedef struct tagLOGRGN  LOGRGN,*PLOGRGN,*NPLOGRGN,*LPLOGRGN;


typedef LPLOGRGN HRGN;


HBITMAP CreateCompatibleBitmap(HDC hdc,i32 cx,i32 cy);


int_bool BitBlt(HDC hdcDest,i32 nXDest,i32 nYDest,i32 nWidth,i32 nHeight,HDC hdcSrc,i32 nXSrc,i32 nYSrc,::u32 dwRop);


//int_bool SetViewportOrgEx(HDC hdc, i32 X, i32 Y, POINT_I32 * lpPoint);



//int_bool get_client_rect(oswindow hwnd,RECTANGLE_I32 * lprect);

//int_bool get_window_rect(oswindow hwnd,RECTANGLE_I32 * lprect);

i32 FillRect(HDC hDC,const RECTANGLE_I32 *lprc,HBRUSH hbr);

//int_bool ReleaseDC(oswindow hwnd,HDC hdc);

//HDC GetWindowDC(oswindow hwnd);


HBRUSH CreateSolidBrush(color32_t color);


/* Enhanced Metafile structures */
typedef struct tagENHMETARECORD
{
   ::u32   iType;              // Record type EMR_XXX
   ::u32   nSize;              // Record size_i32 in bytes
   ::u32   dParm[1];           // Parameters
} ENHMETARECORD,*PENHMETARECORD,*LPENHMETARECORD;

typedef struct tagENHMETAHEADER
{
   ::u32   iType;              // Record typeEMR_HEADER
   ::u32   nSize;              // Record size_i32 in bytes.  This may be greater
   // than the sizeof(ENHMETAHEADER).
   RECTL   rclBounds;          // Inclusive-inclusive bounds in device units
   RECTL   rclFrame;           // Inclusive-inclusive Picture Frame of metafile in .01 mm units
   ::u32   dSignature;         // Signature.  Must be ENHMETA_SIGNATURE.
   ::u32   nVersion;           // Version number
   ::u32   nBytes;             // Size of the metafile in bytes
   ::u32   nRecords;           // Number of records in the metafile
   ::u16    nHandles;           // Number of handles in the handle table
   // Handle index zero is reserved.
   ::u16    sReserved;          // Reserved.  Must be zero.
   ::u32   nDescription;       // Number of chars in the unicode description string
   // This is 0 if there is no description string
   ::u32   offDescription;     // Offset to the metafile description record.
   // This is 0 if there is no description string
   ::u32   nPalEntries;        // Number of entries in the metafile palette.
   SIZEL   szlDevice;          // Size of the matter device in pels
   SIZEL   szlMillimeters;     // Size of the matter device in millimeters
#if(WINVER >= 0x0400)
   ::u32   cbPixelFormat;      // Size of PIXELFORMATDESCRIPTOR information
   // This is 0 if no pixel format is set
   ::u32   offPixelFormat;     // Offset to PIXELFORMATDESCRIPTOR
   // This is 0 if no pixel format is set
   ::u32   bOpenGL;            // true if OpenGL commands are present in
   // the metafile, otherwise false
#endif /* WINVER >= 0x0400 */
#if(WINVER >= 0x0500)
   SIZEL   szlMicrometers;     // Size of the matter device in micrometers
#endif /* WINVER >= 0x0500 */

} ENHMETAHEADER,*PENHMETAHEADER,*LPENHMETAHEADER;





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
//#define e_interpolation_mode_high_quality_bicubic                     4
#define MAXSTRETCHBLTMODE            4


/* StretchBlt() Modes */
#define BLACKONWHITE                 1
#define WHITEONBLACK                 2
#define COLORONCOLOR                 3
//#define e_interpolation_mode_high_quality_bicubic                     4
#define MAXSTRETCHBLTMODE            4


