﻿// Created by camilo on 2021-10-08 11:10 BRT <3ThomasBorregaardS�rensen!!
#pragma once


//// very short name ([{c}])ontext (switchers, as it as action_context) enums


enum enum_default_initialization
{

   e_default_initialization

};


enum enum_no_initialize
{


   e_no_initialize,


};


enum enum_zero
{


   e_zero,


}; 


enum enum_now
{


   e_now,


};


enum enum_infinite
{


   e_infinite,


};


enum enum_normalize
{


   e_normalize


};


enum enum_raw
{


   e_raw


};


enum enum_null
{


   e_null


};


enum enum_empty
{


   e_empty


};



enum enum_create_new
{

   e_create_new

};


enum enum_create
{

   e_create

};


enum enum_defer_new // memory_new - for factoryless_allocation FACTORYLESS_ALLOCATION_ID
{

   e_defer_new

};


enum enum_move_transfer
{

   e_move_transfer

};


enum enum_copy_clone
{

   e_copy_clone

};


enum enum_flush
{

   e_flush,

};


enum enum_unit_size
{


   e_unit_size,


};




enum enum_command
{

   e_command_file_nothing = -1,
   e_command_none = 0,
   e_command_default,
   e_command_application_start,
   e_command_file_new,
   e_command_file_open,
   e_command_file_print,
   e_command_file_print_to,
   e_command_file_dde,
   e_command_app_unregister,
   e_command_request_exit,
   e_command_protocol

};





enum enum_get_buffer
{

   e_get_buffer,

};


//class string;
enum enum_for_moving
{

   e_for_moving,

};



namespace library
{


   enum enum_state
   {

      e_state_none = 0,
      e_state_available = 1,
      e_state_installed = 2,
      e_state_installing = 4,
      e_state_queued = 8,

   };


} // namespace library

