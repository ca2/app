// Created by camilo on 2024-04-17 01:11 <3ThomasBorregaardSorensen!!
#pragma once


class runtime_check_exception :
   virtual public ::exception
{
public:


   runtime_check_exception(const ::e_status& estatus, const_char_pointer  pszMessage = nullptr, const_char_pointer  pszDetails = nullptr, int iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void* caller_address = nullptr);
   runtime_check_exception(const ::e_status& estatus, const ::array_non_particle < error_code >& errorcodea, const_char_pointer  pszMessage = nullptr, const_char_pointer  pszDetails = nullptr, int iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void* caller_address = nullptr);
   virtual ~runtime_check_exception();


};