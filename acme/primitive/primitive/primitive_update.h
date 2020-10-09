#pragma once


class update :
   virtual public ::element
{
public:


   e_update                m_eupdate;
   ::element *              m_pobjectTopic;
   ::action_context       m_context;

   update(::element * pobject) : ::element(pobject) {}
   virtual ~update() {}

};