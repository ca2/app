//
//  macos_ns_exception.hpp
//  acid
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 21/07/17.
//
//
#pragma once


#include "acid/exception/exception.h"


class CLASS_DECL_ACID ns_exception :
   public ::exception
{
public:
   
   ::string             m_strName;
   ::string             m_strDescription;
   ::property_set       m_setUserInfo;
   
   
   ns_exception(const ::e_status & estatus, const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrDescription, const ::property_set & setUserInfo);
   ~ns_exception() override;
   
   
};


void InstallUncaughtExceptionHandler();
void UninstallUncaughtExceptionHandler();
void InstallNullExceptionHandler();




