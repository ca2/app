// Created by camilo on 2021-11-05 16:33 PM <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "api.h"


__FACTORY_EXPORT void api_twitch_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::api_twitch::api, ::api >();

}



