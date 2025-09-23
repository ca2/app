// From application_build_helper to implement.cpp by camilo on 2021-12-17 21:04 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "application.h"


IMPLEMENT_APPLICATION_FACTORY(store);


namespace store
{


application::application()
{
m_strLaunchAppId = "app-core/store";

}

application::~application()
{


}


} // namespace store
