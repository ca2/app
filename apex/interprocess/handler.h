// Created by camilo on 2022-10-11 00:05 <3ThomasBorregaardSorensen!! (Thomas Likes Number 5!!)
#pragma once


namespace interprocess
{


   class CLASS_DECL_APEX handler :
      virtual public ::particle
   {
   public:


      ::pointer < handler > m_pinterprocesshandlerNext;

      //virtual bool on_interprocess_receive(rx * prx, ::pointer<dispatch_item>&& pdispatchitem);
      //virtual bool on_interprocess_handle(::interprocess::target * ptarget, const ::string & strUri);
      //virtual bool on_interprocess_receive(rx * prx, int message, ::memory && memory);
      //virtual void on_interprocess_post(rx * prx, huge_integer a, huge_integer b);

      virtual bool _handle_interprocess(::interprocess::target* ptarget, ::payload& payload, const ::string& strObject, const ::string& strMember, ::property_set& propertyset);

      virtual bool _on_interprocess_handle(::interprocess::target* ptarget, ::payload& payload, const ::string& strObject, const ::string& strMember, ::property_set& propertyset);


   };


} // namespace interprocess



