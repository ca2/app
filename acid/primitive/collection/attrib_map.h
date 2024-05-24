#pragma once


#include "map.h"
#include "acid/primitive/primitive/atom.h"


namespace acid
{


   namespace map
   {


      template <class MAP >
      MAP & copy(MAP & m,const MAP & attribmap)
      {

         if(&m != &attribmap)
         {

            m.erase_all();

            for(auto & pair : attribmap)
            {

               m.set_at(pair.element1(), pair.element2());

            }

         }

         return m;

      }

      
   } // namespace map


} // namespace acid



using procedure_map = ::atom_map < ::procedure_array >;







