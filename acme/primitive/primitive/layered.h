#pragma once


#define MAX_LAYERED_COUNT 8


class CLASS_DECL_ACME layered :
   virtual public ::matter
{
private:


   void* m_pa[MAX_LAYERED_COUNT];

public:

   layered() : m_pa{} { }
   virtual ~layered();

   void set_layer(byte bLayeredIndex, void* p);

   inline void * layer(byte bLayeredIndex) const { return ::c_is_null(this) ? nullptr : m_pa[bLayeredIndex]; }

};


#define LAYERED_OBJECT 0
#define LAYERED_DRAW2D_GRAPHICS 1
#define LAYERED_USER_CREATE 1
#define LAYERED_CHANNEL 1
#define LAYERED_USER_PRIMITIVE 2
#define LAYERED_THREAD 2
#define LAYERED_USER_INTERACTION 3
#define LAYERED_USER_FRAME 4
#define LAYERED_USER_CONTROL_EVENT 7
#define LAYERED_TASK_POOL 5
#define LAYERED_OS_USER_INTERACTION_IMPL 6


class object;


class channel;


class thread;


inline ::object* __object(::layered* playered)
{

   return (::object *) playered->layer(LAYERED_OBJECT);

}


inline ::channel* __channel(::layered* playered)
{

   return (::channel *) playered->layer(LAYERED_OBJECT);

}


inline ::thread* ___thread(::layered* playered)
{

   return (::thread *) playered->layer(LAYERED_THREAD);

}



namespace user
{

   class system;
   class interaction;
   class frame;
   class primitive;
   class control_event;

} // namespace user


inline ::user::system* __user_system(::layered* playered)
{

   return (::user::system *) playered->layer(LAYERED_USER_CREATE);

}


inline ::user::frame * __user_frame(::layered* playered)
{

   return (::user::frame *) playered->layer(LAYERED_USER_FRAME);

}


inline ::user::interaction* __user_interaction(::layered* playered)
{

   return (::user::interaction *) playered->layer(LAYERED_USER_INTERACTION);

}


inline ::user::primitive * __user_primitive(::layered* playered)
{

   return (::user::primitive *) playered->layer(LAYERED_USER_PRIMITIVE);

}



inline ::user::control_event * __user_control_event(::layered* playered)
{

   return (::user::control_event*) playered->layer(LAYERED_USER_CONTROL_EVENT);

}



inline ::task_pool* __task_pool(::layered* playered)
{

   return (::task_pool*) playered->layer(LAYERED_TASK_POOL);

}



