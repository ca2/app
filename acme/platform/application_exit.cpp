// Created on 2021-07-08 13:18 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "application_exit.h"
#include "acme/platform/application.h"


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

      return;

   }

   information() <<  "application_exit request_exit_application";

   m_bProcessingApplicationExitRequest = true;

   application()->post([this]()
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

}


bool application_exit::can_exit_application()
{

   return true;

}


void application_exit::exit_application()
{

   destroy();

   //return ::success;

}
