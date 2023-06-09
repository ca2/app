/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * Windows GDI
 *
 * Copyright 2009-2011 Jay Sorg
 * Copyright 2010-2011 Vic Lee
 * Copyright 2010-2011 Marc-Andre Moreau <marcandre.moreau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>

#include <string.h>
#include <conio.h>

#include <freerdp/log.h>
#include <freerdp/gdi/gdi.h>
#include <freerdp/constants.h>
#include <freerdp/codec/color.h>
#include <freerdp/codec/bitmap.h>
#include <freerdp/codec/rfx.h>
#include <freerdp/codec/nsc.h>

#include "wf_client.h"
#include "wf_graphics.h"
#include "wf_gdi.h"

#define TAG CLIENT_TAG("windows.gdi")

const byte wf_rop2_table[] =
{
	R2_BLACK,       /* 0 */
	R2_NOTMERGEPEN, /* DPon */
	R2_MASKNOTPEN,  /* DPna */
	R2_NOTCOPYPEN,  /* Pn */
	R2_MASKPENNOT,  /* PDna */
	R2_NOT,         /* Dn */
	R2_XORPEN,      /* DPx */
	R2_NOTMASKPEN,  /* DPan */
	R2_MASKPEN,     /* DPa */
	R2_NOTXORPEN,   /* DPxn */
	R2_NOP,         /* D */
	R2_MERGENOTPEN, /* DPno */
	R2_COPYPEN,     /* P */
	R2_MERGEPENNOT, /* PDno */
	R2_MERGEPEN,    /* PDo */
	R2_WHITE,       /* 1 */
};

BOOL wf_set_rop2(HDC hdc, int rop2)
{
	if ((rop2 < 0x01) || (rop2 > 0x10))
	{
		WLog_ERR(TAG,  "Unsupported ROP2: %d", rop2);
		return false;
	}

	SetROP2(hdc, wf_rop2_table[rop2 - 1]);

	return true;
}

wfBitmap* wf_glyph_new(wfContext* wfc, GLYPH_DATA* glyph)
{
	wfBitmap* glyph_bmp;
	glyph_bmp = wf_image_new(wfc, glyph->cx(), glyph->cy(), 1, glyph->aj);
	return glyph_bmp;
}

void wf_glyph_free(wfBitmap* glyph)
{
	wf_image_free(glyph);
}

byte* wf_glyph_convert(wfContext* wfc, int width, int height, byte* data)
{
	int indexx;
	int indexy;
	byte* src;
	byte* dst;
	byte* cdata;
	int src_bytes_per_row;
	int dst_bytes_per_row;

	src_bytes_per_row = (width + 7) / 8;
	dst_bytes_per_row = src_bytes_per_row + (src_bytes_per_row % 2);
	cdata = (byte *) malloc(dst_bytes_per_row * height);

	src = data;
	for (indexy = 0; indexy < height; indexy++)
	{
		dst = cdata + indexy * dst_bytes_per_row;

		for (indexx = 0; indexx < dst_bytes_per_row; indexx++)
		{
			if (indexx < src_bytes_per_row)
				*dst++ = *src++;
			else
				*dst++ = 0;
		}
	}

	return cdata;
}

//HBRUSH wf_create_brush(wfContext* wfc, rdpBrush* brush, ::u32 color, int bpp)
//{
//	int i;
//	HBRUSH br;
//	LOGBRUSH lbr;
//	byte* cdata;
//	byte ipattern[8];
//	HBITMAP pattern = nullptr;
//
//	lbr.lbStyle = brush->style;
//
//	if (lbr.lbStyle == BS_DIBPATTERN || lbr.lbStyle == BS_DIBPATTERN8X8 || lbr.lbStyle == BS_DIBPATTERNPT)
//		lbr.lbColor = DIB_RGB_COLORS;
//	else
//		lbr.lbColor = color;
//
//	if (lbr.lbStyle == BS_PATTERN || lbr.lbStyle == BS_PATTERN8X8)
//	{
//		if (brush->bpp > 1)
//		{
//			pattern = wf_create_dib(wfc, 8, 8, bpp, brush->data, nullptr);
//			lbr.lbHatch = (ULONG_PTR) pattern;
//		}
//		else
//		{
//			for (i = 0; i != 8; i++)
//				ipattern[7 - i] = brush->data[i];
//
//			cdata = wf_glyph_convert(wfc, 8, 8, ipattern);
//			pattern = CreateBitmap(8, 8, 1, 1, cdata);
//			lbr.lbHatch = (ULONG_PTR) pattern;
//			free(cdata);
//		}
//	}
//	else if (lbr.lbStyle == BS_HATCHED)
//	{
//		lbr.lbHatch = brush->hatch;
//	}
//	else
//	{
//		lbr.lbHatch = 0;
//	}
//
//	br = CreateBrushIndirect(&lbr);
//	SetBrushOrgEx(wfc->drawing->hdc, brush->x, brush->y, nullptr);
//
//	if (pattern != nullptr)
//		DeleteObject(pattern);
//
//	return br;
//}

void wf_scale_rect(wfContext* wfc, ::rectangle_i32* source)
{
	int ww, wh, dw, dh;

	if (!wfc->client_width)
		wfc->client_width = wfc->width;

	if (!wfc->client_height)
		wfc->client_height = wfc->height;

	ww = wfc->client_width;
	wh = wfc->client_height;
	dw = wfc->instance->settings->DesktopWidth;
	dh = wfc->instance->settings->DesktopHeight;

	if (!ww)
		ww = dw;

	if (!wh)
		wh = dh;

	if (wfc->instance->settings->SmartSizing && (ww != dw || wh != dh))
	{
		source->bottom = source->bottom * wh / dh + 20;
		source->top = source->top * wh / dh - 20;
		source->left = source->left * ww / dw - 20;
		source->right = source->right * ww / dw + 20;
	}

	source->bottom -= wfc->yCurrentScroll;
	source->top -= wfc->yCurrentScroll;
	source->left -= wfc->xCurrentScroll;
	source->right -= wfc->xCurrentScroll;
}

void wf_invalidate_region(wfContext* wfc, int x, int y, int width, int height)
{
	::rectangle_i32 rectangle_i32;

	wfc->update_rect.left = x + wfc->offset_x;
	wfc->update_rect.top = y + wfc->offset_y;
	wfc->update_rect.right = wfc->update_rect.left + width;
	wfc->update_rect.bottom = wfc->update_rect.top + height;

	wf_scale_rect(wfc, &(wfc->update_rect));
	InvalidateRect(wfc->hwnd, &(wfc->update_rect), false);

	rectangle.left = x;
	rectangle.right = width;
	rectangle.top = y;
	rectangle.bottom = height;
	wf_scale_rect(wfc, &rectangle);
	gdi_InvalidateRegion(wfc->hdc, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);
}

void wf_update_offset(wfContext* wfc)
{
	if (wfc->fullscreen)
	{
		if (wfc->instance->settings->UseMultimon)
		{
			int x = GetSystemMetrics(SM_XVIRTUALSCREEN);
			int y = GetSystemMetrics(SM_YVIRTUALSCREEN);
			int w = GetSystemMetrics(SM_CXVIRTUALSCREEN);
			int h = GetSystemMetrics(SM_CYVIRTUALSCREEN);

			wfc->offset_x = (w - wfc->width) / 2;
			if (wfc->offset_x < x)
				wfc->offset_x = x;
			wfc->offset_y = (h - wfc->height) / 2;
			if (wfc->offset_y < y)
				wfc->offset_y = y;
		}
		else 
		{
			wfc->offset_x = (GetSystemMetrics(SM_CXSCREEN) - wfc->width) / 2;
			if (wfc->offset_x < 0)
				wfc->offset_x = 0;
			wfc->offset_y = (GetSystemMetrics(SM_CYSCREEN) - wfc->height) / 2;
			if (wfc->offset_y < 0)
				wfc->offset_y = 0;
		}
	}
	else
	{
		wfc->offset_x = 0;
		wfc->offset_y = 0;
	}
}

void wf_resize_window(wfContext* wfc)
{
	if (wfc->fullscreen)
	{
		if(wfc->instance->settings->UseMultimon)
		{
			int x = GetSystemMetrics(SM_XVIRTUALSCREEN);
			int y = GetSystemMetrics(SM_YVIRTUALSCREEN);
			int w = GetSystemMetrics(SM_CXVIRTUALSCREEN);
			int h = GetSystemMetrics(SM_CYVIRTUALSCREEN);

			SetWindowLongPtr(wfc->hwnd, GWL_STYLE, WS_POPUP);
			set_window_position(wfc->hwnd, HWND_TOP, x, y, w, h, SWP_FRAMECHANGED);
		}
		else
		{
			SetWindowLongPtr(wfc->hwnd, GWL_STYLE, WS_POPUP);
			set_window_position(wfc->hwnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED);
		}
	}
	else if (!wfc->instance->settings->Decorations)
	{		
		SetWindowLongPtr(wfc->hwnd, GWL_STYLE, WS_CHILD);

		/* Now resize to get full canvas size_i32 and room for caption and borders */
		set_window_position(wfc->hwnd, HWND_TOP, 0, 0, wfc->width, wfc->height, SWP_FRAMECHANGED);

//		wf_update_canvas_diff(wfc);
		set_window_position(wfc->hwnd, HWND_TOP, -1, -1, wfc->width + wfc->diff.x(), wfc->height + wfc->diff.y(), SWP_NOMOVE | SWP_FRAMECHANGED);
	}
	else
	{
		SetWindowLongPtr(wfc->hwnd, GWL_STYLE, WS_CAPTION | WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_SIZEBOX | WS_MAXIMIZEBOX);

		if (!wfc->client_height)
			wfc->client_height = wfc->height;

		if (!wfc->client_width)
			wfc->client_width = wfc->width;

		if (!wfc->client_x)
			wfc->client_x = 10;

		if (!wfc->client_y)
			wfc->client_y = 10;
		
//		wf_update_canvas_diff(wfc);

		/* Now resize to get full canvas size_i32 and room for caption and borders */
		set_window_position(wfc->hwnd, HWND_TOP, wfc->client_x, wfc->client_y, wfc->client_width + wfc->diff.x(), wfc->client_height + wfc->diff.y(), 0 /*SWP_FRAMECHANGED*/);
		//wf_size_scrollbars(wfc,  wfc->client_width, wfc->client_height);
	}
	wf_update_offset(wfc);
}

void wf_toggle_fullscreen(wfContext* wfc)
{
	ShowWindow(wfc->hwnd, SW_HIDE);
	wfc->fullscreen = !wfc->fullscreen;

	if (wfc->fullscreen)
	{
		wfc->disablewindowtracking = true;
	}

	if (wfc->fullscreen)
		floatbar_show(wfc->floatbar);
	else
		floatbar_hide(wfc->floatbar);

	SetParent(wfc->hwnd, wfc->fullscreen ? nullptr : wfc->hWndParent);
	wf_resize_window(wfc);
	ShowWindow(wfc->hwnd, e_display_normal);
	SetForegroundWindow(wfc->hwnd);

	if (!wfc->fullscreen)
	{
		// Reenable window tracking AFTER resizing it back, otherwise it can lean to repositioning errors.
		wfc->disablewindowtracking = false;
	}
}

//BOOL wf_gdi_bitmap_update(rdpContext* context, BITMAP_UPDATE* bitmapUpdate)
//{
//	HDC hdc;
//	int status;
//	int nXDst;
//	int nYDst;
//	int nXSrc;
//	int nYSrc;
//	int nWidth;
//	int nHeight;
//	HBITMAP dib;
//	::u32 index;
//	byte* pSrcData;
//	byte* pDstData;
//	::u32 SrcSize;
//	BOOL compressed;
//	::u32 SrcFormat;
//	::u32 bitsPerPixel;
//	::u32 bytesPerPixel;
//	BITMAP_DATA* bitmap;
//	rdpCodecs* codecs = context->codecs;
//	wfContext* wfc = (wfContext*) context;
//
//	hdc = CreateCompatibleDC(GetDC(nullptr));
//	if (!hdc)
//		return false;
//
//	for (index = 0; index < bitmapUpdate->number; index++)
//	{
//		bitmap = &(bitmapUpdate->rectangles[index]);
//
//		nXSrc = 0;
//		nYSrc = 0;
//
//		nXDst = bitmap->destLeft;
//		nYDst = bitmap->destTop;
//
//		nWidth = bitmap->width;
//		nHeight = bitmap->height;
//
//		pSrcData = bitmap->bitmapDataStream;
//		SrcSize = bitmap->bitmapLength;
//
//		compressed = bitmap->compressed;
//		bitsPerPixel = bitmap->bitsPerPixel;
//		bytesPerPixel = (bitsPerPixel + 7) / 8;
//
//		SrcFormat = gdi_get_pixel_format(bitsPerPixel, true);
//
//		if (wfc->bitmap_size < (::u32) (nWidth * nHeight * 4))
//		{
//			wfc->bitmap_size = nWidth * nHeight * 4;
//			wfc->bitmap_buffer = (byte*) _aligned_realloc(wfc->bitmap_buffer, wfc->bitmap_size, 16);
//
//			if (!wfc->bitmap_buffer)
//				return false;
//		}
//
//		if (compressed)
//		{
//			pDstData = wfc->bitmap_buffer;
//
//			if (bitsPerPixel < 32)
//			{
//				if (!freerdp_client_codecs_prepare(codecs, FREERDP_CODEC_INTERLEAVED))
//					return false;
//
//				status = interleaved_decompress(codecs->interleaved, pSrcData, SrcSize, bitsPerPixel,
//						&pDstData, PIXEL_FORMAT_XRGB32, nWidth * 4, 0, 0, nWidth, nHeight, nullptr);
//			}
//			else
//			{
//				if (!freerdp_client_codecs_prepare(codecs, FREERDP_CODEC_PLANAR))
//					return false;
//
//				status = planar_decompress(codecs->planar, pSrcData, SrcSize, &pDstData,
//						PIXEL_FORMAT_XRGB32, nWidth * 4, 0, 0, nWidth, nHeight, true);
//			}
//
//			if (status < 0)
//			{
//				WLog_ERR(TAG, "bitmap decompression failure");
//				return false;
//			}
//
//			pSrcData = wfc->bitmap_buffer;
//		}
//
//		dib = wf_create_dib(wfc, nWidth, nHeight, 32, pSrcData, nullptr);
//		SelectObject(hdc, dib);
//
//		nWidth = bitmap->destRight - bitmap->destLeft + 1; /* clip width */
//		nHeight = bitmap->destBottom - bitmap->destTop + 1; /* clip height */
//
//		BitBlt(wfc->primary->hdc, nXDst, nYDst, nWidth, nHeight, hdc, 0, 0);
//
//		gdi_InvalidateRegion(wfc->hdc, nXDst, nYDst, nWidth, nHeight);
//
//		DeleteObject(dib);
//	}
//
//	ReleaseDC(nullptr, hdc);
//	return true;
//}
//
void wf_gdi_palette_update(wfContext* wfc, PALETTE_UPDATE* palette)
{

}

//void wf_set_null_clip_rgn(wfContext* wfc)
//{
//	SelectClipRgn(wfc->drawing->hdc, nullptr);
//}
//
//void wf_set_clip_rgn(wfContext* wfc, int x, int y, int width, int height)
//{
//	HRGN clip;
//	clip = CreateRectRgn(x, y, x + width, y + height);
//	SelectClipRgn(wfc->drawing->hdc, clip);
//	DeleteObject(clip);
//}
//
//void wf_gdi_set_bounds(wfContext* wfc, rdpBounds* bounds)
//{
//	HRGN hrgn;
//
//	if (bounds != nullptr)
//	{
//		hrgn = CreateRectRgn(bounds->left, bounds->top, bounds->right + 1, bounds->bottom + 1);
//		SelectClipRgn(wfc->drawing->hdc, hrgn);
//		DeleteObject(hrgn);
//	}
//	else
//	{
//		SelectClipRgn(wfc->drawing->hdc, nullptr);
//	}
//}
//
//void wf_gdi_dstblt(wfContext* wfc, DSTBLT_ORDER* dstblt)
//{
//	BitBlt(wfc->drawing->hdc, dstblt->nLeftRect, dstblt->nTopRect,
//			dstblt->nWidth, dstblt->nHeight, nullptr, 0, 0, gdi_rop3_code(dstblt->bRop));
//
//	wf_invalidate_region(wfc, dstblt->nLeftRect, dstblt->nTopRect,
//			dstblt->nWidth, dstblt->nHeight);
//}

//void wf_gdi_patblt(wfContext* wfc, PATBLT_ORDER* patblt)
//{
//	HBRUSH brush;
//	HBRUSH org_brush;
//	int org_bkmode;
//	::u32 fgcolor;
//	::u32 bgcolor;
//	color32_t org_bkcolor;
//	color32_t org_textcolor;
//
//	fgcolor = freerdp_color_convert_bgr(patblt->foreColor, wfc->srcBpp, wfc->dstBpp, wfc->clrconv);
//	bgcolor = freerdp_color_convert_bgr(patblt->backColor, wfc->srcBpp, wfc->dstBpp, wfc->clrconv);
//
//	brush = wf_create_brush(wfc, &patblt->brush, fgcolor, wfc->srcBpp);
//	org_bkmode = SetBkMode(wfc->drawing->hdc, OPAQUE);
//	org_bkcolor = SetBkColor(wfc->drawing->hdc, bgcolor);
//	org_textcolor = SetTextColor(wfc->drawing->hdc, fgcolor);
//	org_brush = (HBRUSH)SelectObject(wfc->drawing->hdc, brush);
//
//	PatBlt(wfc->drawing->hdc, patblt->nLeftRect, patblt->nTopRect,
//		patblt->nWidth, patblt->nHeight, gdi_rop3_code(patblt->bRop));
//
//	SelectObject(wfc->drawing->hdc, org_brush);
//	DeleteObject(brush);
//
//	SetBkMode(wfc->drawing->hdc, org_bkmode);
//	SetBkColor(wfc->drawing->hdc, org_bkcolor);
//	SetTextColor(wfc->drawing->hdc, org_textcolor);
//
//	if (wfc->drawing == wfc->primary)
//		wf_invalidate_region(wfc, patblt->nLeftRect, patblt->nTopRect, patblt->nWidth, patblt->nHeight);
//}
//
//void wf_gdi_scrblt(wfContext* wfc, SCRBLT_ORDER* scrblt)
//{
//	BitBlt(wfc->drawing->hdc, scrblt->nLeftRect, scrblt->nTopRect,
//			scrblt->nWidth, scrblt->nHeight, wfc->primary->hdc,
//			scrblt->nXSrc, scrblt->nYSrc, gdi_rop3_code(scrblt->bRop));
//
//	wf_invalidate_region(wfc, scrblt->nLeftRect, scrblt->nTopRect,
//			scrblt->nWidth, scrblt->nHeight);
//}
//
//void wf_gdi_opaque_rect(wfContext* wfc, OPAQUE_RECT_ORDER* opaque_rect)
//{
//	::rectangle_i32 rectangle_i32;
//	HBRUSH brush;
//	::u32 brush_color;
//
//	brush_color = freerdp_color_convert_var_bgr(opaque_rect->color, wfc->srcBpp, wfc->dstBpp, wfc->clrconv);
//
//	rectangle.left = opaque_rect->nLeftRect;
//	rectangle.top = opaque_rect->nTopRect;
//	rectangle.right = opaque_rect->nLeftRect + opaque_rect->nWidth;
//	rectangle.bottom = opaque_rect->nTopRect + opaque_rect->nHeight;
//	brush = CreateSolidBrush(brush_color);
//	FillRect(wfc->drawing->hdc, &rectangle, brush);
//	DeleteObject(brush);
//
//	if (wfc->drawing == wfc->primary)
//		wf_invalidate_region(wfc, rectangle.left, rectangle.top, rectangle.right - rectangle.left + 1, rectangle.bottom - rectangle.top + 1);
//}
//
//void wf_gdi_multi_opaque_rect(wfContext* wfc, MULTI_OPAQUE_RECT_ORDER* multi_opaque_rect)
//{
//	int i;
//	::rectangle_i32 rectangle_i32;
//	HBRUSH brush;
//	::u32 brush_color;
//	DELTA_RECT* rectangle_i32;
//
//	brush_color = freerdp_color_convert_var_rgb(multi_opaque_rect->color, wfc->srcBpp, wfc->dstBpp, wfc->clrconv);
//
//	for (i = 1; i < (int) multi_opaque_rect->numRectangles + 1; i++)
//	{
//		rectangle = &multi_opaque_rect->rectangles[i];
//
//		rectangle.left = rectangle_i32->left;
//		rectangle.top = rectangle_i32->top;
//		rectangle.right = rectangle_i32->left + rectangle_i32->width;
//		rectangle.bottom = rectangle_i32->top + rectangle_i32->height;
//		brush = CreateSolidBrush(brush_color);
//
//		FillRect(wfc->drawing->hdc, &rectangle, brush);
//
//		if (wfc->drawing == wfc->primary)
//			wf_invalidate_region(wfc, rectangle.left, rectangle.top, rectangle.right - rectangle.left + 1, rectangle.bottom - rectangle.top + 1);
//
//		DeleteObject(brush);
//	}
//}
//
//void wf_gdi_line_to(wfContext* wfc, LINE_TO_ORDER* line_to)
//{
//	HPEN pen;
//	HPEN org_pen;
//	int x, y, w, h;
//	::u32 pen_color;
//
//	pen_color = freerdp_color_convert_var_bgr(line_to->ppenColor, wfc->srcBpp, wfc->dstBpp, wfc->clrconv);
//
//	pen = CreatePen(line_to->ppenStyle, line_to->ppenWidth, pen_color);
//
//	wf_set_rop2(wfc->drawing->hdc, line_to->bRop2);
//	org_pen = (HPEN) SelectObject(wfc->drawing->hdc, ppen);
//
//	MoveToEx(wfc->drawing->hdc, line_to->nXStart, line_to->nYStart, nullptr);
//	LineTo(wfc->drawing->hdc, line_to->nXEnd, line_to->nYEnd);
//
//	x = (line_to->nXStart < line_to->nXEnd) ? line_to->nXStart : line_to->nXEnd;
//	y = (line_to->nYStart < line_to->nYEnd) ? line_to->nYStart : line_to->nYEnd;
//	w = (line_to->nXStart < line_to->nXEnd) ? (line_to->nXEnd - line_to->nXStart) : (line_to->nXStart - line_to->nXEnd);
//	h = (line_to->nYStart < line_to->nYEnd) ? (line_to->nYEnd - line_to->nYStart) : (line_to->nYStart - line_to->nYEnd);
//
//	if (wfc->drawing == wfc->primary)
//		wf_invalidate_region(wfc, x, y, w, h);
//
//	SelectObject(wfc->drawing->hdc, org_pen);
//	DeleteObject(pen);
//}
//
//void wf_gdi_polyline(wfContext* wfc, POLYLINE_ORDER* polyline)
//{
//	int org_rop2;
//	HPEN hpen;
//	HPEN org_hpen;
//	::u32 pen_color;
//
//	pen_color = freerdp_color_convert_var_bgr(polyline->ppenColor, wfc->srcBpp, wfc->dstBpp, wfc->clrconv);
//
//	hpen = CreatePen(0, 1, pen_color);
//	org_rop2 = wf_set_rop2(wfc->drawing->hdc, polyline->bRop2);
//	org_hpen = (HPEN) SelectObject(wfc->drawing->hdc, hpen);
//
//	if (polyline->numDeltaEntries > 0)
//	{
//		::point_i32  *pts;
//		::point_i32  temp;
//		int    numPoints;
//		int    i;
//
//		numPoints = polyline->numDeltaEntries + 1;
//		pts = (::point_i32*) malloc(sizeof(::point_i32) * numPoints);
//		pts[0].x() = temp.x() = polyline->xStart;
//		pts[0].y() = temp.y() = polyline->yStart;
//
//		for (i = 0; i < (int) polyline->numDeltaEntries; i++)
//		{
//			temp.x() += polyline->points[i].x();
//			temp.y() += polyline->points[i].y();
//			pts[i + 1].x() = temp.x();
//			pts[i + 1].y() = temp.y();
//		}
//		if (wfc->drawing == wfc->primary)
//			wf_invalidate_region(wfc, wfc->client_x, wfc->client_y, wfc->client_width, wfc->client_height);
//		polyline(wfc->drawing->hdc, pts, numPoints);
//		free(pts);
//	}
//
//	SelectObject(wfc->drawing->hdc, org_hpen);
//	wf_set_rop2(wfc->drawing->hdc, org_rop2);
//	DeleteObject(hpen);
//}
//
//void wf_gdi_memblt(wfContext* wfc, MEMBLT_ORDER* memblt)
//{
//	wfBitmap* bitmap;
//
//	bitmap = (wfBitmap*) memblt->bitmap;
//
//   if(wfc->drawing == nullptr)
//      return;
//
//	BitBlt(wfc->drawing->hdc, memblt->nLeftRect, memblt->nTopRect,
//			memblt->nWidth, memblt->nHeight, bitmap->hdc,
//			memblt->nXSrc, memblt->nYSrc, gdi_rop3_code(memblt->bRop));
//
//	if (wfc->drawing == wfc->primary)
//		wf_invalidate_region(wfc, memblt->nLeftRect, memblt->nTopRect, memblt->nWidth, memblt->nHeight);
//}
//
//void wf_gdi_surface_bits(wfContext* wfc, SURFACE_BITS_COMMAND* surface_bits_command)
//{
//	int i, j;
//	int tx, ty;
//	RFX_MESSAGE* message;
//	BITMAPINFO bitmap_info;
//
//	if (surface_bits_command->codecID == RDP_CODEC_ID_REMOTEFX)
//	{
//		if (!freerdp_client_codecs_prepare(wfc->codecs, FREERDP_CODEC_REMOTEFX))
//			return;
//
//		if (!(message = rfx_process_message(wfc->codecs->rfx, surface_bits_command->bitmapData, surface_bits_command->bitmapDataLength)))
//		{
//			WLog_ERR(TAG, "Failed to process RemoteFX message");
//			return;
//		}
//
//		/* blit each tile */
//		for (i = 0; i < message->numTiles; i++)
//		{
//			tx = message->tiles[i]->x + surface_bits_command->destLeft;
//			ty = message->tiles[i]->y + surface_bits_command->destTop;
//
//			freerdp_image_convert(message->tiles[i]->data, wfc->tile->pdata, 64, 64, 32, 32, wfc->clrconv);
//
//			for (j = 0; j < message->numRects; j++)
//			{
//				wf_set_clip_rgn(wfc,
//					surface_bits_command->destLeft + message->rects[j].x(),
//					surface_bits_command->destTop + message->rects[j].y(),
//					message->rects[j].width, message->rects[j].height);
//
//				BitBlt(wfc->primary->hdc, tx, ty, 64, 64, wfc->tile->hdc, 0, 0);
//			}
//		}
//
//		wf_set_null_clip_rgn(wfc);
//
//		/* invalidate regions */
//		for (i = 0; i < message->numRects; i++)
//		{
//			tx = surface_bits_command->destLeft + message->rects[i].x();
//			ty = surface_bits_command->destTop + message->rects[i].y();
//			wf_invalidate_region(wfc, tx, ty, message->rects[i].width, message->rects[i].height);
//		}
//
//		rfx_message_free(wfc->codecs->rfx, message);
//	}
//	else if (surface_bits_command->codecID == RDP_CODEC_ID_NSCODEC)
//	{
//		if (!freerdp_client_codecs_prepare(wfc->codecs, FREERDP_CODEC_NSCODEC))
//			return;
//
//		nsc_process_message(wfc->codecs->nsc, surface_bits_command->bpp, surface_bits_command->width, surface_bits_command->height,
//			surface_bits_command->bitmapData, surface_bits_command->bitmapDataLength);
//		ZeroMemory(&bitmap_info, sizeof(bitmap_info));
//		bitmap_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
//		bitmap_info.bmiHeader.biWidth = surface_bits_command->width;
//		bitmap_info.bmiHeader.biHeight = surface_bits_command->height;
//		bitmap_info.bmiHeader.biPlanes = 1;
//		bitmap_info.bmiHeader.biBitCount = surface_bits_command->bpp;
//		bitmap_info.bmiHeader.biCompression = BI_RGB;
//		SetDIBitsToDevice(wfc->primary->hdc, surface_bits_command->destLeft, surface_bits_command->destTop,
//			surface_bits_command->width, surface_bits_command->height, 0, 0, 0, surface_bits_command->height,
//			wfc->codecs->nsc->BitmapData, &bitmap_info, DIB_RGB_COLORS);
//		wf_invalidate_region(wfc, surface_bits_command->destLeft, surface_bits_command->destTop,
//			surface_bits_command->width, surface_bits_command->height);
//	}
//	else if (surface_bits_command->codecID == RDP_CODEC_ID_NONE)
//	{
//		ZeroMemory(&bitmap_info, sizeof(bitmap_info));
//		bitmap_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
//		bitmap_info.bmiHeader.biWidth = surface_bits_command->width;
//		bitmap_info.bmiHeader.biHeight = surface_bits_command->height;
//		bitmap_info.bmiHeader.biPlanes = 1;
//		bitmap_info.bmiHeader.biBitCount = surface_bits_command->bpp;
//		bitmap_info.bmiHeader.biCompression = BI_RGB;
//		SetDIBitsToDevice(wfc->primary->hdc, surface_bits_command->destLeft, surface_bits_command->destTop,
//			surface_bits_command->width, surface_bits_command->height, 0, 0, 0, surface_bits_command->height,
//			surface_bits_command->bitmapData, &bitmap_info, DIB_RGB_COLORS);
//		wf_invalidate_region(wfc, surface_bits_command->destLeft, surface_bits_command->destTop,
//			surface_bits_command->width, surface_bits_command->height);
//	}
//	else
//	{
//		WLog_ERR(TAG,  "Unsupported codecID %d", surface_bits_command->codecID);
//	}
//}
//
//void wf_gdi_surface_frame_marker(wfContext* wfc, SURFACE_FRAME_MARKER* surface_frame_marker)
//{
//	rdpContext* context;
//	rdpSettings* settings;
//
//	context = (rdpContext*) wfc;
//	settings = wfc->instance->settings;
//
//	if (surface_frame_marker->frameAction == SURFACECMD_FRAMEACTION_END && settings->FrameAcknowledge > 0)
//	{
//		IFCALL(context->instance->update->SurfaceFrameAcknowledge, context, surface_frame_marker->frameId);
//	}
//}
//
//void wf_gdi_register_update_callbacks(rdpUpdate* update)
//{
//	rdpPrimaryUpdate* primary = update->primary;
//
//	update->Palette = (pPalette) wf_gdi_palette_update;
//	update->SetBounds = (pSetBounds) wf_gdi_set_bounds;
//
//	primary->DstBlt = (pDstBlt) wf_gdi_dstblt;
//	primary->PatBlt = (pPatBlt) wf_gdi_patblt;
//	primary->ScrBlt = (pScrBlt) wf_gdi_scrblt;
//	primary->OpaqueRect = (pOpaqueRect) wf_gdi_opaque_rect;
//	primary->DrawNineGrid = nullptr;
//	primary->MultiDstBlt = nullptr;
//	primary->MultiPatBlt = nullptr;
//	primary->MultiScrBlt = nullptr;
//	primary->MultiOpaqueRect = (pMultiOpaqueRect) wf_gdi_multi_opaque_rect;
//	primary->MultiDrawNineGrid = nullptr;
//	primary->LineTo = (pLineTo) wf_gdi_line_to;
//	primary->polyline = (pPolyline) wf_gdi_polyline;
//	primary->MemBlt = (pMemBlt) wf_gdi_memblt;
//	primary->Mem3Blt = nullptr;
//	primary->SaveBitmap = nullptr;
//	primary->GlyphIndex = nullptr;
//	primary->FastIndex = nullptr;
//	primary->FastGlyph = nullptr;
//	primary->PolygonSC = nullptr;
//	primary->PolygonCB = nullptr;
//	primary->EllipseSC = nullptr;
//	primary->EllipseCB = nullptr;
//
//	update->SurfaceBits = (pSurfaceBits) wf_gdi_surface_bits;
//	update->SurfaceFrameMarker = (pSurfaceFrameMarker) wf_gdi_surface_frame_marker;
//}
//
//void wf_update_canvas_diff(wfContext* wfc)
//{
//	::rectangle_i32 rc_client, rc_wnd;
//	int greekdeltax, greekdeltay;
//
//	client_rectangle(wfc->hwnd, &rc_client);
//	window_rectangle(wfc->hwnd, &rc_wnd);
//	
//	greekdeltax = (rc_wnd.right - rc_wnd.left) - rc_client.right;
//	greekdeltay = (rc_wnd.bottom - rc_wnd.top) - rc_client.bottom;
//
//	if (!wfc->disablewindowtracking)
//	{
//		wfc->diff.x() = greekdeltax;
//		wfc->diff.y() = greekdeltay;
//	}
//}
