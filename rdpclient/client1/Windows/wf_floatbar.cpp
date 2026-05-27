/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * Windows Float Bar
 *
 * Copyright 2013 Zhang Zhaolong <zhangzl2013@126.com>
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

#include <winpr/crt.h>
#include <winpr/windows.h>

#include "resource.h"

#include "wf_client.h"
#include "wf_f32bar.h"
#include "wf_gdi.h"

typedef struct _Button Button;

/* TIMERs */
#define TIMER_HIDE          1
#define TIMER_ANIMAT_SHOW   2
#define TIMER_ANIMAT_HIDE   3

/* Button Type */
#define BUTTON_LOCKPIN      0
#define BUTTON_MINIMIZE     1
#define BUTTON_RESTORE      2
#define BUTTON_CLOSE        3
#define BTN_MAX             4

/* bmp i32_size */
#define BACKGROUND_W        581
#define BACKGROUND_H        29
#define LOCK_X              13
#define MINIMIZE_X          (BACKGROUND_W - 91)
#define CLOSE_X             (BACKGROUND_W - 37)
#define RESTORE_X           (BACKGROUND_W - 64)

#define BUTTON_Y            2
#define BUTTON_WIDTH        24
#define BUTTON_HEIGHT       24

struct _Button {
	FloatBar* f32bar;
	::i32 type;
	::i32 x, y, h, w;
	::i32 active;
	HBITMAP bmp;
	HBITMAP bmp_act;

	/* Lock Specified */
	HBITMAP locked_bmp;
	HBITMAP locked_bmp_act;
	HBITMAP unlocked_bmp;
	HBITMAP unlocked_bmp_act;
};

struct _FloatBar {
	HWND parent;
	HWND hwnd;
	::i32_rectangle i32_rectangle;
	::i32 width;
	::i32 height;
	wfContext* wfc;
	Button* buttons[BTN_MAX];
	BOOL shown;
	BOOL locked;
	HDC hdcmem;
	HBITMAP background;
};

static ::i32 button_hit(Button* button)
{
	FloatBar* f32bar = button->f32bar;

	switch (button->type)
	{
		case BUTTON_LOCKPIN:
			if (!f32bar->locked)
			{
				button->bmp = button->locked_bmp;
				button->bmp_act = button->locked_bmp_act;
			}
			else
			{
				button->bmp = button->unlocked_bmp;
				button->bmp_act = button->unlocked_bmp_act;
			}

			f32bar->locked = ~f32bar->locked;
			InvalidateRect(button->f32bar->hwnd, nullptr, false);
			UpdateWindow(button->f32bar->hwnd);
			break;

		case BUTTON_MINIMIZE:
			ShowWindow(f32bar->parent, SW_MINIMIZE);
			break;

		case BUTTON_RESTORE:
			wf_toggle_fullscreen(f32bar->wfc);
			break;

		case BUTTON_CLOSE:
			SendMessage(f32bar->parent, ::user::e_message_destroy, 0 , 0);
			break;

		default:
			return 0;
	}

	return 0;
}

static ::i32 button_paint(Button* button, HDC hdc)
{
	FloatBar* f32bar = button->f32bar;

	SelectObject(f32bar->hdcmem, button->active ? button->bmp_act : button->bmp);
	StretchBlt(hdc, button->x, button->y, button->w, button->h, f32bar->hdcmem, 0, 0, button->w, button->h);

	return 0;
}

static Button* f32bar_create_button(FloatBar* f32bar, ::i32 type, ::i32 resid, ::i32 resid_act, ::i32 x, ::i32 y, ::i32 h, ::i32 w)
{
	Button *button;

	button = (Button *)malloc(sizeof(Button));

	if (!button)
		return nullptr;

	button->f32bar = f32bar;
	button->type = type;
	button->x = x;
	button->y = y;
	button->w = w;
	button->h = h;
	button->active = false;

	button->bmp = (HBITMAP)LoadImage(f32bar->wfc->hInstance, MAKEINTRESOURCE(resid), IMAGE_BITMAP, w, h, LR_DEFAULTCOLOR);
	button->bmp_act = (HBITMAP)LoadImage(f32bar->wfc->hInstance, MAKEINTRESOURCE(resid_act), IMAGE_BITMAP, w, h, LR_DEFAULTCOLOR);

	return button;
}

static Button* f32bar_create_lock_button(FloatBar* f32bar,
									::i32 unlock_resid, ::i32 unlock_resid_act,
									::i32 lock_resid, ::i32 lock_resid_act,
									::i32 x, ::i32 y, ::i32 h, ::i32 w)
{
	Button* button;

	button = f32bar_create_button(f32bar, BUTTON_LOCKPIN, unlock_resid, unlock_resid_act, x, y, h, w);

	if (!button)
		return nullptr;

	button->unlocked_bmp = button->bmp;
	button->unlocked_bmp_act = button->bmp_act;
	button->locked_bmp = (HBITMAP)LoadImage(f32bar->wfc->hInstance, MAKEINTRESOURCE(lock_resid), IMAGE_BITMAP, w, h, LR_DEFAULTCOLOR);
	button->locked_bmp_act = (HBITMAP)LoadImage(f32bar->wfc->hInstance, MAKEINTRESOURCE(lock_resid_act), IMAGE_BITMAP, w, h, LR_DEFAULTCOLOR);

	return button;
}

static Button* f32bar_get_button(FloatBar* f32bar, ::i32 x, ::i32 y)
{
	::i32 i;

	if (y > BUTTON_Y && y < BUTTON_Y + BUTTON_HEIGHT)
		for (i = 0; i < BTN_MAX; i++)
			if (x > f32bar->buttons[i]->x && x < f32bar->buttons[i]->x + f32bar->buttons[i]->w)
				return f32bar->buttons[i];

	return nullptr;
}

static ::i32 f32bar_paint(FloatBar* f32bar, HDC hdc)
{
	::i32 i;

	/* paint background */
	SelectObject(f32bar->hdcmem, f32bar->background);
	StretchBlt(hdc, 0, 0, BACKGROUND_W, BACKGROUND_H, f32bar->hdcmem, 0, 0, BACKGROUND_W, BACKGROUND_H);

	/* paint buttons */
	for (i = 0; i < BTN_MAX; i++)
		button_paint(f32bar->buttons[i], hdc);

	return 0;
}

static ::i32 f32bar_animation(FloatBar* f32bar, BOOL show)
{
	set_timer(f32bar->hwnd, show ? TIMER_ANIMAT_SHOW : TIMER_ANIMAT_HIDE, 10, nullptr);
	f32bar->shown = show;
	return 0;
}

LRESULT CALLBACK f32bar_proc(HWND hWnd, ::u32 Msg, WPARAM wParam, LPARAM lParam)
{
	static ::i32 dragging = false;
	static ::i32 lbtn_dwn = false;
	static ::i32 btn_dwn_x = 0;
	static FloatBar* f32bar;
	static TRACKMOUSEEVENT tme;

	PAINTSTRUCT ps;
	Button* button;
	HDC hdc;
	::i32 pos_x;
	::i32 pos_y;

	::i32 xScreen = GetSystemMetrics(SM_CXSCREEN);

	switch(Msg)
	{
		case ::user::e_message_create:
			f32bar = (FloatBar *)((CREATESTRUCT *)lParam)->lpCreateParams;
			f32bar->hwnd = hWnd;
			f32bar->parent = get_parent(hWnd);

			window_rectangle(f32bar->hwnd, &f32bar->rectangle);
			f32bar->width = f32bar->rectangle.right - f32bar->rectangle.left;
			f32bar->height = f32bar->rectangle.bottom - f32bar->rectangle.top;

			hdc = GetDC(hWnd);
			f32bar->hdcmem = create_compatible_graphics(hdc);
			ReleaseDC(hWnd, hdc);

			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = hWnd;
			tme.dwHoverTime = HOVER_DEFAULT;

			set_timer(hWnd, TIMER_HIDE, 3000, nullptr);
			break;

		case ::user::e_message_paint:
			hdc = BeginPaint(hWnd, &ps);
			f32bar_paint(f32bar, hdc);
			EndPaint(hWnd, &ps);
			break;

		case ::user::e_message_left_button_down:
			pos_x = lParam & 0xffff;
			pos_y = (lParam >> 16) & 0xffff;

			button = f32bar_get_button(f32bar, pos_x, pos_y);
			if (!button)
			{
				SetCapture(hWnd);
				dragging = true;
				btn_dwn_x = lParam & 0xffff;
			}
			else
				lbtn_dwn = true;

			break;

		case ::user::e_message_left_button_up:
			pos_x = lParam & 0xffff;
			pos_y = (lParam >> 16) & 0xffff;

			ReleaseCapture();
			dragging = false;

			if (lbtn_dwn)
			{
				button = f32bar_get_button(f32bar, pos_x, pos_y);
				if (button)
					button_hit(button);
				lbtn_dwn = false;
			}
			break;

		case ::user::e_message_mouse_move:
			kill_timer(hWnd, TIMER_HIDE);
			pos_x = lParam & 0xffff;
			pos_y = (lParam >> 16) & 0xffff;

			if (!f32bar->shown)
				f32bar_animation(f32bar, true);

			if (dragging)
			{
				f32bar->rectangle.left = f32bar->rectangle.left + (lParam & 0xffff) - btn_dwn_x;

				if (f32bar->rectangle.left < 0)
					f32bar->rectangle.left = 0;
				else if (f32bar->rectangle.left > xScreen - f32bar->width)
					f32bar->rectangle.left = xScreen - f32bar->width;

				MoveWindow(hWnd, f32bar->rectangle.left, f32bar->rectangle.top, f32bar->width, f32bar->height, true);
			}
			else
			{
				::i32 i;

				for (i = 0; i < BTN_MAX; i++)
					f32bar->buttons[i]->active = false;

				button = f32bar_get_button(f32bar, pos_x, pos_y);
				if (button)
					button->active = true;

				InvalidateRect(hWnd, nullptr, false);
				UpdateWindow(hWnd);
			}

			TrackMouseEvent(&tme);
			break;

		case ::user::e_message_capture_changed:
			dragging = false;
			break;

		case ::user::e_message_mouse_leave:
		{
			::i32 i;

			for (i = 0; i < BTN_MAX; i++)
				f32bar->buttons[i]->active = false;

			InvalidateRect(hWnd, nullptr, false);
			UpdateWindow(hWnd);

			set_timer(hWnd, TIMER_HIDE, 3000, nullptr);
			break;
		}
		case ::user::e_message_timer:
			switch (wParam)
			{
				case TIMER_HIDE:
				{
					kill_timer(hWnd, TIMER_HIDE);
					if (!f32bar->locked)
						f32bar_animation(f32bar, false);
					break;
				}
				case TIMER_ANIMAT_SHOW:
				{
					static ::i32 y = 0;

					MoveWindow(f32bar->hwnd, f32bar->rectangle.left, (y++ - f32bar->height), f32bar->width, f32bar->height, true);
					if (y == f32bar->height)
					{
						y = 0;
						kill_timer(hWnd, wParam);
					}
					break;
				}
				case TIMER_ANIMAT_HIDE:
				{
					static ::i32 y = 0;

					MoveWindow(f32bar->hwnd, f32bar->rectangle.left, -y++, f32bar->width, f32bar->height, true);
					if (y == f32bar->height)
					{
						y = 0;
						kill_timer(hWnd, wParam);
					}
					break;
				}
				default:
					break;
			}
			break;

		case ::user::e_message_destroy:
			DeleteDC(f32bar->hdcmem);
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	return 0;
}

static FloatBar* f32bar_create(wfContext* wfc)
{
	FloatBar* f32bar;

	f32bar = (FloatBar *)malloc(sizeof(FloatBar));

	if (!f32bar)
		return nullptr;

	f32bar->locked = false;
	f32bar->shown = true;
	f32bar->hwnd = nullptr;
	f32bar->parent = wfc->hwnd;
	f32bar->wfc = wfc;
	f32bar->hdcmem = nullptr;

	f32bar->background = (HBITMAP)LoadImage(wfc->hInstance, MAKEINTRESOURCE(IDB_BACKGROUND), IMAGE_BITMAP, BACKGROUND_W, BACKGROUND_H, LR_DEFAULTCOLOR);
	f32bar->buttons[0] = f32bar_create_button(f32bar, BUTTON_MINIMIZE, IDB_MINIMIZE, IDB_MINIMIZE_ACT, MINIMIZE_X, BUTTON_Y, BUTTON_HEIGHT, BUTTON_WIDTH);
	f32bar->buttons[1] = f32bar_create_button(f32bar, BUTTON_RESTORE, IDB_RESTORE, IDB_RESTORE_ACT, RESTORE_X, BUTTON_Y, BUTTON_HEIGHT, BUTTON_WIDTH);
	f32bar->buttons[2] = f32bar_create_button(f32bar, BUTTON_CLOSE, IDB_CLOSE, IDB_CLOSE_ACT, CLOSE_X, BUTTON_Y, BUTTON_HEIGHT, BUTTON_WIDTH);
	f32bar->buttons[3] = f32bar_create_lock_button(f32bar, IDB_UNLOCK, IDB_UNLOCK_ACT, IDB_LOCK, IDB_LOCK_ACT, LOCK_X, BUTTON_Y, BUTTON_HEIGHT, BUTTON_WIDTH);

	return f32bar;
}

::i32 f32bar_hide(FloatBar* f32bar)
{
	kill_timer(f32bar->hwnd, TIMER_HIDE);
	MoveWindow(f32bar->hwnd, f32bar->rectangle.left, -f32bar->height, f32bar->width, f32bar->height, true);
	return 0;
}

::i32 f32bar_show(FloatBar* f32bar)
{
	set_timer(f32bar->hwnd, TIMER_HIDE, 3000, nullptr);
	MoveWindow(f32bar->hwnd, f32bar->rectangle.left, f32bar->rectangle.top, f32bar->width, f32bar->height, true);
	return 0;
}

//void f32bar_window_create(wfContext *wfc)
//{
//	WNDCLASSEX wnd_cls;
//	HWND barWnd;
//	::i32 x = (GetSystemMetrics(SM_CXSCREEN) - BACKGROUND_W) / 2;
//
//	wnd_cls.cbSize        = sizeof(WNDCLASSEX);
//	wnd_cls.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
//	wnd_cls.lpfnWndProc   = f32bar_proc;
//	wnd_cls.cbClsExtra    = 0;
//	wnd_cls.cbWndExtra    = 0;
//	wnd_cls.hIcon         = LoadIcon(nullptr, IDI_APPLICATION);
//	wnd_cls.hCursor       = LoadCursor(wfc->hInstance, IDC_ARROW);
//	wnd_cls.hbrBackground = nullptr;
//	wnd_cls.lpszMenuName  = nullptr;
//	wnd_cls.lpszClassName = L"f32bar";
//	wnd_cls.hInstance     = wfc->hInstance;
//	wnd_cls.hIconSm       = LoadIcon(nullptr, IDI_APPLICATION);
//
//	RegisterClassEx(&wnd_cls);
//
//	wfc->f32bar = f32bar_create(wfc);
//
//	barWnd = CreateWindowEx(WS_EX_TOPMOST, L"f32bar", L"f32bar", WS_CHILD, x, 0, BACKGROUND_W, BACKGROUND_H, wfc->hwnd, nullptr, wfc->hInstance, wfc->f32bar);
//	if (barWnd == nullptr)
//		return;
//	ShowWindow(barWnd, SW_SHOWNORMAL);
//}
