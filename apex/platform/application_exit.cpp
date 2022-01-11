// Created on 2021-07-08 13:18 BRT <3ThomasBorregaardS�rensen!!
#include "framework.h"



application_exit::application_exit()
{

   m_bProcessingApplicationExitRequest = false;

}


application_exit::~application_exit()
{


}


void application_exit::request_exit_application()
{

   if (m_bProcessingApplicationExitRequest)
   {

      return ::success_scheduled;

   }

   INFORMATION("application_exit request_exit_application");

   m_bProcessingApplicationExitRequest = true;

   post_routine(__routine([this]()
      {

         try
         {

            exit_application();

         }
         catch (...)
         {

         }

         m_bProcessingApplicationExitRequest = false;

      }));

   return ::success;

}


void application_exit::can_exit_application()
{

   return ::success;

}


void application_exit::exit_application()
{

   destroy();

   return ::success;

}
