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
 *	 http://www.apache.org/licenses/LICENSE-2.0
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

#include <winpr/windows.h>

#include <winpr/crt.h>
#include <winpr/credui.h>

#include <errno.h>
#include <stdio.h>

#include <string.h>
#include <tchar.h>
#include <assert.h>
#include <sys/types.h>

#include <freerdp/log.h>
#include <freerdp/event.h>
#include <freerdp/freerdp.h>
#include <freerdp/constants.h>

#include <freerdp/codec/region.h>
#include <freerdp/client/cmdline.h>
#include <freerdp/client/channels.h>
#include <freerdp/channels/channels.h>

#include "wf_gdi.h"
#include "wf_rail.h"
#include "wf_channels.h"
#include "wf_graphics.h"
#include "wf_cliprdr.h"

#include "wf_client.h"

#include "resource.h"

#define TAG CLIENT_TAG("windows")

int wf_create_console(void)
{
	//if (!AllocConsole())
		//return 1;

	//freopen("CONOUT$", "w", stdout);
	//freopen("CONOUT$", "w", stderr);
	WLog_INFO(TAG,  "Debug console created.");
	return 0;
}

BOOL wf_sw_begin_paint(wfContext* wfc)
{
	rdpGdi* gdi = ((rdpContext*) wfc)->gdi;
	gdi->primary->hdc->hwnd->invalid->null = 1;
	gdi->primary->hdc->hwnd->ninvalid = 0;
	return true;
}

BOOL wf_sw_end_paint(wfContext* wfc)
{
	int i;
	rdpGdi* gdi;
	int ninvalid;
	RECTANGLE_I32 updateRect;
	HGDI_RGN cinvalid;
	REGION16 invalidRegion;
	RECTANGLE_16 invalidRect;
	const RECTANGLE_16* extents;
	rdpContext* context = (rdpContext*) wfc;

	gdi = context->gdi;

	ninvalid = gdi->primary->hdc->hwnd->ninvalid;
	cinvalid = gdi->primary->hdc->hwnd->cinvalid;

	if (ninvalid < 1)
		return true;

	region16_init(&invalidRegion);

	for (i = 0; i < ninvalid; i++)
	{
		invalidRect.left = cinvalid[i].x;
		invalidRect.top = cinvalid[i].y;
		invalidRect.right = cinvalid[i].x + cinvalid[i].w;
		invalidRect.bottom = cinvalid[i].y + cinvalid[i].h;

		region16_union_rect(&invalidRegion, &invalidRegion, &invalidRect);
	}

	if (!region16_is_empty(&invalidRegion))
	{
		extents = region16_extents(&invalidRegion);

		updateRect.left = extents->left;
		updateRect.top = extents->top;
		updateRect.right = extents->right;
		updateRect.bottom = extents->bottom;

		InvalidateRect(wfc->hwnd, &updateRect, false);

		if (wfc->rail)
			wf_rail_invalidate_region(wfc, &invalidRegion);
	}

	region16_uninit(&invalidRegion);
	return true;
}

//BOOL wf_sw_desktop_resize(wfContext* wfc)
//{
//	rdpGdi* gdi;
//	rdpContext* context;
//	rdpSettings* settings;
//	freerdp* instance = wfc->instance;
//
//	context = (rdpContext*) wfc;
//	settings = wfc->instance->settings;
//	gdi = context->gdi;
//
//	wfc->width = settings->DesktopWidth;
//	wfc->height = settings->DesktopHeight;
//
//	gdi->primary->bitmap->data = nullptr;
//	gdi_free(instance);
//
//	if (wfc->primary)
//	{
//		wf_image_free(wfc->primary);
//		wfc->primary = wf_image_new(wfc, wfc->width, wfc->height, wfc->dstBpp, nullptr);
//	}
//
//	if (!gdi_init(instance, CLRCONV_ALPHA | CLRBUF_32BPP, wfc->primary->pdata))
//		return false;
//
//	gdi = instance->context->gdi;
//	wfc->hdc = gdi->primary->hdc;
//
//	return true;
//}
//
//BOOL wf_hw_begin_paint(wfContext* wfc)
//{
//	wfc->hdc->hwnd->invalid->null = 1;
//	wfc->hdc->hwnd->ninvalid = 0;
//	return true;
//}
//
//BOOL wf_hw_end_paint(wfContext* wfc)
//{
//	return true;
//}
//
//BOOL wf_hw_desktop_resize(wfContext* wfc)
//{
//	BOOL same;
//	RECTANGLE_I32 rectangle_i32;
//	rdpSettings* settings;
//
//	settings = wfc->instance->settings;
//
//	wfc->width = settings->DesktopWidth;
//	wfc->height = settings->DesktopHeight;
//
//	if (wfc->primary)
//	{
//		same = (wfc->primary == wfc->drawing) ? true : false;
//
//		wf_image_free(wfc->primary);
//
//		wfc->primary = wf_image_new(wfc, wfc->width, wfc->height, wfc->dstBpp, nullptr);
//
//		if (same)
//			wfc->drawing = wfc->primary;
//	}
//
//	if (wfc->fullscreen != true)
//	{
//		if (wfc->hwnd)
//			set_window_position(wfc->hwnd, HWND_TOP, -1, -1, wfc->width + wfc->diff.x, wfc->height + wfc->diff.y, SWP_NOMOVE);
//	}
//	else
//	{
//		wf_update_offset(wfc);
//		get_window_rect(wfc->hwnd, &rectangle);
//		InvalidateRect(wfc->hwnd, &rectangle, true);
//	}
//	return true;
//}

CLASS_DECL_EXPORT BOOL wf_pre_connect(freerdp* instance)
{
	wfContext* wfc;
	int desktopWidth;
	int desktopHeight;
	rdpContext* context;
	rdpSettings* settings;

	context = instance->context;
	wfc = (wfContext*) instance->context;
	wfc->instance = instance;
	wfc->codecs = instance->context->codecs;

	settings = instance->settings;

	if (settings->ConnectionFile)
	{
		if (wfc->connectionRdpFile)
		{
			freerdp_client_rdp_file_free(wfc->connectionRdpFile);
		}

		wfc->connectionRdpFile = freerdp_client_rdp_file_new();
		WLog_INFO(TAG,  "Using connection file: %s", settings->ConnectionFile);
		freerdp_client_parse_rdp_file(wfc->connectionRdpFile, settings->ConnectionFile);
		freerdp_client_populate_settings_from_rdp_file(wfc->connectionRdpFile, settings);
	}

	settings->OsMajorType = OSMAJORTYPE_WINDOWS;
	settings->OsMinorType = OSMINORTYPE_WINDOWS_NT;
	settings->OrderSupport[NEG_DSTBLT_INDEX] = true;
	settings->OrderSupport[NEG_PATBLT_INDEX] = true;
	settings->OrderSupport[NEG_SCRBLT_INDEX] = true;
	settings->OrderSupport[NEG_OPAQUE_RECT_INDEX] = true;
	settings->OrderSupport[NEG_DRAWNINEGRID_INDEX] = false;
	settings->OrderSupport[NEG_MULTIDSTBLT_INDEX] = false;
	settings->OrderSupport[NEG_MULTIPATBLT_INDEX] = false;
	settings->OrderSupport[NEG_MULTISCRBLT_INDEX] = false;
	settings->OrderSupport[NEG_MULTIOPAQUERECT_INDEX] = true;
	settings->OrderSupport[NEG_MULTI_DRAWNINEGRID_INDEX] = false;
	settings->OrderSupport[NEG_LINETO_INDEX] = true;
	settings->OrderSupport[NEG_POLYLINE_INDEX] = true;
	settings->OrderSupport[NEG_MEMBLT_INDEX] = true;
	settings->OrderSupport[NEG_MEM3BLT_INDEX] = false;
	settings->OrderSupport[NEG_SAVEBITMAP_INDEX] = false;
	settings->OrderSupport[NEG_GLYPH_INDEX_INDEX] = false;
	settings->OrderSupport[NEG_FAST_INDEX_INDEX] = false;
	settings->OrderSupport[NEG_FAST_GLYPH_INDEX] = false;
	settings->OrderSupport[NEG_POLYGON_SC_INDEX] = false;
	settings->OrderSupport[NEG_POLYGON_CB_INDEX] = false;
	settings->OrderSupport[NEG_ELLIPSE_SC_INDEX] = false;
	settings->OrderSupport[NEG_ELLIPSE_CB_INDEX] = false;

	settings->GlyphSupportLevel = GLYPH_SUPPORT_NONE;

	wfc->fullscreen = settings->Fullscreen;

	if (wfc->fullscreen)
		wfc->fs_toggle = 1;

	//wfc->clrconv = (HCLRCONV) malloc(sizeof(CLRCONV));
	//ZeroMemory(wfc->clrconv, sizeof(CLRCONV));

	//wfc->clrconv->palette = nullptr;
	//wfc->clrconv->alpha = false;

	if (!(instance->context->cache = cache_new(settings)))
		return false;

	desktopWidth = settings->DesktopWidth;
	desktopHeight = settings->DesktopHeight;

	if (wfc->percentscreen > 0)
	{
		desktopWidth = (GetSystemMetrics(SM_CXSCREEN) * wfc->percentscreen) / 100;
		settings->DesktopWidth = desktopWidth;

		desktopHeight = (GetSystemMetrics(SM_CYSCREEN) * wfc->percentscreen) / 100;
		settings->DesktopHeight = desktopHeight;
	}

	if (wfc->fullscreen)
	{
		if (settings->UseMultimon)
		{
			desktopWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
			desktopHeight = GetSystemMetrics(SM_CYVIRTUALSCREEN);
		}
		else
		{
			desktopWidth = GetSystemMetrics(SM_CXSCREEN);
			desktopHeight = GetSystemMetrics(SM_CYSCREEN);
		}
	}

	/* FIXME: desktopWidth has a limitation that it should be divisible by 4,
	 *        otherwise the screen will crash when connecting to an XP desktop.*/
	desktopWidth = (desktopWidth + 3) & (~3);

	if (desktopWidth != settings->DesktopWidth)
	{
		freerdp_set_param_uint32(settings, FreeRDP_DesktopWidth, desktopWidth);
	}

	if (desktopHeight != settings->DesktopHeight)
	{
		freerdp_set_param_uint32(settings, FreeRDP_DesktopHeight, desktopHeight);
	}

	if ((settings->DesktopWidth < 64) || (settings->DesktopHeight < 64) ||
		(settings->DesktopWidth > 4096) || (settings->DesktopHeight > 4096))
	{
		WLog_ERR(TAG, "invalid dimensions %d %d", settings->DesktopWidth, settings->DesktopHeight);
		return false;
	}

	freerdp_set_param_uint32(settings, FreeRDP_KeyboardLayout, (size_t) GetKeyboardLayout(0) & 0x0000FFFF);

	PubSub_SubscribeChannelConnected(instance->context->pubSub,
		(pChannelConnectedEventHandler) wf_OnChannelConnectedEventHandler);

	PubSub_SubscribeChannelDisconnected(instance->context->pubSub,
		(pChannelDisconnectedEventHandler) wf_OnChannelDisconnectedEventHandler);

	//freerdp_channels_pre_connect(instance->context->channels, instance);

	return true;
}

//void wf_add_system_menu(wfContext* wfc)
//{
//	HMENU hMenu = GetSystemMenu(wfc->hwnd, false);
//
//	MENUITEMINFO item_info;
//	ZeroMemory(&item_info, sizeof(MENUITEMINFO));
//
//	item_info.fMask = MIIM_CHECKMARKS | MIIM_FTYPE | MIIM_ID | MIIM_STRING | MIIM_DATA;
//	item_info.cbSize = sizeof(MENUITEMINFO);
//	item_info.wID = SYSCOMMAND_ID_SMARTSIZING;
//	item_info.fType = MFT_STRING;
//	item_info.dwTypeData = _wcsdup(_T("Smart sizing"));
//	item_info.cch = (::u32) _wcslen(_T("Smart sizing"));
//	item_info.dwItemData = (ULONG_PTR) wfc;
//
//	InsertMenuItem(hMenu, 6, true, &item_info);
//
//	if (wfc->instance->settings->SmartSizing)
//	{
//		CheckMenuItem(hMenu, SYSCOMMAND_ID_SMARTSIZING, MF_CHECKED);
//	}
//}

//BOOL wf_post_connect(freerdp* instance)
//{
//	rdpGdi* gdi;
//	::u32 dwStyle;
//	rdpCache* cache;
//	wfContext* wfc;
//	rdpContext* context;
//	WCHAR lpWindowName[64];
//	rdpSettings* settings;
//	EmbedWindowEventArgs e;
//
//	settings = instance->settings;
//	context = instance->context;
//	wfc = (wfContext*) instance->context;
//	cache = instance->context->cache;
//
//	wfc->dstBpp = 32;
//	wfc->width = settings->DesktopWidth;
//	wfc->height = settings->DesktopHeight;
//
//	if (settings->SoftwareGdi)
//	{
//		wfc->primary = wf_image_new(wfc, wfc->width, wfc->height, wfc->dstBpp, nullptr);
//
//		if (!gdi_init(instance, CLRCONV_ALPHA | CLRBUF_32BPP, wfc->primary->pdata))
//			return false;
//
//		gdi = instance->context->gdi;
//		wfc->hdc = gdi->primary->hdc;
//	}
//	else
//	{
//		wf_gdi_register_update_callbacks(instance->update);
//		wfc->srcBpp = instance->settings->ColorDepth;
//		wfc->primary = wf_image_new(wfc, wfc->width, wfc->height, wfc->dstBpp, nullptr);
//
//		if (!(wfc->hdc = gdi_GetDC()))
//			return false;
//
//		wfc->hdc->bitsPerPixel = wfc->dstBpp;
//		wfc->hdc->bytesPerPixel = wfc->dstBpp / 8;
//
//		wfc->hdc->alpha = wfc->clrconv->alpha;
//		wfc->hdc->invert = wfc->clrconv->invert;
//
//		wfc->hdc->hwnd = (HGDI_WND) malloc(sizeof(GDI_WND));
//		wfc->hdc->hwnd->invalid = gdi_CreateRectRgn(0, 0, 0, 0);
//		wfc->hdc->hwnd->invalid->null = 1;
//
//		wfc->hdc->hwnd->count = 32;
//		wfc->hdc->hwnd->cinvalid = (HGDI_RGN) malloc(sizeof(GDI_RGN) * wfc->hdc->hwnd->count);
//		wfc->hdc->hwnd->ninvalid = 0;
//
//		if (settings->RemoteFxCodec)
//		{
//			wfc->tile = wf_image_new(wfc, 64, 64, 32, nullptr);
//		}
//	}
//
//	if (settings->WindowTitle != nullptr)
//		_snwprintf(lpWindowName, ARRAYSIZE(lpWindowName), L"%S", settings->WindowTitle);
//	else if (settings->ServerPort == 3389)
//		_snwprintf(lpWindowName, ARRAYSIZE(lpWindowName), L"FreeRDP: %S", settings->ServerHostname);
//	else
//		_snwprintf(lpWindowName, ARRAYSIZE(lpWindowName), L"FreeRDP: %S:%d", settings->ServerHostname, settings->ServerPort);
//
//	if (settings->EmbeddedWindow)
//		settings->Decorations = false;
//
//	if (wfc->fullscreen)
//		dwStyle = WS_POPUP;
//	else if (!settings->Decorations)
//		dwStyle = WS_CHILD | WS_BORDER;
//	else
//		dwStyle = WS_CAPTION | WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_SIZEBOX | WS_MAXIMIZEBOX;
//
//	if (!wfc->hwnd)
//	{
//		wfc->hwnd = CreateWindowEx((::u32) nullptr, wfc->wndClassName, lpWindowName, dwStyle,
//			0, 0, 0, 0, wfc->hWndParent, nullptr, wfc->hInstance, nullptr);
//
//		SetWindowLongPtr(wfc->hwnd, GWLP_USERDATA, (LONG_PTR) wfc);
//	}
//
//	wf_resize_window(wfc);
//
//	wf_add_system_menu(wfc);
//
//	BitBlt(wfc->primary->hdc, 0, 0, wfc->width, wfc->height, nullptr, 0, 0, BLACKNESS);
//	wfc->drawing = wfc->primary;
//
//	EventArgsInit(&e, "wfreerdp");
//	e.embed = false;
//	e.handle = (void*) wfc->hwnd;
//	PubSub_OnEmbedWindow(context->pubSub, context, &e);
//
//	ShowWindow(wfc->hwnd, SW_SHOWNORMAL);
//	UpdateWindow(wfc->hwnd);
//
//	if (settings->SoftwareGdi)
//	{
//		instance->update->BeginPaint = (pBeginPaint) wf_sw_begin_paint;
//		instance->update->EndPaint = (pEndPaint) wf_sw_end_paint;
//		instance->update->DesktopResize = (pDesktopResize) wf_sw_desktop_resize;
//	}
//	else
//	{
//		instance->update->BeginPaint = (pBeginPaint) wf_hw_begin_paint;
//		instance->update->EndPaint = (pEndPaint) wf_hw_end_paint;
//		instance->update->DesktopResize = (pDesktopResize) wf_hw_desktop_resize;
//	}
//
//	pointer_cache_register_callbacks(instance->update);
//	wf_register_pointer(context->graphics);
//
//	if (!settings->SoftwareGdi)
//	{
//		brush_cache_register_callbacks(instance->update);
//		bitmap_cache_register_callbacks(instance->update);
//		offscreen_cache_register_callbacks(instance->update);
//		wf_register_graphics(context->graphics);
//		instance->update->BitmapUpdate = wf_gdi_bitmap_update;
//	}
//
//	if (freerdp_channels_post_connect(context->channels, instance) < 0)
//		return false;
//
//	if (wfc->fullscreen)
//		floatbar_window_create(wfc);
//
//	return true;
//}
//
//static CREDUI_INFOA wfUiInfo =
//{
//	sizeof(CREDUI_INFOA),
//	nullptr,
//	"Enter your credentials",
//	"Remote Desktop Security",
//	nullptr
//};

//static BOOL wf_authenticate_raw(freerdp* instance, const ::string & title,
//		char** username, char** password, char** domain)
//{
//   //PubSub_Subscribe(instance->context->pubSub,"ConnectionResult",(pEventHandler)rdpclient_connection_result);
//   return freerdp_authenticate(instance,username,password,domain,instance->context->settings->ServerHostname,0);
//
//
//	//BOOL fSave;
//	//::u32 status;
//	//::u32 dwFlags;
//	//char UserName[CREDUI_MAX_USERNAME_LENGTH + 1];
//	//char Password[CREDUI_MAX_PASSWORD_LENGTH + 1];
//	//char User[CREDUI_MAX_USERNAME_LENGTH + 1];
//	//char Domain[CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1];
//
//	//fSave = false;
//	//ZeroMemory(UserName, sizeof(UserName));
//	//ZeroMemory(Password, sizeof(Password));
//	//dwFlags = CREDUI_FLAGS_DO_NOT_PERSIST | CREDUI_FLAGS_EXCLUDE_CERTIFICATES;
//
//	//status = CredUIPromptForCredentialsA(&wfUiInfo, title, nullptr, 0,
//	//	UserName, CREDUI_MAX_USERNAME_LENGTH + 1,
//	//	Password, CREDUI_MAX_PASSWORD_LENGTH + 1, &fSave, dwFlags);
//
//	//if (status != NO_ERROR)
//	//{
//	//	WLog_ERR(TAG, "CredUIPromptForCredentials unexpected status: 0x%08X", status);
//	//	return false;
//	//}
//
//	//ZeroMemory(User, sizeof(User));
//	//ZeroMemory(Domain, sizeof(Domain));
//
//	//status = CredUIParseUserNameA(UserName, User, sizeof(User), Domain, sizeof(Domain));
//	////WLog_ERR(TAG, "User: %s Domain: %s Password: %s", User, Domain, Password);
//	//*username = _strdup(User);
//	//if (!(*username))
//	//{
//	//	WLog_ERR(TAG, "strdup failed", status);
//	//	return false;
//	//}
//
//	//if (strlen(Domain) > 0)
//	//	*domain = _strdup(Domain);
//	//else
//	//	*domain = _strdup("\0");
//
//	//if (!(*domain))
//	//{
//	//	free(*username);
//	//	WLog_ERR(TAG, "strdup failed", status);
//	//	return false;
//	//}
//
//	//*password = _strdup(Password);
//	//if (!(*password))
//	//{
//	//	free(*username);
//	//	free(*domain);
//	//	return false;
//	//}
//
//	//return true;
//}
//
//static BOOL wf_authenticate(freerdp* instance,
//		char** username, char** password, char** domain)
//{
//	return wf_authenticate_raw(instance, instance->settings->ServerHostname,
//			username, password, domain);
//}
//
//static BOOL wf_gw_authenticate(freerdp* instance,
//		char** username, char** password, char** domain)
//{
//	char tmp[MAX_PATH];
//
//	sprintf(tmp, sizeof(tmp), "Gateway %s", instance->settings->GatewayHostname);
//	return wf_authenticate_raw(instance, tmp, username, password, domain);
//}
//
//BOOL wf_verify_certificate(freerdp* instance, char* subject, char* issuer, char* fingerprint)
//{
//#if 0
//	::u32 mode;
//	int read_size;
//	::u32 read_count;
//	TCHAR answer[2];
//	TCHAR* read_buffer;
//	HANDLE input_handle;
//#endif
//	WLog_INFO(TAG, "Certificate details:");
//	WLog_INFO(TAG, "\tSubject: %s", subject);
//	WLog_INFO(TAG, "\tIssuer: %s", issuer);
//	WLog_INFO(TAG, "\tThumbprint: %s", fingerprint);
//	WLog_INFO(TAG, "The above X.509 certificate could not be verified, possibly because you do not have "
//			  "the CA certificate in your certificate store, or the certificate has expired. "
//			  "Please look at the documentation on how to create local certificate store for a private CA.");
//	/* TODO: ask for user validation */
//#if 0
//	input_handle = GetStdHandle(STD_INPUT_HANDLE);
//
//	GetConsoleMode(input_handle, &mode);
//	mode |= ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT;
//	SetConsoleMode(input_handle, mode);
//#endif
//
//	return true;
//}
//
//static BOOL wf_auto_reconnect(freerdp* instance)
//{
//	wfContext* wfc = (wfContext *)instance->context;
//
//	::u32 num_retries = 0;
//	::u32 max_retries = instance->settings->AutoReconnectMaxRetries;
//
//	/* Only auto reconnect on network disconnects. */
//	if (freerdp_error_info(instance) != 0)
//		return false;
//
//	/* A network disconnect was detected */
//	WLog_ERR(TAG, "Network disconnect!");
//
//	if (!instance->settings->AutoReconnectionEnabled)
//	{
//		/* No auto-reconnect - just quit */
//		return false;
//	}
//
//	/* Perform an auto-reconnect. */
//	for (;;)
//	{
//		/* Quit retrying if maximum retries has been exceeded */
//		if (num_retries++ >= max_retries)
//			return false;
//
//		/* Attempt the next reconnect */
//		WLog_INFO(TAG,  "Attempting reconnect (%u of %u)", num_retries, max_retries);
//
//		if (freerdp_reconnect(instance))
//		{
//			return true;
//		}
//
//		sleep(5000_ms);
//	}
//
//	WLog_ERR(TAG, "Maximum reconnect retries exceeded");
//	return false;
//}
//
//void* wf_input_thread(void* arg)
//{
//	int status;
//	wMessage message;
//	wMessageQueue* queue;
//	freerdp* instance = (freerdp*) arg;
//
//	assert( nullptr != instance);
//
//	status = 1;
//	queue = freerdp_get_message_queue(instance, FREERDP_INPUT_MESSAGE_QUEUE);
//
//	while (MessageQueue_Wait(queue))
//	{
//		while (MessageQueue_Peek(queue, &message, true))
//		{
//			status = freerdp_message_queue_process_message(instance,
//					FREERDP_INPUT_MESSAGE_QUEUE, &message);
//
//			if (!status)
//				break;
//		}
//
//		if (!status)
//			break;
//	}
//
//	ExitThread(0);
//
//	return nullptr;
//}

//::u32 WINAPI wf_client_thread(LPVOID lpParam)
//{
//	MSG msg;
//	int width;
//	int height;
//	BOOL msg_ret;
//	int quit_msg;
//	::u32 nCount;
//	HANDLE handles[64];
//	wfContext* wfc;
//	freerdp* instance;
//	rdpContext* context;
//	rdpChannels* channels;
//	rdpSettings* settings;
//	BOOL async_input;
//	BOOL async_transport;
//	HANDLE input_thread;
//
//	instance = (freerdp*) lpParam;
//	context = instance->context;
//	wfc = (wfContext*) instance->context;
//
//	if (!freerdp_connect(instance))
//		return 0;
//
//	channels = instance->context->channels;
//	settings = instance->context->settings;
//
//	async_input = settings->AsyncInput;
//	async_transport = settings->AsyncTransport;
//
//	if (async_input)
//	{
//		if (!(input_thread = CreateThread(nullptr, 0,
//				(LPTHREAD_START_ROUTINE) wf_input_thread,
//				instance, 0, nullptr)))
//		{
//			WLog_ERR(TAG, "Failed to create async input thread.");
//			goto disconnect;
//		}
//	}
//
//	while (1)
//	{
//		nCount = 0;
//
//		if (freerdp_focus_required(instance))
//		{
//			wf_event_focus_in(wfc);
//			wf_event_focus_in(wfc);
//		}
//
//		if (!async_transport)
//		{
//			::u32 tmp = freerdp_get_event_handles(context, &handles[nCount], 64 - nCount);
//
//			if (tmp == 0)
//			{
//				WLog_ERR(TAG, "freerdp_get_event_handles failed");
//				break;
//			}
//
//			nCount += tmp;
//		}
//
//		if (MsgWaitForMultipleObjects(nCount, handles, false, 1000, QS_ALLINPUT) == WAIT_FAILED)
//		{
//			WLog_ERR(TAG, "wfreerdp_run: WaitForMultipleObjects failed: 0x%04X", get_last_error());
//			break;
//		}
//
//		if (!async_transport)
//		{
//			if (!freerdp_check_event_handles(context))
//			{
//				if (wf_auto_reconnect(instance))
//					continue;
//
//				WLog_ERR(TAG, "Failed to check FreeRDP file descriptor");
//				break;
//			}
//		}
//
//		if (freerdp_shall_disconnect(instance))
//			break;
//
//		quit_msg = false;
//
//		while (PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE))
//		{
//			msg_ret = GetMessage(&msg, nullptr, 0, 0);
//
//			if (instance->settings->EmbeddedWindow)
//			{
//				if ((msg.message == e_message_set_focus) && (msg.lParam == 1))
//				{
//					PostMessage(wfc->hwnd, e_message_set_focus, 0, 0);
//				}
//				else if ((msg.message == e_message_kill_focus) && (msg.lParam == 1))
//				{
//					PostMessage(wfc->hwnd, e_message_kill_focus, 0, 0);
//				}
//			}
//
//			if (msg.message == e_message_size)
//			{
//				width = LOWORD(msg.lParam);
//				height = HIWORD(msg.lParam);
//
//				set_window_position(wfc->hwnd, HWND_TOP, 0, 0, width, height, SWP_FRAMECHANGED);
//			}
//
//			if ((msg_ret == 0) || (msg_ret == -1))
//			{
//				quit_msg = true;
//				break;
//			}
//
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//
//		if (quit_msg)
//			break;
//	}
//
//	/* cleanup */
//	freerdp_channels_disconnect(channels, instance);
//
//	if (async_input)
//	{
//		wMessageQueue* input_queue;
//		input_queue = freerdp_get_message_queue(instance, FREERDP_INPUT_MESSAGE_QUEUE);
//		if (MessageQueue_PostQuit(input_queue, 0))
//			WaitForSingleObject(input_thread, U32_INFINITE_TIMEOUT);
//		CloseHandle(input_thread);
//	}
//
//disconnect:
//	freerdp_disconnect(instance);
//	WLog_DBG(TAG, "Main thread exited.");
//
//	ExitThread(0);
//	return 0;
//}
//
::u32 WINAPI wf_keyboard_thread(LPVOID lpParam)
{
	MSG msg;
	BOOL status;
	wfContext* wfc;
	HHOOK hook_handle;

	wfc = (wfContext*) lpParam;
	assert(nullptr != wfc);

	hook_handle = SetWindowsHookEx(WH_KEYBOARD_LL, wf_ll_kbd_proc, wfc->hInstance, 0);

	if (hook_handle)
	{
		while ((status = GetMessage(&msg, nullptr, 0, 0)) != 0)
		{
			if (status == -1)
			{
				WLog_ERR(TAG, "keyboard thread error getting message");
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		UnhookWindowsHookEx(hook_handle);
	}
	else
	{
		WLog_ERR(TAG, "failed to install keyboard hook");
	}

	WLog_DBG(TAG, "Keyboard thread exited.");
	ExitThread(0);
	return (::u32) nullptr;
}

rdpSettings* freerdp_client_get_settings(wfContext* wfc)
{
	return wfc->instance->settings;
}

int freerdp_client_focus_in(wfContext* wfc)
{
   postthreadmessage(wfc->mainThreadId, e_message_set_focus, 0, 1);
	return 0;
}

int freerdp_client_focus_out(wfContext* wfc)
{
   postthreadmessage(wfc->mainThreadId, e_message_kill_focus, 0, 1);
	return 0;
}

int freerdp_client_set_window_size(wfContext* wfc, int width, int height)
{
	WLog_DBG(TAG,  "freerdp_client_set_window_size %d, %d", width, height);

	if ((width != wfc->client_width) || (height != wfc->client_height))
	{
      postthreadmessage(wfc->mainThreadId, e_message_size, SIZE_RESTORED, ((::u32) height << 16) | (::u32) width);
	}

	return 0;
}

// TODO: Some of that code is a duplicate of wf_pre_connect. Refactor?
int freerdp_client_load_settings_from_rdp_file(wfContext* wfc, char* filename)
{
	rdpSettings* settings;

	settings = wfc->instance->settings;

	if (filename)
	{
		settings->ConnectionFile = _strdup(filename);
		if (!settings->ConnectionFile)
		{
			return 3;
		}

		// free old settings file
		freerdp_client_rdp_file_free(wfc->connectionRdpFile);
		wfc->connectionRdpFile = freerdp_client_rdp_file_new();
		WLog_INFO(TAG,  "Using connection file: %s", settings->ConnectionFile);

		if (!freerdp_client_parse_rdp_file(wfc->connectionRdpFile, settings->ConnectionFile))
		{
			return 1;
		}

		if (!freerdp_client_populate_settings_from_rdp_file(wfc->connectionRdpFile, settings))
		{
			return 2;
		}
	}

	return 0;
}

void wf_size_scrollbars(wfContext* wfc, ::u32 client_width, ::u32 client_height)
{
	if (wfc->disablewindowtracking)
		return;

	// prevent infinite message loop
	wfc->disablewindowtracking = true;

	if (wfc->instance->settings->SmartSizing)
	{
		wfc->xCurrentScroll = 0;
		wfc->yCurrentScroll = 0;

		if (wfc->xScrollVisible || wfc->yScrollVisible)
		{
			if (ShowScrollBar(wfc->hwnd, SB_BOTH, false))
			{
				wfc->xScrollVisible = false;
				wfc->yScrollVisible = false;
			}
		}
	}
	else
	{
		SCROLLINFO si;
		BOOL horiz = wfc->xScrollVisible;
		BOOL vert = wfc->yScrollVisible;;

		if (!horiz && client_width < wfc->instance->settings->DesktopWidth)
		{
			horiz = true;
		}
		else if (horiz && client_width >= wfc->instance->settings->DesktopWidth/* - GetSystemMetrics(SM_CXVSCROLL)*/)
		{
			horiz = false;
		}

		if (!vert && client_height < wfc->instance->settings->DesktopHeight)
		{
			vert = true;
		}
		else if (vert && client_height >= wfc->instance->settings->DesktopHeight/* - GetSystemMetrics(SM_CYHSCROLL)*/)
		{
			vert = false;
		}

		if (horiz == vert && (horiz != wfc->xScrollVisible && vert != wfc->yScrollVisible))
		{
			if (ShowScrollBar(wfc->hwnd, SB_BOTH, horiz))
			{
				wfc->xScrollVisible = horiz;
				wfc->yScrollVisible = vert;
			}
		}

		if (horiz != wfc->xScrollVisible)
		{
			if (ShowScrollBar(wfc->hwnd, SB_HORZ, horiz))
			{
				wfc->xScrollVisible = horiz;
			}
		}

		if (vert != wfc->yScrollVisible)
		{
			if (ShowScrollBar(wfc->hwnd, SB_VERT, vert))
			{
				wfc->yScrollVisible = vert;
			}
		}

		if (horiz)
		{
			// The horizontal scrolling range is defined by
			// (bitmap_width) - (client_width). The current horizontal
			// scroll value remains within the horizontal scrolling range.
			wfc->xMaxScroll = maximum(wfc->instance->settings->DesktopWidth - client_width, 0);
			wfc->xCurrentScroll = minimum(wfc->xCurrentScroll, wfc->xMaxScroll);
			si.cbSize = sizeof(si);
			si.fMask  = SIF_RANGE | SIF_PAGE | SIF_POS;
			si.nMin   = wfc->xMinScroll;
			si.nMax   = wfc->instance->settings->DesktopWidth;
			si.nPage  = client_width;
			si.nPos   = wfc->xCurrentScroll;
			SetScrollInfo(wfc->hwnd, SB_HORZ, &si, true);
		}

		if (vert)
		{
			// The vertical scrolling range is defined by
			// (bitmap_height) - (client_height). The current vertical
			// scroll value remains within the vertical scrolling range.
			wfc->yMaxScroll = maximum(wfc->instance->settings->DesktopHeight - client_height, 0);
			wfc->yCurrentScroll = minimum(wfc->yCurrentScroll, wfc->yMaxScroll);
			si.cbSize = sizeof(si);
			si.fMask  = SIF_RANGE | SIF_PAGE | SIF_POS;
			si.nMin   = wfc->yMinScroll;
			si.nMax   = wfc->instance->settings->DesktopHeight;
			si.nPage  = client_height;
			si.nPos   = wfc->yCurrentScroll;
			SetScrollInfo(wfc->hwnd, SB_VERT, &si, true);
		}
	}

	wfc->disablewindowtracking = false;
//	wf_update_canvas_diff(wfc);
}

BOOL wfreerdp_client_global_init(void)
{
	WSADATA wsaData;

	if (!getenv("HOME"))
	{
		char home[MAX_PATH * 2] = "HOME=";
		ansi_concatenate(home, getenv("HOMEDRIVE"));
		ansi_concatenate(home, getenv("HOMEPATH"));
		_putenv(home);
	}

	WSAStartup(0x101, &wsaData);

#if defined(WITH_DEBUG) || defined(_DEBUG)
	wf_create_console();
#endif

	freerdp_register_addin_provider((FREERDP_LOAD_CHANNEL_ADDIN_ENTRY_FN) freerdp_channels_load_static_addin_entry, 0);
	return true;
}

void wfreerdp_client_global_uninit(void)
{
	WSACleanup();
}

//BOOL wfreerdp_client_new(freerdp* instance, rdpContext* context)
//{
//	wfContext* wfc = (wfContext*) context;
//
//	if (!(wfreerdp_client_global_init()))
//		return false;
//
//	if (!(context->channels = freerdp_channels_new()))
//		return false;
//
//	instance->PreConnect = wf_pre_connect;
//	instance->PostConnect = wf_post_connect;
//	instance->Authenticate = wf_authenticate;
//	instance->GatewayAuthenticate = wf_gw_authenticate;
//	instance->VerifyCertificate = wf_verify_certificate;
//
//	wfc->instance = instance;
//	wfc->settings = instance->settings;
//
//	return true;
//}

void wfreerdp_client_free(freerdp* instance, rdpContext* context)
{
	if (!context)
		return;

	if (context->channels)
	{
//		freerdp_channels_close(context->channels, instance);
	//	freerdp_channels_free(context->channels);
		context->channels = nullptr;
	}

	if (context->cache)
	{
		cache_free(context->cache);
		context->cache = nullptr;
	}
}
//
//int wfreerdp_client_start(rdpContext* context)
//{
//	HWND hWndParent;
//	HINSTANCE hInstance;
//	wfContext* wfc = (wfContext*) context;
//	freerdp* instance = context->instance;
//
//	hInstance = GetModuleHandle(nullptr);
//	hWndParent = (HWND) instance->settings->ParentWindowId;
//	instance->settings->EmbeddedWindow = (hWndParent) ? true : false;
//
//	wfc->hWndParent = hWndParent;
//	wfc->hInstance = hInstance;
//	wfc->cursor = LoadCursor(nullptr, IDC_ARROW);
//	wfc->icon = LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_ICON1));
//	wfc->wndClassName = _tcsdup(_T("FreeRDP"));
//
//	wfc->wndClass.cbSize = sizeof(WNDCLASSEX);
//	wfc->wndClass.style = CS_HREDRAW | CS_VREDRAW;
//	wfc->wndClass.lpfnWndProc = wf_event_proc;
//	wfc->wndClass.cbClsExtra = 0;
//	wfc->wndClass.cbWndExtra = 0;
//	wfc->wndClass.hCursor = wfc->cursor;
//	wfc->wndClass.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
//	wfc->wndClass.lpszMenuName = nullptr;
//	wfc->wndClass.lpszClassName = wfc->wndClassName;
//	wfc->wndClass.hInstance = hInstance;
//	wfc->wndClass.hIcon = wfc->icon;
//	wfc->wndClass.hIconSm = wfc->icon;
//	RegisterClassEx(&(wfc->wndClass));
//
//	wfc->keyboardThread = CreateThread(nullptr, 0, wf_keyboard_thread, (void*) wfc, 0, &wfc->keyboardThreadId);
//
//	if (!wfc->keyboardThread)
//		return -1;
//
//	freerdp_client_load_addins(context->channels, instance->settings);
//
//	wfc->thread = CreateThread(nullptr, 0, wf_client_thread, (void*) instance, 0, &wfc->mainThreadId);
//
//	if (!wfc->thread)
//		return -1;
//
//	return 0;
//}

int wfreerdp_client_stop(rdpContext* context)
{
	wfContext* wfc = (wfContext*) context;

	if (wfc->thread)
	{
      postthreadmessage(wfc->mainThreadId, e_message_quit, 0, 0);

		WaitForSingleObject(wfc->thread, U32_INFINITE_TIMEOUT);
		CloseHandle(wfc->thread);
		wfc->thread = nullptr;
		wfc->mainThreadId = 0;
	}

	if (wfc->keyboardThread)
	{
      postthreadmessage(wfc->keyboardThreadId, e_message_quit, 0, 0);

		WaitForSingleObject(wfc->keyboardThread, U32_INFINITE_TIMEOUT);
		CloseHandle(wfc->keyboardThread);

		wfc->keyboardThread = nullptr;
		wfc->keyboardThreadId = 0;
	}

	return 0;
}

//int RdpClientEntry(RDP_CLIENT_ENTRY_POINTS* pEntryPoints)
//{
//	pEntryPoints->Version = 1;
//	pEntryPoints->Size = sizeof(RDP_CLIENT_ENTRY_POINTS_V1);
//
//	pEntryPoints->GlobalInit = wfreerdp_client_global_init;
//	pEntryPoints->GlobalUninit = wfreerdp_client_global_uninit;
//
//	pEntryPoints->ContextSize = sizeof(wfContext);
//	pEntryPoints->ClientNew = wfreerdp_client_new;
//	pEntryPoints->ClientFree = wfreerdp_client_free;
//
//	pEntryPoints->ClientStart = wfreerdp_client_start;
//	pEntryPoints->ClientStop = wfreerdp_client_stop;
//
//	return 0;
//}
