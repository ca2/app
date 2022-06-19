// Recreated by camilo on 2022-01-12 23:15 <3ThomasBorregaardSørensen!!
#pragma once


class CLASS_DECL_ACME conversation :
   virtual public ::element
{
public:


   __pointer(::sequence < ::conversation >)           m_psequence;
   ::atom                                             m_atomResult;


   virtual void do_message_box(const ::string& strMessage, const string& strTitle, const ::e_message_box& emessagebox);


   virtual ::string get_message_box_message();
   virtual ::string get_message_box_title();
   virtual ::e_message_box get_message_box_flags();
   
   
   virtual ::atom do_synchronously();


};



