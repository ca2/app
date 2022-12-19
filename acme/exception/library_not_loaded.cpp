// Created by camilo on 2022-02-05 21:34 <3ThomasBorregaardS�rensen!! (Thomas likes number 5 : day 5)
#include "framework.h"
#include "library_not_loaded.h"


library_not_loaded::library_not_loaded(const scoped_string & strMessage, const scoped_string & strDetails, const ::e_status & estatus) :
   ::exception(estatus, pszMessage, pszDetails)
{

}


library_not_loaded::~library_not_loaded()
{


}



