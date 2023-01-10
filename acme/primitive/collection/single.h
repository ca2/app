#pragma once



#define MAKE_SINGLE(SINGLE, T, MEMBER) \
class SINGLE                                    \
{                                               \
public: \
 \
 \
      using TYPE = T; \
      using ARG_TYPE = argument_of < TYPE >; \
\
\
      T  MEMBER; \
\
\
      TYPE & element() { return MEMBER; } \
      const TYPE & element() const { return MEMBER; }       \
                                       \
                                       \
SINGLE() {} \
SINGLE(ARG_TYPE t) : MEMBER(t) {} \
\
\
}


template < typename T >
MAKE_SINGLE(single, T, m_element);


template < typename SINGLE >
struct make_single :
   public SINGLE
{
public:


   using TYPE = typename SINGLE::TYPE;
   using ARG_TYPE = typename SINGLE::ARG_TYPE;


   using ITEM = TYPE;
   using ARG_ITEM = ARG_TYPE;


   inline auto & topic() { return *this;}
   inline auto & item() { return this->element(); }

   inline auto & topic() const { return *this; }
   inline auto & item() const { return this->element(); }


   make_single() {}
   make_single(ARG_TYPE t) : SINGLE(t) {}


};


#if defined(ANDROID)

#define ALIENATED_ANDROID_ANARCHY class

#else

#define ALIENATED_ANDROID_ANARCHY struct

#endif


namespace std
{


   template < typename T >
   ALIENATED_ANDROID_ANARCHY tuple_size< ::single <T > > : integral_constant<size_t, 1> {};


} // namespace std
