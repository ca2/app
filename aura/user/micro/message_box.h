// Created by camilo on 2022-05-08 18:23 <3ThomasBorregaardSørensen!!
#pragma once



class CLASS_DECL_AURA micro_message_box :
   virtual public ::conversation,
   virtual public ::object
{
public:


   micro_message_box();
   ~micro_message_box() override;


   void do_message_box(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox) override;


};
