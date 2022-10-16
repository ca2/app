#pragma once


namespace papaya
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


} // namespace papaya


template < typename TYPE, typename ARG_TYPE = typename argument_of < TYPE >::type, typename PAIR = pair < ::atom, TYPE, typename argument_of < ::atom >::type, ARG_TYPE > >
using id_map = ::map < atom, TYPE, typename argument_of < ::atom >::type, ARG_TYPE, PAIR >;


using procedure_map = ::id_map < ::procedure_array >;


using id_to_id = id_map < atom >;


using id_to_index = id_map < index >;





