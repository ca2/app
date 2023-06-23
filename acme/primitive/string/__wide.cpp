#include "framework.h"
#include "__wide.h"
#include "acme/primitive/primitive/memory.h"


void __wide_append(memory & memory, const scoped_string & scopedstr)
{

   wstring wstr(scopedstr);

   memory.append(wstr.c_str(), wstr.length() * sizeof(wchar_t));

}


void __wide_append_null(memory & memory)
{

   wchar_t wch{};

   memory.append(&wch, sizeof(wch));

}


