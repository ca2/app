#pragma once


class CLASS_DECL_AURA context_image :
   virtual public ::object
{
public:


   //handler_manager                     m_managerImageLoad;


   context_image();
   virtual ~context_image();


   virtual ::e_status initialize(::layered * pobjectContext) override;


   virtual ::e_status set_finish_composites(::context_object * pcontextobjectFinish) override;


   virtual ::image_result get_image(const ::payload & varFile, bool bCache = true, bool bSync = true);
   virtual ::image_result matter_image(const string & strMatter, bool bCache = true, bool bSync = true);

   virtual ::image_result load_image(const ::payload & varFile, bool bCache = true, bool bSync = true, bool bCreateHelperMaps = false);
   virtual ::image_result load_matter_image(const string & strMatter, bool bCache = true, bool bSync = true, bool bCreateHelperMaps = false);
   virtual ::image_result load_matter_icon(string_array & straMatter, string strIcon);
   virtual ::image_result load_thumbnail(const ::payload & varFile, int w, int h);
   virtual ::image_result load_thumbnail(const string & strPath);
   virtual ::image_result load_dib(const ::file::path & pathDib);
   //virtual ::icon_result load_icon(const ::payload & varFile);


   virtual ::e_status _get_image(image * pimage, const ::payload & varFile, bool bSync = true);
   virtual ::e_status _matter_image(image * pimage, const string & strMatter, bool bSync = true);


   virtual ::e_status _load_image(image * pimage, const ::payload & varFile, bool bSync = true, bool bCreateHelperMaps = false);
   virtual ::e_status _load_matter_image(image * pimage, const string & pszMatter, bool bSync = true, bool bCreateHelperMaps = false);
   virtual ::e_status _load_matter_icon(image * pimage, string_array & straMatter, string strIcon);
   virtual ::e_status _load_thumbnail(image * pimage, const ::payload & varFile, int w, int h);
   virtual ::e_status _load_thumbnail(image * pimage, const ::payload & varFile);
   virtual ::e_status _load_dib(image * pimage, const ::file::path & pathDib);


   virtual ::e_status save_image(const ::payload & varFile, const image * pimage, const ::save_image * psaveimage = nullptr);
   virtual ::e_status save_image(memory & memory, const image * pimage, const ::save_image * psaveimage = nullptr);
   virtual ::e_status save_dib(const ::file::path & path, const image * pimage);

   
   virtual HCURSOR CreateAlphaCursor(oswindow oswindow, const image * pimage, int xHotSpot, int yHotSpot);
   virtual void set_cursor_image(const image * pimage, int xHotSpot, int yHotSpot);


   virtual ::image_result _load_image_from_file(const ::payload & varFile, const payload & varOptions);
   virtual ::e_status _save_to_file(const ::payload & varFile, const image * pimage, const payload & varOptions);
   
   virtual ::e_status _load_image(::image* pimage, __pointer(image_frame_array)& pframea, ::memory_pointer pmemory);
   
   virtual ::e_status load_cursor(::draw2d::cursor* pcursor, ::file::path path, bool bSync, bool bCache = true);

   virtual bool _load_multi_frame_image(::image* pimage, memory_pointer pmemory);

   virtual ::e_status load_svg(::image* pimage, ::memory_pointer pmemory);

#ifdef _UWP
   virtual bool _desk_to_image(::image* pimage);
   virtual bool _desk_has_image();
   virtual bool _image_to_desk(const ::image* pimage);
#endif

};



