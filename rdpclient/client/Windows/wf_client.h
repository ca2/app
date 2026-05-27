/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * Windows Client
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

#ifndef __WF_INTERFACE_H
#define __WF_INTERFACE_H

#include <winpr/windows.h>

#include <winpr/collections.h>

#include <freerdp/api.h>
#include <freerdp/freerdp.h>
#include <freerdp/gdi/gdi.h>
#include <freerdp/gdi/dc.h>
#include <freerdp/gdi/region.h>
#include <freerdp/cache/cache.h>
#include <freerdp/codec/color.h>

#include <freerdp/client/rail.h>
#include <freerdp/channels/channels.h>
#include <freerdp/codec/rfx.h>
#include <freerdp/codec/nsc.h>
#include <freerdp/client/file.h>

typedef struct wf_context wfContext;

#include "wf_channels.h"
#include "wf_floatbar.h"
#include "wf_event.h"
#include "wf_cliprdr.h"

#ifdef __cplusplus
extern "C" {
#endif

// System menu constants
#define SYSCOMMAND_ID_SMARTSIZING 1000

struct wf_bitmap
{
	rdpBitmap _bitmap;
	HDC hdc;
	HBITMAP bitmap;
	HBITMAP org_bitmap;
	::u8* pdata;
};
typedef struct wf_bitmap wfBitmap;

struct wf_pointer
{
	rdpPointer pointer;
	HCURSOR cursor;
};
typedef struct wf_pointer wfPointer;

struct wf_context
{
	rdpContext action_context;
	DEFINE_RDP_CLIENT_COMMON();

	::i32 offset_x;
	::i32 offset_y;
	::i32 fs_toggle;
	::i32 fullscreen;
	::i32 percentscreen;
	::i8 window_title[64];
	::i32 client_x;
	::i32 client_y;
	::i32 client_width;
	::i32 client_height;

	HANDLE keyboardThread;

	HICON icon;
	HWND hWndParent;
	HINSTANCE hInstance;
	WNDCLASSEX wndClass;
	LPCTSTR wndClassName;
	HCURSOR hDefaultCursor;

	HWND hwnd;
	::i32_point diff;

	wfBitmap* primary;
	wfBitmap* drawing;
	HCURSOR cursor;
	HBRUSH brush;
	HBRUSH org_brush;
	::i32_rectangle update_rect;
	::i32_rectangle scale_update_rect;

	::u32 mainThreadId;
	::u32 keyboardThreadId;

	rdpFile* connectionRdpFile;

	BOOL disablewindowtracking;

	BOOL updating_scrollbars;
	BOOL xScrollVisible;
	::i32 xMinScroll;
	::i32 xCurrentScroll;
	::i32 xMaxScroll;

	BOOL yScrollVisible;
	::i32 yMinScroll;
	::i32 yCurrentScroll;
	::i32 yMaxScroll;

	void* clipboard;
	CliprdrClientContext* cliprdr;

	FloatBar* floatbar;

	RailClientContext* rail;
	wHashTable* railWindows;
};

/**
 * Client Interface
 */

FREERDP_API ::i32 RdpClientEntry(RDP_CLIENT_ENTRY_POINTS* pEntryPoints);
FREERDP_API ::i32 freerdp_client_set_window_size(wfContext* wfc, ::i32 width,
        ::i32 height);
FREERDP_API void wf_size_scrollbars(wfContext* wfc, ::u32 client_width,
                                    ::u32 client_height);

#ifdef __cplusplus
}
#endif

#endif
