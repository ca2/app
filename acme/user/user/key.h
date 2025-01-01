#pragma once


#include "acme/platform/message.h"


namespace user
{


   class CLASS_DECL_ACME key :
      virtual public ::acme::message
   {
   public:

      int               m_iCode;
      uptr              m_nChar;
      uptr              m_nScanCode;
      unsigned int              m_nRepCnt;
      unsigned int              m_nFlags;
      bool              m_bExt;
      int               m_iVirtualKey;

      ::user::enum_key     m_ekey;

      string            m_strText;

      key();
      key(const ::user::key & key);

      key & operator = (const key & key);

   };


} // namespace user



