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

   using ELEMENT1 = TYPE;
   using ARG_ELEMENT1 = ARG_TYPE;
   using ELEMENT2 = TYPE;
   using ARG_ELEMENT2 = ARG_TYPE;


   using KEY = TYPE;
   using ARG_KEY = ARG_TYPE;
   using PAYLOAD = TYPE;
   using ARG_PAYLOAD = ARG_TYPE;


   inline auto & topic() { return *this;}
   inline auto & item() { return this->element(); }

   inline auto & topic() const { return *this; }
   inline auto & item() const { return this->element(); }

   inline auto & key() { return this->element();}
   inline auto & key() const { return this->element(); }

   inline auto & payload() { return this->element(); }
   inline auto & payload() const { return this->element(); }



   make_single() {}
   make_single(ARG_TYPE t) : SINGLE(t) {}


   void defer_set_payload(ARG_PAYLOAD)
   {


   }


};




