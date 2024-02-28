//
// Created by camilo on 01/02/2022 01:01 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "_nano.h"


//namespace x11
//{
//
//
//   nano_font::nano_font()
//   {
//
//      m_pdisplay = nullptr;
//      m_xfontset = 0;
//
//   }
//
//
//   nano_font::~nano_font()
//   {
//
//      if(m_xfontset)
//      {
//
//         XFreeFontSet(m_pdisplay, m_xfontset);
//
//      }
//
//   }
//
//
//   void nano_font::update(::nano_device * pnanodevice)
//   {
//
//      auto px11nanodevice = dynamic_cast < ::x11::nano_device * >(pnanodevice);
//
//      if(m_pdisplay == nullptr)
//      {
//
//         m_pdisplay = px11nanodevice->m_pdisplay;
//
//         if (m_xfontset)
//         {
//
//            XFreeFontSet(m_pdisplay, m_xfontset);
//
//            m_xfontset = 0;
//
//         }
//
//         char ** missingCharset_list = nullptr;
//
//         int missingCharset_count = 0;
//
//         m_xfontset = XCreateFontSet(m_pdisplay,
//                                     "-*-*-medium-r-*-*-*-140-75-75-*-*-*-*",
//                                     &missingCharset_list, &missingCharset_count, nullptr);
//
//         if (missingCharset_count)
//         {
//
//            fprintf(stderr, "Missing charsets :\n");
//
//            for (int i = 0; i < missingCharset_count; i++)
//            {
//
//               fprintf(stderr, "%s\n", missingCharset_list[i]);
//
//            }
//
//            XFreeStringList(missingCharset_list);
//
//         }
//
//      }
//
//
//   }
//
//
//} // namespace x11
//
//
//
