#include "framework.h"


//int_bool m_psystem->m_pacmefile->put_contents(const char * path, const char * contents)
//{
//
//   return m_psystem->m_pacmefile->put_contents(path, contents, strlen(contents));
//
//}


CLASS_DECL_ACME bool _os_resolve_alias(::matter * pobject, ::file::path & path, const char * psz, ::user::primitive * pinteraction, bool bNoUI, bool bNoMount);

CLASS_DECL_ACME bool _os_may_have_alias(const char * psz);

//bool context::os_resolve_alias(::file::path & path, const char * psz, ::user::primitive * pinteraction, bool bNoUI, bool bNoMount)
//{
//
//   if (_os_resolve_alias(path, psz, pinteraction, bNoUI, bNoMount))
//   {
//
//      return true;
//
//   }
//
//   if (_os_may_have_alias(psz))
//   {
//
//      ::file::patha patha;
//
//      ::file::patha pathaRelative;
//
//      path.ascendants_path(patha, &pathaRelative);
//
//      for (index i = 0; i < patha.get_count(); i++)
//      {
//
//         ::file::path pathAlias = patha[i];
//
//#ifndef LINUX
//         if (os_is_alias(pathAlias))
//#endif
//         {
//
//            ::file::path pathTargetFolder;
//
//            if (_os_resolve_alias(pathTargetFolder, pathAlias, pinteraction, bNoUI, bNoMount))
//            {
//
//               path = pathTargetFolder / pathaRelative[i];
//
//               return true;
//
//            }
//
//         }
//
//      }
//
//   }
//
//   return false;
//
//}
//
//
//
//
