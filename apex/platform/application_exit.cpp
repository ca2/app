// Created on 2021-07-08 13:18 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"



application_exit::application_exit()
{

   m_bProcessingApplicationExitRequest = true;

}


application_exit::~application_exit()
{


}


::e_status application_exit::request_exit_application()
{

   if (m_bProcessingApplicationExitRequest)
   {

      return ::success_scheduled;

   }

   m_bProcessingApplicationExitRequest = true;

   fork([this]()
      {

         try
         {

            exit_application();

         }
         catch (...)
         {

         }

         m_bProcessingApplicationExitRequest = false;

      });

   return ::success;

}


::e_status application_exit::can_exit_application()
{

   return ::success;

}


::e_status application_exit::exit_application()
{

   finish();

   return ::success;

}
