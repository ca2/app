#pragma once


class CLASS_DECL_ACME wait_future : 
   public future
{
public:


   var                     m_varResult;
   manual_reset_event      m_event;


   wait_future();

   virtual ~wait_future();


};



