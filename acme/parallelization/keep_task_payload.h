// Created by camilo on 2021-10-13 00:54 BRT <3ThomasBorregaardSørensen!!
#pragma once


CLASS_DECL_ACME::payload& task_payload(enum_task_payload etaskpayload);


class CLASS_DECL_ACME ___keep_task_payload
{
public:


   ::payload m_payloadOld;


   ::payload & m_payload;


   ___keep_task_payload(enum_task_payload etaskpayload) :
      m_payload(task_payload(etaskpayload)),
      m_payloadOld(m_payload)
   {

   }


   ~___keep_task_payload()
   {

      m_payload = m_payloadOld;

   }


};


inline ___keep_task_payload keep_thread_payload(enum_task_payload etaskpayload)
{

   return etaskpayload;

}


#define __keep_task_payload(...) auto TOKEN_AT_LINE(__keep_task_payload) = keep_task_payload(__VA_ARGS__)



