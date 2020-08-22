#pragma once


//template <class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class HASH = ::comparison::hash < ARG_KEY >,class EQUALS = ::comparison::equals_type_arg_type < KEY,ARG_KEY > >
//map < KEY,ARG_KEY, VALUE,ARG_VALUE,HASH,EQUALS > & copy(map < KEY,ARG_KEY, VALUE,ARG_VALUE,HASH,EQUALS > & m,const map < KEY,ARG_KEY, VALUE,ARG_VALUE,HASH,EQUALS > & attribmap)
//{
//   if(&m != &attribmap)
//   {
//      m.remove_all();
//      type_map::m_nBlockSize = attribmap.type_map::m_nBlockSize;
//      const typename type_map::pair * ppair = attribmap.get_start();
//      while(ppair != nullptr)
//      {
//         m.set_at(ppair->element1(),ppair->element2());
//         ppair  = attribmap.get_next(ppair);
//      }
//   }
//   return m;
//}


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


template < typename TYPE,typename ARG_TYPE = const TYPE &, typename PAIR = pair < id, TYPE > >
using id_map = ::map < id,const id &, TYPE, ARG_TYPE, PAIR > ;

using id_to_id = id_map < id,const id & > ;

using id_to_index = id_map < index,index > ;


template < typename KEY, typename TYPE, typename ARG_TYPE = const TYPE &, typename PAIR = pair < KEY *, TYPE > >
using ptrmap = ::map < KEY *, KEY *, TYPE, ARG_TYPE, PAIR >;