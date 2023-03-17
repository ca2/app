//
// Created by camilo on 2021-08-12 03:03 BRT <3Thomas Borregaard Sorensen!!
//
#pragma once


CLASS_DECL_ACME void copy(struct timespec * ptimespec, const class ::time * ptime);
CLASS_DECL_ACME void copy(class ::time * ptime, const struct timespec * ptimespec);



[[noreturn]] CLASS_DECL_ACME void throw_errno_exception(const ::scoped_string & scopedstr = nullptr, int iErrNo = 0);
[[noreturn]] CLASS_DECL_ACME void throw_errno_exception(const ::file::path & path, ::file::e_open eopen, const ::scoped_string & scopedstr = nullptr, int iErrNo = 0);



