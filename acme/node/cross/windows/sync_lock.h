#pragma once


class CLASS_DECL_ACME synchronous_lock :
   public initial_single_lock
{
public:


   explicit synchronous_lock(synchronization_object * pobject) :
      initial_single_lock(pobject)
   {


   }


   synchronous_lock(matter * pobject) :
      initial_single_lock(pobject == nullptr ? nullptr : pobject->mutex())
   {

   }


};





