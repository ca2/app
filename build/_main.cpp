#include "framework.h"
#define APPLICATION app_core_build
#define __APP_ID "app-core/hellomultiverse"
#if defined(WINDOWS_DESKTOP) && defined(CUBE)
#include "([a-z0-9_]+)_factory.inl"
#endif
#include "acme/application.h"
