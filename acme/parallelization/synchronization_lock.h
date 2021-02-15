#pragma once


class CLASS_DECL_ACME synchronization_lock :
   public initial_single_lock
{
public:


   explicit synchronization_lock(synchronization_object * pobject) :
      initial_single_lock(pobject)
   {


   }


   synchronization_lock(matter * pobject) :
      initial_single_lock(pobject == nullptr ? nullptr : pobject->mutex())
   {

   }


};





