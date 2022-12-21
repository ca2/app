// Created by camilo on 2022-03-13 02:57 PM <3ThomasBorregaardS�rensen!!
#include "framework.h"
#include "bad_file_format.h"


bad_file_format::bad_file_format(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrDetails, const ::e_status & estatus) :
   ::exception(estatus, pszMessage, pszDetails)
{

}


bad_file_format::~bad_file_format()
{


}



