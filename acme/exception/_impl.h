// Created on by camilo 2021-04-08 07:54 BRT <3TBS_!!
#pragma once


inline void throw_status(const ::e_status& estatus, const char * pszMessage)
{

   throw_status(estatus.m_estatus, pszMessage);

}


inline void throw_status(const ::enum_status& estatus, const char* pszMessage)
{

   if (estatus == error_not_implemented)
   {

      throw not_implemented_exception(pszMessage);

   }
   else if (estatus == error_interface_only)
   {

      throw interface_only_exception(pszMessage);

   }
   else if (estatus == error_io)
   {

      throw io_exception(pszMessage);

   }
   else
   {
    
      throw ::exception::exception(estatus, pszMessage);

   }

}



