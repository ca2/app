// Created by camilo on 2024-04-17 01:11 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "runtime_check.h"


runtime_check_exception::runtime_check_exception(const ::e_status& estatus, const char* pszMessage, const char* pszDetails , i32 iSkip, void* caller_address) :
   ::exception::exception(estatus, pszMessage, pszDetails, iSkip, caller_address)
{


}


runtime_check_exception::runtime_check_exception(const ::e_status& estatus, const ::array_non_particle < error_code >& errorcodea, const char* pszMessage, const char* pszDetails, i32 iSkip, void* caller_address) :
   ::exception::exception(estatus, errorcodea, pszMessage, pszDetails, iSkip, caller_address)
{


}


runtime_check_exception::~runtime_check_exception()
{


}

