//
// Created by camilo on 22/10/22 22:26 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "assert.h"


assert_exception::assert_exception(const ::scoped_string & scopedstrFile, long lLine) :
   ::exception(::error_assert)
{

   m_strMessage.append_formatf("Assert File=\"%s\" Line=\"%d\"", scopedstrFile.c_str(), lLine);

}


assert_exception::~assert_exception()
{


}


CLASS_DECL_ACME int throw_assert_exception(const char * pszFileName,int iLineNumber)
{

   throw assert_exception(pszFileName,iLineNumber);

}



