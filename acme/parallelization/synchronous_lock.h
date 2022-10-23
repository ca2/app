#pragma once


#include "single_lock.h"


class CLASS_DECL_ACME synchronous_lock :
   public single_lock
{
public:


   explicit synchronous_lock(synchronization_object * pobject) :
      single_lock(pobject, true)
   {


   }


   synchronous_lock(matter * pobject) :
      single_lock(pobject == nullptr ? nullptr : pobject->mutex())
   {

   }


};




class CLASS_DECL_ACME _synchronous_lock :
   public _single_lock
{
public:


   explicit _synchronous_lock(synchronization_object * pobject) :
      _single_lock(pobject, true)
   {


   }


   _synchronous_lock(matter * pobject) :
      _single_lock(pobject == nullptr ? nullptr : pobject->mutex())
   {

   }


};



