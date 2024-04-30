#pragma once


template < typename ID_TYPE, typename ITEM_TYPE, typename ARRAY = array < ITEM_TYPE > >
class packset :
   public map < ID_TYPE, ARRAY >
{
public:
   

   using BASE_MAP = map < ID_TYPE, ARRAY >;
   using ARG_ID_TYPE = typename BASE_MAP::ARG_ITEM;
   using ARG_ITEM_TYPE = typename BASE_MAP::PAYLOAD::BASE_ARG_TYPE;
   
   packset();
   
   
   void pack(ARG_ID_TYPE atom, ARG_ITEM_TYPE item);


   ::raw::count get_pack_count();
   ::raw::count get_item_count();


};


template < typename ID_TYPE, typename ITEM_TYPE, typename ARRAY >
packset < ID_TYPE, ITEM_TYPE, ARRAY > ::packset()
{

}


template < typename ID_TYPE, typename ITEM_TYPE, typename ARRAY >
void packset < ID_TYPE, ITEM_TYPE, ARRAY > ::pack(ARG_ID_TYPE atom, ARG_ITEM_TYPE item)
{
   
   this->operator[](atom).add(item);

}


template < typename ID_TYPE, typename ITEM_TYPE, typename ARRAY >
::raw::count packset < ID_TYPE, ITEM_TYPE, ARRAY > ::get_pack_count()
{
   
   return this->get_size();

}


template < typename ID_TYPE, typename ITEM_TYPE, typename ARRAY >
::raw::count packset < ID_TYPE, ITEM_TYPE, ARRAY > ::get_item_count()
{
   
   ::raw::count count = 0;

   auto ppair = this->get_start();
   
   while(ppair != nullptr)
   {
      
      count += ppair->element2().get_count();

      this->get_next(ppair);

   }

   return count;

}



