#pragma once


// consult cpluplus.com


template < class TYPE, class ARG_TYPE = const TYPE &, class CONTAINER = array < TYPE, ARG_TYPE >, class FIRST = ::comparison::less < TYPE, ARG_TYPE > >
class priority_queue
{
public:

   inline bool is_empty() const;
   inline ::count size() const;

   inline TYPE & top();
   inline const TYPE & top() const;

   inline void push(const TYPE & t);

   inline void pop();

};


template < class TYPE, class ARG_TYPE, class CONTAINER, class FIRST >
inline bool priority_queue < TYPE, ARG_TYPE, CONTAINER, FIRST > ::is_empty() const
{

   return this->CONTAINER::is_empty();

}

template < class TYPE, class ARG_TYPE, class CONTAINER, class FIRST >
inline ::count priority_queue < TYPE, ARG_TYPE, CONTAINER, FIRST > ::size() const
{

   return this->CONTAINER::size();

}


template < class TYPE, class ARG_TYPE, class CONTAINER, class FIRST >
inline TYPE & priority_queue < TYPE, ARG_TYPE, CONTAINER, FIRST > ::top()
{

   return this->CONTAINER::front();

}

template < class TYPE, class ARG_TYPE, class CONTAINER, class FIRST >
inline const TYPE & priority_queue < TYPE, ARG_TYPE, CONTAINER, FIRST > ::top() const
{

   return this->CONTAINER::front();

}

template < class TYPE, class ARG_TYPE, class CONTAINER, class FIRST >
inline void priority_queue < TYPE, ARG_TYPE, CONTAINER, FIRST > ::push(const TYPE & t)
{

   this->priority_queue::push_back(t);

   ::sort::quick_sort < FIRST > ((CONTAINER *) this);

}

template < class TYPE, class ARG_TYPE, class CONTAINER, class FIRST >
inline void priority_queue < TYPE, ARG_TYPE, CONTAINER, FIRST > ::pop()
{

   this->CONTAINER::pop_back();

}
