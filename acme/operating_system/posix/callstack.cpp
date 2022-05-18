//
// Created by camilo on 5/17/22 02:38 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include <cxxabi.h>


void backtrace_symbol_parse(string & strSymbolName, string & strAddress, char * pmessage, void * address)
{

    char * pszMangledName = nullptr;

    char * pszOffsetBegin = nullptr;

    char * pszOffsetEnd = nullptr;

    // find parantheses and +address offset surrounding mangled name
    for (char * psz = pmessage; *psz; ++psz)
    {

        if (*psz == '(')
        {

            pszMangledName = psz;

        }
        else if (*psz == '+')
        {

            pszOffsetBegin = psz;

        }
        else if (*psz == ')')
        {

            pszOffsetEnd = psz;

            break;

        }

    }

    if (pszMangledName && pszOffsetBegin && pszOffsetEnd && pszMangledName < pszOffsetBegin)
    {

        *pszMangledName++ = '\0';
        *pszOffsetBegin++ = '\0';
        *pszOffsetEnd++ = '\0';

        i32 status;

        acme::malloc < char * > pszRealName = abi::__cxa_demangle(pszMangledName, 0, 0, &status);

        const char * pszSymbolName;

        if (status == 0)
        {

            strSymbolName = (const char *) (char *) pszRealName;

        }
        else
        {

            strSymbolName = pszMangledName;

        }

        strAddress = pszOffsetEnd;

    }

}


