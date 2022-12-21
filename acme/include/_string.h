// Created by camilo on 2022-12-18 20:33 <3ThomasBorregaardSorensen!!
#pragma once


/// String dependent declarations


CLASS_DECL_ACME::atom message_box_synchronous(::particle * ppartcicle, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const e_message_box & emessagebox = e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr);

CLASS_DECL_ACME void message_box_asynchronous(::function < void(const ::atom & atom) > function, ::particle * pparticle, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const e_message_box & emessagebox = e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr);

CLASS_DECL_ACME void throw_exit_exception(const ::e_status & estatus = error_failed, ::task * playeredThreadExit = nullptr, const ::scoped_string & scopedstrMessage = nullptr);

CLASS_DECL_ACME void output_error_message(const ::scoped_string & strMessage, const ::scoped_string & strTitle = nullptr, int iMessageBox = 0);
CLASS_DECL_ACME void output_debug_string(const ::scoped_string & str);
//CLASS_DECL_ACME void output_debug_string(const ::scoped_string & str;
//CLASS_DECL_ACME void output_debug_string(const ::wd32_character * psz);



