// Created by camilo on 2022-02-05 21:34 <3ThomasBorregaardS�rensen!! (Thomas likes number 5 : day 5)
#include "framework.h"
#include "library_not_loaded.h"


library_not_loaded::library_not_loaded(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrDetails, const ::e_status & estatus) :
   ::exception(estatus, scopedstrMessage, scopedstrDetails)
{

}


library_not_loaded::~library_not_loaded()
{


}



