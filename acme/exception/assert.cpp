//
// Created by camilo on 22/10/22 22:26 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "assert.h"


assert_exception::assert_exception(const char * pszFile, long lLine) :
   ::exception(::error_assert)
{

   m_strMessage.append_format("Assert File=\"%s\" Line=\"%d\"", pszFile, lLine)


}


assert_exception::~assert_exception()
{


}


CLASS_DECL_ACME int throw_assert_exception(const char * pszFileName,int iLineNumber)
{

   throw assert_exception(pszFileName,iLineNumber);

}



