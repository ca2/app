// Created by camilo on 2022-03-13 20:26 <3ThomasBorregaardSorensen!!
// Mummy prepared - hinted that was sort of easy, lot of steps though :)
// Fish with Lemon, Tofu with premium soy sauce, grind ginger and chive, 
// japanese rice, fried egg-plant, some see weed leafs and cola extra coffee.
#include "framework.h"
//#include "path_array.h"


namespace file
{


   void path_array_base::patch_base_path(const ::file::path & pathBase)
   {

      for (auto & path : *this)
      {

         path.patch_base_path(pathBase);

      }

   }


} // namespace file


CLASS_DECL_ACME ::file::path_array_base operator / (const ::file::path & pathBase, const string_array_base & straRelativeItems)
{

   ::file::path_array_base patha;

   for(auto & strRelative : straRelativeItems)
   {

      auto pathNew = pathBase / strRelative;

      patha.add_item(pathNew);

   }

   return ::transfer(patha);

}


template < typename TYPE1, typename TYPE2 >
constexpr smallest_type<TYPE1, TYPE2> non_null_minimum(const TYPE1 & a, const TYPE2 & b)
{

   return ::comparison::comparison2<TYPE1, TYPE2>().order(a, b) <= 0 ?
      (smallest_type<TYPE1, TYPE2>) (!a ? (smallest_type<TYPE1, TYPE2>)b : (smallest_type<TYPE1, TYPE2>)a) :
      (smallest_type<TYPE1, TYPE2>) (!b ? (smallest_type<TYPE1, TYPE2>)a : (smallest_type<TYPE1, TYPE2>)b);

}




CLASS_DECL_ACME ::file::path_array_base & ascendants_path(const ::file::path & path, ::file::path_array_base & pathaFolder, ::file::path_array_base * ppathaRelative)
//path_array & path::ascendants_path(path_array & straParam, path_array * ppathaRelative) const
{

   if (path.is_empty())
   {

      return pathaFolder;

   }

   auto p = path.begin();

#if !defined(WINDOWS)

   pathaFolder.add("/");

#endif

   if (path == "/")
   {

      return pathaFolder;

   }

   while(p && p < path.end())
   {

      auto range = ::const_ansi_range(p, path.end());

      auto pProtocol = range.find(":/");
      auto pProtocol2 = range.find("://");
      auto pSlash = range.find_first('/');
      auto pBackSlash = range.find_first('\\');

      p = non_null_minimum(pProtocol, non_null_minimum(pProtocol2, non_null_minimum(pSlash, pBackSlash)));

      if (!p)
      {

         pathaFolder.add(path);

         break;

      }
      else if (p == pProtocol2)
      {

         p += 3;

         pathaFolder.add(path(0, p));

      }
      else if (p == pProtocol)
      {

         p += 2;

         pathaFolder.add(path(0, p));

      }
      else if (p == pSlash || p == pBackSlash)
      {

         auto range = path(0, p);

         if (range.has_character())
         {

            pathaFolder.add(range);

         }

         p = path(p).skip_any_character_in("\\/");

      }
      
   }
   
   if(::is_set(ppathaRelative))
   {
      
      for(auto & pathItem : pathaFolder)
      {
         
         ::file::path pathRelative = path;
         
         pathRelative.begins_eat(pathItem);
       
         ppathaRelative->add(pathRelative);
         
      }
      
   }

//   if (::is_set(ppathaRelative))
//   {
//
//      throw "needs to do and redoitout";
//
//   }

   //string_array_base stra;

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

   //for (int i = 1; i < stra.get_size(); i++)
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



CLASS_DECL_ACME ::file::path_array_base & ascendants_path(::file::path_array_base & patha, const ::file::path & pathParam)
{

   if(pathParam.has_character())
   {

      auto path = pathParam;

      do
      {

         patha.add(path);

         path = path.folder();

      } while (path.has_character());

   }

   return patha;

}


CLASS_DECL_ACME ::string_array_base & ascendants_name(::string_array_base & stra, const ::file::path & pathParam)
{

   if(pathParam.has_character())
   {

      auto path = pathParam;

      do
      {

         stra.add(path.name());

         path = path.folder();

      } while (path.has_character());

   }

   return stra;

}


CLASS_DECL_ACME::file::path_array_base ascendants_path(const ::file::path& pathBase)
{

   ::file::path_array_base patha;

   ascendants_path(patha, pathBase);

   return ::transfer(patha);

}


CLASS_DECL_ACME::string_array_base ascendants_name(const ::file::path& pathBase)
{

   ::string_array_base stra;

   ascendants_name(stra, pathBase);

   return ::transfer(stra);

}





void _000001_stra_to_patha_assignment_test()
{

   string_array_base stra;

   stra.add("C:\\a");
   stra.add("C:\\b");
   stra.add("C:\\c");
   stra.add("C:\\d");

   ::file::path_array_base patha;

   patha = stra;

}



