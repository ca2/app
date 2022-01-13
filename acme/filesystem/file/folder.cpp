// Created by camilo on 2021-11-10 10:40 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"


folder::folder()
{

   m_etypeCurrent = ::file::e_type_none;

   m_iFilePosition = -1;

}


folder::~folder()
{

}


void folder::initialize(::object* pobject)
{

   /* auto estatus = */ ::object::initialize(pobject);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


bool folder::is_reading() const
{

   throw interface_only_exception();

   //return false;

}


void folder::open_for_reading(file_pointer pfile, int iBufferLevel)
{

   throw interface_only_exception();

   //throw ::interface_only_exception();

}


bool folder::locate(const char* pszFileName)
{

   throw interface_only_exception();

//   return false;

}


::file_pointer folder::get_file(const char * pszFile)
{

   throw interface_only_exception();

   return nullptr;

}

   
bool folder::has_sub_folder(const char* pszFileName)
{

   return false;

}


void folder::extract(memory& m, const char* pszFile)
{

   throw interface_only_exception();

   //throw ::interface_only_exception();

}


bool folder::is_compressed(const char* pszFileName)
{

   return false;

}


void folder::extract_all(const char* pszTargetDir, ::file::patha* ppatha, string_array* pstraFilter, bool_array* pbaBeginsFilterEat)
{

   throw interface_only_exception();

   //throw ::interface_only_exception();

}


bool folder::perform_file_listing(::file::listing& listing)
{

   throw interface_only_exception();

   return false;

}


bool folder::perform_file_relative_name_listing(::file::listing& listing)
{

   throw interface_only_exception();

   return false;

}


void folder::open_for_writing(file_pointer pfile)
{

   throw interface_only_exception();

   //throw ::interface_only_exception();

}


void folder::add_file(const ::file::path& pszRelative, ::file::file* pfile)
{

   throw interface_only_exception();

}



