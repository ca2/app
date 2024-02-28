#include "framework.h"
#include "acme/_operating_system.h"


bool _c_simple_message_loop_step()
{

   MSG msg;

   if (!::GetMessage(&msg, nullptr, 0, 0xffffffffu))
   {

      return false;

   }

   TranslateMessage(&msg);

   DispatchMessage(&msg);

   return true;

}




void _c_simple_message_loop()
{

	while(_c_simple_message_loop_step())
	{
		
	}

}



