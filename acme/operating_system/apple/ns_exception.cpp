//
//  macos_ns_exception.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 21/07/17.
//
//

#include "ns_exception.h"


ns_exception::ns_exception(const ::e_status & estatus, const scoped_string & strName, const scoped_string & strDescription, const ::property_set & setUserInfo) :
exception(estatus, pszName, pszDescription),
m_strName(pszName),
m_strDescription(pszDescription),
m_setUserInfo(setUserInfo)
{

   

}


ns_exception::~ns_exception()
{

}
