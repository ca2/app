#pragma once



class CLASS_DECL_ACME wait_result_callback : 
   public callback
{
public:


   var                     m_varResult;
   manual_reset_event      m_event;


   wait_result_callback();

   virtual ~wait_result_callback();


};



