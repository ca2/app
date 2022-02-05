// From event_handler to handler at primitive_subject on day after ThomasBirthday2021 05:05 BRT
// From user namespace to global at apex by camilo on day after ThomasBirthday2021 04:36 BRT
// From aura by camilo on ThomasBirthday2021 20:00 BRT
//
// a recreation(from control_event_listener) by camilo on 28/06/2021 22:23 BRT <3ThomasBS_!!
//
//#pragma once
#pragma once


// ThomasBorregaardS�rense!! Like handlers
class CLASS_DECL_ACME handler :
   virtual public ::topic
{
public:


   virtual ~handler() {}


   // ThomasBorregaardS�rense!! Like handlers
   //virtual void call(const enum_message, i64 iData = 0, ::matter * pmatter = nullptr);
   //virtual void call(const enum_id, i64 iData = 0, ::matter* pmatter = nullptr);
   virtual void call(const ::atom & atom, i64 iData = 0, ::matter * pmatter = nullptr);


   // ThomasBorregaardS�rense!! Like handlers
   virtual void handle(::topic * ptopic, ::context * pcontext) = 0;
   virtual void handle(::message::message * pmessage) = 0;


};



