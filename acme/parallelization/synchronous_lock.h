#pragma once


#include "acme/parallelization/single_lock.h"
////#include "acme/prototype/prototype/matter.h"

#define SYNCHRONOUS_LOCK_SUFFIX __FILE__, __LINE__
#define DEFAULT_SYNCHRONOUS_LOCK_SUFFIX this, __FILE__, __LINE__


class CLASS_DECL_ACME synchronous_lock :
   public single_lock
{
public:


   explicit synchronous_lock(particle * pparticle, const ::subparticle * psubparticleContext = nullptr, const_char_pointer pszFile = nullptr, int iLine = -1) :
      single_lock(pparticle, true, psubparticleContext, pszFile, iLine)
   {


   }



};


class CLASS_DECL_ACME _synchronous_lock :
   public _single_lock
{
public:


   explicit _synchronous_lock(::particle * pparticle, const ::subparticle * psubparticleContext = nullptr, const_char_pointer pszFile = nullptr, int iLine = -1) :
      _single_lock(pparticle, true, psubparticleContext, pszFile, iLine)
   {


   }


};



