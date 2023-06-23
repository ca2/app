// Created by camilo on 2022-10-11 00:05 <3ThomasBorregaardSorensen!! (Thomas Likes Number 5!!)
#pragma once


namespace interprocess
{


   class CLASS_DECL_APEX handler :
      virtual public ::element
   {
   public:


      //virtual bool on_interprocess_receive(rx * prx, ::pointer<dispatch_item>&& pdispatchitem);
      virtual bool on_interprocess_handle(::interprocess::target * ptarget, const ::string & strUri);
      //virtual bool on_interprocess_receive(rx * prx, int message, ::memory && memory);
      //virtual void on_interprocess_post(rx * prx, i64 a, i64 b);


   };


} // namespace interprocess



