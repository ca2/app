// Created by camilo on 2021-11-10 10:40 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "folder.h"
#include "acme/exception/interface_only.h"


folder::folder()
{

   m_etypeCurrent = ::file::e_type_unknown;

   m_iFilePosition = -1;
   
   m_iConsumeFromPathBeginningWhenExtracting = 0;

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


bool folder::locate_file(const ::file::path & path)
{

   throw ::interface_only();

   return false;

}


bool folder::locate_folder(const ::file::path & pathFolderName)
{

   throw ::interface_only();

   return false;

}


bool folder::locate(const ::function < bool(const char*) >& function)
{

   throw ::interface_only();

   return false;

}


::file_pointer folder::get_file()
{

   throw ::interface_only();

   return nullptr;

}


::file_pointer folder::get_file(const ::file::path & pathFile)
{

   throw ::interface_only();

   return nullptr;

}

   
bool folder::has_sub_folder(const ::file::path & path)
{

   return false;

}


void folder::extract(memory& m, const ::file::path & pathFile)
{

   throw ::interface_only();

   //throw ::interface_only();

}


bool folder::is_compressed(const ::file::path & path)
{

   return false;

}


void folder::e_extract_all(const ::file::path & pathTargetDir, ::file::path_array * ppatha, string_array* pstraFilter, bool_array* pbaBeginsFilterEat, ::function<bool(const::scoped_string& scopedstr) > functionCallback)
{

   throw ::interface_only();

   //throw ::interface_only();

}


::file::path folder::e_extract_first_ends(const ::file::path& pathTargetDir, const ::scoped_string& scopedstr)
{

   throw ::interface_only();

   //throw ::interface_only();

   return "";

}


//void folder::e_extract_sub_directory(const ::file::path& pathTargetDir, const ::scoped_string& scopedstrPrefix, ::file::path_array* ppatha, string_array* pstraFilter, bool_array* pbaBeginsFilterEat, ::function<bool(const::scoped_string& scopedstr) > functionCallback)
//{
//
//   throw ::interface_only();
//
//   //throw ::interface_only();
//
//   //return "";
//
//}

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


void folder::add_file(const ::file::path & pathRelative, ::file::file* pfile)
{

   throw ::interface_only();

}


::file::enum_type folder::type(const ::file::path & pathItem)
{

   if (pathItem.is_empty())
   {

      throw ::exception(error_bad_argument);

   }

   if (locate_file(pathItem))
   {

      return ::file::e_type_existent_file;

   }

   if (locate_folder(pathItem))
   {

      return ::file::e_type_existent_folder;

   }

   return ::file::e_type_doesnt_exist;

}



