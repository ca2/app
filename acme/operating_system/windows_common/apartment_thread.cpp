//
// Created by camilo on 2026-05-23 20:00 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#include "framework.h"
#include "apartment_thread.h"


namespace windows
{

   apartment_thread::apartment_thread()
   {
      m_strTaskName = "apartment_thread";
      m_bCoInitialize=true;
      m_bCoInitializeMultithreaded=false;
      m_bMessageThread= true;
      m_bRunMainLoop = true;
   }
   apartment_thread::~apartment_thread()
   {

   }
} // namespace windows

namespace platform
{
   ::windows::apartment_thread * system::apartment_thread()
   {

      if (!m_papartmentthread)
      {


         construct_newø(m_papartmentthread);
         m_papartmentthread->branch_synchronously();
      }
      return m_papartmentthread;


   }
}// namespace platform