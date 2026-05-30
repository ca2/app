#pragma once


#include "acme/platform/message.h"


namespace user
{


   class CLASS_DECL_ACME key :
      virtual public ::acme::message
   {
   public:

      ::i32                  m_iCode;
      uptr                 m_nChar;
      uptr                 m_nScanCode;
      ::u32         m_nRepCnt;
      ::u32         m_nFlags;
      bool                 m_bExt;
      ::i32                  m_iVirtualKey;

      ::user::e_key     m_ekey;

      string            m_strText;

      key();
      key(const ::user::key & key);

      key & operator = (const key & key);

   };


} // namespace user



