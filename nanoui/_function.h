//
// Created by camilo on 2022-09-08 22:16 <3ThomasBorregaardSørensen!!
//

//**
//* \brief Determine whether an icon ID is a texture loaded via ``::nano2d::_image_icon``.
//*
//* \rst
//* The implementation defines all ``value < 1024`` as image icons, and
//   * everything ``> = 1024`` as an Entypo icon(see :::pointer:`file_nanoui_entypo.h`).
//      * The value ``1024`` exists to provide a generous buffer on how many images
//      * may have been loaded by NanoVG.
//      * \endrst
//      *
//      *\param value
//      * The integral value of the icon.
//      *
//      *\return
//      *Whether or not this is an image icon.
//      * /
inline bool nano2d_is_image_icon(int value) { return value < 1024; }

/**
 * \brief Determine whether an icon ID is a font-based icon (e.g. from ``entypo.ttf``).
 *
 * \rst
 * See :func:`nanoui::nano2d::_is_image_icon` for details.
 * \endrst
 *
 * \param value
 *     The integral value of the icon.
 *
 * \return
 *     Whether or not this is a font icon (from ``entypo.ttf``).
 */
inline bool nano2d_is_font_icon(int value) { return value >= 1024; }

