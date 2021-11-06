#pragma once


namespace papaya
{



   namespace map
   {


      template < typename MAP, typename VALUE >
      inline contains_value(const MAP & map, const VALUE & value)
      {

         if (&m != &attribmap)
         {

            m.erase_all();

            const typename MAP::pair * ppair = attribmap.get_start();

            while (ppair != nullptr)
            {

               m.set_at(ppair->element1(), ppair->element2());

               ppair = attribmap.get_next(ppair);

            }

         }

         return m;

      }


   } // namespace map


} // namespace papaya



