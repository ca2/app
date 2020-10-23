#include "framework.h"
#include "acme/id.h"


sync_future::sync_future() :
   future(__future([this](const var& var)
      {

         m_var = var;

         m_event.set_event();

      }))
{

}


sync_future::~sync_future()
{

   m_event.lock();

}



