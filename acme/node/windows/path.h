#pragma once


namespace windows
{


   struct CLASS_DECL_ACME path
   {

#ifdef WINDOWS_DESKTOP

      itemidlist        m_idlist;

#endif

      path_os() {}


#ifdef WINDOWS_DESKTOP

      path_os(const path_os & path) : m_idlist(path.m_idlist) {}

      path_os(path_os && path) : m_idlist(::move(path.m_idlist)) {}

#else

      path_os(const path_os & path) {}

      path_os(path_os && path) {}

#endif




   };



} // namespace windows


