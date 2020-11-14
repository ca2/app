#include "framework.h"


namespace ios
{


   copydesk::copydesk(::layered * pobjectContext) :
      ::object(pobject),
      ::user::copydesk(pobject)
   {
   }

   copydesk::~copydesk()
   {
   }

   i32 copydesk::get_file_count()
   {

//      if(m_p == nullptr)
//         return 0;
//
//      if(!m_p->OpenClipboard())
//         return 0;
      i32 iCount = 0;
      __throw(todo());
      /* xxx HDROP hdrop = (HDROP) ::GetClipboardData(CF_HDROP);
      if(hdrop != nullptr)
      {
         iCount = ::DragQueryFile(hdrop , 0xFFFFFFFF, nullptr, 0);
      }
      ::CloseClipboard(); */
      return iCount;
   }


   void copydesk::get_filea(::file::patha & patha)
   {
      i32 iCount = get_file_count();
      if(iCount <= 0)
         return;
//      if(!m_p->OpenClipboard())
      //       return;
      __throw(todo());
      /* HDROP hdrop = (HDROP) ::GetClipboardData(CF_HDROP);
      string str;
      for(i32 i = 0; i < iCount; i++)
      {
         ::u32 uLen = ::DragQueryFileW(hdrop, i, nullptr, 0);
         unichar * lpwsz = (unichar *) malloc(sizeof(unichar) * (uiLen + 1));
         ::DragQueryFileW(hdrop, i, lpwsz, uiLen + 1);
         stra.add(::str::international::unicode_to_utf8(lpwsz));
         free(lpwsz);
      }
      ::CloseClipboard();
      */
   }

   void copydesk::set_filea(const ::file::patha & patha)
   {

//      ASSERT(m_p->is_window());

      strsize iLen = 0;

      for(i32 i = 0; i < patha.get_size(); i++)
      {
         iLen += ::str::international::utf8_to_unicode_count(patha[i]) + 1;
      }

      __throw(todo());

      /* xxx

            HGLOBAL hglbCopy = ::GlobalAlloc(GMEM_MOVEABLE, sizeof(DROPFILES) + (iLen + 1) * sizeof(WCHAR));
            LPDROPFILES pDropFiles = (LPDROPFILES) ::GlobalLock(hglbCopy);
            pDropFiles->pFiles = sizeof(DROPFILES);
            pDropFiles->point.x = pDropFiles->point.y = 0;
            pDropFiles->fNC = TRUE;
            pDropFiles->fWide = TRUE; // ANSI charset

            ASSERT(m_p->is_window());
            char * lptstrCopy = (char *) pDropFiles;
            lptstrCopy += pDropFiles->pFiles;
            unichar * lpwstrCopy = (unichar *) lptstrCopy;
            for(i32 i = 0; i < stra.get_size(); i++)
            {
               ASSERT(m_p->is_window());
               ::str::international::utf8_to_unicode(lpwstrCopy, ::str::international::utf8_to_unicode_count(stra[i]) + 1, stra[i]);
               ASSERT(m_p->is_window());
               lpwstrCopy += (stra[i].get_length() + 1);
            }
            ASSERT(m_p->is_window());
            *lpwstrCopy = '\0';    // null character
            ASSERT(m_p->is_window());
            ::GlobalUnlock(hglbCopy);
            ASSERT(m_p->is_window());
            if(!m_p->OpenClipboard())
            {
               ::GlobalFree(hglbCopy);
               return;
            }
            EmptyClipboard();
            SetClipboardData(CF_HDROP, hglbCopy);
            VERIFY(::CloseClipboard());

      */

   }



   bool copydesk::initialize()
   {

      if(!::user::copydesk::initialize())
         return false;

      //    if(!m_p->CreateEx(0, System.RegisterWndClass(0), nullptr, 0, rect(0, 0, 0, 0), nullptr, id()))
      //     return false;

//      if(!m_p->CreateEx(0, nullptr, nullptr, 0, rect(0, 0, 0, 0), nullptr, id()))
      //       return false;

      return true;

   }


   bool copydesk::finalize()
   {

      bool bOk;

      bOk = ::user::copydesk::finalize();

//      if(window_pointer::is_set() && window_pointer::m_p->is_window())
//      {
//         bOk = window_pointer::m_p->DestroyWindow() != FALSE;
//      }
//      else
//      {
//         bOk = false;
//      }

      return bOk;

   }

   void copydesk::_set_plain_text(const char * psz)
   {
//      ASSERT(m_p->is_window());
//   //   i32 iLen = 0;
//
//      string str;
//      str = ::str::international::utf8_to_unicode(psz);
//
//
//
//      ASSERT(m_p->is_window());
//      if(!m_p->OpenClipboard())
//      {
//         return;
//      }

      __throw(todo());

      /*

            EmptyClipboard();


            count iCount = ::str::international::utf8_to_unicode_count(str) + 1;
            HGLOBAL hglbCopy = ::GlobalAlloc(GMEM_MOVEABLE, iCount * sizeof(WCHAR));
            unichar * lpwstrCopy  = (unichar *) ::GlobalLock(hglbCopy);
            ::str::international::utf8_to_unicode(lpwstrCopy, iCount, str);
            ::GlobalUnlock(hglbCopy);

            HGLOBAL hglbCopy2 = ::GlobalAlloc(GMEM_MOVEABLE, sizeof(char) * (strlen(psz) + 1));
            char * lpstrCopy  = (char *) ::GlobalLock(hglbCopy2);
            strcpy(lpstrCopy, psz);
            ::GlobalUnlock(hglbCopy2);


            SetClipboardData(CF_UNICODETEXT, hglbCopy);
            SetClipboardData(CF_TEXT, hglbCopy2);
            VERIFY(::CloseClipboard());

      */

   }


   string copydesk::get_plain_text()
   {
      __throw(todo());
      return "";
      /* xxx
            if (IsClipboardFormatAvailable(CF_UNICODETEXT))
            {
               if(!m_p->OpenClipboard())
                  return "";
               HGLOBAL hglb = GetClipboardData(CF_UNICODETEXT);
               string str(::str::international::unicode_to_utf8((const unichar *) GlobalLock(hglb)));
               GlobalUnlock(hglb);
               VERIFY(::CloseClipboard());
               return str;
            }
            else if (IsClipboardFormatAvailable(CF_TEXT))
            {
               if(!m_p->OpenClipboard())
                  return "";
               HGLOBAL hglb = GetClipboardData(CF_TEXT);
               string str((char *) GlobalLock(hglb));
               GlobalUnlock(hglb);
               VERIFY(::CloseClipboard());
               return str;
            }
            else
            {
               return "";
            }
      */
   }

/*   bool copydesk::desk_to_image(::image * pimage)
   {
//      if(!m_p->OpenClipboard())
//         return false;
      bool bOk = false;
      __throw(todo());
      /* xxx
            HBITMAP hbitmap = (HBITMAP) ::GetClipboardData(CF_BITMAP);
            try
            {
               ::draw2d::bitmap_pointer bitmap(get_object());
               bitmap->Attach(hbitmap);
               //HDC hdc = ::CreateCompatibleDC(nullptr);
               //::draw2d::graphics_pointer g(get_object());
               //g->Attach(hdc);
               //::draw2d::graphics_pointer & pgraphics = Application.graphics_from_os_data(hdc);
               //g->SelectObject(hbitmap);
             //  BITMAP bm;
               //::GetObjectA(hbitmap, sizeof(bm), &bm);
/*               //if(!pimage = create_image({bm.bmWidth,  bm.bmHeight)})
                 // return false;
               ::draw2d::graphics_pointer g(get_object());
               g->SelectObject(bitmap);
               size sz = bitmap->GetBitmapDimension();
/*               if(pimage = create_image(sz))
               {
/*                  bOk = pimage->g()->BitBlt(0, 0, sz.cx, sz.cy, g, 0, 0) != FALSE;
               }
            }
            catch(...)
            {
            }
            ::DeleteObject((HGDIOBJ) hbitmap);
            //::DeleteDC(hdc);
            ::CloseClipboard();

      */

      return bOk;
   }


} // namespace ios


