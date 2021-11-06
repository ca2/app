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
#include "wf_floatbar.h"
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

/* bmp size_i32 */
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
	FloatBar* floatbar;
	int type;
	int x, y, h, w;
	int active;
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
	RECTANGLE_I32 rectangle_i32;
	::i32 width;
	::i32 height;
	wfContext* wfc;
	Button* buttons[BTN_MAX];
	BOOL shown;
	BOOL locked;
	HDC hdcmem;
	HBITMAP background;
};

static int button_hit(Button* button)
{
	FloatBar* floatbar = button->floatbar;

	switch (button->type)
	{
		case BUTTON_LOCKPIN:
			if (!floatbar->locked)
			{
				button->bmp = button->locked_bmp;
				button->bmp_act = button->locked_bmp_act;
			}
			else
			{
				button->bmp = button->unlocked_bmp;
				button->bmp_act = button->unlocked_bmp_act;
			}

			floatbar->locked = ~floatbar->locked;
			InvalidateRect(button->floatbar->hwnd, nullptr, false);
			UpdateWindow(button->floatbar->hwnd);
			break;

		case BUTTON_MINIMIZE:
			ShowWindow(floatbar->parent, SW_MINIMIZE);
			break;

		case BUTTON_RESTORE:
			wf_toggle_fullscreen(floatbar->wfc);
			break;

		case BUTTON_CLOSE:
			SendMessage(floatbar->parent, e_message_destroy, 0 , 0);
			break;

		default:
			return 0;
	}

	return 0;
}

static int button_paint(Button* button, HDC hdc)
{
	FloatBar* floatbar = button->floatbar;

	SelectObject(floatbar->hdcmem, button->active ? button->bmp_act : button->bmp);
	StretchBlt(hdc, button->x, button->y, button->w, button->h, floatbar->hdcmem, 0, 0, button->w, button->h);

	return 0;
}

static Button* floatbar_create_button(FloatBar* floatbar, int type, int resid, int resid_act, int x, int y, int h, int w)
{
	Button *button;

	button = (Button *)malloc(sizeof(Button));

	if (!button)
		return nullptr;

	button->floatbar = floatbar;
	button->type = type;
	button->x = x;
	button->y = y;
	button->w = w;
	button->h = h;
	button->active = false;

	button->bmp = (HBITMAP)LoadImage(floatbar->wfc->hInstance, MAKEINTRESOURCE(resid), IMAGE_BITMAP, w, h, LR_DEFAULTCOLOR);
	button->bmp_act = (HBITMAP)LoadImage(floatbar->wfc->hInstance, MAKEINTRESOURCE(resid_act), IMAGE_BITMAP, w, h, LR_DEFAULTCOLOR);

	return button;
}

static Button* floatbar_create_lock_button(FloatBar* floatbar,
									int unlock_resid, int unlock_resid_act,
									int lock_resid, int lock_resid_act,
									int x, int y, int h, int w)
{
	Button* button;

	button = floatbar_create_button(floatbar, BUTTON_LOCKPIN, unlock_resid, unlock_resid_act, x, y, h, w);

	if (!button)
		return nullptr;

	button->unlocked_bmp = button->bmp;
	button->unlocked_bmp_act = button->bmp_act;
	button->locked_bmp = (HBITMAP)LoadImage(floatbar->wfc->hInstance, MAKEINTRESOURCE(lock_resid), IMAGE_BITMAP, w, h, LR_DEFAULTCOLOR);
	button->locked_bmp_act = (HBITMAP)LoadImage(floatbar->wfc->hInstance, MAKEINTRESOURCE(lock_resid_act), IMAGE_BITMAP, w, h, LR_DEFAULTCOLOR);

	return button;
}

static Button* floatbar_get_button(FloatBar* floatbar, int x, int y)
{
	int i;

	if (y > BUTTON_Y && y < BUTTON_Y + BUTTON_HEIGHT)
		for (i = 0; i < BTN_MAX; i++)
			if (x > floatbar->buttons[i]->x && x < floatbar->buttons[i]->x + floatbar->buttons[i]->w)
				return floatbar->buttons[i];

	return nullptr;
}

static int floatbar_paint(FloatBar* floatbar, HDC hdc)
{
	int i;

	/* paint background */
	SelectObject(floatbar->hdcmem, floatbar->background);
	StretchBlt(hdc, 0, 0, BACKGROUND_W, BACKGROUND_H, floatbar->hdcmem, 0, 0, BACKGROUND_W, BACKGROUND_H);

	/* paint buttons */
	for (i = 0; i < BTN_MAX; i++)
		button_paint(floatbar->buttons[i], hdc);

	return 0;
}

static int floatbar_animation(FloatBar* floatbar, BOOL show)
{
	SetTimer(floatbar->hwnd, show ? TIMER_ANIMAT_SHOW : TIMER_ANIMAT_HIDE, 10, nullptr);
	floatbar->shown = show;
	return 0;
}

LRESULT CALLBACK floatbar_proc(HWND hWnd, ::u32 Msg, WPARAM wParam, LPARAM lParam)
{
	static int dragging = false;
	static int lbtn_dwn = false;
	static int btn_dwn_x = 0;
	static FloatBar* floatbar;
	static TRACKMOUSEEVENT tme;

	PAINTSTRUCT ps;
	Button* button;
	HDC hdc;
	int pos_x;
	int pos_y;

	int xScreen = GetSystemMetrics(SM_CXSCREEN);

	switch(Msg)
	{
		case e_message_create:
			floatbar = (FloatBar *)((CREATESTRUCT *)lParam)->lpCreateParams;
			floatbar->hwnd = hWnd;
			floatbar->parent = get_parent(hWnd);

			get_window_rect(floatbar->hwnd, &floatbar->rectangle);
			floatbar->width = floatbar->rectangle.right - floatbar->rectangle.left;
			floatbar->height = floatbar->rectangle.bottom - floatbar->rectangle.top;

			hdc = GetDC(hWnd);
			floatbar->hdcmem = CreateCompatibleDC(hdc);
			ReleaseDC(hWnd, hdc);

			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = hWnd;
			tme.dwHoverTime = HOVER_DEFAULT;

			SetTimer(hWnd, TIMER_HIDE, 3000, nullptr);
			break;

		case e_message_paint:
			hdc = BeginPaint(hWnd, &ps);
			floatbar_paint(floatbar, hdc);
			EndPaint(hWnd, &ps);
			break;

		case e_message_left_button_down:
			pos_x = lParam & 0xffff;
			pos_y = (lParam >> 16) & 0xffff;

			button = floatbar_get_button(floatbar, pos_x, pos_y);
			if (!button)
			{
				SetCapture(hWnd);
				dragging = true;
				btn_dwn_x = lParam & 0xffff;
			}
			else
				lbtn_dwn = true;

			break;

		case e_message_left_button_up:
			pos_x = lParam & 0xffff;
			pos_y = (lParam >> 16) & 0xffff;

			ReleaseCapture();
			dragging = false;

			if (lbtn_dwn)
			{
				button = floatbar_get_button(floatbar, pos_x, pos_y);
				if (button)
					button_hit(button);
				lbtn_dwn = false;
			}
			break;

		case e_message_mouse_move:
			KillTimer(hWnd, TIMER_HIDE);
			pos_x = lParam & 0xffff;
			pos_y = (lParam >> 16) & 0xffff;

			if (!floatbar->shown)
				floatbar_animation(floatbar, true);

			if (dragging)
			{
				floatbar->rectangle.left = floatbar->rectangle.left + (lParam & 0xffff) - btn_dwn_x;

				if (floatbar->rectangle.left < 0)
					floatbar->rectangle.left = 0;
				else if (floatbar->rectangle.left > xScreen - floatbar->width)
					floatbar->rectangle.left = xScreen - floatbar->width;

				MoveWindow(hWnd, floatbar->rectangle.left, floatbar->rectangle.top, floatbar->width, floatbar->height, true);
			}
			else
			{
				int i;

				for (i = 0; i < BTN_MAX; i++)
					floatbar->buttons[i]->active = false;

				button = floatbar_get_button(floatbar, pos_x, pos_y);
				if (button)
					button->active = true;

				InvalidateRect(hWnd, nullptr, false);
				UpdateWindow(hWnd);
			}

			TrackMouseEvent(&tme);
			break;

		case e_message_capture_changed:
			dragging = false;
			break;

		case e_message_mouse_leave:
		{
			int i;

			for (i = 0; i < BTN_MAX; i++)
				floatbar->buttons[i]->active = false;

			InvalidateRect(hWnd, nullptr, false);
			UpdateWindow(hWnd);

			SetTimer(hWnd, TIMER_HIDE, 3000, nullptr);
			break;
		}
		case e_message_timer:
			switch (wParam)
			{
				case TIMER_HIDE:
				{
					KillTimer(hWnd, TIMER_HIDE);
					if (!floatbar->locked)
						floatbar_animation(floatbar, false);
					break;
				}
				case TIMER_ANIMAT_SHOW:
				{
					static int y = 0;

					MoveWindow(floatbar->hwnd, floatbar->rectangle.left, (y++ - floatbar->height), floatbar->width, floatbar->height, true);
					if (y == floatbar->height)
					{
						y = 0;
						KillTimer(hWnd, wParam);
					}
					break;
				}
				case TIMER_ANIMAT_HIDE:
				{
					static int y = 0;

					MoveWindow(floatbar->hwnd, floatbar->rectangle.left, -y++, floatbar->width, floatbar->height, true);
					if (y == floatbar->height)
					{
						y = 0;
						KillTimer(hWnd, wParam);
					}
					break;
				}
				default:
					break;
			}
			break;

		case e_message_destroy:
			DeleteDC(floatbar->hdcmem);
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	return 0;
}

static FloatBar* floatbar_create(wfContext* wfc)
{
	FloatBar* floatbar;

	floatbar = (FloatBar *)malloc(sizeof(FloatBar));

	if (!floatbar)
		return nullptr;

	floatbar->locked = false;
	floatbar->shown = true;
	floatbar->hwnd = nullptr;
	floatbar->parent = wfc->hwnd;
	floatbar->wfc = wfc;
	floatbar->hdcmem = nullptr;

	floatbar->background = (HBITMAP)LoadImage(wfc->hInstance, MAKEINTRESOURCE(IDB_BACKGROUND), IMAGE_BITMAP, BACKGROUND_W, BACKGROUND_H, LR_DEFAULTCOLOR);
	floatbar->buttons[0] = floatbar_create_button(floatbar, BUTTON_MINIMIZE, IDB_MINIMIZE, IDB_MINIMIZE_ACT, MINIMIZE_X, BUTTON_Y, BUTTON_HEIGHT, BUTTON_WIDTH);
	floatbar->buttons[1] = floatbar_create_button(floatbar, BUTTON_RESTORE, IDB_RESTORE, IDB_RESTORE_ACT, RESTORE_X, BUTTON_Y, BUTTON_HEIGHT, BUTTON_WIDTH);
	floatbar->buttons[2] = floatbar_create_button(floatbar, BUTTON_CLOSE, IDB_CLOSE, IDB_CLOSE_ACT, CLOSE_X, BUTTON_Y, BUTTON_HEIGHT, BUTTON_WIDTH);
	floatbar->buttons[3] = floatbar_create_lock_button(floatbar, IDB_UNLOCK, IDB_UNLOCK_ACT, IDB_LOCK, IDB_LOCK_ACT, LOCK_X, BUTTON_Y, BUTTON_HEIGHT, BUTTON_WIDTH);

	return floatbar;
}

int floatbar_hide(FloatBar* floatbar)
{
	KillTimer(floatbar->hwnd, TIMER_HIDE);
	MoveWindow(floatbar->hwnd, floatbar->rectangle.left, -floatbar->height, floatbar->width, floatbar->height, true);
	return 0;
}

int floatbar_show(FloatBar* floatbar)
{
	SetTimer(floatbar->hwnd, TIMER_HIDE, 3000, nullptr);
	MoveWindow(floatbar->hwnd, floatbar->rectangle.left, floatbar->rectangle.top, floatbar->width, floatbar->height, true);
	return 0;
}

//void floatbar_window_create(wfContext *wfc)
//{
//	WNDCLASSEX wnd_cls;
//	HWND barWnd;
//	int x = (GetSystemMetrics(SM_CXSCREEN) - BACKGROUND_W) / 2;
//
//	wnd_cls.cbSize        = sizeof(WNDCLASSEX);
//	wnd_cls.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
//	wnd_cls.lpfnWndProc   = floatbar_proc;
//	wnd_cls.cbClsExtra    = 0;
//	wnd_cls.cbWndExtra    = 0;
//	wnd_cls.hIcon         = LoadIcon(nullptr, IDI_APPLICATION);
//	wnd_cls.hCursor       = LoadCursor(wfc->hInstance, IDC_ARROW);
//	wnd_cls.hbrBackground = nullptr;
//	wnd_cls.lpszMenuName  = nullptr;
//	wnd_cls.lpszClassName = L"floatbar";
//	wnd_cls.hInstance     = wfc->hInstance;
//	wnd_cls.hIconSm       = LoadIcon(nullptr, IDI_APPLICATION);
//
//	RegisterClassEx(&wnd_cls);
//
//	wfc->floatbar = floatbar_create(wfc);
//
//	barWnd = CreateWindowEx(WS_EX_TOPMOST, L"floatbar", L"floatbar", WS_CHILD, x, 0, BACKGROUND_W, BACKGROUND_H, wfc->hwnd, nullptr, wfc->hInstance, wfc->floatbar);
//	if (barWnd == nullptr)
//		return;
//	ShowWindow(barWnd, SW_SHOWNORMAL);
//}
