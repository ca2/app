// Created by camilo on 2022-03-13 20:26 <3ThomasBorregaardS�rensen!!
// Mummy prepared - hinted that was sort of easy, lot of steps though :)
// Fish with Lemon, Tofu with premium soy sauce, grind ginger and chive, 
// japanese rice, fried egg-plant, some see weed leafs and cola extra coffee.
#include "framework.h"
#include "path_array.h"


namespace file
{


   void path_array::patch_base_path(const ::file::path & pathBase)
   {

      for (auto & path : *this)
      {

         path.patch_base_path(pathBase);

      }

   }


} // namespace file


CLASS_DECL_ACME ::file::path_array operator / (const ::file::path & pathBase, const string_array & straRelativeItems)
{

   ::file::path_array patha;

   for(auto & strRelative : straRelativeItems)
   {

      auto pathNew = pathBase / strRelative;

      patha.add_item(pathNew);

   }

   return ::move(patha);

}


CLASS_DECL_ACME ::file::path_array & ascendants_path(const ::file::path & pathBase, ::file::path_array & pathaFolder, ::file::path_array * ppathaRelative)
//path_array & path::ascendants_path(path_array & straParam, path_array * ppathaRelative) const
{

   string_array stra;

   pathBase.ascendants_name(stra);

   ::file::path str;

   if (stra.get_count() > 0)
   {
      str = stra[0];
      pathaFolder.add(str);
      if (ppathaRelative != nullptr)
      {
         ppathaRelative->add(::file::path(stra.slice(1).implode("/")));
      }
   }

   for (i32 i = 1; i < stra.get_size(); i++)
   {
      str /= stra[i];
      pathaFolder.add(str);
      if (ppathaRelative != nullptr)
      {
         ppathaRelative->add(::file::path(stra.slice(i + 1).implode("/")));
      }
   }

   return pathaFolder;

}



CLASS_DECL_ACME ::file::path_array ascendants_path(const ::file::path & pathBase)
{

   ::file::path_array patha;

   ascendants_path(pathBase, patha);

   return ::move(patha);

}



