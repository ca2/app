#pragma once


namespace base
{


   class CLASS_DECL_BASE system:
      virtual public ::aura::system
   {
   public:


      system();
      virtual ~system();


      virtual ::estatus initialize_system(::object * pobjectContext, app_core * pappcore) override;


      virtual ::estatus process_init() override;
      virtual void term_system() override;

      //virtual __pointer(::aura::session) on_create_session() override;

      virtual void set_active_guie(::user::interaction * pinteraction);
      virtual void set_focus_guie(::user::interaction * pinteraction);



      //virtual ::install::canvas * install_create_canvas() override;
      //virtual void install_canvas_on_paint(::draw2d::graphics_pointer & pgraphics, const ::rect & rect);
      //virtual int install_canvas_increment_mode() override;



      virtual DWORD get_monitor_color_temperature(index iMonitor);
      virtual bool adjust_monitor(index iMonitor, DWORD dwTemperature, double dBrightness, double dwGamma);
      virtual bool get_monitor_rect(index iMonitor,RECT * prect) override;

      virtual ::count get_monitor_count() override;

      bool get_wkspace_rect(index iWkspace,RECT * prect) override;


      //virtual ::user::interaction_impl * impl_from_handle(void * pdata) override;
      //virtual ::user::interaction * ui_from_handle(void * pdata) override;

      virtual void update(::update * pupdate) override;



      virtual bool initialize_native_window1() override;



   };


} // namespace base



template < size_t _Bits >
inline stream & operator << (stream & _Ostr,const bitset<_Bits>& _Right)
{
   // insert bitset as a string
   return (_Ostr << _Right.template to_string());
}

// TEMPLATE operator>>
template < size_t _Bits >
inline stream & operator >> (stream &  _Istr,bitset<_Bits>& _Right)
{
   // extract bitset as a string
   string _Str;

   _Istr >> _Str;

   _Right = bitset<_Bits>(_Str); // convert string and store

   return (_Istr);

}




void CLASS_DECL_BASE __start_system(::base::system * psystem);




