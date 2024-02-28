#pragma once


#include "single_lock.h"
////#include "acme/primitive/primitive/matter.h"


class CLASS_DECL_ACME synchronous_lock :
   public single_lock
{
public:


   explicit synchronous_lock(particle * pparticle) :
      single_lock(pparticle, true)
   {


   }



};


class CLASS_DECL_ACME _synchronous_lock :
   public _single_lock
{
public:


   explicit _synchronous_lock(::particle * pparticle) :
      _single_lock(pparticle, true)
   {


   }


};



