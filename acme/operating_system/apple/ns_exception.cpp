//
//  macos_ns_exception.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 21/07/17.
//
//

#include "ns_exception.h"


ns_exception::ns_exception(const ::e_status & estatus, const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrDescription, const ::property_set & setUserInfo) :
exception(estatus, scopedstrName, scopedstrDescription),
m_strName(scopedstrName),
m_strDescription(scopedstrDescription),
m_setUserInfo(setUserInfo)
{

   

}


ns_exception::~ns_exception()
{

}
