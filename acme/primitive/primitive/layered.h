#pragma once


#define MAX_LAYERED_COUNT 8

class CLASS_DECL_ACME layered :
   virtual public ::generic
{
private:


   void* m_pa[MAX_LAYERED_COUNT];

public:

   layered() { xxf_zero(m_pa); }
   virtual ~layered();

   void set_layer(byte bLayeredIndex, void* p);
      
   template < typename LAYER >
   inline LAYER* layer(byte bLayeredIndex) const { return ::is_null(this) ? nullptr : (LAYER *)m_pa[bLayeredIndex]; }

};

#define LAYERED_OBJECT 0
#define LAYERED_DRAW2D_GRAPHICS 1
#define LAYERED_USER_CREATE 1
#define LAYERED_CHANNEL 1
#define LAYERED_USER_PRIMITIVE 2
#define LAYERED_THREAD 2
#define LAYERED_USER_INTERACTION 3


class object;

class channel;


inline ::object* __object(::layered* playered)
{

   return playered->layer<::object>(LAYERED_OBJECT);

}


inline ::channel* __channel(::layered* playered)
{

   return playered->layer<::channel>(LAYERED_OBJECT);

}


inline ::user::create* __user_create(::layered* playered)
{

   return playered->layer<::user::create>(LAYERED_USER_CREATE);

}


inline ::user::interaction* __user_interaction(::layered* playered)
{

   return playered->layer<::user::interaction>(LAYERED_USER_INTERACTION);

}

inline ::user::primitive * __user_primitive(::layered* playered)
{

   return playered->layer<::user::primitive>(LAYERED_USER_PRIMITIVE);

}


inline ::thread* __thread(::layered* playered)
{

   return playered->layer<::thread>(LAYERED_THREAD);

}



