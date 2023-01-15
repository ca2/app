// Created by camilo on 2022-08-27 15:59 <3ThomasBorregaardSørensen!!
#pragma once



#define CBRS_DRAGMOVE            0x01000000L
/*#undef CBRS_ALL
#define CBRS_ALL            0x0140ffffL*/





// Standard control bars (IDW = interaction_impl ID)
#define __IDW_CONTROLBAR_FIRST        0xE800
#define __IDW_CONTROLBAR_LAST         0xE8FF

#define __IDW_TOOLBAR                 0xE800  // main Toolbar for interaction_impl
//#define "status_bar"              0xE801  // Status bar interaction_impl
#define __IDW_PREVIEW_BAR             0xE802  // PrintThumbnail Dialog Bar
#define __IDW_RESIZE_BAR              0xE803  // OLE in-place resize bar
#define __IDW_REBAR                   0xE804  // COMCTL32 "rebar" Bar
#define __IDW_DIALOGBAR               0xE805  // dialogBar

// Note: If your application supports docking toolbars, you should
//  not use the following IDs for your own toolbars.  The IDs chosen
//  are at the top of the first 32 such that the bars will be hidden
//  while in print thumbnail mode, and are not likely to conflict with
//  IDs your application may have used succesfully in the past.

#define __IDW_DOCKBAR_TOP             0xE81B
#define __IDW_DOCKBAR_LEFT            0xE81C
#define __IDW_DOCKBAR_RIGHT           0xE81D
#define __IDW_DOCKBAR_BOTTOM          0xE81E
#define __IDW_DOCKBAR_FLOAT           0xE81F

// Macro for mapping standard control bars to bitmask (limit of 32)
#define __CONTROLBAR_MASK(nIDC)   (1L << (nIDC - __IDW_CONTROLBAR_FIRST))



// on_layout Modes for CalcDynamicLayout
#define LM_STRETCH  0x01    // same meaning as bStretch in CalcFixedLayout.  If set, ignores nLength
// and returns dimensions based on LM_HORZ state, otherwise LM_HORZ is used
// to determine if nLength is the desired horizontal or vertical length
// and dimensions are returned based on nLength
#define LM_HORZ     0x02    // same as bHorz in CalcFixedLayout
#define LM_MRUWIDTH 0x04    // Most Recently Used Dynamic width
#define LM_HORZDOCK 0x08    // Horizontal Docked Dimensions
#define LM_VERTDOCK 0x10    // Vertical Docked Dimensions
#define LM_LENGTHY  0x20    // set if nLength is a height instead of a width
#define LM_COMMIT   0x40    // Remember MRUWidth


#ifndef CCS_TOP

// begin_r_commctrl

//====== COMMON CONTROL STYLES ================================================

#define CCS_TOP                 0x00000001L
#define CCS_NOMOVEY             0x00000002L
#define CCS_BOTTOM              0x00000003L
#define CCS_NORESIZE            0x00000004L
#define CCS_NOPARENTALIGN       0x00000008L
#define CCS_ADJUSTABLE          0x00000020L
#define CCS_NODIVIDER           0x00000040L
#define CCS_VERT                0x00000080L
#define CCS_LEFT                (CCS_VERT | CCS_TOP)
#define CCS_RIGHT               (CCS_VERT | CCS_BOTTOM)
#define CCS_NOMOVEX             (CCS_VERT | CCS_NOMOVEY)

// end_r_commctrl

//====== SysLink control =========================================

#ifdef _WIN32
#if (NTDDI_VERSION >= NTDDI_WINXP)

#define INVALID_LINK_INDEX  (-1)
#define MAX_LINKID_TEXT     48
#define L_MAX_URL_LENGTH    (2048 + 32 + sizeof("://"))

#define WC_LINK         L"SysLink"

// begin_r_commctrl

#define LWS_TRANSPARENT     0x0001
#define LWS_IGNORERETURN    0x0002
#if (NTDDI_VERSION >= NTDDI_VISTA)
#define LWS_NOPREFIX        0x0004
#define LWS_USEVISUALSTYLE  0x0008
#define LWS_USECUSTOMTEXT   0x0010
#define LWS_RIGHT           0x0020
#endif // (NTDDI_VERSION >= NTDDI_VISTA)

// end_r_commctrl

#define LIF_ITEMINDEX    0x00000001
#define LIF_STATE        0x00000002
#define LIF_ITEMID       0x00000004
#define LIF_URL          0x00000008

#define LIS_FOCUSED         0x00000001
#define LIS_ENABLED         0x00000002
#define LIS_VISITED         0x00000004
#if (NTDDI_VERSION >= NTDDI_VISTA)
#define LIS_HOTTRACK        0x00000008
#define LIS_DEFAULTCOLORS   0x00000010 // Don't use any custom text colors
#endif

#endif

#endif

#endif



#define WM_SETMESSAGESTRING 0x0362  // wParam = nIDS (or 0),



