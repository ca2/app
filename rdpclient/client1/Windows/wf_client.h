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

#include "rdpclient/client/common/graphics.h"

#include "wf_channels.h"
#include "wf_floatbar.h"
#include "wf_event.h"
#include "wf_cliprdr.h"




#ifdef __cplusplus
extern "C" {
#endif

// System menu constants
#define SYSCOMMAND_ID_SMARTSIZING 1000

struct wf_bitmap :
   public axisrdp_bitmap
{
	rdpBitmap _bitmap;
	HDC hdc;
	HBITMAP bitmap;
	HBITMAP org_bitmap;
	byte* pdata;
};
typedef struct wf_bitmap wfBitmap;

struct wf_pointer
{
	rdpPointer pointer;
	HCURSOR cursor;
};
typedef struct wf_pointer wfPointer;

struct wf_context :
   public axisrdp_context
{
	

	int fs_toggle;
	int fullscreen;
	int percentscreen;

	HANDLE keyboardThread;

	HICON icon;
	HWND hWndParent;
	HINSTANCE hInstance;
	WNDCLASSEX wndClass;
	LPCTSTR wndClassName;
	HCURSOR hDefaultCursor;

	HWND hwnd;
	POINT_I32 diff;
	HGDI_DC hdc;

//	HCLRCONV clrconv;
	HCURSOR cursor;
	HBRUSH brush;
	HBRUSH org_brush;
	RECTANGLE_I32 update_rect;
	RECTANGLE_I32 scale_update_rect;

	wfBitmap* tile;
	::u32 mainThreadId;
	::u32 keyboardThreadId;

	rdpFile* connectionRdpFile;

	BOOL disablewindowtracking;

	BOOL updating_scrollbars;
	BOOL xScrollVisible;
	int xMinScroll;
	int xCurrentScroll;
	int xMaxScroll;

	BOOL yScrollVisible;
	int yMinScroll;
	int yCurrentScroll;
	int yMaxScroll;

	wfClipboard* clipboard;
	CliprdrClientContext* cliprdr;

	FloatBar* floatbar;

	RailClientContext* rail;
	wHashTable* railWindows;
};

/**
 * Client Interface
 */

FREERDP_API int RdpClientEntry(RDP_CLIENT_ENTRY_POINTS* pEntryPoints);
FREERDP_API int freerdp_client_set_window_size(wfContext* wfc, int width, int height);
FREERDP_API void wf_size_scrollbars(wfContext* wfc, ::u32 client_width, ::u32 client_height);

#ifdef __cplusplus
}
#endif

#endif
