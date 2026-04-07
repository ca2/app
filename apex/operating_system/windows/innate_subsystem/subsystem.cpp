//
// Created by camilo on 2026-04-06 10:54 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "subsystem.h"


namespace windows
{

namespace innate_subsystem
{


   subsystem::subsystem()
   {



   }


   subsystem::~subsystem()
   {


   }

   //
   // ::subsystem::string_table * subsystem::string_table()
   // {
   //
   //    if (!m_pstringtable)
   //    {
   //
   //       constructø(m_pstringtable);
   //
   //    }
   //
   //    return m_pstringtable;
   //
   // }
   //
   //
   //
   // ::subsystem::resource_loader * subsystem::resource_loader()
   // {
   //
   //    if (!m_presourceloader)
   //    {
   //
   //       constructø(m_presourceloader);
   //
   //    }
   //
   //    return m_presourceloader;
   //
   // }
   //
   //
   //
   // ::subsystem::Registry * subsystem::registry()
   // {
   //
   //    if (!m_pregistry)
   //    {
   //
   //       construct_newø(m_pregistry);
   //
   //    }
   //
   //    return m_pregistry;
   //
   // }
   //
   //
   // ::subsystem::Shell * subsystem::shell()
   // {
   //
   //    if (!m_pshell)
   //    {
   //
   //       constructø(m_pshell);
   //
   //    }
   //
   //    return m_pshell;
   //
   // }
   //
   // ::pointer < ::subsystem::SecurityIdentifier > subsystem::createSidFromString(const ::scoped_string & scopedstr)
   // {
   //
   //    return nullptr;
   //
   // }


   int subsystem::message_box(
                   HWND hwnd,
                   const ::scoped_string & scopedstrMessage,
                   const ::scoped_string & scopedstrCaption,
                   unsigned int uType)
   {

      auto iResult = ::MessageBox(hwnd, ::wstring(scopedstrMessage), ::wstring(scopedstrCaption), uType);

      return iResult;

   }



}//namespace subsystem


} // namespace windows