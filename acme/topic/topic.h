// Injected in acme (camilo) from apex(thomas) by camilo on ThomasMonth19-2021 12:27 BRT
// Merge with control_"topic" by camilo on day after ThomasBirthday2021 10:14
// Created by camilo on 2021-02-04 18:05 <3ThomasBorregaardSorensen!!
// Renamed to topic by camilo on 2021-02-04 18:05 <3ThomasBorregaardSorensen!!
#pragma once


class extended_topic;


class CLASS_DECL_ACME topic :
   virtual public ::element
{
public:


   bool                                   m_bRet;
   bool                                   m_bOk;
   item                                   m_item;
   ::action_context                       m_actioncontext;
   __pointer(::property_object)           m_psender;
   __pointer(::user::element)             m_puserelement; // user::interaction
   __pointer(::matter)                    m_pmatter;


   topic(const ::atom & atom) : 
      ::PARTICLE(atom),
      ::particle(atom)
   { 
   
      m_bOk = true;
      m_bRet = false;

   }

   ~topic() override 
   { 
   
      m_pmatter.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS_FUNCTION_LINE);
   
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

   ::atom user_element_id() const;


   virtual ::extended_topic * _extended_topic() { return nullptr; }
   virtual const ::extended_topic * _extended_topic() const { return nullptr; }


};
   

inline ::topic_pointer create_topic(const ::atom & atom)
{

   auto ptopic = __new(::topic(atom));;

   return ::move(ptopic);

}



