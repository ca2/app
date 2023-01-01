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

      string str;

      pfile->as(str);

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


   //ini::ini(::acme::application * papp)
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

   //   auto preader = Ctx(pparticle).file()->get_reader(         auto psystem = acmesystem();

//         auto pacmedirectory = psystem->m_pacmedirectory;
//
//pacmedirectory->localconfig() / "this.ini");

   //   if (preader)
   //   {

   //      string str;

   //      preader->full_read_string(str);

   //      parse_ini(str);

   //   }

   //}


} // namespace handle
