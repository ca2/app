// Created by CamiloSTTBS 2020-12-25 14:01 BRT <3ThomasBS_, Mummi and bilbo!!
#include "framework.h"


namespace aura
{


    ::estatus system::message_box(const char* pszMessage, const char* pszTitle, const ::e_message_box& emessagebox, const ::promise::process& process)
    {

        auto estatus = os_message_box(pszMessage, pszTitle, emessagebox, process);

        return estatus;

    }


    ::estatus system::message_box_timeout(const char* pszMessage, const char* pszTitle, const ::duration & duration, const ::e_message_box& emessagebox, const ::promise::process& process)
    {

        auto estatus = os_message_box(pszMessage, pszTitle, emessagebox, process);

        return estatus;

    }


} // namespace aura




