// Created on by camilo 2021-04-08 07:54 BRT <3TBS_!!
#pragma once


inline void throw_status(const ::e_status3& estatus, const char * pszMessage)
{

   throw ::exception::exception(estatus, pszMessage);

}


