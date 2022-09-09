//
// Created by camilo on 2022-09-08 22:16 <3ThomasBorregaardSorensen!!
//

//**
//* \brief Determine whether an icon ID is a texture loaded via ``nvg_image_icon``.
//*
//* \rst
//* The implementation defines all ``value < 1024`` as image icons, and
//   * everything ``> = 1024`` as an Entypo icon(see :ref:`file_nanogui_entypo.h`).
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
inline bool nvg_is_image_icon(int value) { return value < 1024; }

/**
 * \brief Determine whether an icon ID is a font-based icon (e.g. from ``entypo.ttf``).
 *
 * \rst
 * See :func:`nanogui::nvg_is_image_icon` for details.
 * \endrst
 *
 * \param value
 *     The integral value of the icon.
 *
 * \return
 *     Whether or not this is a font icon (from ``entypo.ttf``).
 */
inline bool nvg_is_font_icon(int value) { return value >= 1024; }

