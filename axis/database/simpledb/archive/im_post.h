#pragma once


class db_server;


class CLASS_DECL_CORE im_post :
   public db_set
{
public:

   im_post(db_server * pdatacentral);
   virtual ~im_post();


   /*class CLASS_DECL_CORE record
   {
   public:
      ::payload sender;
      ::payload recipient;
      ::payload sent;
      ::payload send_time;
      ::payload index;
      ::payload message;
   };*/


   bool write(::payload record);
   ::payload get_since(::payload record);
   ::payload last(::payload user1, ::payload user2);
   ::payload current();


};


