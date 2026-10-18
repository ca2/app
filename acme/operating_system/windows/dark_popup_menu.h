#pragma once

#include <windows.h>
#include <memory>
#include <string>
#include <vector>

namespace windows
{
   // Scoped owner drawing: leave native menus untouched outside TrackPopupMenu.
   class dark_popup_menu
   {
      struct item
      {
         HMENU menu;
         UINT position;
         MENUITEMINFOW original{};
         std::wstring text;
      };
      struct background { HMENU menu; HBRUSH original; };
      HWND m_owner = nullptr;
      WNDPROC m_previous = nullptr;
      HBRUSH m_brush = nullptr;
      HFONT m_font = nullptr;
      HFONT m_bold = nullptr;
      int m_height = 20;
      std::vector<std::unique_ptr<item>> m_items;
      std::vector<background> m_backgrounds;

      static LPCWSTR property() { return L"ca2.windows.dark_popup_menu"; }

      void decorate(HMENU menu)
      {
         MENUINFO info{sizeof(info)};
         info.fMask = MIM_BACKGROUND;
         bool hasBackground = false;
         for (const auto & background : m_backgrounds)
            if (background.menu == menu) hasBackground = true;
         if (!hasBackground && GetMenuInfo(menu, &info))
         {
            m_backgrounds.push_back({menu, info.hbrBack});
            info.hbrBack = m_brush;
            SetMenuInfo(menu, &info);
         }
         const int count = GetMenuItemCount(menu);
         for (int position = 0; position < count; ++position)
         {
            auto entry = std::make_unique<item>();
            entry->menu = menu;
            entry->position = position;
            auto & original = entry->original;
            original.cbSize = sizeof(original);
            original.fMask = MIIM_FTYPE | MIIM_DATA | MIIM_SUBMENU | MIIM_STRING;
            if (!GetMenuItemInfoW(menu, position, TRUE, &original))
               continue;
            if (original.hSubMenu)
               decorate(original.hSubMenu);
            if (auto existing = find(original.dwItemData))
            {
               existing->position = position;
               continue;
            }
            // Preserve existing custom renderers.
            if (original.fType & (MFT_OWNERDRAW | MFT_BITMAP))
               continue;
            entry->text.resize(original.cch + 1);
            original.dwTypeData = &entry->text[0];
            original.cch = static_cast<UINT>(entry->text.size());
            if (!GetMenuItemInfoW(menu, position, TRUE, &original))
               continue;
            entry->text.resize(original.cch);
            MENUITEMINFOW changed{sizeof(changed)};
            changed.fMask = MIIM_FTYPE | MIIM_DATA;
            changed.fType = original.fType | MFT_OWNERDRAW;
            changed.dwItemData = reinterpret_cast<ULONG_PTR>(entry.get());
            // Keep the record alive even if the OS rejects the update.
            m_items.push_back(std::move(entry));
            SetMenuItemInfoW(menu, position, TRUE, &changed);
         }
      }

      item * find(ULONG_PTR data)
      {
         for (auto & entry : m_items)
            if (reinterpret_cast<ULONG_PTR>(entry.get()) == data)
               return entry.get();
         return nullptr;
      }

      bool handle(UINT message, WPARAM wparam, LPARAM lparam, LRESULT & result)
      {
         result = TRUE;
         if (message == WM_MENUCHAR)
         {
            const auto menu = reinterpret_cast<HMENU>(lparam);
            int current = -1, first = -1, next = -1, matches = 0;
            const WCHAR character = static_cast<WCHAR>(LOWORD(wparam));
            for (auto & entry : m_items)
               if (entry->menu == menu && (GetMenuState(menu, entry->position, MF_BYPOSITION) & MF_HILITE))
                  current = static_cast<int>(entry->position);
            for (auto & entry : m_items)
            {
               if (entry->menu != menu || (GetMenuState(menu, entry->position, MF_BYPOSITION) & (MF_DISABLED | MF_GRAYED)))
                  continue;
               for (size_t index = 0; index + 1 < entry->text.size(); ++index)
               {
                  if (entry->text[index] != L'&') continue;
                  if (entry->text[index + 1] == L'&') { ++index; continue; }
                  if (CompareStringW(LOCALE_USER_DEFAULT, NORM_IGNORECASE,
                     &entry->text[index + 1], 1, &character, 1) == CSTR_EQUAL)
                  {
                     const int position = static_cast<int>(entry->position);
                     if (first < 0) first = position;
                     if (next < 0 && position > current) next = position;
                     ++matches;
                  }
                  break;
               }
            }
            if (!matches) return false;
            result = MAKELRESULT(next < 0 ? first : next, matches == 1 ? MNC_EXECUTE : MNC_SELECT);
            return true;
         }
         if (message == WM_MEASUREITEM)
         {
            auto measure = reinterpret_cast<MEASUREITEMSTRUCT *>(lparam);
            auto entry = measure->CtlType == ODT_MENU ? find(measure->itemData) : nullptr;
            if (!entry)
               return false;
            auto dc = GetDC(m_owner);
            const auto old = SelectObject(dc, m_bold);
            SIZE size{};
            GetTextExtentPoint32W(dc, entry->text.c_str(), static_cast<int>(entry->text.size()), &size);
            SelectObject(dc, old);
            ReleaseDC(m_owner, dc);
            measure->itemHeight = (entry->original.fType & MFT_SEPARATOR) ? m_height / 2 : m_height + 10;
            measure->itemWidth = size.cx + m_height * 3;
            return true;
         }
         if (message != WM_DRAWITEM)
            return false;
         auto draw = reinterpret_cast<DRAWITEMSTRUCT *>(lparam);
         auto entry = draw->CtlType == ODT_MENU ? find(draw->itemData) : nullptr;
         if (!entry)
            return false;
         const auto dc = draw->hDC;
         const int saved = SaveDC(dc);
         const bool disabled = (draw->itemState & (ODS_DISABLED | ODS_GRAYED)) != 0;
         const bool selected = (draw->itemState & ODS_SELECTED) != 0 && !disabled;
         auto brush = static_cast<HBRUSH>(GetStockObject(DC_BRUSH));
         SetDCBrushColor(dc, selected ? RGB(65, 67, 70) : RGB(32, 32, 32));
         FillRect(dc, &draw->rcItem, brush);
         const COLORREF foreground = disabled ? RGB(135, 135, 135) : RGB(235, 235, 235);
         const auto pen = CreatePen(PS_SOLID, 1, foreground);
         const auto oldPen = SelectObject(dc, pen);
         RECT rectangle = draw->rcItem;
         if (entry->original.fType & MFT_SEPARATOR)
         {
            const int y = (rectangle.top + rectangle.bottom) / 2;
            MoveToEx(dc, rectangle.left + m_height, y, nullptr);
            LineTo(dc, rectangle.right - 6, y);
         }
         else
         {
            SetTextColor(dc, foreground);
            SetBkMode(dc, TRANSPARENT);
            SelectObject(dc, (draw->itemState & ODS_DEFAULT) ? m_bold : m_font);
            rectangle.left += m_height + 8;
            rectangle.right -= m_height;
            const auto tab = entry->text.find(L'\t');
            const UINT flags = DT_SINGLELINE | DT_VCENTER
               | ((draw->itemState & ODS_NOACCEL) ? DT_HIDEPREFIX : 0);
            DrawTextW(dc, entry->text.c_str(), static_cast<int>(tab == std::wstring::npos ? entry->text.size() : tab),
               &rectangle, flags);
            if (tab != std::wstring::npos)
               DrawTextW(dc, entry->text.c_str() + tab + 1, -1, &rectangle, flags | DT_RIGHT);
            const int y = (rectangle.top + rectangle.bottom) / 2;
            if (draw->itemState & ODS_CHECKED)
            {
               const int x = draw->rcItem.left + 8;
               MoveToEx(dc, x, y, nullptr); LineTo(dc, x + 3, y + 3); LineTo(dc, x + 8, y - 3);
            }
            if (entry->original.hSubMenu)
            {
               const int x = draw->rcItem.right - 9;
               MoveToEx(dc, x - 3, y - 3, nullptr); LineTo(dc, x, y); LineTo(dc, x - 3, y + 3);
            }
         }
         SelectObject(dc, oldPen);
         DeleteObject(pen);
         if (saved)
            RestoreDC(dc, saved);
         return true;
      }

      static LRESULT CALLBACK procedure(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
      {
         auto self = reinterpret_cast<dark_popup_menu *>(GetPropW(hwnd, property()));
         if (message == WM_INITMENU || message == WM_INITMENUPOPUP)
         {
            // The original handler may insert About or remove system commands.
            const auto result = CallWindowProcW(self->m_previous, hwnd, message, wparam, lparam);
            try { self->decorate(reinterpret_cast<HMENU>(wparam)); }
            catch (...) { self->restore(); }
            return result;
         }
         LRESULT result;
         if (self->handle(message, wparam, lparam, result))
            return result;
         return CallWindowProcW(self->m_previous, hwnd, message, wparam, lparam);
      }

   public:
      static bool enabled()
      {
#if defined(__REACTOS__)
         return false;
#else
         HIGHCONTRASTW contrast{sizeof(contrast)};
         if (!SystemParametersInfoW(SPI_GETHIGHCONTRAST, sizeof(contrast), &contrast, 0)
            || (contrast.dwFlags & HCF_HIGHCONTRASTON))
            return false;
         HKEY key = nullptr;
         if (RegOpenKeyExW(HKEY_CURRENT_USER,
            L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
            0, KEY_QUERY_VALUE, &key) != ERROR_SUCCESS)
            return false;
         DWORD value = 1, type = 0, size = sizeof(value);
         const auto status = RegQueryValueExW(key, L"AppsUseLightTheme", nullptr,
            &type, reinterpret_cast<BYTE *>(&value), &size);
         RegCloseKey(key);
         return status == ERROR_SUCCESS && type == REG_DWORD && size == sizeof(value) && value == 0;
#endif
      }

      dark_popup_menu(HWND owner, HMENU menu)
      {
         if (!enabled() || !IsMenu(menu) || GetPropW(owner, property())
            || GetWindowThreadProcessId(owner, nullptr) != GetCurrentThreadId())
            return;
         m_owner = owner;
         NONCLIENTMETRICSW metrics{sizeof(metrics)};
         if (!SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, 0))
            return;
         m_font = CreateFontIndirectW(&metrics.lfMenuFont);
         metrics.lfMenuFont.lfWeight = FW_BOLD;
         m_bold = CreateFontIndirectW(&metrics.lfMenuFont);
         m_brush = CreateSolidBrush(RGB(32, 32, 32));
         if (!m_font || !m_bold || !m_brush)
            return;
         auto dc = GetDC(owner);
         const auto old = SelectObject(dc, m_font);
         TEXTMETRICW text{};
         GetTextMetricsW(dc, &text);
         m_height = text.tmHeight;
         SelectObject(dc, old); ReleaseDC(owner, dc);
         m_previous = reinterpret_cast<WNDPROC>(GetWindowLongPtrW(owner, GWLP_WNDPROC));
         if (!m_previous || !SetPropW(owner, property(), this))
         { m_previous = nullptr; return; }
         if (!SetWindowLongPtrW(owner, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(procedure)))
         { RemovePropW(owner, property()); m_previous = nullptr; return; }
         try { decorate(menu); }
         catch (...) { restore(); }
      }

      void restore()
      {
         for (auto & entry : m_items)
         {
            MENUITEMINFOW original = entry->original;
            original.fMask = MIIM_FTYPE | MIIM_DATA;
            // Positions may have changed since decoration. Restore only our item.
            const int count = GetMenuItemCount(entry->menu);
            for (int position = 0; position < count; ++position)
            {
               MENUITEMINFOW current{sizeof(current)};
               current.fMask = MIIM_DATA;
               if (GetMenuItemInfoW(entry->menu, position, TRUE, &current)
                  && current.dwItemData == reinterpret_cast<ULONG_PTR>(entry.get()))
               {
                  SetMenuItemInfoW(entry->menu, position, TRUE, &original);
                  break;
               }
            }
         }
         m_items.clear();
         for (auto & background : m_backgrounds)
         {
            MENUINFO info{sizeof(info)};
            info.fMask = MIM_BACKGROUND; info.hbrBack = background.original;
            if (IsMenu(background.menu)) SetMenuInfo(background.menu, &info);
         }
         m_backgrounds.clear();
         if (m_previous && IsWindow(m_owner))
         {
            SetWindowLongPtrW(m_owner, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_previous));
            RemovePropW(m_owner, property());
         }
         m_previous = nullptr;
      }

      ~dark_popup_menu()
      {
         restore();
         if (m_font) DeleteObject(m_font);
         if (m_bold) DeleteObject(m_bold);
         if (m_brush) DeleteObject(m_brush);
      }
      dark_popup_menu(const dark_popup_menu &) = delete;
      dark_popup_menu & operator=(const dark_popup_menu &) = delete;
   };
}
