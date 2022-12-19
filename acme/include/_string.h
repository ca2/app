// Created by camilo on 2022-12-18 20:33 <3ThomasBorregaardSorensen!!
#pragma once


/// String dependent declarations


CLASS_DECL_ACME::atom message_box_synchronous(::particle * ppartcicle, const scoped_string & strMessage, const scoped_string & strTitle = nullptr, const e_message_box & emessagebox = e_message_box_ok, const scoped_string & strDetails = nullptr);

CLASS_DECL_ACME void message_box_asynchronous(::function < void(const ::atom & atom) > function, ::particle * pparticle, const scoped_string & strMessage, const scoped_string & strTitle = nullptr, const e_message_box & emessagebox = e_message_box_ok, const scoped_string & strDetails = nullptr);

CLASS_DECL_ACME void throw_exit_exception(const ::e_status & estatus = error_failed, ::task * playeredThreadExit = nullptr, const scoped_string & strMessage = nullptr);




