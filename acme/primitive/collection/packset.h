#pragma once


template < typename ID_TYPE, typename ARG_ID_TYPE, typename ITEM_TYPE, typename ARG_ITEM_TYPE, typename ARRAY = array < ITEM_TYPE, ARG_ITEM_TYPE > >
class packset :
   public map < ID_TYPE, ARRAY, ARG_ID_TYPE, const ARRAY & >
{
public:
   
   
   packset();
   
   
   void pack(ARG_ID_TYPE id, ARG_ITEM_TYPE item);


   ::count get_pack_count();
   ::count get_item_count();


};


template < typename ID_TYPE, typename ARG_ID_TYPE, typename ITEM_TYPE, typename ARG_ITEM_TYPE, typename ARRAY >
packset < ID_TYPE, ARG_ID_TYPE, ITEM_TYPE, ARG_ITEM_TYPE, ARRAY > ::packset()
{

}


template < typename ID_TYPE, typename ARG_ID_TYPE, typename ITEM_TYPE, typename ARG_ITEM_TYPE, typename ARRAY >
void packset < ID_TYPE, ARG_ID_TYPE, ITEM_TYPE, ARG_ITEM_TYPE, ARRAY > ::pack(ARG_ID_TYPE id, ARG_ITEM_TYPE item)
{
   
   this->operator[](id).add(item);

}


template < typename ID_TYPE, typename ARG_ID_TYPE, typename ITEM_TYPE, typename ARG_ITEM_TYPE, typename ARRAY >
::count packset < ID_TYPE, ARG_ID_TYPE, ITEM_TYPE, ARG_ITEM_TYPE, ARRAY > ::get_pack_count()
{
   
   return this->get_size();

}


template < typename ID_TYPE, typename ARG_ID_TYPE, typename ITEM_TYPE, typename ARG_ITEM_TYPE, typename ARRAY >
::count packset < ID_TYPE, ARG_ID_TYPE, ITEM_TYPE, ARG_ITEM_TYPE, ARRAY > ::get_item_count()
{
   
   ::count count = 0;

   auto ppair = this->get_start();
   
   while(ppair != nullptr)
   {
      
      count += ppair->element2().get_count();

      this->get_next(ppair);

   }

   return count;

}



