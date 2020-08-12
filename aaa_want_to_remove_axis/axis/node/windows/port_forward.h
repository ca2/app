#pragma once



#include <Natupnp.h>
#include <UPnP.h>


namespace windows
{


   class port_forward :
      virtual public ::net::port_forward
   {
   public:

      // forward declarations

      interface IDerivedNATExternalIPAddressCallback;
      interface IDerivedNATNumberOfEntriesCallback;


      // protected interfaces, which were forward-declared above, and which are used for event notifications from COM
      // most of the code is here in this .h file, except for the QueryInterface method which is in the .cpp file

      interface IDerivedNATExternalIPAddressCallback : public INATExternalIPAddressCallback
      {
         IDerivedNATExternalIPAddressCallback( ::net::port_forward_change_callbacks * pdispatch) : m_pdispatch(pdispatch), m_dwRef( 0 ) { };

         HRESULT STDMETHODCALLTYPE NewExternalIPAddress( BSTR bstrNewExternalIPAddress )
         {
            ASSERT( m_pdispatch != nullptr );
            string strNewExternalIPAddress(bstrNewExternalIPAddress);
            return m_pdispatch->OnNewExternalIPAddress(strNewExternalIPAddress );
         }

         HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void ** ppvObject);

         ULONG STDMETHODCALLTYPE AddRef()  {	return ++m_dwRef; }

         ULONG STDMETHODCALLTYPE Release()
         {
            if ( --m_dwRef == 0 )
               delete this;

            return m_dwRef;
         }

         DWORD		m_dwRef;
         ::net::port_forward_change_callbacks*	m_pdispatch;
      };

      interface IDerivedNATNumberOfEntriesCallback : public INATNumberOfEntriesCallback
      {
         IDerivedNATNumberOfEntriesCallback( ::net::port_forward_change_callbacks* point ) : m_pdispatch( point ), m_dwRef( 0 ) { };

         HRESULT STDMETHODCALLTYPE NewNumberOfEntries( long lNewNumberOfEntries )
         {
            ASSERT(m_pdispatch != nullptr );
            return m_pdispatch->OnNewNumberOfEntries( lNewNumberOfEntries );
         }

         HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void ** ppvObject);

         ULONG STDMETHODCALLTYPE AddRef()  { return ++m_dwRef; }

         ULONG STDMETHODCALLTYPE Release()
         {
            if ( --m_dwRef == 0 )
               delete this;

            return m_dwRef;
         }

         DWORD		m_dwRef;
         ::net::port_forward_change_callbacks* m_pdispatch;
      };

      // public functions -- there are only a few

      port_forward();
      virtual ~port_forward();

      virtual HRESULT ListenForUpnpChanges(::net::port_forward_change_callbacks *pCallbacks = nullptr);  // nullptr==default object; if you provide your own pointer to a port_forward_change_callbacks-derived object it is deleted for you automatically
      virtual HRESULT StopListeningForUpnpChanges( );  // Stops listenting for UPnP change events on the router and deletes any port_forward_change_callbacks-derived objects

      virtual bool async_device_information_retrieval( oswindow oswindow );  // starts a thread that will get IGD (router) device information; the thread posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION message to oswindow when it's done
      virtual bool async_port_retrieval( oswindow oswindow );  // starts a thread that will get all mappings; the thread posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION message to oswindow when it's done
      virtual bool async_edit_mapping( port_map& oldMapping, port_map& newMapping, oswindow oswindow );  // starts a thread that will edit one specific mapping; the thread posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION message to oswindow when it's done
      virtual bool async_add_mapping( port_map& newMapping, oswindow oswindow );  // starts a thread that will add one new mapping; the thread posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION message to oswindow when it's done
      virtual bool async_delete_mapping( port_map& oldMapping, oswindow oswindow );  // starts a thread that will delete one specific mapping; the thread posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION message to oswindow when it's done

      virtual pointer_array < port_map > get_port_map() const;  // gets a copy of currently-known port mappings
      virtual pointer_array < device >  get_igd() const;  // gets a copy of currently-know device information

      virtual bool IsAnyThreadRunning() const;  // returns TRUE if there is any thread currently running


   protected:

      // protected functions used internally by PortMappingEngine

      void InitializeMembersToNull();
      void DeinitializeCom();
      HRESULT PopulateDeviceInfoContainer( IUPnPDevice* piDevice, device & deviceInfo, oswindow oswindow=nullptr );
      HRESULT GetNextMapping( IEnumVARIANT* piEnumerator, port_map & mappingContainer );
      HRESULT SetChangeEventCallbackPointer(::net::port_forward_change_callbacks *pCallbacks);

      void task_port_retrieval();
      void task_device_information_retrieval();
      void task_edit_mapping();
      void task_add_mapping();
      void task_delete_mapping();


   protected:

      // protected members

      IUPnPNAT*								m_piNAT;
      IDerivedNATExternalIPAddressCallback*	m_piExternalIPAddressCallback;
      IDerivedNATNumberOfEntriesCallback*		m_piNumberOfEntriesCallback;

      INATEventManager*						m_piEventManager;
      ::net::port_forward_change_callbacks*			m_pChangeCallbackFunctions;

      bool m_bListeningForUpnpChanges;

      //::thread_pointer m_pthreadPortRetrieval;
      //::thread_pointer m_pthreadDeviceInfo;
      //::thread_pointer m_pthreadAddMapping;
      //::thread_pointer m_pthreadEditMapping;
      //::thread_pointer m_pthreadDeleteMapping;

      pointer_array<port_map> m_MappingContainer;

      CRITICAL_SECTION m_cs;


      // some more protected members, most of which could not be declared until after full-declaration
      // of the device_information_container and port_map nested classes

      pointer_array<device> m_DeviceInfo;

      // good-enough method for inter-thread transfer of information, since only
      // one thread of each type is ever permitted at one time

      port_map m_scratchpadOldMapping;
      port_map m_scratchpadNewMapping;
      port_map m_scratchpadAddedMapping;
      port_map m_scratchpadDeletedMapping;

      oswindow m_oswindowForPortMapping;
      oswindow m_oswindowForDeviceInfo;
      oswindow m_oswindowForAddMapping;
      oswindow m_oswindowForEditMapping;
      oswindow m_oswindowForDeleteMapping;

      ::thread_pointer     m_ptaskPortRetrieval;
      ::thread_pointer     m_ptaskDeviceInformationRetrieval;
      ::thread_pointer     m_ptaskEditMapping;
      ::thread_pointer     m_ptaskAddMapping;
      ::thread_pointer     m_ptaskDeleteMapping;


   };


} // namespace axis

