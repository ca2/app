#include "framework.h"
#include "acme/id.h"


wait_future::wait_future() :
   future(id_result, [this](const var& varResult)
      {

         m_varResult = varResult;

         m_event.set_event();

      })
{

}


wait_future::~wait_future()
{

   m_event.wait();

}



