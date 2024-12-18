/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * Event Handling
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

#include <freerdp/freerdp.h>

#include "wf_client.h"

#include "wf_gdi.h"
#include "wf_event.h"

#include <freerdp/happening.h>

static HWND g_focus_hWnd;

#define X_POS(lParam) ((::u3216) (lParam & 0xFFFF))
#define Y_POS(lParam) ((::u3216) ((lParam >> 16) & 0xFFFF))

BOOL wf_scale_blt(wfContext* wfc, HDC hdc, int x, int y, int w, int h, HDC hdcSrc, int x1, int y1, unsigned int rop);
void wf_scale_mouse_event(wfContext* wfc, rdpInput* input, ::u3216 flags, ::u3216 x, ::u3216 y);

static BOOL g_flipping_in;
static BOOL g_flipping_out;

static BOOL alt_ctrl_down()
{
	return ((GetAsyncKeyState(VK_CONTROL) & 0x8000) ||
		(GetAsyncKeyState(VK_MENU) & 0x8000));
}

LRESULT CALLBACK wf_ll_kbd_proc(int nCode, WPARAM wParam, LPARAM lParam)
{
	wfContext* wfc;
	unsigned int rdp_scancode;
	rdpInput* input;
	PKBDLLHOOKSTRUCT p;

	DEBUG_KBD("Low-level keyboard hook, hWnd %X nCode %X wParam %X", g_focus_hWnd, nCode, wParam);

	if (g_flipping_in)
	{
		if (!alt_ctrl_down())
			g_flipping_in = false;
		return CallNextHookEx(nullptr, nCode, wParam, lParam);
	}

	if (g_focus_hWnd && (nCode == HC_ACTION))
	{
		switch (wParam)
		{
			case e_message_key_down:
			case e_message_sys_key_down:
			case e_message_key_up:
			case e_message_sys_key_up:
				wfc = (wfContext*) GetWindowLongPtr(g_focus_hWnd, GWLP_USERDATA);
				p = (PKBDLLHOOKSTRUCT) lParam;

				if (!wfc || !p)
					return 1;
				
				input = wfc->instance->input;
				rdp_scancode = MAKE_RDP_SCANCODE((unsigned char) p->scanCode, p->flags & LLKHF_EXTENDED);

				DEBUG_KBD("keydown %d scanCode %04X flags %02X vkCode %02X",
					(wParam == e_message_key_down), (unsigned char) p->scanCode, p->flags, p->vkCode);

				if (wfc->fs_toggle &&
					((p->vkCode == VK_RETURN) || (p->vkCode == VK_CANCEL)) &&
					(GetAsyncKeyState(VK_CONTROL) & 0x8000) &&
					(GetAsyncKeyState(VK_MENU) & 0x8000)) /* could also use flags & LLKHF_ALTDOWN */
				{
					if (wParam == e_message_key_down)
					{
						wf_toggle_fullscreen(wfc);
						return 1;
					}
				}

				if (rdp_scancode == RDP_SCANCODE_NUMLOCK_EXTENDED)
				{
					/* Windows sends NumLock as extended - rdp doesn't */
					DEBUG_KBD("hack: NumLock (x45) should not be extended");
					rdp_scancode = RDP_SCANCODE_NUMLOCK;
				}
				else if (rdp_scancode == RDP_SCANCODE_NUMLOCK)
				{
					/* Windows sends Pause as if it was a RDP NumLock (handled above).
					 * It must however be sent as a one-shot Ctrl+NumLock */
					if (wParam == e_message_key_down)
					{
						DEBUG_KBD("Pause, sent as Ctrl+NumLock");
						freerdp_input_send_keyboard_event_ex(input, true, RDP_SCANCODE_LCONTROL);
						freerdp_input_send_keyboard_event_ex(input, true, RDP_SCANCODE_NUMLOCK);
						freerdp_input_send_keyboard_event_ex(input, false, RDP_SCANCODE_LCONTROL);
						freerdp_input_send_keyboard_event_ex(input, false, RDP_SCANCODE_NUMLOCK);
					}
					else
					{
						DEBUG_KBD("Pause up");
					}

					return 1;
				}
				else if (rdp_scancode == RDP_SCANCODE_RSHIFT_EXTENDED)
				{
					DEBUG_KBD("right shift (x36) should not be extended");
					rdp_scancode = RDP_SCANCODE_RSHIFT;
				}

				freerdp_input_send_keyboard_event_ex(input, !(p->flags & LLKHF_UP), rdp_scancode);

				if (p->vkCode == VK_NUMLOCK || p->vkCode == VK_CAPITAL || p->vkCode == VK_SCROLL || p->vkCode == VK_KANA)
					DEBUG_KBD("lock keys are processed on client side too to toggle their indicators");
				else
					return 1;

				break;
		}
	}

	if (g_flipping_out)
	{
		if (!alt_ctrl_down())
		{
			g_flipping_out = false;
			g_focus_hWnd = nullptr;
		}
	}

	return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

void wf_event_focus_in(wfContext* wfc)
{
	::u3216 syncFlags;
	rdpInput* input;
	::int_point pt;
	::int_rectangle rc;

	input = wfc->instance->input;

	syncFlags = 0;

	if (GetKeyState(VK_NUMLOCK))
		syncFlags |= KBD_SYNC_NUM_LOCK;

	if (GetKeyState(VK_CAPITAL))
		syncFlags |= KBD_SYNC_CAPS_LOCK;

	if (GetKeyState(VK_SCROLL))
		syncFlags |= KBD_SYNC_SCROLL_LOCK;

	if (GetKeyState(VK_KANA))
		syncFlags |= KBD_SYNC_KANA_LOCK;

	input->FocusInEvent(input, syncFlags);

	/* send pointer position if the cursor is currently inside our client area */
	GetCursorPos(&pt);
	screen_to_client(wfc->hwnd, &pt);
	this->rectangle(wfc->hwnd, &rc);

	if (point.x() >= rc.left() && point.x() < rc.right() && point.y() >= rc.top() && point.y() < rc.bottom())
		input->MouseEvent(input, PTR_FLAGS_MOVE, (::u3216)point.x(), (::u3216)point.y());
}

static int wf_event_process_WM_MOUSEWHEEL(wfContext* wfc, HWND hWnd, unsigned int Msg, WPARAM wParam, LPARAM lParam)
{
	int delta;
	int flags;
	rdpInput* input;

	DefWindowProc(hWnd, Msg, wParam, lParam);
	input = wfc->instance->input;
	delta = ((signed short) HIWORD(wParam)); /* GET_WHEEL_DELTA_WPARAM(wParam); */

	if (delta > 0)
	{
		flags = PTR_FLAGS_WHEEL | 0x0078;
	}
	else
	{
		flags = PTR_FLAGS_WHEEL | PTR_FLAGS_WHEEL_NEGATIVE | 0x0088;
	}

	input->MouseEvent(input, flags, 0, 0);
	
	return 0;
}

void wf_sizing(wfContext* wfc, WPARAM wParam, LPARAM lParam)
{
	// Holding the CTRL key down while resizing the window will force the desktop aspect ratio.
	::int_rectangle * int_rectangle;

	if (wfc->instance->settings->SmartSizing && (GetAsyncKeyState(VK_CONTROL) & 0x8000))
	{
		rectangle = (::int_rectangle *) wParam;

		switch(lParam)
		{
			case WMSZ_LEFT:
			case WMSZ_RIGHT:
			case WMSZ_BOTTOMRIGHT:
				// Adjust height
				int_rectangle->bottom() = int_rectangle->top() + wfc->height * (int_rectangle->right() - int_rectangle->left()) / wfc->instance->settings->DesktopWidth;
				break;

			case WMSZ_TOP:
			case WMSZ_BOTTOM:
			case WMSZ_TOPRIGHT:			
				// Adjust width
				int_rectangle->right() = int_rectangle->left() + wfc->width * (int_rectangle->bottom() - int_rectangle->top()) / wfc->instance->settings->DesktopHeight;
				break;

			case WMSZ_BOTTOMLEFT:
			case WMSZ_TOPLEFT:
				// adjust width
				int_rectangle->left() = int_rectangle->right() - (wfc->width * (int_rectangle->bottom() - int_rectangle->top()) / wfc->instance->settings->DesktopHeight);

				break;
		}
	}

}

//LRESULT CALLBACK wf_event_proc(HWND hWnd, unsigned int Msg, WPARAM wParam, LPARAM lParam)
//{
//	HDC hdc;
//	LONG_PTR ptr;
//	wfContext* wfc;
//	int x, y, w, h;
//	PAINTSTRUCT ps;
//	rdpInput* input;
//	BOOL processed;
//	::int_rectangle windowRect;
//	MINMAXINFO* minmax;
//	SCROLLINFO si;
//
//	processed = true;
//	ptr = GetWindowLongPtr(hWnd, GWLP_USERDATA);
//	wfc = (wfContext*) ptr;
//
//
//	if (wfc != nullptr)
//	{
//		input = wfc->instance->input;
//
//		switch (Msg)
//		{
//			case e_message_reposition:
//				if (!wfc->disablewindowtracking)
//				{
//					int x = (int)(short) LOWORD(lParam);
//					int y = (int)(short) HIWORD(lParam);
//					wfc->client_x = x;
//					wfc->client_y = y;
//				}
//				break;
//
//			case WM_GETMINMAXINFO:
//				if (wfc->instance->settings->SmartSizing)
//				{
//					processed = false;
//				}
//				else
//				{
//					// Set maximum window int_size for resizing
//
//					minmax = (MINMAXINFO*) lParam;
//
//					//always use the last determined canvas diff, because it could be
//					//that the window is minimized when this gets called
//					//wf_update_canvas_diff(wfc);
//
//					if (!wfc->fullscreen)
//					{
//						// add window decoration
//						minmax->ptMaxTrackSize.x() = wfc->width + wfc->diff.x();
//						minmax->ptMaxTrackSize.y() = wfc->height + wfc->diff.y();
//					}
//				}
//				break;
//
//			case WM_SIZING:
//				wf_sizing(wfc, lParam, wParam);
//				break;
//			
//			case e_message_size:
//				window_rectangle(wfc->hwnd, &windowRect);
//				
//				if (!wfc->fullscreen)
//				{
//					wfc->client_width = LOWORD(lParam);
//					wfc->client_height = HIWORD(lParam);
//					wfc->client_x = windowRect.left();
//					wfc->client_y = windowRect.top();
//				}
//				
//				if (wfc->client_width && wfc->client_height)
//				{
//					wf_size_scrollbars(wfc, LOWORD(lParam), HIWORD(lParam));
//
//					// Workaround: when the window is maximized, the call to "ShowScrollBars" returns true but has no effect.
//					if (wParam == SIZE_MAXIMIZED && !wfc->fullscreen)
//						set_window_position(wfc->hwnd, HWND_TOP, 0, 0, windowRect.right() - windowRect.left(), windowRect.bottom() - windowRect.top(), SWP_NOMOVE | SWP_FRAMECHANGED);
//				}
//
//				break;
//
//			case WM_EXITSIZEMOVE:
//				wf_size_scrollbars(wfc, wfc->client_width, wfc->client_height);
//				break;
//
//			case e_message_erase_background:
//				/* Say we handled it - prevents flickering */
//				return (LRESULT) 1;
//
//			case e_message_paint:
//				hdc = BeginPaint(hWnd, &ps);
//
//				x = ps.rcPaint.left();
//				y = ps.rcPaint.top();
//				w = ps.rcPaint.right() - ps.rcPaint.left() + 1;
//				h = ps.rcPaint.bottom() - ps.rcPaint.top() + 1;
//
//				wf_scale_blt(wfc, hdc, x, y, w, h, ((wfBitmap *)wfc->primary)->hdc, x - wfc->offset_x + wfc->xCurrentScroll, y - wfc->offset_y + wfc->yCurrentScroll);
//
//				EndPaint(hWnd, &ps);
//				break;
//
//			case e_message_left_button_down:
//				wf_scale_mouse_event(wfc, input, PTR_FLAGS_DOWN | PTR_FLAGS_BUTTON1, X_POS(lParam) - wfc->offset_x, Y_POS(lParam) - wfc->offset_y);
//				break;
//
//			case e_message_left_button_up:
//				wf_scale_mouse_event(wfc, input, PTR_FLAGS_BUTTON1, X_POS(lParam) - wfc->offset_x, Y_POS(lParam) - wfc->offset_y);
//				break;
//
//			case e_message_right_button_down:
//				wf_scale_mouse_event(wfc, input, PTR_FLAGS_DOWN | PTR_FLAGS_BUTTON2, X_POS(lParam) - wfc->offset_x, Y_POS(lParam) - wfc->offset_y);
//				break;
//
//			case e_message_right_button_up:
//				wf_scale_mouse_event(wfc, input, PTR_FLAGS_BUTTON2, X_POS(lParam) - wfc->offset_x, Y_POS(lParam) - wfc->offset_y);
//				break;
//
//			case e_message_mouse_move:
//				wf_scale_mouse_event(wfc, input, PTR_FLAGS_MOVE, X_POS(lParam) - wfc->offset_x, Y_POS(lParam) - wfc->offset_y);
//				break;
//
//			case e_message_mouse_wheel:
//				wf_event_process_WM_MOUSEWHEEL(wfc, hWnd, Msg, wParam, lParam);
//				break;
//
//			case e_message_set_cursor:
//				if (LOWORD(lParam) == HTCLIENT)
//					SetCursor(wfc->cursor);
//				else
//					DefWindowProc(hWnd, Msg, wParam, lParam);
//				break;
//
//			case e_message_scroll_x:
//				{
//					int xDelta;     // xDelta = new_pos - current_pos  
//					int xNewPos;    // ___new position 
//					int yDelta = 0; 
// 
//					switch (LOWORD(wParam)) 
//					{ 
//						// User clicked the scroll bar shaft left of the scroll box. 
//						case SB_PAGEUP: 
//							xNewPos = wfc->xCurrentScroll - 50;
//							break; 
// 
//						// User clicked the scroll bar shaft right of the scroll box. 
//						case SB_PAGEDOWN: 
//							xNewPos = wfc->xCurrentScroll + 50;
//							break; 
// 
//						// User clicked the left arrow. 
//						case SB_LINEUP: 
//							xNewPos = wfc->xCurrentScroll - 5;
//							break; 
// 
//						// User clicked the right arrow. 
//						case SB_LINEDOWN: 
//							xNewPos = wfc->xCurrentScroll + 5;
//							break; 
// 
//						// User dragged the scroll box. 
//						case SB_THUMBPOSITION: 
//							xNewPos = HIWORD(wParam); 
//
//						// user is dragging the scrollbar
//						case SB_THUMBTRACK :
//							xNewPos = HIWORD(wParam); 
//							break; 
// 
//						default: 
//							xNewPos = wfc->xCurrentScroll;
//					} 
// 
//					// New position must be between 0 and the screen width. 
//					xNewPos = maximum(0, xNewPos); 
//					xNewPos = minimum(wfc->xMaxScroll, xNewPos);
// 
//					// If the current position does not change, do not scroll.
//					if (xNewPos == wfc->xCurrentScroll)
//						break; 
// 
//					// Determine the amount scrolled (in pixels). 
//					xDelta = xNewPos - wfc->xCurrentScroll;
// 
//					// Reset the current scroll position. 
//					wfc->xCurrentScroll = xNewPos;
// 
//					// Scroll the window. (The system repaints most of the 
//					// client area when ScrollWindowEx is called; however, it is 
//					// necessary to call UpdateWindow in order to repaint the 
//					// int_rectangle of pixels that were invalidated.) 
//					ScrollWindowEx(wfc->hwnd, -xDelta, -yDelta, (const ::int_rectangle *) nullptr,
//						(const ::int_rectangle *) nullptr, (HRGN) nullptr, (PRECT) nullptr,
//						SW_INVALIDATE); 
//					UpdateWindow(wfc->hwnd);
// 
//					// Reset the scroll bar. 
//					si.cbSize = sizeof(si); 
//					si.fMask  = SIF_POS; 
//					si.nPos   = wfc->xCurrentScroll;
//					SetScrollInfo(wfc->hwnd, SB_HORZ, &si, true);
//				}
//				break;
//
//				case e_message_scroll_y:
//				{ 
//					int xDelta = 0; 
//					int yDelta;     // yDelta = new_pos - current_pos 
//					int yNewPos;    // ___new position 
// 
//					switch (LOWORD(wParam)) 
//					{ 
//						// User clicked the scroll bar shaft above the scroll box. 
//						case SB_PAGEUP: 
//							yNewPos = wfc->yCurrentScroll - 50;
//							break; 
// 
//						// User clicked the scroll bar shaft below the scroll box. 
//						case SB_PAGEDOWN: 
//							yNewPos = wfc->yCurrentScroll + 50;
//							break; 
// 
//						// User clicked the top arrow. 
//						case SB_LINEUP: 
//							yNewPos = wfc->yCurrentScroll - 5;
//							break; 
// 
//						// User clicked the bottom arrow. 
//						case SB_LINEDOWN: 
//							yNewPos = wfc->yCurrentScroll + 5;
//							break; 
// 
//						// User dragged the scroll box. 
//						case SB_THUMBPOSITION: 
//							yNewPos = HIWORD(wParam); 
//							break; 
// 
//						// user is dragging the scrollbar
//						case SB_THUMBTRACK :
//							yNewPos = HIWORD(wParam); 
//							break; 
//
//						default: 
//							yNewPos = wfc->yCurrentScroll;
//					} 
// 
//					// New position must be between 0 and the screen height. 
//					yNewPos = maximum(0, yNewPos); 
//					yNewPos = minimum(wfc->yMaxScroll, yNewPos);
// 
//					// If the current position does not change, do not scroll.
//					if (yNewPos == wfc->yCurrentScroll)
//						break; 
// 
//					// Determine the amount scrolled (in pixels). 
//					yDelta = yNewPos - wfc->yCurrentScroll;
// 
//					// Reset the current scroll position. 
//					wfc->yCurrentScroll = yNewPos;
// 
//					// Scroll the window. (The system repaints most of the 
//					// client area when ScrollWindowEx is called; however, it is 
//					// necessary to call UpdateWindow in order to repaint the 
//					// int_rectangle of pixels that were invalidated.) 
//					ScrollWindowEx(wfc->hwnd, -xDelta, -yDelta, (const ::int_rectangle *) nullptr,
//						(const ::int_rectangle *) nullptr, (HRGN) nullptr, (PRECT) nullptr,
//						SW_INVALIDATE); 
//					UpdateWindow(wfc->hwnd);
// 
//					// Reset the scroll bar. 
//					si.cbSize = sizeof(si); 
//					si.fMask  = SIF_POS; 
//					si.nPos   = wfc->yCurrentScroll;
//					SetScrollInfo(wfc->hwnd, SB_VERT, &si, true);
//				}
//				break; 
//
//				case WM_SYSCOMMAND:
//				{
//					if (wParam == SYSCOMMAND_ID_SMARTSIZING)
//					{
//						HMENU hMenu = GetSystemMenu(wfc->hwnd, false);
//						freerdp_set_param_bool(wfc->instance->settings, FreeRDP_SmartSizing, !wfc->instance->settings->SmartSizing);
//						CheckMenuItem(hMenu, SYSCOMMAND_ID_SMARTSIZING, wfc->instance->settings->SmartSizing ? MF_CHECKED : MF_UNCHECKED);
//
//					}
//					else
//					{
//						processed = false;
//					}
//				}
//				break;
//
//			default:
//				processed = false;
//				break;
//		}
//	}
//	else
//	{
//		processed = false;
//	}
//
//	if (processed)
//		return 0;
//
//	switch (Msg)
//	{
//		case e_message_destroy:
//			PostQuitMessage(e_message_quit);
//			break;
//
//		case e_message_set_cursor:
//			if (LOWORD(lParam) == HTCLIENT)
//				SetCursor(wfc->hDefaultCursor);
//			else
//				DefWindowProc(hWnd, Msg, wParam, lParam);
//			break;
//
//		case e_message_set_focus:
//			DEBUG_KBD("getting focus %X", hWnd);
//			if (alt_ctrl_down())
//				g_flipping_in = true;
//			g_focus_hWnd = hWnd;
//			freerdp_set_focus(wfc->instance);
//			break;
//
//		case e_message_kill_focus:
//			if (g_focus_hWnd == hWnd && wfc && !wfc->fullscreen)
//			{
//				DEBUG_KBD("loosing focus %X", hWnd);
//				if (alt_ctrl_down())
//					g_flipping_out = true;
//				else
//					g_focus_hWnd = nullptr;
//			}
//			break;
//
//		case e_message_activate:
//			{
//				int activate = (int)(short) LOWORD(wParam);
//				if (activate != WA_INACTIVE)
//				{
//					if (alt_ctrl_down())
//						g_flipping_in = true;
//					g_focus_hWnd = hWnd;
//				}
//				else
//				{
//					if (alt_ctrl_down())
//						g_flipping_out = true;
//					else
//						g_focus_hWnd = nullptr;
//				}
//			}
//
//		default:
//			return DefWindowProc(hWnd, Msg, wParam, lParam);
//			break;
//	}
//
//	return 0;
//}
//
//BOOL wf_scale_blt(wfContext* wfc, HDC hdc, int x, int y, int w, int h, HDC hdcSrc, int x1, int y1, unsigned int rop)
//{
//	int ww, wh, dw, dh;
//
//	if (!wfc->client_width)
//		wfc->client_width = wfc->width;
//
//	if (!wfc->client_height)
//		wfc->client_height = wfc->height;
//
//	ww = wfc->client_width;
//	wh = wfc->client_height;
//	dw = wfc->instance->settings->DesktopWidth;
//	dh = wfc->instance->settings->DesktopHeight;
//
//	if (!ww)
//		ww = dw;
//
//	if (!wh)
//		wh = dh;
//
//	if (wfc->fullscreen || !wfc->instance->settings->SmartSizing || (ww == dw && wh == dh))
//	{
//		return BitBlt(hdc, x, y, w, h, wfc->primary->hdc, x1, y1);
//	}
//	else
//	{
//		set_interpolation_mode(hdc, e_interpolation_mode_high_quality_bicubic);
//		SetBrushOrgEx(hdc, 0, 0, nullptr);
//
//		return StretchBlt(hdc, 0, 0, ww, wh, wfc->primary->hdc, 0, 0, dw, dh);
//	}
//
//	return true;
//}

void wf_scale_mouse_event(wfContext* wfc, rdpInput* input, ::u3216 flags, ::u3216 x, ::u3216 y)
{
	int ww, wh, dw, dh;
	rdpContext* context;
	MouseEventEventArgs eventArgs;

	if (!wfc->client_width)
		wfc->client_width = wfc->width;

	if (!wfc->client_height)
		wfc->client_height = wfc->height;

	ww = wfc->client_width;
	wh = wfc->client_height;
	dw = wfc->instance->settings->DesktopWidth;
	dh = wfc->instance->settings->DesktopHeight;

	if (!wfc->instance->settings->SmartSizing || ((ww == dw) && (wh == dh)))
		input->MouseEvent(input, flags, x + wfc->xCurrentScroll, y + wfc->yCurrentScroll);
	else
		input->MouseEvent(input, flags, x * dw / ww + wfc->xCurrentScroll, y * dh / wh + wfc->yCurrentScroll);

	eventArgs.flags = flags;
	eventArgs.x() = x;
	eventArgs.y() = y;
	context = (rdpContext*) wfc;
	PubSub_OnMouseEvent(context->pubSub, context, &eventArgs);
}
