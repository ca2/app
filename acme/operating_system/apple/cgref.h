//
//  cgref.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 18/06/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#pragma once


#include "acme/operating_system/apple/cfref.h"

#include <CoreGraphics/CoreGraphics.h>
#include <CoreText/CoreText.h>

template < >
inline CGColorRef cfref_retain<CGColorRef>(CGColorRef cgcolorref) { ::CGColorRetain(cgcolorref); }

template < >
inline void cfref_release<CGColorRef>(CGColorRef cgcolorref) { ::CGColorRelease(cgcolorref); }

using cgcolorref = cfref<CGColorRef>;


template < >
inline CGColorSpaceRef cfref_retain<CGColorSpaceRef>(CGColorSpaceRef cgcolorspaceref) { ::CGColorSpaceRetain(cgcolorspaceref); }

template < >
inline void cfref_release<CGColorSpaceRef>(CGColorSpaceRef cgcolorspaceref) { ::CGColorSpaceRelease(cgcolorspaceref); }

using cgcolorspaceref = cfref<CGColorSpaceRef >;

//template < >
//inline CTLineRef cfref_retain<CTLineRef>(CTLineRef ctlineref) { CTLineRetain(ctlineref); }
//
//template < >
//inline void cfref_release<CTLineRef>(CTLineRef ctlineref) { ::CFRelease(ctlineref); }
//
//using ctlineref = cfref<CTLineRef >;
//template < >
//inline auto cftransfer<CTLineRef>(CTLineRef ctlineref)
//{
//   
//   return ::ref <::cftyperef> {transfer_t{}, new ::cftyperef(ctlineref)};
//   
//}


//template < >
//inline CTFontRef cfref_retain<CTFontRef>(CTFontRef ctfontref) { ::CTFontRetain(ctfontref); }
//
//template < >
//inline void cfref_release<CTFontRef>(CTFontRef ctfontref) { ::CFRelease(ctfontref); }


template < >
inline CGContextRef cfref_retain<CGContextRef>(CGContextRef cgcontextref) { ::CGContextRetain(cgcontextref); }

template < >
inline void cfref_release<CGContextRef>(CGContextRef cgcontextref) { ::CGContextRelease(cgcontextref); }


template < >
inline CGLayerRef cfref_retain<CGLayerRef>(CGLayerRef cglayerref) { ::CGLayerRetain(cglayerref); }

template < >
inline void cfref_release<CGLayerRef>(CGLayerRef cglayerref) { ::CGLayerRelease(cglayerref); }


template < >
inline CGPathRef cfref_retain<CGPathRef>(CGPathRef cgpathref) { ::CGPathRetain(cgpathref); }

template < >
inline void cfref_release<CGPathRef>(CGPathRef cgpathref) { ::CGPathRelease(cgpathref); }



