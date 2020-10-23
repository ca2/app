#pragma once


class CLASS_DECL_ACME sync_future : 
   public future
{
public:


   var                     m_var;
   manual_reset_event      m_event;


   sync_future();

   virtual ~sync_future();


};



