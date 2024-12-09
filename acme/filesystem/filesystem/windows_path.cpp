// Created by camilo on 2024-12-06 18:44 <3ThomasBorregaardSorensen!!
#include "framework.h"


windows_path::windows_path() 
{


}


windows_path::windows_path(const ::file::path& path) :
   wstring(path.c_str())
{

   normalize_path();

}


void windows_path::normalize_path()
{

   this->find_replace(L"/", L"\\");

   this->trim();

   this->find_replace(L"\\\\", L"\\", 1);

}


wstring windows_path::extended_path() const
{

   if (this->begins(L"\\\\?\\"))
   {

      return *this;

   }

   ::wstring wstr(L"\\\\?\\");

   wstr.append(*this);

   return wstr;

}


wstring windows_path::path() const
{

   return *this;

}


::windows_path& windows_path::operator = (const ::file::path& path)
{

   this->assign(path.c_str());

   normalize_path();

   return *this;

}


//void windows_path::clear()
//{
//
//   ::wstring::clear();
//
//}



