#pragma once


class db_server;


class CLASS_DECL_AURA veiev_post :
   public db_set
{
public:


   veiev_post(db_server * pdatacentral);
   virtual ~veiev_post();


   /*class CLASS_DECL_AURA record
   {
   public:
      payload sender;
      payload recipient;
      payload sent;
      payload send_time;
      payload index;
      payload message;
   };*/


   bool write(payload record);
   payload last();
   payload current();


   payload get_page(::index iPage, ::count iMessageCountPerPage);
   i64 get_count();


};



