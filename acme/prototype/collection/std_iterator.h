#pragma once


//	ITERATOR STUFF (from <iterator>)
// ITERATOR TAGS
struct input_iterator_tag
{	// identifying tag for input iterators
};

struct output_iterator_tag
{	// identifying tag for output iterators
};

struct forward_iterator_tag
	: public input_iterator_tag, output_iterator_tag
{	// identifying tag for forward iterators
};

struct bidirectional_iterator_tag
	: public forward_iterator_tag
{	// identifying tag for bidirectional iterators
};

struct random_access_iterator_tag
	: public bidirectional_iterator_tag
{	// identifying tag for random-access iterators
};

struct _Int_iterator_tag
{	// identifying tag for integer types, not an iterator
};

// POINTER ITERATOR TAGS
struct _Nonscalar_ptr_iterator_tag
{	// pointer to unknown type
};
struct _Scalar_ptr_iterator_tag
{	// pointer to scalar type
};


// TEMPLATE CLASS iterator
template<class _Category,
	class _Ty,
	class _Diff = ptrdiff_t,
	class _Pointer = _Ty*,
	class _Reference = _Ty&>
	struct iterator
{	// base type for all iterator classes
	typedef _Category iterator_category;
	typedef _Ty value_type;
	typedef _Diff difference_type;
	typedef _Diff distance_type;	// retained
	typedef _Pointer pointer;
	typedef _Reference matter;
};
