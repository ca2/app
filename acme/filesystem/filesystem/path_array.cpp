// Created by camilo on 2022-03-13 20:26 <3ThomasBorregaardS�rensen!!
// Mummy prepared - hinted that was sort of easy, lot of steps though :)
// Fish with Lemon, Tofu with premium soy sauce, grind ginger and chive, 
// japanese rice, fried egg-plant, some see weed leafs and cola extra coffee.
#include "framework.h"
//#include "path_array.h"


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

   return ::transfer(patha);

}


CLASS_DECL_ACME ::file::path_array & ascendants_path(const ::file::path & pathBase, ::file::path_array & pathaFolder, ::file::path_array * ppathaRelative)
//path_array & path::ascendants_path(path_array & straParam, path_array * ppathaRelative) const
{

   auto path = pathBase;

   while (path.has_char())
   {

      pathaFolder.insert_at(0, path);

      path = path.folder();

   }

   if (::is_set(ppathaRelative))
   {

      throw "needs to do and redoitout";

   }

   //string_array stra;

   //ascendants_name(stra, pathBase);

   //::file::path str;

   //if (stra.get_count() > 0)
   //{
   //   str = stra[0];
   //   pathaFolder.add(str);
   //   if (ppathaRelative != nullptr)
   //   {
   //      ppathaRelative->add(::file::path(stra.slice(1).implode("/")));
   //   }
   //}

   //for (i32 i = 1; i < stra.get_size(); i++)
   //{
   //   str /= stra[i];
   //   pathaFolder.add(str);
   //   if (ppathaRelative != nullptr)
   //   {
   //      ppathaRelative->add(::file::path(stra.slice(i + 1).implode("/")));
   //   }
   //}

   return pathaFolder;

}



CLASS_DECL_ACME ::file::path_array & ascendants_path(::file::path_array & patha, const ::file::path & pathParam)
{

   if(pathParam.has_char())
   {

      auto path = pathParam;

      do
      {

         patha.add(path);

         path = path.folder();

      } while (path.has_char());

   }

   return patha;

}


CLASS_DECL_ACME ::string_array & ascendants_name(::string_array & stra, const ::file::path & pathParam)
{

   if(pathParam.has_char())
   {

      auto path = pathParam;

      do
      {

         stra.add(path.name());

         path = path.folder();

      } while (path.has_char());

   }

   return stra;

}


CLASS_DECL_ACME::file::path_array ascendants_path(const ::file::path& pathBase)
{

   ::file::path_array patha;

   ascendants_path(patha, pathBase);

   return ::transfer(patha);

}


CLASS_DECL_ACME::string_array ascendants_name(const ::file::path& pathBase)
{

   ::string_array stra;

   ascendants_name(stra, pathBase);

   return ::transfer(stra);

}



