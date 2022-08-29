#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif
#include "icon.h"


namespace filemanager
{


   icon_key::icon_key()
   {
      m_iIcon = -1;
   }

   icon_key::icon_key(const icon_key & key)
   {
      m_strPath         = key.m_strPath;
      m_iIcon           = key.m_iIcon;
      m_strExtension    = key.m_strExtension;
   }

   bool icon_key::operator == (const icon_key & key) const
   {
      return m_strPath == key.m_strPath
         && m_strExtension == key.m_strExtension
         && m_iIcon == key.m_iIcon;
   }

   icon::icon()
   {
      m_iImage = -1;
   }


} // namespace filemanager



