#pragma once


template < typename ELEMENT1, typename ELEMENT2, typename ARRAY = array < ELEMENT2 > >
class packset :
   public map_base < ELEMENT1, ARRAY >
{
public:
   

   using BASE_MAP = map_base < ELEMENT1, ARRAY >;
   using ARG_ELEMENT1 = typename BASE_MAP::ARG_KEY;
   using ARG_ELEMENT2 = typename BASE_MAP::PAYLOAD::BASE_ARG_TYPE;
   
   packset();
   
   
   void pack(ARG_ELEMENT1 atom, ARG_ELEMENT2 item);


   ::collection::count get_pack_count();
   ::collection::count get_item_count();


};


template < typename ELEMENT1, typename ELEMENT2, typename ARRAY >
packset < ELEMENT1, ELEMENT2, ARRAY > ::packset()
{

}


template < typename ELEMENT1, typename ELEMENT2, typename ARRAY >
void packset < ELEMENT1, ELEMENT2, ARRAY > ::pack(ARG_ELEMENT1 atom, ARG_ELEMENT2 item)
{
   
   this->operator[](atom).add(item);

}


template < typename ELEMENT1, typename ELEMENT2, typename ARRAY >
::collection::count packset < ELEMENT1, ELEMENT2, ARRAY > ::get_pack_count()
{
   
   return this->get_size();

}


template < typename ELEMENT1, typename ELEMENT2, typename ARRAY >
::collection::count packset < ELEMENT1, ELEMENT2, ARRAY > ::get_item_count()
{
   
   ::collection::count count = 0;

   auto iterator = this->get_start();
   
   while(iterator != nullptr)
   {
      
      count += iterator->element2().get_count();

      this->get_next(iterator);

   }

   return count;

}



