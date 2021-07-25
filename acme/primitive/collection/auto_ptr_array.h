#pragma once


template < typename POINTER_TYPE >
class auto_ptr_array :
   public pointer_array_process < comparable_array < POINTER_TYPE * >, POINTER_TYPE >
{
public:


   using pointer_array_process < comparable_array < POINTER_TYPE * >, POINTER_TYPE >::pointer_array_process;


   auto_ptr_array() { }
   auto_ptr_array(auto_ptr_array && array) : pointer_array_process < comparable_array < POINTER_TYPE * >, POINTER_TYPE >(::move(array)) { }
   ~auto_ptr_array() override { this->erase_all(); }


   POINTER_TYPE & object_at(::index i) { return *this->element_at(i); }
   const POINTER_TYPE & object_at(::index i) const { return *this->element_at(i); }

   void erase_at(::index i)
   {

      delete this->element_at(i);

      pointer_array_process < comparable_array < POINTER_TYPE * >, POINTER_TYPE >::erase_at(i);

   }

   void erase_all()
   {

      for(auto & p : this->ptra())
      {

         delete p;

      }

      pointer_array_process < comparable_array < POINTER_TYPE * >, POINTER_TYPE >::erase_all();

   }


};


namespace papaya
{


   template < class TDST, class TSRC >
   ::count copy(auto_ptr_array < TDST >& dsta, const auto_ptr_array < TSRC >& srca)
   {

      dsta.erase_all();

      dsta.set_size(srca.get_size());

      for (int i = 0; i < srca.get_size(); i++)
      {
         
         dsta[i] = new TDST(*srca[i]);

      }

      return dsta.get_size();

   }


} // namespace papaya



