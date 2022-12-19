// Created by camilo on 2021-11-10 10:40 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "folder.h"
#include "acme/exception/interface_only.h"


folder::folder()
{

   m_etypeCurrent = ::file::e_type_unknown;

   m_iFilePosition = -1;

}


folder::~folder()
{

}


void folder::initialize(::particle * pparticle)
{

   ::object::initialize(pparticle);

}


bool folder::is_reading() const
{

   throw ::interface_only();

   return false;

}


void folder::open_for_reading(file_pointer pfile, int iBufferLevel)
{

   throw ::interface_only();

}


bool folder::locate_file(const scoped_string & strFileName)
{

   throw ::interface_only();

   return false;

}


bool folder::locate_folder(const scoped_string & strFolderName)
{

   throw ::interface_only();

   return false;

}


bool folder::locate(const ::function < bool(const char*) >& function)
{

   throw ::interface_only();

   return false;

}


::file_pointer folder::get_file(const scoped_string & strFile)
{

   throw ::interface_only();

   return nullptr;

}

   
bool folder::has_sub_folder(const scoped_string & strFileName)
{

   return false;

}


void folder::extract(memory& m, const scoped_string & strFile)
{

   throw ::interface_only();

   //throw ::interface_only();

}


bool folder::is_compressed(const scoped_string & strFileName)
{

   return false;

}


void folder::e_extract_all(const scoped_string & strTargetDir, ::file::path_array * ppatha, string_array* pstraFilter, bool_array* pbaBeginsFilterEat)
{

   throw ::interface_only();

   //throw ::interface_only();

}

//
//bool folder::enumerates(::file::listing & listing)
//{
//
//   return true;
//
//}


bool folder::enumerate(::file::listing& listing)
{

   throw ::interface_only();

   return false;

}


//bool folder::perform_file_relative_name_listing(::file::listing& listing)
//{
//
//   throw ::interface_only();
//
//   return false;
//
//}


void folder::open_for_writing(file_pointer pfile)
{

   throw ::interface_only();

   //throw ::interface_only();

}


void folder::add_file(const ::file::path& pszRelative, ::file::file* pfile)
{

   throw ::interface_only();

}


::file::enum_type folder::type(const scoped_string & strItem)
{

   if (::is_empty(pszItem))
   {

      throw ::exception(error_bad_argument);

   }

   if (locate_file(pszItem))
   {

      return ::file::e_type_file;

   }

   if (locate_folder(pszItem))
   {

      return ::file::e_type_folder;

   }

   return ::file::e_type_doesnt_exist;

}



