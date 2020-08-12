#pragma once


template <class Container>
class back_insert_iterator :
    public iterator < output_iterator_tag, void, void, void, void >
{
protected:
  Container* container;

public:
  typedef Container container_type;
  explicit back_insert_iterator (Container& x) : container(x) {}
  back_insert_iterator<Container>& operator= (typename Container::const_reference value)
    { container->push_back(value); return *this; }
  back_insert_iterator<Container>& operator* ()
    { return *this; }
  back_insert_iterator<Container>& operator++ ()
    { return *this; }
  back_insert_iterator<Container> operator++ (i32)
    { return *this; }
};