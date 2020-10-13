#pragma once


#include "app/axis/axis/axis/axis.h"


#include "app/aura/node/ansios/ansios.h"
#include "app/aura/node/ios/ios.h"



string get_error_message(DWORD dwError);

__pointer(::aura::application)     ios_instantiate_application(__pointer(::aura::application) pappSystem, const char * pszId);


#include "ios_implementation.h"
#include "ios_axis_dir.h"
#include "ios_axis_file_system.h"
#include "ios_factory_exchange.h"
#include "ios_port_forward.h"
#include "ios_copydesk.h"
#include "ios_crypto.h"
#include "ios_file_set.h"
//#include "ios_ip_enum.h"




int_bool PeekMessage(
                    LPMESSAGE lpMsg,
                    oswindow hWnd,
                    UINT wMsgFilterMin,
                    UINT wMsgFilterMax,
                    UINT wRemoveMsg);

int_bool GetMessage(
                   LPMESSAGE lpMsg,
                   oswindow hWnd,
                   UINT wMsgFilterMin,
                   UINT wMsgFilterMax);



i32 CLASS_DECL_AXIS __ios_main(i32 argc, char * argv[]);


CLASS_DECL_AXIS void vfxThrowFileException(__pointer(::aura::application) papp, i32 cause, LONG lOsError, const char * lpszFileName = nullptr);





