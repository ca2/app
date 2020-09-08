/**
* \brief Session independent waitables
*/
#pragma once


class mutex;
class event;




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




