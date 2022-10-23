#pragma once


namespace acme
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


} // namespace acme



using procedure_map = ::atom_map < ::procedure_array >;


using id_to_id = atom_map < atom >;


using id_to_index = atom_map < index >;





