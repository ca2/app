#pragma once


#ifdef WINDOWS_DESKTOP

class CLASS_DECL_AURA aaa_composition_imm_client :
   virtual public imm_client
{
public:



   virtual void get_ime_composition_area(::rectangle & r);
   virtual bool edit_undo();


};

#endif


