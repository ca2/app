#pragma once


#ifdef WINDOWS


namespace networking
{


   class CLASS_DECL_APEX port_forward_change_callbacks :
      virtual public object
   {
   public:


      port_forward_change_callbacks();
      virtual ~port_forward_change_callbacks();


      virtual HRESULT OnNewNumberOfEntries( i32 lNewNumberOfEntries );
      virtual HRESULT OnNewExternalIPAddress(const char * psz );


   };


   class CLASS_DECL_APEX port_forward :
      virtual public ::object
   {
   public:


      // a public enum which is used by classes that respond to the registered interaction_impl message
      // UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION, so they can decode the wParam and lParam values


      enum THREAD_STATUS
      {
         EnumPortRetrieveInterval	= 0x0001,
         EnumPortRetrieveDone	= 0x0002,
         EnumDeviceInfoInterval	= 0x0011,
         EnumDeviceInfoDone		= 0x0012,
         EnumAddMappingInterval	= 0x0021,
         EnumAddMappingDone		= 0x0022,
         EnumEditMappingInterval	= 0x0041,
         EnumEditMappingDone		= 0x0042,
         EnumDeleteMappingInterval	= 0x0081,
         EnumDeleteMappingDone		= 0x0082
      };

      // public nested classes, which were forward-declared above
      // these are public because they are needed by classes that call the
      // GetPortMappingVector() and GetDeviceInformationContainer() methods

      class CLASS_DECL_APEX port_map :
         virtual public object
      {
      public:
         string ExternalIPAddress;
         string ExternalPort;
         string InternalPort;
         string Protocol;
         string InternalClient;
         string Enabled;
         string Description;
      };

      class CLASS_DECL_APEX device :
         virtual public object
      {
      public:



         // see http://msdn.microsoft.com/library/en-us/upnp/upnp/iupnpdevice.asp

         string Children;			// Child devices of the device.
         string Description;		// Human-readable form of the summary of a device's functionality.
         string FriendlyName;		// Device display name.
         string HasChildren;		// Indicates whether the device has any child devices.
         string IconURL;			// URL of icon
         string IsRootDevice;		// Indicates whether the device is the top-most device in the device tree.
         string ManufacturerName;	// Human-readable form of the manufacturer name.
         string ManufacturerURL;	// URL for the manufacturer's Web site.
         string ModelName;			// Human-readable form of the model name.
         string ModelNumber;		// Human-readable form of the model number.
         string ModelURL;			// URL for a Web page that contains model-specific information.
         string ParentDevice;		// Parent of the device.
         string PresentationURL;	// Presentation URL for a Web page that can be used to control the device.
         string RootDevice;			// Top-most device in the device tree.
         string SerialNumber;		// Human-readable form of the serial number.
         string Services;			// List of services provided by the device.
         string Type;				// Uniform resource identifier (URI) for the device type.
         string UniqueDeviceName;	// Unique device name (UDN) of the device.
         string UPC;				// Human-readable form of the product code.

      };


   public:

      port_forward();
      virtual ~port_forward();

      virtual HRESULT ListenForUpnpChanges(port_forward_change_callbacks *pCallbacks = nullptr);  // nullptr==default object; if you provide your own pointer to a port_forward_change_callbacks-derived object it is deleted for you automatically
      virtual HRESULT StopListeningForUpnpChanges( );  // Stops listenting for UPnP machine events on the router and deletes any port_forward_change_callbacks-derived objects

      virtual bool GetDeviceInformationUsingThread( oswindow oswindow );  // starts a thread that will get IGD (router) device information; the thread posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION message to oswindow when it's done
      virtual bool GetMappingsUsingThread( oswindow oswindow );  // starts a thread that will get all mappings; the thread posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION message to oswindow when it's done
      virtual bool EditMappingUsingThread( port_map & oldMapping, port_map& newMapping, oswindow oswindow );  // starts a thread that will edit one specific mapping; the thread posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION message to oswindow when it's done
      virtual bool AddMappingUsingThread( port_map& newMapping, oswindow oswindow );  // starts a thread that will add one new mapping; the thread posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION message to oswindow when it's done
      virtual bool DeleteMappingUsingThread( port_map& oldMapping, oswindow oswindow );  // starts a thread that will delete one specific mapping; the thread posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION message to oswindow when it's done

      virtual pointer_array < port_map > get_port_map() const;  // gets a copy of currently-known port mappings
      virtual pointer_array < device > get_igd() const;  // gets a copy of currently-know device information

      virtual bool IsAnyThreadRunning() const;  // returns true if there is any thread currently running


   };


   typedef ___pointer < port_forward > port_forward_pointer;


} // namespace net


#endif



