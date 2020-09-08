/**
* \brief Session independent waitables
*/
#pragma once


class mutex;
class event;



///  \brief    pauses object for specified time
///  \lparam    duration sleeping time of object
CLASS_DECL_AQUA void sleep(const duration & duration);


class sync;



class CLASS_DECL_AQUA sync_callback
{
public:
   virtual ~sync_callback();

   /// called on signalization of a sync
   /// \lparam signaling sync
   virtual void on_sync(sync * psync) = 0;

};



namespace aura
{


   // platform abstraction layer
   namespace pal
   {


      typedef ::object WaitableItem;


   } // namespace pal - platform abstraction layer


} // namespace aura




