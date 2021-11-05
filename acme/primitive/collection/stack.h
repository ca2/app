#pragma once


template < class TYPE, class ARG_TYPE = const TYPE &, class BASE_CONTAINER = deque < TYPE, ARG_TYPE > >
class stack :
   public BASE_CONTAINER
{
public:


   inline TYPE * operator ->()
   {
      return &BASE_CONTAINER::last();
   }

   inline const TYPE * operator ->() const
   {
      return &BASE_CONTAINER::last();
   }

   inline TYPE & top()
   {
      return BASE_CONTAINER::last();
   }

   inline const TYPE & top() const
   {
      return BASE_CONTAINER::last();
   }

   inline void push(ARG_TYPE t)
   {
      BASE_CONTAINER::push_back(t);
   }

   inline TYPE pop(index n = -1)
   {

      index i = this->get_upper_bound(n);

      TYPE t = this->element_at(i);

      this->erase_at(i);

      return t;

   }


   inline TYPE pop_to()
   {

      TYPE lastelement = this->pop();

      this->last() = lastelement;

      return this->last();

   }

   inline void push_last()
   {

      this->add(this->last());

   }


};


template < class TYPE, class ARG_TYPE = const TYPE & >
class raw_stack :
   virtual public stack < TYPE, raw_array < TYPE, ARG_TYPE > >
{
public:


};

template < class TYPE, class STACK = stack < TYPE > >
class stacker
{
public:

   STACK & m_stack;

   stacker(STACK & stack) :
      m_stack(stack)
   {
      m_stack.add_new();
      m_stack.last() = m_stack.last(-2);
   }

   ~stacker()
   {
      m_stack.pop();
   }

   TYPE * operator ->()
   {
      return &m_stack.last();
   }

   const TYPE * operator ->() const
   {
      return &m_stack.last();
   }

};




