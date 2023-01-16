// Created by camilo on 2022-11-03 17:24 <3ThomasBorregaardSørensen!!
#pragma once


////#include "acme/exception/exception.h"
#include "acme/_operating_system.h"


class CLASS_DECL_ACME last_error_exception :
   public ::exception
{
public:


   last_error_exception(DWORD dwLastError, const ::scoped_string & scopedstrMessage = nullptr, const ::scoped_string & scopedstrDetails = nullptr);


};



