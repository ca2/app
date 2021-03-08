#pragma once


#define MAX_LAYERED_COUNT 8


class CLASS_DECL_ACME layered :
   virtual public ::context_object
{
private:


   void *      m_pa[MAX_LAYERED_COUNT];
   void *      m_osdataa[MAX_LAYERED_COUNT];


public:



   layered() : m_pa{}, m_osdataa{} { }
   virtual ~layered();

   void set_layer(byte bLayeredIndex, void* p);
   inline void * layer(byte bLayeredIndex) const { return ::c_is_null(this) ? nullptr : m_pa[bLayeredIndex]; }
   inline void clear_layers()  { __zero(m_pa); }



   void set_os_data(byte b, void * p);
   inline void * get_os_data(byte b = 0) const { return m_osdataa[b]; }
   inline void set_os_data(void * p) { set_os_data(0, p); }
   inline void clear_os_data() { __zero(m_osdataa); }


};


#define LAYERED_ACME 0
#define LAYERED_APEX 1
#define LAYERED_AQUA 2
#define LAYERED_AURA 3
#define LAYERED_AXIS 4
#define LAYERED_BASE 5
#define LAYERED_BRED 6
#define LAYERED_CORE 7

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
#define LAYERED_IMPL 7
#define LAYERED_X11 6


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



