#include "framework.h" 



wait_cursor::wait_cursor(::object * pobject) :
   ::object(pobject)
{
	
	Application.BeginWaitCursor();

}


 wait_cursor::~wait_cursor()
{

    Application.EndWaitCursor();

}


void wait_cursor::Restore()
{
	
	Application.RestoreWaitCursor();

}


