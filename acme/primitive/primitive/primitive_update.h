#pragma once


class update :
   virtual public ::elemental
{
public:


   e_update                m_eupdate;
   ::elemental *              m_pobjectTopic;
   ::action_context       m_context;

   update(::elemental * pobject) : ::elemental(pobject) {}
   virtual ~update() {}

};