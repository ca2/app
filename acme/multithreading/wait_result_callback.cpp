#include "framework.h"
#include "acme/id.h"


wait_result_callback::wait_result_callback() :
   callback(id_result, [this](const var& varResult)
      {

         m_varResult = varResult;

         m_event.set_event();

      })
{

}


wait_result_callback::~wait_result_callback()
{

   m_event.wait();

}



