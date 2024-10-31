#include "framework.h"
#include "message.h"
#include "acme/platform/http.h"


namespace http
{


   message::message() 
   {

      m_estatusRet   = ::success_none;

   }


void message::run()
{

      http()->get(this);

}



} // namespace http




