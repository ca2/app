#include "aura/.h"
#include "rdpclient/client/common/rdpclient.h"

struct CLASS_DECL_AXIS_RDPCLIENT rdp_event_item
{

   void * input;
   int bKey;
   int down;
   ::u32 scancode;
   const ::atom & atom;
   ::point_i32 pt;
   void send();
};


typedef array < rdp_event_item > rdp_event_itema;

::pointer< ::mutex > g_pmutexRdpEvent = nullptr;

map < void *,void *,rdp_event_itema> g_eventmap;

CLASS_DECL_AXIS_RDPCLIENT void ca2rdp_send_event(void * input,int bKey,int down,::u32 scancode,const ::atom & atom,::point_i32 pt);

::pointer< ::mutex > ca2rdp_get_event_queue_mutex()
{

   if(g_pmutexRdpEvent == nullptr)
   {

      g_pmutexRdpEvent = memory_new ::pointer < ::mutex >();

   }

   return g_pmutexRdpEvent;


}

CLASS_DECL_AXIS_RDPCLIENT void ca2rdp_queue_event(void * input,int bKey,int down,::u32 scancode,const ::atom & atom,::point_i32 pt)
{

   synchronous_lock synchronouslock(ca2rdp_get_event_queue_mutex());

   rdp_event_item item;
   item.input = input;
   item.bKey = bKey;
   item.down = down;
   item.scancode = scancode;
   item.emessage = emessage;
   item.pt = point;

   g_eventmap[input].add(item);
}

CLASS_DECL_AXIS_RDPCLIENT int  ca2rdp_get_event(rdp_event_item & item,void* input)
{

   synchronous_lock synchronouslock(ca2rdp_get_event_queue_mutex());

   if(g_eventmap[input].has_elements())
   {
      item = g_eventmap[input][0];
      g_eventmap[input].erase_at(0);
      return true;
   }
   return false;
}



void rdp_event_item::send()
{

   ca2rdp_send_event(input,bKey,down,scancode,emessage, point);

}
