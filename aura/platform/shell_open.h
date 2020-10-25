#pragma once


class CLASS_DECL_AURA shell_open :
   virtual public ::object
{
public:


   shell_open();
   virtual ~shell_open();

   virtual ::estatus initialize(::layered * pobjectContext) override;


   virtual ::estatus initialize_shell_open();


};



