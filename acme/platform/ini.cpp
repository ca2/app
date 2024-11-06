//
// Created by camilo on 2022-10-23 23:49 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "ini.h"
#include "acme/filesystem/file/file.h"


namespace handle
{

   
   ini::ini() 
   {
   
   }


   ini::ini(const ::string & str)
   {

      parse_ini(str);

   }


   ini::ini(::file::file * pfile)
   {

      auto str = pfile->full_string();

      parse_ini(str);

   }

   
   ini::ini(const ::property_set & set) :
      ::property_set(set)
   {
   
   }


   ini::ini(::property_set && set) : 
      ::property_set(::transfer(set))
   {
   
   }


   ini::ini(const ini & ini) :
      ::property_set(ini)
   {
   
   
   }

   
   ini::ini(ini && ini) : 
      property_set(::transfer(ini)) 
   {
   
   
   }


   //ini::ini(::platform::application * papp)
   //{

   //   auto preader = Ctx(papp).file()->get_reader(papp->get_app_localconfig_folder());

   //   if (preader)
   //   {

   //      string str;

   //      preader->full_read_string(str);

   //      parse_ini(str);

   //   }

   //}


   //localini::localini(::particle * pparticle)
   //{

   //   auto preader = Ctx(pparticle).file()->get_reader(         auto psystem = system();

//         auto pdirectorysystem = psystem->m_pdirectorysystem;
//
//pdirectorysystem->localconfig() / "this.ini");

   //   if (preader)
   //   {

   //      string str;

   //      preader->full_read_string(str);

   //      parse_ini(str);

   //   }

   //}


} // namespace handle
