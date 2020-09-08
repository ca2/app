#pragma once


class update :
   virtual public ::context_object
{
public:


   e_update                m_eupdate;
   ::object *              m_pobjectTopic;
   ::action_context       m_context;

   update(::object * pobject) : ::context_object(pobject) {}
   virtual ~update() {}

};