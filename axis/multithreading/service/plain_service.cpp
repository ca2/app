#include "framework.h"


plain_service::plain_service()
{

}


plain_service::~plain_service()
{

}


void plain_service::Start(u32)
{

   thread_pool::QueueUserWorkItem(this, &plain_service::CallServiceThread);

}


void plain_service::Stop(u32 ui)
{

   //System.m_bDoNotExitIfNoApplications = false;

   m_bStopping = true;

   m_stopped.wait(millis((u32) m_dwStopTimeout));

}


void plain_service::CallServiceThread()
{

   call_server();

}



