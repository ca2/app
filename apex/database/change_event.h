#pragma once


#include "key.h"
#include "apex/user/user/message.h"
//#include "acme/prototype/prototype/payload.h"


namespace database
{


   class server;
   //class key;


   class CLASS_DECL_APEX change_event :
      public ::message::message
   {
   public:


      server *                m_pserver;
      client *                m_pclient;
      ::string                m_strDataKey;
      ::topic *               m_pupdate;
      bool                    m_bOk;
      ::payload *             m_ppayload;


      change_event();
      change_event(::payload & payload);


      bool _data_get(::payload & payload);


      inline ::payload data_get()
      {

         ::payload payload;

         if (!_data_get(payload))
         {

            return ::e_type_not_found;

         }

         return payload;

      }



   };


} // namespace happening


