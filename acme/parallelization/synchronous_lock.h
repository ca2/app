#pragma once


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



