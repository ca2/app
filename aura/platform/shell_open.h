#pragma once


class CLASS_DECL_AURA shell_open :
   virtual public ::object
{
public:


   shell_open();
   virtual ~shell_open();

   virtual ::e_status initialize(::layered * pobjectContext) override;


   virtual ::e_status initialize_shell_open();


};



