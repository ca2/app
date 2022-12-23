#pragma once


// #include "acme/primitive/string/string.h"


namespace filemanager
{


   class CLASS_DECL_CORE icon_key
   {
   public:


      i32         m_iIcon;
      string      m_strPath;
      string      m_strExtension;


      icon_key();
      icon_key(const icon_key & key);


      operator u32 () const
      {
         return m_iIcon;
      }

      bool operator == (const icon_key & key) const;


   };


   class CLASS_DECL_CORE icon
   {
   public:


      i32                 m_iImage;
      ::draw2d::icon *        m_picon;

      icon();


   };



} // namespace filemanager

















