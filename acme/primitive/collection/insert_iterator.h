#pragma once


template <class Container>
class insert_iterator :
   public iterator<output_iterator_tag,void,void,void,void>
{
protected:
  Container* container;
  typename Container::iterator iter;

public:
  typedef Container container_type;
  explicit insert_iterator (Container& x, typename Container::iterator i)
    : container(&x), iter(i) {}
  insert_iterator<Container>& operator= (typename Container::const_reference value)
    { iter=container->insert(iter,value); ++iter; return *this; }
  insert_iterator<Container>& operator* ()
    { return *this; }
  insert_iterator<Container>& operator++ ()
    { return *this; }
  insert_iterator<Container> operator++ (i32)
    { return *this; }
};
