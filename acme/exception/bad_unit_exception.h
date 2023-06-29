// Created by camilo on 2022-06-29 09:14 PM <3ThomasBorregaardSorensen!!
#pragma once


#include "exception.h"


template < typename ENUM > 
class bad_unit_exception :
   public ::exception
{
public:

   
   ENUM m_eunit;


   bad_unit_exception(ENUM eunit) :m_eunit(eunit) {}
   ~bad_unit_exception() override {}


};
