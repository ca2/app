//
// Created by camilo on 2026-04-05 03:04 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "subsystem.h"
#include "node/Shell.h"
#include "node/WTS.h"


namespace windows
{
   namespace subsystem
   {


      subsystem::subsystem()
      {



      }


      subsystem::~subsystem()
      {


      }


       ::windows::WTS* subsystem::wts()
      {

          if (!m_pwts)
          {

              construct_newø(m_pwts);

          }

          return m_pwts;


      }


   }//namespace subsystem
} // namespace windows

