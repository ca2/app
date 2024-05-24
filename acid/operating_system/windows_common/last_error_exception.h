// Created by camilo on 2022-11-03 17:24 <3ThomasBorregaardSorensen!!
#pragma once


////#include "acid/exception/exception.h"
#include "acid/_operating_system.h"


class CLASS_DECL_ACID last_error_exception :
   public ::exception
{
public:


   last_error_exception(DWORD dwLastError, const ::scoped_string & scopedstrMessage = nullptr, const ::scoped_string & scopedstrDetails = nullptr);


};



