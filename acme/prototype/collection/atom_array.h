#pragma once


#include "array_base.h"
//#include "comparable_eq_array.h"
//#include "comparable_array.h"



class atom_array_base :
   public ::comparable_array_base < atom >
{
public:


   using BASE_ARRAY = ::comparable_array_base < atom >;


   ///using BASE_ARRAY::BASE_ARRAY;
   using BASE_ARRAY::operator =;

   
   atom_array_base() {}
   atom_array_base(const atom_array_base & a):BASE_ARRAY(a) {}
   atom_array_base(const std::initializer_list < ::atom > & atomlist) :BASE_ARRAY(atomlist) {}


};








using atom_array = ::array_particle < atom_array_base >;
