// Created by camilo on 2026-07-31 17:48 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "platform.h"
#include "device_independent_bitmap.h"


namespace windows
{


   device_independent_bitmap::device_independent_bitmap()
   {

      m_hdcMemory = nullptr;
      m_hbitmap = nullptr;
      m_hbitmapOld = nullptr;

   }


   device_independent_bitmap::~device_independent_bitmap()
   {

      destroy_device_independent_bitmap();

   }


   void device_independent_bitmap::defer_create_device_independent_bitmap(const ::i32_size & sizeRaw)
   {

      if (sizeRaw <= m_sizeRaw
         && ::is_set(m_pimage32Raw)
         && m_hdcMemory
         && m_hbitmap)
      {

         return;

      }

      destroy_device_independent_bitmap();

      BITMAPINFO info{};
      info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      info.bmiHeader.biWidth = sizeRaw.cx;
      info.bmiHeader.biHeight = -sizeRaw.cy; // Top-down.
      info.bmiHeader.biPlanes = 1;
      info.bmiHeader.biBitCount = 32; // Memory order is BGRA.
      info.bmiHeader.biCompression = BI_RGB;

      m_pimage32Raw = nullptr;

      m_hdcMemory = CreateCompatibleDC(nullptr);

      if (!m_hdcMemory)
      {

         throw ::exception(error_failed, "defer_create_device_independent_bitmap CreateCompatibleDC failed");

      }

      ::SetLastError(ERROR_SUCCESS);
      m_hbitmap = CreateDIBSection(m_hdcMemory, &info, DIB_RGB_COLORS, (void **)&m_pimage32Raw, nullptr, 0);

      if (!m_hdcMemory || !m_hbitmap || !m_pimage32Raw)
      {

         const DWORD error = ::GetLastError();
         destroy_device_independent_bitmap();
         m_pimage32Raw = nullptr;
         m_pimage32 = nullptr;
         ::string message;
         message.formatf("defer_create_device_independent_bitmap CreateDIBSection failed size=(%d,%d) bytes=%llu error=%lu",
            sizeRaw.cx, sizeRaw.cy,
            (unsigned long long)(sizeRaw.cx > 0 && sizeRaw.cy > 0
               ? (unsigned long long)sizeRaw.cx * sizeRaw.cy * sizeof(::image32_t) : 0),
            (unsigned long)error);
         throw ::exception(error_failed, message);

      }

      m_hbitmapOld = (HBITMAP)SelectObject(m_hdcMemory, m_hbitmap);

      m_sizeRaw = sizeRaw;

      m_size = m_sizeRaw;

      m_iScan = m_sizeRaw.cx * sizeof(::image32_t);

      m_point.clear();

      m_pimage32 = m_pimage32Raw;

   }


   void device_independent_bitmap::destroy_device_independent_bitmap()
   {

      if (m_hbitmap)
      {

         if (m_hdcMemory && m_hbitmapOld)
         {

            ::SelectObject(m_hdcMemory, m_hbitmapOld);
         }

         ::DeleteObject(m_hbitmap);

         m_hbitmap = nullptr;

         m_hbitmapOld = nullptr;

      }

      if (m_hdcMemory)
      {

         ::DeleteDC(m_hdcMemory);

         m_hdcMemory = nullptr;

      }

   }


} // namespace windows
