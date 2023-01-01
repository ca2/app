#pragma once


namespace acme
{


   namespace map
   {


      template < typename MAP, typename PAYLOAD >
      inline bool contains_payload(const MAP & map, const PAYLOAD & payload);
      

   } // namespace map


} // namespace acme






namespace acme
{



   namespace map
   {


      template < typename MAP, typename PAYLOAD >
      inline contains_payload(const MAP & map, const PAYLOAD & payload)
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


} // namespace acme



