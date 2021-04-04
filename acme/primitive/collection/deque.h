#pragma once


template < class TYPE,class ARG_TYPE = const TYPE &,class BASE_ARRAY = array < TYPE,ARG_TYPE > >
class deque:
   public BASE_ARRAY
{
public:

    typedef TYPE BASE_TYPE;
    typedef ARG_TYPE BASE_ARG_TYPE;

    inline void push_back(ARG_TYPE t)
    {
       BASE_ARRAY::add(t);
    }

    inline void pop_back(index n = -1)
    {
       this->erase_at(this->get_upper_bound(n));
    }


};
