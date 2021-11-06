#pragma once


namespace user
{


   class CLASS_DECL_AURA key :
      public ::user::message
   {
   public:

      int               m_iCode;
      uptr              m_nChar;
      uptr              m_nScanCode;
      ::u32              m_nRepCnt;
      ::u32              m_nFlags;
      bool              m_bExt;
      int               m_iVirtualKey;

      ::user::enum_key     m_ekey;

      string            m_strText;

      key();
      key(const ::user::key & key);

      void copy_this(const key & key);

   };


} // namespace user



