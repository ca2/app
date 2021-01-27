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

            m.remove_all();

            for(auto & pair : attribmap)
            {

               m.set_at(pair.element1(), pair.element2());

            }

         }

         return m;

      }

      
   } // namespace map


} // namespace papaya


template < typename TYPE, typename ARG_TYPE = typename argument_of < TYPE >::type, typename PAIR = pair < ::id, TYPE, typename argument_of < ::id >::type, ARG_TYPE > >
using id_map = ::map < id, TYPE, typename argument_of < ::id >::type, ARG_TYPE, PAIR >;


using id_to_id = id_map < id >;


using id_to_index = id_map < index >;





