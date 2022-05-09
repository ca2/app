// Injected in acme (camilo) from apex(thomas) by camilo on ThomasMonth19-2021 12:27 BRT
// Merge with control_"topic" by camilo on day after ThomasBirthday2021 10:14
// Created by camilo on 2021-02-04 18:05 <3ThomasBorregaardSorensen!!
// Renamed to topic by camilo on 2021-02-04 18:05 <3ThomasBorregaardSorensen!!
#pragma once


class extended_topic;


struct PARTICLE
{
public:


   class ::atom         m_atom;


   PARTICLE()
   {

   }


   PARTICLE(const class ::atom & atom) :
      m_atom(atom)
   {

   }


   PARTICLE(const PARTICLE & topic) :
      m_atom(topic.m_atom)
   {

   }


   PARTICLE(PARTICLE && topic) :
      m_atom(topic.m_atom)
   {

   }


};



class CLASS_DECL_ACME particle :
   virtual public PARTICLE
{
public:


   particle()
   {

   }


   particle(const class ::atom & atom) :
      PARTICLE(atom)
   {

   }


   particle(const particle & particle) :
      PARTICLE(particle)
   {

   }


   particle(particle && particle) :
      PARTICLE(particle)
   {

   }


};



