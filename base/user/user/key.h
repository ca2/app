#pragma once



namespace user
{


   class CLASS_DECL_AURA key :
      public ::message::base
   {
      public:

         int               m_iCode;
         uptr              m_nChar;
         uptr              m_nScanCode;
         UINT              m_nRepCnt;
         UINT              m_nFlags;
         bool              m_bExt;
         int               m_iVirtualKey;

         ::user::e_key     m_ekey;

         string            m_strText;

         key();
         key(const ::user::key & key);

         void copy_this(const key & key);

   };


} // namespace user


