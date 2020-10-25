//*****************************************************************************
//
//      Class:          manual_reset_event
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Notifies one or more waiting threads that an event has
//                      occurred.
//
//*****************************************************************************
#include "framework.h"


manual_reset_event::manual_reset_event(char * sz, bool bInitiallyOwn) :
   ::event(sz, bInitiallyOwn, true)
{

}



