#pragma once


#define MAX_LAYERED_COUNT 8

class CLASS_DECL_ACME layered :
   virtual public ::generic
{
private:


   void* m_osdataa[MAX_LAYERED_COUNT];

public:

   layered() { xxf_zero(m_osdataa); }
   virtual ~layered();

   void set_os_data(byte bIndex, void* p);
      
   template < typename LAYER >
   inline LAYER* layer(bool bIndex) const { return (LAYER *)m_osdataa[bIndex]; }

};

#define LAYERED_USER_CREATE 0
#define LAYERED_USER_PRIMITIVE 0
#define LAYERED_THREAD 0
#define LAYERED_DRAW2D_GRAPHICS 0
#define LAYERED_USER_INTERACTION 1


inline ::user::create* __user_create(::layered* playered)
{

   return playered->layer<::user::create>(LAYERED_USER_CREATE);

}


inline ::user::primitive * __user_primitive(::layered* playered)
{

   return playered->layer<::user::primitive>(LAYERED_USER_PRIMITIVE);

}


inline ::thread* __thread(::layered* playered)
{

   return playered->layer<::thread>(LAYERED_THREAD);

}



