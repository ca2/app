// Created by camilo:hi5! on 2024-05-07 10:47 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "quantum.h"



quantum::~quantum()
{



}


void quantum::information_log(const char * psz)
{

    ::information_log(psz);

}


void quantum::informationf_log(const char * psz,...)
{

    va_list args;

    va_start(args, psz);
    auto str = string_formatf_arguments(psz, args);
    va_end(args);

    information_log(str);

}



void quantum::error_log(const char * psz)
{

    ::acid::error_log(psz);

}


void quantum::errorf_log(const char * psz,...)
{

    va_list args;

    va_start(args, psz);
    auto str = string_formatf_arguments(psz, args);
    va_end(args);

    error_log(str);

}

