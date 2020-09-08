#pragma once


namespace database
{


   class server;


   class CLASS_DECL_AQUA change_event :
      public ::message::message
   {
   public:


      server *          m_pserver;
      client *          m_pclient;
      key               m_datakey;
      ::update *        m_pupdate;
      bool              m_bOk;
      var *             m_pvar;

      change_event();
      change_event(var & var);


      bool _data_get(var & var);


      inline var data_get()
      {

         var var;

         if (!_data_get(var))
         {

            return ::type_not_found;

         }

         return var;

      }



   };


} // namespace event


