#include "framework.h"
#define APPLICATION app_message_box
#define __APP_ID "app/message_box"
#if defined(WINDOWS_DESKTOP) && defined(CUBE)
#include "([a-z0-9_]+)_factory.inl"
#endif
#include "acme/application.h"
