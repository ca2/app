// Created by camilo on 2022-11-19 03:54 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/department.h"
#include "acme/prototype/collection/comparable_list.h"
#include "_.h"


namespace nano
{

namespace graphics
{
class CLASS_DECL_ACME graphics :
virtual public acme::department
{
public:
   
   
   //::pointer_array < ::micro::elemental >         m_interchangea;
   
   
   graphics();
   ~graphics() override;
   
   
   inline static const_char_pointer represented_component_name(){return "nano_graphics";}

   
   //::pointer < ::subparticle > nano()->message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::::user::e_message_box& emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr);
   
   
   ////pointer< ::sequence < ::conversation > > message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::::user::e_message_box & emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr);
   
   //::pointer < ::subparticle > nano()->message_console(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::::user::e_message_box& emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr);
   
   
//   ::pointer < ::subparticle > message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::::user::e_message_box& emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon=nullptr);
//
//   ::pointer < ::subparticle > exception_message_box(const ::exception& exception, const ::scoped_string & scopedstrMessage = nullptr, const ::scoped_string & scopedstrTitle = nullptr, const ::::user::e_message_box& emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon=nullptr);
//
//   ::pointer < ::subparticle > message_console(const ::scoped_string & scopedstrMessage = nullptr, const ::scoped_string & scopedstrTitle = nullptr, const ::::user::e_message_box& emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon=nullptr);
//
//   ::pointer < ::subparticle > exception_message_console(const ::exception& exception, const ::scoped_string & scopedstrMessage = nullptr, const ::scoped_string & scopedstrTitle = nullptr, const ::::user::e_message_box& emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon=nullptr);
//
   
   void handle(::topic * ptopic, ::handler_context * phandlercontext) override;
   
//
//   virtual void sync(const ::procedure & procedure);
//   virtual void async(const ::procedure & procedure);

//
//   virtual void process_messages();
//
//   virtual bool init_threads();

   
};



   } // namespace graphics


} // namespace nano





CLASS_DECL_ACME void initialize_nano_user(::factory::factory * pfactory);



