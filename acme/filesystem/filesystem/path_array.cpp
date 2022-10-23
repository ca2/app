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



