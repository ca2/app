#pragma once

// from cplusplus.com
// FIFO queue
// queues are a type of container adaptor, specifically designed to operate in a
// FIFO action_context (first-in first-out), where elements are inserted into one end of
// the container and extracted from the other.
//
// queues are implemented as containers adaptors, which are classes that use an
// encapsulated object of a specific container class as its underlying container,
/// providing a specific set of member functions to access its elements. Elements
// are pushed into the "back" of the specific container and popped from its "front".

// The underlying container may be one of the standard container class template or
// some other specifically designed container class. The only requirement is that
// it supports the following operations:

//    front()
//    back()
//    push_back()
//    pop_front()




template < class TYPE, class CONTAINER = deque < TYPE > >
class queue :
   public CONTAINER
{
public:

   inline bool is_empty() const;
   inline ::count size() const;

   inline TYPE & front();
   inline const TYPE & front() const;

   inline TYPE & back();
   inline const TYPE & back() const;

   inline void push(const TYPE & t);

   inline void pop();

};


template < class TYPE, class CONTAINER >
inline bool queue < TYPE, CONTAINER > ::is_empty() const
{

   return this->CONTAINER::is_empty();

}

template < class TYPE, class CONTAINER >
inline ::count queue < TYPE, CONTAINER > ::size() const
{

   return this->CONTAINER::size();

}


template < class TYPE, class CONTAINER >
inline TYPE & queue < TYPE, CONTAINER > ::front()
{

   return this->CONTAINER::front();

}

template < class TYPE, class CONTAINER >
inline const TYPE & queue < TYPE, CONTAINER > ::front() const
{

   return this->CONTAINER::front();

}

template < class TYPE, class CONTAINER >
inline TYPE & queue < TYPE, CONTAINER > ::back()
{

   return this->CONTAINER::back();

}

template < class TYPE, class CONTAINER >
inline const TYPE & queue < TYPE, CONTAINER > ::back() const
{

   return this->CONTAINER::back();

}

template < class TYPE, class CONTAINER >
inline void queue < TYPE, CONTAINER > ::push(const TYPE & t)
{

   this->CONTAINER::push_back(t);

}

template < class TYPE, class CONTAINER >
inline void queue < TYPE, CONTAINER > ::pop()
{

   this->CONTAINER::pop_front();

}


