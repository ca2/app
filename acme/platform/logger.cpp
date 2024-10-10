// Created by camilo on 2021-07-17 23:30 BRT <3ThomasBorregaardSorensen!!
// Dedicated logger.cpp for logger created by camilo on
// 2024-09-23 01:19 Always(altid) dedicated to <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "logger.h"
#include "acme/platform/system.h"


void logger::initialize(::particle * pparticle)
{

    ::object::initialize(pparticle);

    if(m_etracelevelMinimum == e_trace_level_undefined)
    {

        m_etracelevelMinimum = system()->get_trace_level();

    }

}



