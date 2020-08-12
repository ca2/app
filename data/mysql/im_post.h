#pragma once


class db_server;


class CLASS_DECL_AURA im_post :
   public db_set
{
public:

   im_post(db_server * pdatacentral);
   virtual ~im_post();


   /*class CLASS_DECL_AURA record
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
   var get_since(var record);
   var last(var user1, var user2);
   var current();


};


