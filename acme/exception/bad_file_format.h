// Created by camilo on 2022-03-13 02:56 PM <3ThomasBorregaardS�rensen!!
#pragma once


#include "exception.h"


class CLASS_DECL_ACME bad_file_format :
   public ::exception
{
public:


   bad_file_format(const ::scoped_string & scopedstrMessage = nullptr, const ::scoped_string & scopedstrDetails = nullptr, const ::e_status & estatus = error_bad_file_format);
   ~bad_file_format() override;


};
