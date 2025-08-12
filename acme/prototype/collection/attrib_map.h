#pragma once


#include "map_base.h"
#include "acme/prototype/prototype/atom.h"


namespace acme
{


   namespace map_base
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

      
   } // namespace map_base


} // namespace acme



using procedure_map = ::atom_map_base < ::procedure_array >;







