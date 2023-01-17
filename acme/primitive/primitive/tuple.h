// Created by camilo on 2022-05-19 18:00 <3ThomasBorregaardSorense!! and Mummi!!
#pragma once


template <::index i, typename TYPE >
class tuple_item
{
public:
   tuple_item()
   {

   }
   tuple_item(TYPE const& t)
   {
      tuple_item<i, TYPE>::m_element = t;
   }
   tuple_item(TYPE&& t)
   {
      tuple_item<i, TYPE>::m_element = ::transfer(t);
   }
   TYPE& get()
   {
      return tuple_item<i, TYPE>::m_element;
   }
   TYPE m_element;

};


/*
General template class declaration.
*/
template <::index i, typename... types>
class tuple_recursion
{
};



/////*
//This is a partial specialization, so as long as there is at least one template argument, apart from the index, this specialization is preferred to the previously defined _tuple_recurr_base<std::size_t, typename �Eypes>
//*/
//template <std::size_t _index, typename L, typename�Etypes>
//class _tuple_recurr_base<_index, L, types�E :
//   public _tuple_impl<_index, typename std::remove_reference<L>::type>,
//   public _tuple_recurr_base<_index + 1, types�E
//{
//};
template <::index i, typename L, typename... types>
class tuple_recursion < i, L, types... > :
   public tuple_item < i, typename ::erase_reference<L>::TYPE >,
   public tuple_recursion<i + 1, types... >
{
public:
   tuple_recursion()
   {

   }
   template <typename CL, typename... CArgs>
   tuple_recursion(CL&& arg, CArgs &&... args) : tuple_item<i, typename erase_reference<CL>::TYPE>(std::forward<CL>(arg)),
      tuple_recursion<i + 1, types...>(std::forward < CArgs(args)... > )
   {
   }
};




template <typename L, typename... types>
class tuple :
   public tuple_recursion<0, L, types...>
{
public:

   tuple()
   {
   }

   template <typename... CArgs>
   tuple(CArgs&&... args) : /* Call base ctors */
      tuple_recursion<0, L, types...>(std::forward<CArgs>(args)...)
   {
   }
};





template <::index i, typename L, typename... Args>
struct extract_type_at
{

   using type = typename extract_type_at < i - 1, Args...>::type;

};


template <typename L, typename... Args>
struct extract_type_at<0, L, Args... >
{
   using type = L;
};

template <::index i, typename... Args >
auto& get(tuple<Args...>& t)
{
   return (static_cast<tuple_item<i, typename extract_type_at< i, Args ...>::type> &>(t)).get();
}




// from acme/tuple.h Created by camilo on 2022-11-02 04:49 <3ThomasBorregaardSørensen!!
#pragma once


template < typename TUPLE, typename FIND_CONDITION, typename CONTINUE_CONDITION >
inline TUPLE* tuple_array_find(TUPLE* ptuple, FIND_CONDITION find_condition, CONTINUE_CONDITION continue_condition)
{

   while (continue_condition(ptuple))
   {

      if (find_condition(ptuple))
      {

         return ptuple;

      }

      ptuple++;

   }

   return nullptr;

}



