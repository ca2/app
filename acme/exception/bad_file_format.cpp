// Created by camilo on 2022-03-13 02:57 PM <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "bad_file_format.h"


bad_file_format::bad_file_format(const char * pszMessage, const char * pszDetails, const ::e_status & estatus) :
   ::exception(estatus, pszMessage, pszDetails)
{

}


bad_file_format::~bad_file_format()
{


}



