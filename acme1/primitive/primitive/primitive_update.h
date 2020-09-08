#pragma once


class update :
   virtual public ::generic
{
public:


   e_update                m_eupdate;
   ::generic *              m_pobjectTopic;
   ::action_context       m_context;

   update(::generic * pobject) : ::generic(pobject) {}
   virtual ~update() {}

};