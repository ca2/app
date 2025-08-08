// Created by camilo on 2024-04-17 01:11 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "runtime_check.h"


runtime_check_exception::runtime_check_exception(const ::e_status& estatus, const_char_pointer pszMessage, const_char_pointer pszDetails , int iSkip, void* caller_address) :
   ::exception::exception(estatus, pszMessage, pszDetails, iSkip, caller_address)
{


}


runtime_check_exception::runtime_check_exception(const ::e_status& estatus, const ::proto < array < error_code > > & errorcodea, const_char_pointer pszMessage, const_char_pointer pszDetails, int iSkip, void* caller_address) :
   ::exception::exception(estatus, errorcodea, pszMessage, pszDetails, iSkip, caller_address)
{


}


runtime_check_exception::~runtime_check_exception()
{


}

