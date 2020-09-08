/**
* \brief Session independent waitables
*/
#pragma once


class mutex;
class event;



///  \brief    pauses generic for specified time
///  \lparam    duration sleeping time of generic
CLASS_DECL_ACME void sleep(const duration & duration);


class sync;



class CLASS_DECL_ACME sync_callback
{
public:
   virtual ~sync_callback();

   /// called on signalization of a sync
   /// \lparam signaling sync
   virtual void on_sync(sync * psync) = 0;

};



namespace acme
{


   // platform abstraction layer
   namespace pal
   {


      typedef ::generic WaitableItem;


   } // namespace pal - platform abstraction layer


} // namespace acme




