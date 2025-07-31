// Recreated by camilo on 2022-01-12 23:15 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/handler/sequence.h"


class CLASS_DECL_ACME conversation :
   virtual public particle
{
public:


   //pointer< ::sequence < ::conversation > >           m_psequence;
   //::atom                                             m_atomResult;


   conversation() {};
   conversation(conversation && conversation) = delete;


   virtual void initialize_conversation(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon);
   virtual void do_conversation(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box& emessagebox, const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon);


   virtual ::string get_conversation_message();
   virtual ::string get_conversation_title();
   virtual ::e_message_box get_conversation_flags();
   virtual ::string get_conversation_details();
   virtual ::payload get_conversation_result();
   
   //void aggregate(sequence * psequence) override;
   //void aggregate(::subparticle * psubparticle) override;
   //void do_asynchronously() override;


   //virtual void display_conversation_options();

   void run() override;
   
   void complete_step(::sequencer & sequencer) override;


};



