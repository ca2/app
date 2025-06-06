// Injected in acme (camilo) from apex(thomas) by camilo on ThomasMonth19-2021 12:27 BRT
// Merge with control_"topic" by camilo on day after ThomasBirthday2021 10:14
// Created by camilo on 2021-02-04 18:05 <3ThomasBorregaardSorensen!!
// Renamed to topic by camilo on 2021-02-04 18:05 <3ThomasBorregaardSorensen!!
#pragma once


////#include "acme/prototype/prototype/property_object.h"
#include "acme/prototype/prototype/action_context.h"


class extended_topic;


class CLASS_DECL_ACME topic :
   virtual public ::property_object
{
public:


   bool                                   m_bRet;
   bool                                   m_bOk;
   ::item_pointer                         m_pitem;
   ::user::enum_key                       m_ekey;
   ::action_context                       m_actioncontext;
   ::pointer<::property_object>           m_psender;
   ::pointer<::user::element>             m_puserelement; // user::interaction
   ::pointer<::particle>                  m_pparticle;
   unsigned long long                     m_uUpdateSerial;

   //::pointer<::user::activation_token>    m_puseractivationtoken;


   topic(const ::atom & atom) 
   { 
   
      m_atomMatterId = atom;
      m_bOk = true;
      m_bRet = false;

   }

   ~topic() override 
   { 
   
   }


   void Nok()
   {

      m_bOk = false;

      m_bRet = true;

   }


   void Ret()
   {

      m_bRet = true;

   }


   void Ok()
   {

      m_bOk = true;

      m_bRet = true;

   }


   virtual ::user::interaction * user_interaction();

   virtual ::acme::user::interaction * acme_user_interaction();

   virtual ::user::activation_token * user_activation_token();

   ::atom user_interaction_id() const;


   virtual ::extended_topic * _extended_topic() { return nullptr; }
   virtual const ::extended_topic * _extended_topic() const { return nullptr; }


   virtual ::user::form * get_form() const;


   virtual ::user::element * get_form_user_element() const;


   virtual bool is_about(::user::element * pelement) const;


   virtual bool topic_step();


};
   


