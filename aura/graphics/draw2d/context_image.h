#pragma once


class CLASS_DECL_AURA context_image :
   virtual public ::object
{
public:


   //handler_manager                     m_managerImageLoad;


   context_image();
   ~context_image() override;


   ::e_status initialize(::object * pobject) override;


   //virtual ::e_status set_finish_composites(::property_object* pcontextobjectRootFinishingInitiator) override;

   ::e_status destroy_composites() override;


   virtual ::icon_transport get_icon(const ::payload & varFile, bool bCache = true, bool bSync = true);
   virtual ::image_transport get_image(const ::payload & varFile, bool bCache = true, bool bSync = true);
   virtual ::image_transport matter_image(const ::string & strMatter, bool bCache = true, bool bSync = true);

   virtual ::image_transport load_image(const ::payload & varFile, bool bCache = true, bool bSync = true, bool bCreateHelperMaps = false);
   virtual ::image_transport load_matter_image(const ::string & strMatter, bool bCache = true, bool bSync = true, bool bCreateHelperMaps = false);
   virtual ::image_transport load_matter_icon(string_array & straMatter, string strIcon);
   virtual ::image_transport load_thumbnail(const ::payload & varFile, int w, int h);
   virtual ::image_transport load_thumbnail(const ::string & strPath);
   virtual ::image_transport load_dib(const ::file::path & pathDib);
   //virtual ::icon_transport load_icon(const ::payload & varFile);


   virtual ::e_status _get_icon(::draw2d::icon * picon, const ::payload & varFile);


   virtual ::e_status _load_icon(::draw2d::icon * picon, const ::payload & varFile);


   virtual ::e_status _get_image(image * pimage, const ::payload & varFile, bool bSync = true);
   virtual ::e_status _matter_image(image * pimage, const ::string & strMatter, bool bSync = true);


   virtual ::e_status _load_image(image * pimage, const ::payload & varFile, bool bSync = true, bool bCreateHelperMaps = false);
   virtual ::e_status _load_matter_image(image * pimage, const string & pszMatter, bool bSync = true, bool bCreateHelperMaps = false);
   virtual ::e_status _load_matter_icon(image * pimage, string_array & straMatter, string strIcon);
   virtual ::e_status _load_thumbnail(image * pimage, const ::payload & varFile, int w, int h);
   virtual ::e_status _load_thumbnail(image * pimage, const ::payload & varFile);
   virtual ::e_status _load_dib(image * pimage, const ::file::path & pathDib);


   virtual ::e_status save_image(const ::payload & varFile, const image * pimage, const ::save_image * psaveimage = nullptr);
   virtual ::e_status save_image(memory & memory, const image * pimage, const ::save_image * psaveimage = nullptr);
   virtual ::e_status save_dib(const ::file::path & path, const image * pimage);

   
   
   virtual void set_cursor_image(const image * pimage, int xHotSpot, int yHotSpot);


   virtual ::image_transport _load_image_from_file(const ::payload & varFile, const ::payload & varOptions);
   virtual ::e_status _save_to_file(const ::payload & varFile, const image * pimage, const ::payload & varOptions);
   
   virtual ::e_status _load_image(::image* pimage, __pointer(image_frame_array)& pframea, memory & memory);
   
   virtual bool _load_multi_frame_image(::image* pimage, memory & memory);

   virtual ::e_status load_svg(::image* pimage, memory & memory);

#ifdef _UWP
   virtual bool _desk_to_image(::image* pimage);
   virtual bool _desk_has_image();
   virtual bool _image_to_desk(const ::image* pimage);
#endif
   

};



