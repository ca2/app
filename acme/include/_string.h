// Created by camilo on 2022-12-18 20:33 <3ThomasBorregaardSorensen!!
#pragma once


/// String dependent declarations


CLASS_DECL_ACME::atom message_box_synchronous(::particle * ppartcicle, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const e_message_box & emessagebox = e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr);

CLASS_DECL_ACME void message_box_asynchronous(::function < void(const ::atom & atom) > function, ::particle * pparticle, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const e_message_box & emessagebox = e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr);

CLASS_DECL_ACME void throw_exit_exception(const ::e_status & estatus = error_failed, ::task * playeredThreadExit = nullptr, const ::scoped_string & scopedstrMessage = nullptr);

CLASS_DECL_ACME void output_error_message(const ::scoped_string & strMessage, const ::scoped_string & strTitle = nullptr, int iMessageBox = 0);
CLASS_DECL_ACME void output_debug_string(const ::scoped_string & str);
///CLASS_DECL_ACME void output_debug_string(const ::wide_character * psz);
CLASS_DECL_ACME void output_debug_string_format(const char* pszFormat, ...);

CLASS_DECL_ACME ::string as_string(const ::e_status & estatus);

inline ::string as_string(bool b) { return b ? "1" : "0"; }

CLASS_DECL_ACME void throw_resource_exception(const ::scoped_string & scopedstrMessage);
CLASS_DECL_ACME void throw_exception(const ::e_status & estatus, const ::scoped_string & scopedstrMessage);
CLASS_DECL_ACME void throw_exception(const ::e_status & estatus, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrDetails, i32 iSkip = -1);


template < typename TYPE, enum_type m_etypeContainer >
inline void implode(const numeric_array < TYPE, m_etypeContainer > & a, string & rwstr, const ::scoped_string & scopedstrSeparator = nullptr, ::index start = 0, ::count count = -1);

template < typename TYPE, enum_type m_etypeContainer >
   inline string implode(const numeric_array < TYPE, m_etypeContainer > & a,const ::scoped_string & scopedstrSeparator = nullptr, ::index iStart = 0, ::count iCount = -1);

template < typename TYPE, enum_type m_etypeContainer >
   string surround_and_implode(const numeric_array < TYPE, m_etypeContainer > & a,const ::scoped_string & scopedstrSeparator = nullptr, const ::scoped_string & scopedstrPrefix = nullptr, const ::scoped_string & scopedstrSuffix = nullptr, ::index iStart = 0, ::count iCount = -1);

#include "acme/primitive/collection/_impl_string_array.h"
#include "acme/primitive/primitive/_impl_atom.h"
#include "acme/primitive/collection/_impl_factory.h"
#include "acme/primitive/primitive/_impl_payload.h"
#include "acme/primitive/primitive/_impl_type.h"
#include "acme/filesystem/file/_impl_write_text_stream.h"
#include "acme/filesystem/filesystem/_impl_path.h"







