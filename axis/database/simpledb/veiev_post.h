#pragma once


class db_server;


class CLASS_DECL_AXIS veiev_post :
   public db_set
{
public:


   veiev_post(db_server * pdatacentral);
   virtual ~veiev_post();


   /*class CLASS_DECL_AXIS record
   {
   public:
      var sender;
      var recipient;
      var sent;
      var send_time;
      var index;
      var message;
   };*/


   bool write(var record);
   var last();
   var current();


   var get_page(::index iPage, ::count iMessageCountPerPage);
   i64 get_count();


};



