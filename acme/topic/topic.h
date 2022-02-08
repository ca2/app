// Injected in acme (camilo) from apex(thomas) by camilo on ThomasMonth19-2021 12:27 BRT
// Merge with control_"topic" by camilo on day after ThomasBirthday2021 10:14
// Created by camilo on 2021-02-04 18:05 <3ThomasBorregaardSorensen!!
// Renamed to topic by camilo on 2021-02-04 18:05 <3ThomasBorregaardSorensen!!
#pragma once


class extended_topic;


struct TOPIC
{
public:
   

   class ::atom         m_atom;

   TOPIC()
   {

   }


   TOPIC(const class ::atom & atom) :
      m_atom(atom)
   {

   }


   TOPIC(const TOPIC & topic) :
      m_atom(topic.m_atom)
   {

   }


   TOPIC(TOPIC && topic) :
      m_atom(topic.m_atom)
   {

   }


};
   


class CLASS_DECL_ACME topic :
   virtual public TOPIC
{
public:


   topic()
   {

   }


   topic(const class ::atom & atom) :
      TOPIC(atom)
   {

   }


   topic(const topic & topic) :
      TOPIC(topic)
   {

   }


   topic(topic && topic) :
      TOPIC(topic)
   {

   }


   virtual ::extended_topic * get_extended_topic();
   virtual const ::extended_topic * get_extended_topic() const;


};
   


