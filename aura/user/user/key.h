#pragma once


#include "apex/user/user/message.h"


namespace user
{


   class CLASS_DECL_AURA key :
      public ::user::message
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

      void copy_this(const key & key);

   };


} // namespace user



