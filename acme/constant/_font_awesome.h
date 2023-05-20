/*
    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

/* Developer note: need to make a change to this file?
 * Please raise an Issue on GitHub describing what needs to change.  This file
 * was generated, so the scripts that generated it needs to update as well.
 */

 /**
  * \file nanoui/icons.h
  *
  * \brief This is a list of icon codes for the free variant of the
  * FontAwesome 5.10.1 font.
  *
  * \rst
  *
  * This file defines the full listing of
  * `FontAwesome <https://raw.githubusercontent.com/FortAwesome/Font-Awesome>`_
  * icons available in NanoGUI.  Please note that if viewing the documentation
  * on the web, your browser may display the icons differently than what they
  * look like in NanoGUI.  Run the one of the :ref:`nanoui_example_icons`
  * executables to see what they all look like in NanoGUI.
  *
  * .. tip::
  *
  *    In C++, ``#include <nanoui/icons.h>`` to gain access to the ``#define``
  *    shown in these docs and simply reference the names as listed in the
  *    documentation.  To use the icons from Python, declare
  *    ``from nanoui import icons`` and reference the icons as follows:
  *    ``icons.FA_ASTERISK``.
  *
  * The following icons are available:
  *
  * .. raw:: html
  *
  *    <center>
  *      <div class="wy-table-responsive">
  *        <table class="docutils" border=1>
  *          <colgroup>
  *            <col width="90%" align="center"/>
  *            <col width="10%" align="center" />
  *          </colgroup>
  *          <thead valign="bottom">
  *            <tr class="row-odd">
  *              <th class="head" align="center">Definition</th>
  *              <th class="head" align="center">Icon</th>
  *            </tr>
  *          </thead>
  *          <tbody valign="top">
  *            <tr class="row-even">
  *              <td align="right"><code>FA_AD</code></td>
  *              <td align="center"><span class="fa-ad"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ADDRESS_BOOK</code></td>
  *              <td align="center"><span class="fa-address-book"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ADDRESS_CARD</code></td>
  *              <td align="center"><span class="fa-address-card"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ADJUST</code></td>
  *              <td align="center"><span class="fa-adjust"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_AIR_FRESHENER</code></td>
  *              <td align="center"><span class="fa-air-freshener"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ALIGN_CENTER</code></td>
  *              <td align="center"><span class="fa-align-center"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ALIGN_JUSTIFY</code></td>
  *              <td align="center"><span class="fa-align-justify"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ALIGN_LEFT</code></td>
  *              <td align="center"><span class="fa-align-left"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ALIGN_RIGHT</code></td>
  *              <td align="center"><span class="fa-align-right"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ALLERGIES</code></td>
  *              <td align="center"><span class="fa-allergies"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_AMBULANCE</code></td>
  *              <td align="center"><span class="fa-ambulance"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_AMERICAN_SIGN_LANGUAGE_INTERPRETING</code></td>
  *              <td align="center"><span class="fa-american-sign-language-interpreting"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ANCHOR</code></td>
  *              <td align="center"><span class="fa-anchor"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ANGLE_DOUBLE_DOWN</code></td>
  *              <td align="center"><span class="fa-angle-double-down"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ANGLE_DOUBLE_LEFT</code></td>
  *              <td align="center"><span class="fa-angle-double-left"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ANGLE_DOUBLE_RIGHT</code></td>
  *              <td align="center"><span class="fa-angle-double-right"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ANGLE_DOUBLE_UP</code></td>
  *              <td align="center"><span class="fa-angle-double-up"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ANGLE_DOWN</code></td>
  *              <td align="center"><span class="fa-angle-down"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ANGLE_LEFT</code></td>
  *              <td align="center"><span class="fa-angle-left"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ANGLE_RIGHT</code></td>
  *              <td align="center"><span class="fa-angle-right"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ANGLE_UP</code></td>
  *              <td align="center"><span class="fa-angle-up"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ANGRY</code></td>
  *              <td align="center"><span class="fa-angry"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ANKH</code></td>
  *              <td align="center"><span class="fa-ankh"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_APPLE_ALT</code></td>
  *              <td align="center"><span class="fa-apple-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ARCHIVE</code></td>
  *              <td align="center"><span class="fa-archive"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ARCHWAY</code></td>
  *              <td align="center"><span class="fa-archway"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ARROW_ALT_CIRCLE_DOWN</code></td>
  *              <td align="center"><span class="fa-arrow-alt-circle-down"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ARROW_ALT_CIRCLE_LEFT</code></td>
  *              <td align="center"><span class="fa-arrow-alt-circle-left"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ARROW_ALT_CIRCLE_RIGHT</code></td>
  *              <td align="center"><span class="fa-arrow-alt-circle-right"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ARROW_ALT_CIRCLE_UP</code></td>
  *              <td align="center"><span class="fa-arrow-alt-circle-up"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ARROW_CIRCLE_DOWN</code></td>
  *              <td align="center"><span class="fa-arrow-circle-down"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ARROW_CIRCLE_LEFT</code></td>
  *              <td align="center"><span class="fa-arrow-circle-left"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ARROW_CIRCLE_RIGHT</code></td>
  *              <td align="center"><span class="fa-arrow-circle-right"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ARROW_CIRCLE_UP</code></td>
  *              <td align="center"><span class="fa-arrow-circle-up"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ARROW_DOWN</code></td>
  *              <td align="center"><span class="fa-arrow-down"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ARROW_LEFT</code></td>
  *              <td align="center"><span class="fa-arrow-left"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ARROW_RIGHT</code></td>
  *              <td align="center"><span class="fa-arrow-right"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ARROW_UP</code></td>
  *              <td align="center"><span class="fa-arrow-up"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ARROWS_ALT</code></td>
  *              <td align="center"><span class="fa-arrows-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ARROWS_ALT_H</code></td>
  *              <td align="center"><span class="fa-arrows-alt-h"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ARROWS_ALT_V</code></td>
  *              <td align="center"><span class="fa-arrows-alt-v"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ASSISTIVE_LISTENING_SYSTEMS</code></td>
  *              <td align="center"><span class="fa-assistive-listening-systems"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ASTERISK</code></td>
  *              <td align="center"><span class="fa-asterisk"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_AT</code></td>
  *              <td align="center"><span class="fa-at"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ATLAS</code></td>
  *              <td align="center"><span class="fa-atlas"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ATOM</code></td>
  *              <td align="center"><span class="fa-atom"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_AUDIO_DESCRIPTION</code></td>
  *              <td align="center"><span class="fa-audio-description"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_AWARD</code></td>
  *              <td align="center"><span class="fa-award"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BABY</code></td>
  *              <td align="center"><span class="fa-baby"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BABY_CARRIAGE</code></td>
  *              <td align="center"><span class="fa-baby-carriage"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BACKSPACE</code></td>
  *              <td align="center"><span class="fa-backspace"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BACKWARD</code></td>
  *              <td align="center"><span class="fa-backward"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BACON</code></td>
  *              <td align="center"><span class="fa-bacon"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BALANCE_SCALE</code></td>
  *              <td align="center"><span class="fa-balance-scale"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BALANCE_SCALE_LEFT</code></td>
  *              <td align="center"><span class="fa-balance-scale-left"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BALANCE_SCALE_RIGHT</code></td>
  *              <td align="center"><span class="fa-balance-scale-right"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BAN</code></td>
  *              <td align="center"><span class="fa-ban"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BAND_AID</code></td>
  *              <td align="center"><span class="fa-band-aid"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BARCODE</code></td>
  *              <td align="center"><span class="fa-barcode"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BARS</code></td>
  *              <td align="center"><span class="fa-bars"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BASEBALL_BALL</code></td>
  *              <td align="center"><span class="fa-baseball-ball"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BASKETBALL_BALL</code></td>
  *              <td align="center"><span class="fa-basketball-ball"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BATH</code></td>
  *              <td align="center"><span class="fa-bath"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BATTERY_EMPTY</code></td>
  *              <td align="center"><span class="fa-battery-empty"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BATTERY_FULL</code></td>
  *              <td align="center"><span class="fa-battery-full"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BATTERY_HALF</code></td>
  *              <td align="center"><span class="fa-battery-half"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BATTERY_QUARTER</code></td>
  *              <td align="center"><span class="fa-battery-quarter"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BATTERY_THREE_QUARTERS</code></td>
  *              <td align="center"><span class="fa-battery-three-quarters"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BED</code></td>
  *              <td align="center"><span class="fa-bed"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BEER</code></td>
  *              <td align="center"><span class="fa-beer"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BELL</code></td>
  *              <td align="center"><span class="fa-bell"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BELL_SLASH</code></td>
  *              <td align="center"><span class="fa-bell-slash"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BEZIER_CURVE</code></td>
  *              <td align="center"><span class="fa-bezier-curve"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BIBLE</code></td>
  *              <td align="center"><span class="fa-bible"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BICYCLE</code></td>
  *              <td align="center"><span class="fa-bicycle"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BIKING</code></td>
  *              <td align="center"><span class="fa-biking"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BINOCULARS</code></td>
  *              <td align="center"><span class="fa-binoculars"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BIOHAZARD</code></td>
  *              <td align="center"><span class="fa-biohazard"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BIRTHDAY_CAKE</code></td>
  *              <td align="center"><span class="fa-birthday-cake"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BLENDER</code></td>
  *              <td align="center"><span class="fa-blender"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BLENDER_PHONE</code></td>
  *              <td align="center"><span class="fa-blender-phone"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BLIND</code></td>
  *              <td align="center"><span class="fa-blind"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BLOG</code></td>
  *              <td align="center"><span class="fa-blog"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BOLD</code></td>
  *              <td align="center"><span class="fa-bold"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BOLT</code></td>
  *              <td align="center"><span class="fa-bolt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BOMB</code></td>
  *              <td align="center"><span class="fa-bomb"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BONE</code></td>
  *              <td align="center"><span class="fa-bone"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BONG</code></td>
  *              <td align="center"><span class="fa-bong"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BOOK</code></td>
  *              <td align="center"><span class="fa-book"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BOOK_DEAD</code></td>
  *              <td align="center"><span class="fa-book-dead"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BOOK_MEDICAL</code></td>
  *              <td align="center"><span class="fa-book-medical"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BOOK_OPEN</code></td>
  *              <td align="center"><span class="fa-book-open"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BOOK_READER</code></td>
  *              <td align="center"><span class="fa-book-reader"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BOOKMARK</code></td>
  *              <td align="center"><span class="fa-bookmark"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BORDER_ALL</code></td>
  *              <td align="center"><span class="fa-border-all"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BORDER_NONE</code></td>
  *              <td align="center"><span class="fa-border-none"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BORDER_STYLE</code></td>
  *              <td align="center"><span class="fa-border-style"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BOWLING_BALL</code></td>
  *              <td align="center"><span class="fa-bowling-ball"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BOX</code></td>
  *              <td align="center"><span class="fa-box"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BOX_OPEN</code></td>
  *              <td align="center"><span class="fa-box-open"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BOXES</code></td>
  *              <td align="center"><span class="fa-boxes"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BRAILLE</code></td>
  *              <td align="center"><span class="fa-braille"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BRAIN</code></td>
  *              <td align="center"><span class="fa-brain"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BREAD_SLICE</code></td>
  *              <td align="center"><span class="fa-bread-slice"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BRIEFCASE</code></td>
  *              <td align="center"><span class="fa-briefcase"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BRIEFCASE_MEDICAL</code></td>
  *              <td align="center"><span class="fa-briefcase-medical"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BROADCAST_TOWER</code></td>
  *              <td align="center"><span class="fa-broadcast-tower"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BROOM</code></td>
  *              <td align="center"><span class="fa-broom"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BRUSH</code></td>
  *              <td align="center"><span class="fa-brush"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BUG</code></td>
  *              <td align="center"><span class="fa-bug"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BUILDING</code></td>
  *              <td align="center"><span class="fa-building"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BULLHORN</code></td>
  *              <td align="center"><span class="fa-bullhorn"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BULLSEYE</code></td>
  *              <td align="center"><span class="fa-bullseye"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BURN</code></td>
  *              <td align="center"><span class="fa-burn"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BUS</code></td>
  *              <td align="center"><span class="fa-bus"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_BUS_ALT</code></td>
  *              <td align="center"><span class="fa-bus-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_BUSINESS_TIME</code></td>
  *              <td align="center"><span class="fa-business-time"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CALCULATOR</code></td>
  *              <td align="center"><span class="fa-calculator"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CALENDAR</code></td>
  *              <td align="center"><span class="fa-calendar"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CALENDAR_ALT</code></td>
  *              <td align="center"><span class="fa-calendar-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CALENDAR_CHECK</code></td>
  *              <td align="center"><span class="fa-calendar-check"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CALENDAR_DAY</code></td>
  *              <td align="center"><span class="fa-calendar-day"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CALENDAR_MINUS</code></td>
  *              <td align="center"><span class="fa-calendar-minus"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CALENDAR_PLUS</code></td>
  *              <td align="center"><span class="fa-calendar-plus"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CALENDAR_TIMES</code></td>
  *              <td align="center"><span class="fa-calendar-times"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CALENDAR_WEEK</code></td>
  *              <td align="center"><span class="fa-calendar-week"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CAMERA</code></td>
  *              <td align="center"><span class="fa-camera"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CAMERA_RETRO</code></td>
  *              <td align="center"><span class="fa-camera-retro"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CAMPGROUND</code></td>
  *              <td align="center"><span class="fa-campground"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CANDY_CANE</code></td>
  *              <td align="center"><span class="fa-candy-cane"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CANNABIS</code></td>
  *              <td align="center"><span class="fa-cannabis"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CAPSULES</code></td>
  *              <td align="center"><span class="fa-capsules"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CAR</code></td>
  *              <td align="center"><span class="fa-car"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CAR_ALT</code></td>
  *              <td align="center"><span class="fa-car-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CAR_BATTERY</code></td>
  *              <td align="center"><span class="fa-car-battery"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CAR_CRASH</code></td>
  *              <td align="center"><span class="fa-car-crash"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CAR_SIDE</code></td>
  *              <td align="center"><span class="fa-car-side"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CARET_DOWN</code></td>
  *              <td align="center"><span class="fa-caret-down"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CARET_LEFT</code></td>
  *              <td align="center"><span class="fa-caret-left"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CARET_RIGHT</code></td>
  *              <td align="center"><span class="fa-caret-right"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CARET_SQUARE_DOWN</code></td>
  *              <td align="center"><span class="fa-caret-square-down"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CARET_SQUARE_LEFT</code></td>
  *              <td align="center"><span class="fa-caret-square-left"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CARET_SQUARE_RIGHT</code></td>
  *              <td align="center"><span class="fa-caret-square-right"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CARET_SQUARE_UP</code></td>
  *              <td align="center"><span class="fa-caret-square-up"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CARET_UP</code></td>
  *              <td align="center"><span class="fa-caret-up"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CARROT</code></td>
  *              <td align="center"><span class="fa-carrot"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CART_ARROW_DOWN</code></td>
  *              <td align="center"><span class="fa-cart-arrow-down"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CART_PLUS</code></td>
  *              <td align="center"><span class="fa-cart-plus"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CASH_REGISTER</code></td>
  *              <td align="center"><span class="fa-cash-register"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CAT</code></td>
  *              <td align="center"><span class="fa-cat"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CERTIFICATE</code></td>
  *              <td align="center"><span class="fa-certificate"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CHAIR</code></td>
  *              <td align="center"><span class="fa-chair"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CHALKBOARD</code></td>
  *              <td align="center"><span class="fa-chalkboard"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CHALKBOARD_TEACHER</code></td>
  *              <td align="center"><span class="fa-chalkboard-teacher"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CHARGING_STATION</code></td>
  *              <td align="center"><span class="fa-charging-station"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CHART_AREA</code></td>
  *              <td align="center"><span class="fa-chart-area"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CHART_BAR</code></td>
  *              <td align="center"><span class="fa-chart-bar"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CHART_LINE</code></td>
  *              <td align="center"><span class="fa-chart-line"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CHART_PIE</code></td>
  *              <td align="center"><span class="fa-chart-pie"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CHECK</code></td>
  *              <td align="center"><span class="fa-check"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CHECK_CIRCLE</code></td>
  *              <td align="center"><span class="fa-check-circle"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CHECK_DOUBLE</code></td>
  *              <td align="center"><span class="fa-check-double"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CHECK_SQUARE</code></td>
  *              <td align="center"><span class="fa-check-square"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CHEESE</code></td>
  *              <td align="center"><span class="fa-cheese"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CHESS</code></td>
  *              <td align="center"><span class="fa-chess"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CHESS_BISHOP</code></td>
  *              <td align="center"><span class="fa-chess-bishop"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CHESS_BOARD</code></td>
  *              <td align="center"><span class="fa-chess-board"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CHESS_KING</code></td>
  *              <td align="center"><span class="fa-chess-king"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CHESS_KNIGHT</code></td>
  *              <td align="center"><span class="fa-chess-knight"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CHESS_PAWN</code></td>
  *              <td align="center"><span class="fa-chess-pawn"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CHESS_QUEEN</code></td>
  *              <td align="center"><span class="fa-chess-queen"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CHESS_ROOK</code></td>
  *              <td align="center"><span class="fa-chess-rook"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CHEVRON_CIRCLE_DOWN</code></td>
  *              <td align="center"><span class="fa-chevron-circle-down"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CHEVRON_CIRCLE_LEFT</code></td>
  *              <td align="center"><span class="fa-chevron-circle-left"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CHEVRON_CIRCLE_RIGHT</code></td>
  *              <td align="center"><span class="fa-chevron-circle-right"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CHEVRON_CIRCLE_UP</code></td>
  *              <td align="center"><span class="fa-chevron-circle-up"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CHEVRON_DOWN</code></td>
  *              <td align="center"><span class="fa-chevron-down"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CHEVRON_LEFT</code></td>
  *              <td align="center"><span class="fa-chevron-left"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CHEVRON_RIGHT</code></td>
  *              <td align="center"><span class="fa-chevron-right"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CHEVRON_UP</code></td>
  *              <td align="center"><span class="fa-chevron-up"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CHILD</code></td>
  *              <td align="center"><span class="fa-child"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CHURCH</code></td>
  *              <td align="center"><span class="fa-church"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CIRCLE</code></td>
  *              <td align="center"><span class="fa-circle"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CIRCLE_NOTCH</code></td>
  *              <td align="center"><span class="fa-circle-notch"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CITY</code></td>
  *              <td align="center"><span class="fa-city"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CLINIC_MEDICAL</code></td>
  *              <td align="center"><span class="fa-clinic-medical"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CLIPBOARD</code></td>
  *              <td align="center"><span class="fa-clipboard"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CLIPBOARD_CHECK</code></td>
  *              <td align="center"><span class="fa-clipboard-check"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CLIPBOARD_LIST</code></td>
  *              <td align="center"><span class="fa-clipboard-list"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CLOCK</code></td>
  *              <td align="center"><span class="fa-clock"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CLONE</code></td>
  *              <td align="center"><span class="fa-clone"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CLOSED_CAPTIONING</code></td>
  *              <td align="center"><span class="fa-closed-captioning"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CLOUD</code></td>
  *              <td align="center"><span class="fa-cloud"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CLOUD_DOWNLOAD_ALT</code></td>
  *              <td align="center"><span class="fa-cloud-download-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CLOUD_MEATBALL</code></td>
  *              <td align="center"><span class="fa-cloud-meatball"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CLOUD_MOON</code></td>
  *              <td align="center"><span class="fa-cloud-moon"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CLOUD_MOON_RAIN</code></td>
  *              <td align="center"><span class="fa-cloud-moon-rain"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CLOUD_RAIN</code></td>
  *              <td align="center"><span class="fa-cloud-rain"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CLOUD_SHOWERS_HEAVY</code></td>
  *              <td align="center"><span class="fa-cloud-showers-heavy"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CLOUD_SUN</code></td>
  *              <td align="center"><span class="fa-cloud-sun"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CLOUD_SUN_RAIN</code></td>
  *              <td align="center"><span class="fa-cloud-sun-rain"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CLOUD_UPLOAD_ALT</code></td>
  *              <td align="center"><span class="fa-cloud-upload-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_COCKTAIL</code></td>
  *              <td align="center"><span class="fa-cocktail"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CODE</code></td>
  *              <td align="center"><span class="fa-code"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CODE_BRANCH</code></td>
  *              <td align="center"><span class="fa-code-branch"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_COFFEE</code></td>
  *              <td align="center"><span class="fa-coffee"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_COG</code></td>
  *              <td align="center"><span class="fa-cog"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_COGS</code></td>
  *              <td align="center"><span class="fa-cogs"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_COINS</code></td>
  *              <td align="center"><span class="fa-coins"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_COLUMNS</code></td>
  *              <td align="center"><span class="fa-columns"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_COMMENT</code></td>
  *              <td align="center"><span class="fa-comment"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_COMMENT_ALT</code></td>
  *              <td align="center"><span class="fa-comment-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_COMMENT_DOLLAR</code></td>
  *              <td align="center"><span class="fa-comment-dollar"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_COMMENT_DOTS</code></td>
  *              <td align="center"><span class="fa-comment-dots"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_COMMENT_MEDICAL</code></td>
  *              <td align="center"><span class="fa-comment-medical"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_COMMENT_SLASH</code></td>
  *              <td align="center"><span class="fa-comment-slash"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_COMMENTS</code></td>
  *              <td align="center"><span class="fa-comments"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_COMMENTS_DOLLAR</code></td>
  *              <td align="center"><span class="fa-comments-dollar"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_COMPACT_DISC</code></td>
  *              <td align="center"><span class="fa-compact-disc"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_COMPASS</code></td>
  *              <td align="center"><span class="fa-compass"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_COMPRESS</code></td>
  *              <td align="center"><span class="fa-compress"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_COMPRESS_ARROWS_ALT</code></td>
  *              <td align="center"><span class="fa-compress-arrows-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CONCIERGE_BELL</code></td>
  *              <td align="center"><span class="fa-concierge-bell"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_COOKIE</code></td>
  *              <td align="center"><span class="fa-cookie"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_COOKIE_BITE</code></td>
  *              <td align="center"><span class="fa-cookie-bite"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_COPY</code></td>
  *              <td align="center"><span class="fa-copy"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_COPYRIGHT</code></td>
  *              <td align="center"><span class="fa-copyright"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_COUCH</code></td>
  *              <td align="center"><span class="fa-couch"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CREDIT_CARD</code></td>
  *              <td align="center"><span class="fa-credit-card"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CROP</code></td>
  *              <td align="center"><span class="fa-crop"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CROP_ALT</code></td>
  *              <td align="center"><span class="fa-crop-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CROSS</code></td>
  *              <td align="center"><span class="fa-cross"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CROSSHAIRS</code></td>
  *              <td align="center"><span class="fa-crosshairs"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CROW</code></td>
  *              <td align="center"><span class="fa-crow"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CROWN</code></td>
  *              <td align="center"><span class="fa-crown"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CRUTCH</code></td>
  *              <td align="center"><span class="fa-crutch"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CUBE</code></td>
  *              <td align="center"><span class="fa-cube"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_CUBES</code></td>
  *              <td align="center"><span class="fa-cubes"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_CUT</code></td>
  *              <td align="center"><span class="fa-cut"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_DATABASE</code></td>
  *              <td align="center"><span class="fa-database"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_DEAF</code></td>
  *              <td align="center"><span class="fa-deaf"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_DEMOCRAT</code></td>
  *              <td align="center"><span class="fa-democrat"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_DESKTOP</code></td>
  *              <td align="center"><span class="fa-desktop"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_DHARMACHAKRA</code></td>
  *              <td align="center"><span class="fa-dharmachakra"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_DIAGNOSES</code></td>
  *              <td align="center"><span class="fa-diagnoses"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_DICE</code></td>
  *              <td align="center"><span class="fa-dice"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_DICE_D20</code></td>
  *              <td align="center"><span class="fa-dice-d20"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_DICE_D6</code></td>
  *              <td align="center"><span class="fa-dice-d6"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_DICE_FIVE</code></td>
  *              <td align="center"><span class="fa-dice-five"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_DICE_FOUR</code></td>
  *              <td align="center"><span class="fa-dice-four"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_DICE_ONE</code></td>
  *              <td align="center"><span class="fa-dice-one"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_DICE_SIX</code></td>
  *              <td align="center"><span class="fa-dice-six"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_DICE_THREE</code></td>
  *              <td align="center"><span class="fa-dice-three"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_DICE_TWO</code></td>
  *              <td align="center"><span class="fa-dice-two"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_DIGITAL_TACHOGRAPH</code></td>
  *              <td align="center"><span class="fa-digital-tachograph"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_DIRECTIONS</code></td>
  *              <td align="center"><span class="fa-directions"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_DIVIDE</code></td>
  *              <td align="center"><span class="fa-divide"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_DIZZY</code></td>
  *              <td align="center"><span class="fa-dizzy"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_DNA</code></td>
  *              <td align="center"><span class="fa-dna"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_DOG</code></td>
  *              <td align="center"><span class="fa-dog"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_DOLLAR_SIGN</code></td>
  *              <td align="center"><span class="fa-dollar-sign"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_DOLLY</code></td>
  *              <td align="center"><span class="fa-dolly"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_DOLLY_FLATBED</code></td>
  *              <td align="center"><span class="fa-dolly-flatbed"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_DONATE</code></td>
  *              <td align="center"><span class="fa-donate"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_DOOR_CLOSED</code></td>
  *              <td align="center"><span class="fa-door-closed"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_DOOR_OPEN</code></td>
  *              <td align="center"><span class="fa-door-open"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_DOT_CIRCLE</code></td>
  *              <td align="center"><span class="fa-dot-circle"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_DOVE</code></td>
  *              <td align="center"><span class="fa-dove"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_DOWNLOAD</code></td>
  *              <td align="center"><span class="fa-download"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_DRAFTING_COMPASS</code></td>
  *              <td align="center"><span class="fa-drafting-compass"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_DRAGON</code></td>
  *              <td align="center"><span class="fa-dragon"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_DRAW_POLYGON</code></td>
  *              <td align="center"><span class="fa-draw-polygon"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_DRUM</code></td>
  *              <td align="center"><span class="fa-drum"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_DRUM_STEELPAN</code></td>
  *              <td align="center"><span class="fa-drum-steelpan"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_DRUMSTICK_BITE</code></td>
  *              <td align="center"><span class="fa-drumstick-bite"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_DUMBBELL</code></td>
  *              <td align="center"><span class="fa-dumbbell"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_DUMPSTER</code></td>
  *              <td align="center"><span class="fa-dumpster"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_DUMPSTER_FIRE</code></td>
  *              <td align="center"><span class="fa-dumpster-fire"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_DUNGEON</code></td>
  *              <td align="center"><span class="fa-dungeon"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_EDIT</code></td>
  *              <td align="center"><span class="fa-edit"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_EGG</code></td>
  *              <td align="center"><span class="fa-egg"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_EJECT</code></td>
  *              <td align="center"><span class="fa-eject"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ELLIPSIS_H</code></td>
  *              <td align="center"><span class="fa-ellipsis-h"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ELLIPSIS_V</code></td>
  *              <td align="center"><span class="fa-ellipsis-v"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ENVELOPE</code></td>
  *              <td align="center"><span class="fa-envelope"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ENVELOPE_OPEN</code></td>
  *              <td align="center"><span class="fa-envelope-open"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ENVELOPE_OPEN_TEXT</code></td>
  *              <td align="center"><span class="fa-envelope-open-text"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ENVELOPE_SQUARE</code></td>
  *              <td align="center"><span class="fa-envelope-square"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_EQUALS</code></td>
  *              <td align="center"><span class="fa-equals"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ERASER</code></td>
  *              <td align="center"><span class="fa-eraser"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ETHERNET</code></td>
  *              <td align="center"><span class="fa-ethernet"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_EURO_SIGN</code></td>
  *              <td align="center"><span class="fa-euro-sign"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_EXCHANGE_ALT</code></td>
  *              <td align="center"><span class="fa-exchange-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_EXCLAMATION</code></td>
  *              <td align="center"><span class="fa-exclamation"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_EXCLAMATION_CIRCLE</code></td>
  *              <td align="center"><span class="fa-exclamation-circle"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_EXCLAMATION_TRIANGLE</code></td>
  *              <td align="center"><span class="fa-exclamation-triangle"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_EXPAND</code></td>
  *              <td align="center"><span class="fa-expand"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_EXPAND_ARROWS_ALT</code></td>
  *              <td align="center"><span class="fa-expand-arrows-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_EXTERNAL_LINK_ALT</code></td>
  *              <td align="center"><span class="fa-external-link-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_EXTERNAL_LINK_SQUARE_ALT</code></td>
  *              <td align="center"><span class="fa-external-link-square-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_EYE</code></td>
  *              <td align="center"><span class="fa-eye"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_EYE_DROPPER</code></td>
  *              <td align="center"><span class="fa-eye-dropper"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_EYE_SLASH</code></td>
  *              <td align="center"><span class="fa-eye-slash"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FAN</code></td>
  *              <td align="center"><span class="fa-fan"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FAST_BACKWARD</code></td>
  *              <td align="center"><span class="fa-fast-backward"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FAST_FORWARD</code></td>
  *              <td align="center"><span class="fa-fast-forward"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FAX</code></td>
  *              <td align="center"><span class="fa-fax"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FEATHER</code></td>
  *              <td align="center"><span class="fa-feather"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FEATHER_ALT</code></td>
  *              <td align="center"><span class="fa-feather-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FEMALE</code></td>
  *              <td align="center"><span class="fa-female"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FIGHTER_JET</code></td>
  *              <td align="center"><span class="fa-fighter-jet"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FILE</code></td>
  *              <td align="center"><span class="fa-file"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FILE_ALT</code></td>
  *              <td align="center"><span class="fa-file-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FILE_ARCHIVE</code></td>
  *              <td align="center"><span class="fa-file-archive"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FILE_AUDIO</code></td>
  *              <td align="center"><span class="fa-file-audio"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FILE_CODE</code></td>
  *              <td align="center"><span class="fa-file-code"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FILE_CONTRACT</code></td>
  *              <td align="center"><span class="fa-file-contract"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FILE_CSV</code></td>
  *              <td align="center"><span class="fa-file-csv"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FILE_DOWNLOAD</code></td>
  *              <td align="center"><span class="fa-file-download"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FILE_EXCEL</code></td>
  *              <td align="center"><span class="fa-file-excel"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FILE_EXPORT</code></td>
  *              <td align="center"><span class="fa-file-export"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FILE_IMAGE</code></td>
  *              <td align="center"><span class="fa-file-image"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FILE_IMPORT</code></td>
  *              <td align="center"><span class="fa-file-import"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FILE_INVOICE</code></td>
  *              <td align="center"><span class="fa-file-invoice"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FILE_INVOICE_DOLLAR</code></td>
  *              <td align="center"><span class="fa-file-invoice-dollar"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FILE_MEDICAL</code></td>
  *              <td align="center"><span class="fa-file-medical"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FILE_MEDICAL_ALT</code></td>
  *              <td align="center"><span class="fa-file-medical-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FILE_PDF</code></td>
  *              <td align="center"><span class="fa-file-pdf"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FILE_POWERPOINT</code></td>
  *              <td align="center"><span class="fa-file-powerpoint"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FILE_PRESCRIPTION</code></td>
  *              <td align="center"><span class="fa-file-prescription"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FILE_SIGNATURE</code></td>
  *              <td align="center"><span class="fa-file-signature"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FILE_UPLOAD</code></td>
  *              <td align="center"><span class="fa-file-upload"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FILE_VIDEO</code></td>
  *              <td align="center"><span class="fa-file-video"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FILE_WORD</code></td>
  *              <td align="center"><span class="fa-file-word"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FILL</code></td>
  *              <td align="center"><span class="fa-fill"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FILL_DRIP</code></td>
  *              <td align="center"><span class="fa-fill-drip"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FILM</code></td>
  *              <td align="center"><span class="fa-film"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FILTER</code></td>
  *              <td align="center"><span class="fa-filter"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FINGERPRINT</code></td>
  *              <td align="center"><span class="fa-fingerprint"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FIRE</code></td>
  *              <td align="center"><span class="fa-fire"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FIRE_ALT</code></td>
  *              <td align="center"><span class="fa-fire-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FIRE_EXTINGUISHER</code></td>
  *              <td align="center"><span class="fa-fire-extinguisher"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FIRST_AID</code></td>
  *              <td align="center"><span class="fa-first-aid"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FISH</code></td>
  *              <td align="center"><span class="fa-fish"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FIST_RAISED</code></td>
  *              <td align="center"><span class="fa-fist-raised"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FLAG</code></td>
  *              <td align="center"><span class="fa-flag"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FLAG_CHECKERED</code></td>
  *              <td align="center"><span class="fa-flag-checkered"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FLAG_USA</code></td>
  *              <td align="center"><span class="fa-flag-usa"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FLASK</code></td>
  *              <td align="center"><span class="fa-flask"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FLUSHED</code></td>
  *              <td align="center"><span class="fa-flushed"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FOLDER</code></td>
  *              <td align="center"><span class="fa-folder"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FOLDER_MINUS</code></td>
  *              <td align="center"><span class="fa-folder-minus"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FOLDER_OPEN</code></td>
  *              <td align="center"><span class="fa-folder-open"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FOLDER_PLUS</code></td>
  *              <td align="center"><span class="fa-folder-plus"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FONT</code></td>
  *              <td align="center"><span class="fa-font"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FONT_AWESOME_LOGO_FULL</code></td>
  *              <td align="center"><span class="fa-font-awesome-logo-full"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FOOTBALL_BALL</code></td>
  *              <td align="center"><span class="fa-football-ball"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FORWARD</code></td>
  *              <td align="center"><span class="fa-forward"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FROG</code></td>
  *              <td align="center"><span class="fa-frog"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FROWN</code></td>
  *              <td align="center"><span class="fa-frown"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FROWN_OPEN</code></td>
  *              <td align="center"><span class="fa-frown-open"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_FUNNEL_DOLLAR</code></td>
  *              <td align="center"><span class="fa-funnel-dollar"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_FUTBOL</code></td>
  *              <td align="center"><span class="fa-futbol"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_GAMEPAD</code></td>
  *              <td align="center"><span class="fa-gamepad"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_GAS_PUMP</code></td>
  *              <td align="center"><span class="fa-gas-pump"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_GAVEL</code></td>
  *              <td align="center"><span class="fa-gavel"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_GEM</code></td>
  *              <td align="center"><span class="fa-gem"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_GENDERLESS</code></td>
  *              <td align="center"><span class="fa-genderless"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_GHOST</code></td>
  *              <td align="center"><span class="fa-ghost"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_GIFT</code></td>
  *              <td align="center"><span class="fa-gift"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_GIFTS</code></td>
  *              <td align="center"><span class="fa-gifts"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_GLASS_CHEERS</code></td>
  *              <td align="center"><span class="fa-glass-cheers"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_GLASS_MARTINI</code></td>
  *              <td align="center"><span class="fa-glass-martini"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_GLASS_MARTINI_ALT</code></td>
  *              <td align="center"><span class="fa-glass-martini-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_GLASS_WHISKEY</code></td>
  *              <td align="center"><span class="fa-glass-whiskey"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_GLASSES</code></td>
  *              <td align="center"><span class="fa-glasses"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_GLOBE</code></td>
  *              <td align="center"><span class="fa-globe"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_GLOBE_AFRICA</code></td>
  *              <td align="center"><span class="fa-globe-africa"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_GLOBE_AMERICAS</code></td>
  *              <td align="center"><span class="fa-globe-americas"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_GLOBE_ASIA</code></td>
  *              <td align="center"><span class="fa-globe-asia"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_GLOBE_EUROPE</code></td>
  *              <td align="center"><span class="fa-globe-europe"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_GOLF_BALL</code></td>
  *              <td align="center"><span class="fa-golf-ball"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_GOPURAM</code></td>
  *              <td align="center"><span class="fa-gopuram"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_GRADUATION_CAP</code></td>
  *              <td align="center"><span class="fa-graduation-cap"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_GREATER_THAN</code></td>
  *              <td align="center"><span class="fa-greater-than"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_GREATER_THAN_EQUAL</code></td>
  *              <td align="center"><span class="fa-greater-than-equal"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_GRIMACE</code></td>
  *              <td align="center"><span class="fa-grimace"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_GRIN</code></td>
  *              <td align="center"><span class="fa-grin"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_GRIN_ALT</code></td>
  *              <td align="center"><span class="fa-grin-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_GRIN_BEAM</code></td>
  *              <td align="center"><span class="fa-grin-beam"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_GRIN_BEAM_SWEAT</code></td>
  *              <td align="center"><span class="fa-grin-beam-sweat"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_GRIN_HEARTS</code></td>
  *              <td align="center"><span class="fa-grin-hearts"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_GRIN_SQUINT</code></td>
  *              <td align="center"><span class="fa-grin-squint"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_GRIN_SQUINT_TEARS</code></td>
  *              <td align="center"><span class="fa-grin-squint-tears"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_GRIN_STARS</code></td>
  *              <td align="center"><span class="fa-grin-stars"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_GRIN_TEARS</code></td>
  *              <td align="center"><span class="fa-grin-tears"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_GRIN_TONGUE</code></td>
  *              <td align="center"><span class="fa-grin-tongue"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_GRIN_TONGUE_SQUINT</code></td>
  *              <td align="center"><span class="fa-grin-tongue-squint"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_GRIN_TONGUE_WINK</code></td>
  *              <td align="center"><span class="fa-grin-tongue-wink"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_GRIN_WINK</code></td>
  *              <td align="center"><span class="fa-grin-wink"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_GRIP_HORIZONTAL</code></td>
  *              <td align="center"><span class="fa-grip-horizontal"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_GRIP_LINES</code></td>
  *              <td align="center"><span class="fa-grip-lines"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_GRIP_LINES_VERTICAL</code></td>
  *              <td align="center"><span class="fa-grip-lines-vertical"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_GRIP_VERTICAL</code></td>
  *              <td align="center"><span class="fa-grip-vertical"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_GUITAR</code></td>
  *              <td align="center"><span class="fa-guitar"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_H_SQUARE</code></td>
  *              <td align="center"><span class="fa-h-square"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HAMBURGER</code></td>
  *              <td align="center"><span class="fa-hamburger"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HAMMER</code></td>
  *              <td align="center"><span class="fa-hammer"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HAMSA</code></td>
  *              <td align="center"><span class="fa-hamsa"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HAND_HOLDING</code></td>
  *              <td align="center"><span class="fa-hand-holding"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HAND_HOLDING_HEART</code></td>
  *              <td align="center"><span class="fa-hand-holding-heart"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HAND_HOLDING_USD</code></td>
  *              <td align="center"><span class="fa-hand-holding-usd"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HAND_LIZARD</code></td>
  *              <td align="center"><span class="fa-hand-lizard"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HAND_MIDDLE_FINGER</code></td>
  *              <td align="center"><span class="fa-hand-middle-finger"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HAND_PAPER</code></td>
  *              <td align="center"><span class="fa-hand-paper"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HAND_PEACE</code></td>
  *              <td align="center"><span class="fa-hand-peace"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HAND_POINT_DOWN</code></td>
  *              <td align="center"><span class="fa-hand-point-down"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HAND_POINT_LEFT</code></td>
  *              <td align="center"><span class="fa-hand-point-left"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HAND_POINT_RIGHT</code></td>
  *              <td align="center"><span class="fa-hand-point-right"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HAND_POINT_UP</code></td>
  *              <td align="center"><span class="fa-hand-point-up"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HAND_POINTER</code></td>
  *              <td align="center"><span class="fa-hand-pointer"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HAND_ROCK</code></td>
  *              <td align="center"><span class="fa-hand-rock"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HAND_SCISSORS</code></td>
  *              <td align="center"><span class="fa-hand-scissors"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HAND_SPOCK</code></td>
  *              <td align="center"><span class="fa-hand-spock"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HANDS</code></td>
  *              <td align="center"><span class="fa-hands"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HANDS_HELPING</code></td>
  *              <td align="center"><span class="fa-hands-helping"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HANDSHAKE</code></td>
  *              <td align="center"><span class="fa-handshake"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HANUKIAH</code></td>
  *              <td align="center"><span class="fa-hanukiah"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HARD_HAT</code></td>
  *              <td align="center"><span class="fa-hard-hat"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HASHTAG</code></td>
  *              <td align="center"><span class="fa-hashtag"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HAT_WIZARD</code></td>
  *              <td align="center"><span class="fa-hat-wizard"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HAYKAL</code></td>
  *              <td align="center"><span class="fa-haykal"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HDD</code></td>
  *              <td align="center"><span class="fa-hdd"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HEADING</code></td>
  *              <td align="center"><span class="fa-heading"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HEADPHONES</code></td>
  *              <td align="center"><span class="fa-headphones"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HEADPHONES_ALT</code></td>
  *              <td align="center"><span class="fa-headphones-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HEADSET</code></td>
  *              <td align="center"><span class="fa-headset"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HEART</code></td>
  *              <td align="center"><span class="fa-heart"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HEART_BROKEN</code></td>
  *              <td align="center"><span class="fa-heart-broken"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HEARTBEAT</code></td>
  *              <td align="center"><span class="fa-heartbeat"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HELICOPTER</code></td>
  *              <td align="center"><span class="fa-helicopter"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HIGHLIGHTER</code></td>
  *              <td align="center"><span class="fa-highlighter"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HIKING</code></td>
  *              <td align="center"><span class="fa-hiking"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HIPPO</code></td>
  *              <td align="center"><span class="fa-hippo"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HISTORY</code></td>
  *              <td align="center"><span class="fa-history"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HOCKEY_PUCK</code></td>
  *              <td align="center"><span class="fa-hockey-puck"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HOLLY_BERRY</code></td>
  *              <td align="center"><span class="fa-holly-berry"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HOME</code></td>
  *              <td align="center"><span class="fa-home"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HORSE</code></td>
  *              <td align="center"><span class="fa-horse"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HORSE_HEAD</code></td>
  *              <td align="center"><span class="fa-horse-head"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HOSPITAL</code></td>
  *              <td align="center"><span class="fa-hospital"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HOSPITAL_ALT</code></td>
  *              <td align="center"><span class="fa-hospital-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HOSPITAL_SYMBOL</code></td>
  *              <td align="center"><span class="fa-hospital-symbol"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HOT_TUB</code></td>
  *              <td align="center"><span class="fa-hot-tub"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HOTDOG</code></td>
  *              <td align="center"><span class="fa-hotdog"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HOTEL</code></td>
  *              <td align="center"><span class="fa-hotel"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HOURGLASS</code></td>
  *              <td align="center"><span class="fa-hourglass"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HOURGLASS_END</code></td>
  *              <td align="center"><span class="fa-hourglass-end"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HOURGLASS_HALF</code></td>
  *              <td align="center"><span class="fa-hourglass-half"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HOURGLASS_START</code></td>
  *              <td align="center"><span class="fa-hourglass-start"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_HOUSE_DAMAGE</code></td>
  *              <td align="center"><span class="fa-house-damage"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_HRYVNIA</code></td>
  *              <td align="center"><span class="fa-hryvnia"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_I_CURSOR</code></td>
  *              <td align="center"><span class="fa-i-cursor"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ICE_CREAM</code></td>
  *              <td align="center"><span class="fa-ice-cream"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ICICLES</code></td>
  *              <td align="center"><span class="fa-icicles"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ICONS</code></td>
  *              <td align="center"><span class="fa-icons"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ID_BADGE</code></td>
  *              <td align="center"><span class="fa-id-badge"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ID_CARD</code></td>
  *              <td align="center"><span class="fa-id-card"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ID_CARD_ALT</code></td>
  *              <td align="center"><span class="fa-id-card-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_IGLOO</code></td>
  *              <td align="center"><span class="fa-igloo"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_IMAGE</code></td>
  *              <td align="center"><span class="fa-image"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_IMAGES</code></td>
  *              <td align="center"><span class="fa-images"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_INBOX</code></td>
  *              <td align="center"><span class="fa-inbox"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_INDENT</code></td>
  *              <td align="center"><span class="fa-indent"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_INDUSTRY</code></td>
  *              <td align="center"><span class="fa-industry"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_INFINITY</code></td>
  *              <td align="center"><span class="fa-infinity"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_INFO</code></td>
  *              <td align="center"><span class="fa-info"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_INFO_CIRCLE</code></td>
  *              <td align="center"><span class="fa-info-circle"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ITALIC</code></td>
  *              <td align="center"><span class="fa-italic"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_JEDI</code></td>
  *              <td align="center"><span class="fa-jedi"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_JOINT</code></td>
  *              <td align="center"><span class="fa-joint"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_JOURNAL_WHILLS</code></td>
  *              <td align="center"><span class="fa-journal-whills"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_KAABA</code></td>
  *              <td align="center"><span class="fa-kaaba"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_KEY</code></td>
  *              <td align="center"><span class="fa-key"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_KEYBOARD</code></td>
  *              <td align="center"><span class="fa-keyboard"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_KHANDA</code></td>
  *              <td align="center"><span class="fa-khanda"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_KISS</code></td>
  *              <td align="center"><span class="fa-kiss"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_KISS_BEAM</code></td>
  *              <td align="center"><span class="fa-kiss-beam"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_KISS_WINK_HEART</code></td>
  *              <td align="center"><span class="fa-kiss-wink-heart"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_KIWI_BIRD</code></td>
  *              <td align="center"><span class="fa-kiwi-bird"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_LANDMARK</code></td>
  *              <td align="center"><span class="fa-landmark"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_LANGUAGE</code></td>
  *              <td align="center"><span class="fa-language"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_LAPTOP</code></td>
  *              <td align="center"><span class="fa-laptop"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_LAPTOP_CODE</code></td>
  *              <td align="center"><span class="fa-laptop-code"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_LAPTOP_MEDICAL</code></td>
  *              <td align="center"><span class="fa-laptop-medical"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_LAUGH</code></td>
  *              <td align="center"><span class="fa-laugh"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_LAUGH_BEAM</code></td>
  *              <td align="center"><span class="fa-laugh-beam"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_LAUGH_SQUINT</code></td>
  *              <td align="center"><span class="fa-laugh-squint"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_LAUGH_WINK</code></td>
  *              <td align="center"><span class="fa-laugh-wink"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_LAYER_GROUP</code></td>
  *              <td align="center"><span class="fa-layer-group"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_LEAF</code></td>
  *              <td align="center"><span class="fa-leaf"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_LEMON</code></td>
  *              <td align="center"><span class="fa-lemon"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_LESS_THAN</code></td>
  *              <td align="center"><span class="fa-less-than"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_LESS_THAN_EQUAL</code></td>
  *              <td align="center"><span class="fa-less-than-equal"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_LEVEL_DOWN_ALT</code></td>
  *              <td align="center"><span class="fa-level-down-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_LEVEL_UP_ALT</code></td>
  *              <td align="center"><span class="fa-level-up-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_LIFE_RING</code></td>
  *              <td align="center"><span class="fa-life-ring"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_LIGHTBULB</code></td>
  *              <td align="center"><span class="fa-lightbulb"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_LINK</code></td>
  *              <td align="center"><span class="fa-link"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_LIRA_SIGN</code></td>
  *              <td align="center"><span class="fa-lira-sign"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_LIST</code></td>
  *              <td align="center"><span class="fa-list"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_LIST_ALT</code></td>
  *              <td align="center"><span class="fa-list-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_LIST_OL</code></td>
  *              <td align="center"><span class="fa-list-ol"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_LIST_UL</code></td>
  *              <td align="center"><span class="fa-list-ul"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_LOCATION_ARROW</code></td>
  *              <td align="center"><span class="fa-location-arrow"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_LOCK</code></td>
  *              <td align="center"><span class="fa-lock"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_LOCK_OPEN</code></td>
  *              <td align="center"><span class="fa-lock-open"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_LONG_ARROW_ALT_DOWN</code></td>
  *              <td align="center"><span class="fa-long-arrow-alt-down"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_LONG_ARROW_ALT_LEFT</code></td>
  *              <td align="center"><span class="fa-long-arrow-alt-left"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_LONG_ARROW_ALT_RIGHT</code></td>
  *              <td align="center"><span class="fa-long-arrow-alt-right"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_LONG_ARROW_ALT_UP</code></td>
  *              <td align="center"><span class="fa-long-arrow-alt-up"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_LOW_VISION</code></td>
  *              <td align="center"><span class="fa-low-vision"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_LUGGAGE_CART</code></td>
  *              <td align="center"><span class="fa-luggage-cart"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MAGIC</code></td>
  *              <td align="center"><span class="fa-magic"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MAGNET</code></td>
  *              <td align="center"><span class="fa-magnet"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MAIL_BULK</code></td>
  *              <td align="center"><span class="fa-mail-bulk"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MALE</code></td>
  *              <td align="center"><span class="fa-male"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MAP</code></td>
  *              <td align="center"><span class="fa-map"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MAP_MARKED</code></td>
  *              <td align="center"><span class="fa-map-marked"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MAP_MARKED_ALT</code></td>
  *              <td align="center"><span class="fa-map-marked-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MAP_MARKER</code></td>
  *              <td align="center"><span class="fa-map-marker"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MAP_MARKER_ALT</code></td>
  *              <td align="center"><span class="fa-map-marker-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MAP_PIN</code></td>
  *              <td align="center"><span class="fa-map-pin"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MAP_SIGNS</code></td>
  *              <td align="center"><span class="fa-map-signs"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MARKER</code></td>
  *              <td align="center"><span class="fa-marker"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MARS</code></td>
  *              <td align="center"><span class="fa-mars"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MARS_DOUBLE</code></td>
  *              <td align="center"><span class="fa-mars-double"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MARS_STROKE</code></td>
  *              <td align="center"><span class="fa-mars-stroke"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MARS_STROKE_H</code></td>
  *              <td align="center"><span class="fa-mars-stroke-h"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MARS_STROKE_V</code></td>
  *              <td align="center"><span class="fa-mars-stroke-v"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MASK</code></td>
  *              <td align="center"><span class="fa-mask"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MEDAL</code></td>
  *              <td align="center"><span class="fa-medal"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MEDKIT</code></td>
  *              <td align="center"><span class="fa-medkit"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MEH</code></td>
  *              <td align="center"><span class="fa-meh"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MEH_BLANK</code></td>
  *              <td align="center"><span class="fa-meh-blank"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MEH_ROLLING_EYES</code></td>
  *              <td align="center"><span class="fa-meh-rolling-eyes"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MEMORY</code></td>
  *              <td align="center"><span class="fa-memory"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MENORAH</code></td>
  *              <td align="center"><span class="fa-menorah"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MERCURY</code></td>
  *              <td align="center"><span class="fa-mercury"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_METEOR</code></td>
  *              <td align="center"><span class="fa-meteor"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MICROCHIP</code></td>
  *              <td align="center"><span class="fa-microchip"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MICROPHONE</code></td>
  *              <td align="center"><span class="fa-microphone"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MICROPHONE_ALT</code></td>
  *              <td align="center"><span class="fa-microphone-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MICROPHONE_ALT_SLASH</code></td>
  *              <td align="center"><span class="fa-microphone-alt-slash"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MICROPHONE_SLASH</code></td>
  *              <td align="center"><span class="fa-microphone-slash"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MICROSCOPE</code></td>
  *              <td align="center"><span class="fa-microscope"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MINUS</code></td>
  *              <td align="center"><span class="fa-minus"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MINUS_CIRCLE</code></td>
  *              <td align="center"><span class="fa-minus-circle"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MINUS_SQUARE</code></td>
  *              <td align="center"><span class="fa-minus-square"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MITTEN</code></td>
  *              <td align="center"><span class="fa-mitten"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MOBILE</code></td>
  *              <td align="center"><span class="fa-mobile"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MOBILE_ALT</code></td>
  *              <td align="center"><span class="fa-mobile-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MONEY_BILL</code></td>
  *              <td align="center"><span class="fa-money-bill"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MONEY_BILL_ALT</code></td>
  *              <td align="center"><span class="fa-money-bill-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MONEY_BILL_WAVE</code></td>
  *              <td align="center"><span class="fa-money-bill-wave"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MONEY_BILL_WAVE_ALT</code></td>
  *              <td align="center"><span class="fa-money-bill-wave-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MONEY_CHECK</code></td>
  *              <td align="center"><span class="fa-money-check"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MONEY_CHECK_ALT</code></td>
  *              <td align="center"><span class="fa-money-check-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MONUMENT</code></td>
  *              <td align="center"><span class="fa-monument"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MOON</code></td>
  *              <td align="center"><span class="fa-moon"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MORTAR_PESTLE</code></td>
  *              <td align="center"><span class="fa-mortar-pestle"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MOSQUE</code></td>
  *              <td align="center"><span class="fa-mosque"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MOTORCYCLE</code></td>
  *              <td align="center"><span class="fa-motorcycle"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MOUNTAIN</code></td>
  *              <td align="center"><span class="fa-mountain"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MOUSE_POINTER</code></td>
  *              <td align="center"><span class="fa-mouse-pointer"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_MUG_HOT</code></td>
  *              <td align="center"><span class="fa-mug-hot"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_MUSIC</code></td>
  *              <td align="center"><span class="fa-music"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_NETWORK_WIRED</code></td>
  *              <td align="center"><span class="fa-network-wired"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_NEUTER</code></td>
  *              <td align="center"><span class="fa-neuter"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_NEWSPAPER</code></td>
  *              <td align="center"><span class="fa-newspaper"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_NOT_EQUAL</code></td>
  *              <td align="center"><span class="fa-not-equal"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_NOTES_MEDICAL</code></td>
  *              <td align="center"><span class="fa-notes-medical"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_OBJECT_GROUP</code></td>
  *              <td align="center"><span class="fa-object-group"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_OBJECT_UNGROUP</code></td>
  *              <td align="center"><span class="fa-object-ungroup"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_OIL_CAN</code></td>
  *              <td align="center"><span class="fa-oil-can"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_OM</code></td>
  *              <td align="center"><span class="fa-om"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_OTTER</code></td>
  *              <td align="center"><span class="fa-otter"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_OUTDENT</code></td>
  *              <td align="center"><span class="fa-outdent"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PAGER</code></td>
  *              <td align="center"><span class="fa-pager"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PAINT_BRUSH</code></td>
  *              <td align="center"><span class="fa-paint-brush"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PAINT_ROLLER</code></td>
  *              <td align="center"><span class="fa-paint-roller"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PALETTE</code></td>
  *              <td align="center"><span class="fa-palette"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PALLET</code></td>
  *              <td align="center"><span class="fa-pallet"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PAPER_PLANE</code></td>
  *              <td align="center"><span class="fa-paper-plane"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PAPERCLIP</code></td>
  *              <td align="center"><span class="fa-paperclip"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PARACHUTE_BOX</code></td>
  *              <td align="center"><span class="fa-parachute-box"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PARAGRAPH</code></td>
  *              <td align="center"><span class="fa-paragraph"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PARKING</code></td>
  *              <td align="center"><span class="fa-parking"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PASSPORT</code></td>
  *              <td align="center"><span class="fa-passport"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PASTAFARIANISM</code></td>
  *              <td align="center"><span class="fa-pastafarianism"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PASTE</code></td>
  *              <td align="center"><span class="fa-paste"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PAUSE</code></td>
  *              <td align="center"><span class="fa-pause"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PAUSE_CIRCLE</code></td>
  *              <td align="center"><span class="fa-pause-circle"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PAW</code></td>
  *              <td align="center"><span class="fa-paw"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PEACE</code></td>
  *              <td align="center"><span class="fa-peace"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PEN</code></td>
  *              <td align="center"><span class="fa-pen"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PEN_ALT</code></td>
  *              <td align="center"><span class="fa-pen-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PEN_FANCY</code></td>
  *              <td align="center"><span class="fa-pen-fancy"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PEN_NIB</code></td>
  *              <td align="center"><span class="fa-pen-nib"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PEN_SQUARE</code></td>
  *              <td align="center"><span class="fa-pen-square"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PENCIL_ALT</code></td>
  *              <td align="center"><span class="fa-pencil-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PENCIL_RULER</code></td>
  *              <td align="center"><span class="fa-pencil-ruler"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PEOPLE_CARRY</code></td>
  *              <td align="center"><span class="fa-people-carry"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PEPPER_HOT</code></td>
  *              <td align="center"><span class="fa-pepper-hot"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PERCENT</code></td>
  *              <td align="center"><span class="fa-percent"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PERCENTAGE</code></td>
  *              <td align="center"><span class="fa-percentage"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PERSON_BOOTH</code></td>
  *              <td align="center"><span class="fa-person-booth"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PHONE</code></td>
  *              <td align="center"><span class="fa-phone"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PHONE_ALT</code></td>
  *              <td align="center"><span class="fa-phone-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PHONE_SLASH</code></td>
  *              <td align="center"><span class="fa-phone-slash"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PHONE_SQUARE</code></td>
  *              <td align="center"><span class="fa-phone-square"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PHONE_SQUARE_ALT</code></td>
  *              <td align="center"><span class="fa-phone-square-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PHONE_VOLUME</code></td>
  *              <td align="center"><span class="fa-phone-volume"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PHOTO_VIDEO</code></td>
  *              <td align="center"><span class="fa-photo-video"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PIGGY_BANK</code></td>
  *              <td align="center"><span class="fa-piggy-bank"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PILLS</code></td>
  *              <td align="center"><span class="fa-pills"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PIZZA_SLICE</code></td>
  *              <td align="center"><span class="fa-pizza-slice"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PLACE_OF_WORSHIP</code></td>
  *              <td align="center"><span class="fa-place-of-worship"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PLANE</code></td>
  *              <td align="center"><span class="fa-plane"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PLANE_ARRIVAL</code></td>
  *              <td align="center"><span class="fa-plane-arrival"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PLANE_DEPARTURE</code></td>
  *              <td align="center"><span class="fa-plane-departure"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PLAY</code></td>
  *              <td align="center"><span class="fa-play"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PLAY_CIRCLE</code></td>
  *              <td align="center"><span class="fa-play-circle"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PLUG</code></td>
  *              <td align="center"><span class="fa-plug"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PLUS</code></td>
  *              <td align="center"><span class="fa-plus"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PLUS_CIRCLE</code></td>
  *              <td align="center"><span class="fa-plus-circle"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PLUS_SQUARE</code></td>
  *              <td align="center"><span class="fa-plus-square"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PODCAST</code></td>
  *              <td align="center"><span class="fa-podcast"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_POLL</code></td>
  *              <td align="center"><span class="fa-poll"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_POLL_H</code></td>
  *              <td align="center"><span class="fa-poll-h"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_POO</code></td>
  *              <td align="center"><span class="fa-poo"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_POO_STORM</code></td>
  *              <td align="center"><span class="fa-poo-storm"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_POOP</code></td>
  *              <td align="center"><span class="fa-poop"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PORTRAIT</code></td>
  *              <td align="center"><span class="fa-portrait"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_POUND_SIGN</code></td>
  *              <td align="center"><span class="fa-pound-sign"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_POWER_OFF</code></td>
  *              <td align="center"><span class="fa-power-off"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PRAY</code></td>
  *              <td align="center"><span class="fa-pray"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PRAYING_HANDS</code></td>
  *              <td align="center"><span class="fa-praying-hands"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PRESCRIPTION</code></td>
  *              <td align="center"><span class="fa-prescription"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PRESCRIPTION_BOTTLE</code></td>
  *              <td align="center"><span class="fa-prescription-bottle"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PRESCRIPTION_BOTTLE_ALT</code></td>
  *              <td align="center"><span class="fa-prescription-bottle-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PRINT</code></td>
  *              <td align="center"><span class="fa-print"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PROCEDURES</code></td>
  *              <td align="center"><span class="fa-procedures"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_PROJECT_DIAGRAM</code></td>
  *              <td align="center"><span class="fa-project-diagram"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_PUZZLE_PIECE</code></td>
  *              <td align="center"><span class="fa-puzzle-piece"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_QRCODE</code></td>
  *              <td align="center"><span class="fa-qrcode"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_QUESTION</code></td>
  *              <td align="center"><span class="fa-question"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_QUESTION_CIRCLE</code></td>
  *              <td align="center"><span class="fa-question-circle"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_QUIDDITCH</code></td>
  *              <td align="center"><span class="fa-quidditch"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_QUOTE_LEFT</code></td>
  *              <td align="center"><span class="fa-quote-left"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_QUOTE_RIGHT</code></td>
  *              <td align="center"><span class="fa-quote-right"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_QURAN</code></td>
  *              <td align="center"><span class="fa-quran"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_RADIATION</code></td>
  *              <td align="center"><span class="fa-radiation"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_RADIATION_ALT</code></td>
  *              <td align="center"><span class="fa-radiation-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_RAINBOW</code></td>
  *              <td align="center"><span class="fa-rainbow"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_RANDOM</code></td>
  *              <td align="center"><span class="fa-random"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_RECEIPT</code></td>
  *              <td align="center"><span class="fa-receipt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_RECYCLE</code></td>
  *              <td align="center"><span class="fa-recycle"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_REDO</code></td>
  *              <td align="center"><span class="fa-redo"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_REDO_ALT</code></td>
  *              <td align="center"><span class="fa-redo-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_REGISTERED</code></td>
  *              <td align="center"><span class="fa-registered"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_REMOVE_FORMAT</code></td>
  *              <td align="center"><span class="fa-remove-format"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_REPLY</code></td>
  *              <td align="center"><span class="fa-reply"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_REPLY_ALL</code></td>
  *              <td align="center"><span class="fa-reply-all"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_REPUBLICAN</code></td>
  *              <td align="center"><span class="fa-republican"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_RESTROOM</code></td>
  *              <td align="center"><span class="fa-restroom"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_RETWEET</code></td>
  *              <td align="center"><span class="fa-retweet"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_RIBBON</code></td>
  *              <td align="center"><span class="fa-ribbon"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_RING</code></td>
  *              <td align="center"><span class="fa-ring"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ROAD</code></td>
  *              <td align="center"><span class="fa-road"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ROBOT</code></td>
  *              <td align="center"><span class="fa-robot"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_ROCKET</code></td>
  *              <td align="center"><span class="fa-rocket"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_ROUTE</code></td>
  *              <td align="center"><span class="fa-route"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_RSS</code></td>
  *              <td align="center"><span class="fa-rss"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_RSS_SQUARE</code></td>
  *              <td align="center"><span class="fa-rss-square"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_RUBLE_SIGN</code></td>
  *              <td align="center"><span class="fa-ruble-sign"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_RULER</code></td>
  *              <td align="center"><span class="fa-ruler"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_RULER_COMBINED</code></td>
  *              <td align="center"><span class="fa-ruler-combined"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_RULER_HORIZONTAL</code></td>
  *              <td align="center"><span class="fa-ruler-horizontal"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_RULER_VERTICAL</code></td>
  *              <td align="center"><span class="fa-ruler-vertical"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_RUNNING</code></td>
  *              <td align="center"><span class="fa-running"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_RUPEE_SIGN</code></td>
  *              <td align="center"><span class="fa-rupee-sign"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SAD_CRY</code></td>
  *              <td align="center"><span class="fa-sad-cry"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SAD_TEAR</code></td>
  *              <td align="center"><span class="fa-sad-tear"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SATELLITE</code></td>
  *              <td align="center"><span class="fa-satellite"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SATELLITE_DISH</code></td>
  *              <td align="center"><span class="fa-satellite-dish"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SAVE</code></td>
  *              <td align="center"><span class="fa-save"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SCHOOL</code></td>
  *              <td align="center"><span class="fa-school"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SCREWDRIVER</code></td>
  *              <td align="center"><span class="fa-screwdriver"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SCROLL</code></td>
  *              <td align="center"><span class="fa-scroll"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SD_CARD</code></td>
  *              <td align="center"><span class="fa-sd-card"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SEARCH</code></td>
  *              <td align="center"><span class="fa-search"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SEARCH_DOLLAR</code></td>
  *              <td align="center"><span class="fa-search-dollar"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SEARCH_LOCATION</code></td>
  *              <td align="center"><span class="fa-search-location"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SEARCH_MINUS</code></td>
  *              <td align="center"><span class="fa-search-minus"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SEARCH_PLUS</code></td>
  *              <td align="center"><span class="fa-search-plus"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SEEDLING</code></td>
  *              <td align="center"><span class="fa-seedling"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SERVER</code></td>
  *              <td align="center"><span class="fa-server"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SHAPES</code></td>
  *              <td align="center"><span class="fa-shapes"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SHARE</code></td>
  *              <td align="center"><span class="fa-share"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SHARE_ALT</code></td>
  *              <td align="center"><span class="fa-share-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SHARE_ALT_SQUARE</code></td>
  *              <td align="center"><span class="fa-share-alt-square"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SHARE_SQUARE</code></td>
  *              <td align="center"><span class="fa-share-square"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SHEKEL_SIGN</code></td>
  *              <td align="center"><span class="fa-shekel-sign"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SHIELD_ALT</code></td>
  *              <td align="center"><span class="fa-shield-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SHIP</code></td>
  *              <td align="center"><span class="fa-ship"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SHIPPING_FAST</code></td>
  *              <td align="center"><span class="fa-shipping-fast"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SHOE_PRINTS</code></td>
  *              <td align="center"><span class="fa-shoe-prints"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SHOPPING_BAG</code></td>
  *              <td align="center"><span class="fa-shopping-bag"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SHOPPING_BASKET</code></td>
  *              <td align="center"><span class="fa-shopping-basket"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SHOPPING_CART</code></td>
  *              <td align="center"><span class="fa-shopping-cart"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SHOWER</code></td>
  *              <td align="center"><span class="fa-shower"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SHUTTLE_VAN</code></td>
  *              <td align="center"><span class="fa-shuttle-van"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SIGN</code></td>
  *              <td align="center"><span class="fa-sign"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SIGN_IN_ALT</code></td>
  *              <td align="center"><span class="fa-sign-in-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SIGN_LANGUAGE</code></td>
  *              <td align="center"><span class="fa-sign-language"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SIGN_OUT_ALT</code></td>
  *              <td align="center"><span class="fa-sign-out-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SIGNAL</code></td>
  *              <td align="center"><span class="fa-signal"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SIGNATURE</code></td>
  *              <td align="center"><span class="fa-signature"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SIM_CARD</code></td>
  *              <td align="center"><span class="fa-sim-card"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SITEMAP</code></td>
  *              <td align="center"><span class="fa-sitemap"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SKATING</code></td>
  *              <td align="center"><span class="fa-skating"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SKIING</code></td>
  *              <td align="center"><span class="fa-skiing"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SKIING_NORDIC</code></td>
  *              <td align="center"><span class="fa-skiing-nordic"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SKULL</code></td>
  *              <td align="center"><span class="fa-skull"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SKULL_CROSSBONES</code></td>
  *              <td align="center"><span class="fa-skull-crossbones"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SLASH</code></td>
  *              <td align="center"><span class="fa-slash"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SLEIGH</code></td>
  *              <td align="center"><span class="fa-sleigh"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SLIDERS_H</code></td>
  *              <td align="center"><span class="fa-sliders-h"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SMILE</code></td>
  *              <td align="center"><span class="fa-smile"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SMILE_BEAM</code></td>
  *              <td align="center"><span class="fa-smile-beam"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SMILE_WINK</code></td>
  *              <td align="center"><span class="fa-smile-wink"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SMOG</code></td>
  *              <td align="center"><span class="fa-smog"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SMOKING</code></td>
  *              <td align="center"><span class="fa-smoking"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SMOKING_BAN</code></td>
  *              <td align="center"><span class="fa-smoking-ban"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SMS</code></td>
  *              <td align="center"><span class="fa-sms"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SNOWBOARDING</code></td>
  *              <td align="center"><span class="fa-snowboarding"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SNOWFLAKE</code></td>
  *              <td align="center"><span class="fa-snowflake"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SNOWMAN</code></td>
  *              <td align="center"><span class="fa-snowman"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SNOWPLOW</code></td>
  *              <td align="center"><span class="fa-snowplow"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SOCKS</code></td>
  *              <td align="center"><span class="fa-socks"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SOLAR_PANEL</code></td>
  *              <td align="center"><span class="fa-solar-panel"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SORT</code></td>
  *              <td align="center"><span class="fa-sort"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SORT_ALPHA_DOWN</code></td>
  *              <td align="center"><span class="fa-sort-alpha-down"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SORT_ALPHA_DOWN_ALT</code></td>
  *              <td align="center"><span class="fa-sort-alpha-down-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SORT_ALPHA_UP</code></td>
  *              <td align="center"><span class="fa-sort-alpha-up"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SORT_ALPHA_UP_ALT</code></td>
  *              <td align="center"><span class="fa-sort-alpha-up-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SORT_AMOUNT_DOWN</code></td>
  *              <td align="center"><span class="fa-sort-amount-down"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SORT_AMOUNT_DOWN_ALT</code></td>
  *              <td align="center"><span class="fa-sort-amount-down-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SORT_AMOUNT_UP</code></td>
  *              <td align="center"><span class="fa-sort-amount-up"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SORT_AMOUNT_UP_ALT</code></td>
  *              <td align="center"><span class="fa-sort-amount-up-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SORT_DOWN</code></td>
  *              <td align="center"><span class="fa-sort-down"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SORT_NUMERIC_DOWN</code></td>
  *              <td align="center"><span class="fa-sort-numeric-down"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SORT_NUMERIC_DOWN_ALT</code></td>
  *              <td align="center"><span class="fa-sort-numeric-down-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SORT_NUMERIC_UP</code></td>
  *              <td align="center"><span class="fa-sort-numeric-up"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SORT_NUMERIC_UP_ALT</code></td>
  *              <td align="center"><span class="fa-sort-numeric-up-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SORT_UP</code></td>
  *              <td align="center"><span class="fa-sort-up"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SPA</code></td>
  *              <td align="center"><span class="fa-spa"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SPACE_SHUTTLE</code></td>
  *              <td align="center"><span class="fa-space-shuttle"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SPELL_CHECK</code></td>
  *              <td align="center"><span class="fa-spell-check"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SPIDER</code></td>
  *              <td align="center"><span class="fa-spider"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SPINNER</code></td>
  *              <td align="center"><span class="fa-spinner"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SPLOTCH</code></td>
  *              <td align="center"><span class="fa-splotch"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SPRAY_CAN</code></td>
  *              <td align="center"><span class="fa-spray-can"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SQUARE</code></td>
  *              <td align="center"><span class="fa-square"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SQUARE_FULL</code></td>
  *              <td align="center"><span class="fa-square-full"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SQUARE_ROOT_ALT</code></td>
  *              <td align="center"><span class="fa-square-root-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_STAMP</code></td>
  *              <td align="center"><span class="fa-stamp"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_STAR</code></td>
  *              <td align="center"><span class="fa-star"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_STAR_AND_CRESCENT</code></td>
  *              <td align="center"><span class="fa-star-and-crescent"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_STAR_HALF</code></td>
  *              <td align="center"><span class="fa-star-half"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_STAR_HALF_ALT</code></td>
  *              <td align="center"><span class="fa-star-half-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_STAR_OF_DAVID</code></td>
  *              <td align="center"><span class="fa-star-of-david"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_STAR_OF_LIFE</code></td>
  *              <td align="center"><span class="fa-star-of-life"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_STEP_BACKWARD</code></td>
  *              <td align="center"><span class="fa-step-backward"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_STEP_FORWARD</code></td>
  *              <td align="center"><span class="fa-step-forward"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_STETHOSCOPE</code></td>
  *              <td align="center"><span class="fa-stethoscope"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_STICKY_NOTE</code></td>
  *              <td align="center"><span class="fa-sticky-note"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_STOP</code></td>
  *              <td align="center"><span class="fa-stop"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_STOP_CIRCLE</code></td>
  *              <td align="center"><span class="fa-stop-circle"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_STOPWATCH</code></td>
  *              <td align="center"><span class="fa-stopwatch"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_STORE</code></td>
  *              <td align="center"><span class="fa-store"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_STORE_ALT</code></td>
  *              <td align="center"><span class="fa-store-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_STREAM</code></td>
  *              <td align="center"><span class="fa-stream"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_STREET_VIEW</code></td>
  *              <td align="center"><span class="fa-street-view"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_STRIKETHROUGH</code></td>
  *              <td align="center"><span class="fa-strikethrough"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_STROOPWAFEL</code></td>
  *              <td align="center"><span class="fa-stroopwafel"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SUBSCRIPT</code></td>
  *              <td align="center"><span class="fa-subscript"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SUBWAY</code></td>
  *              <td align="center"><span class="fa-subway"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SUITCASE</code></td>
  *              <td align="center"><span class="fa-suitcase"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SUITCASE_ROLLING</code></td>
  *              <td align="center"><span class="fa-suitcase-rolling"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SUN</code></td>
  *              <td align="center"><span class="fa-sun"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SUPERSCRIPT</code></td>
  *              <td align="center"><span class="fa-superscript"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SURPRISE</code></td>
  *              <td align="center"><span class="fa-surprise"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SWATCHBOOK</code></td>
  *              <td align="center"><span class="fa-swatchbook"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SWIMMER</code></td>
  *              <td align="center"><span class="fa-swimmer"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SWIMMING_POOL</code></td>
  *              <td align="center"><span class="fa-swimming-pool"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SYNAGOGUE</code></td>
  *              <td align="center"><span class="fa-synagogue"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SYNC</code></td>
  *              <td align="center"><span class="fa-sync"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_SYNC_ALT</code></td>
  *              <td align="center"><span class="fa-sync-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_SYRINGE</code></td>
  *              <td align="center"><span class="fa-syringe"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TABLE</code></td>
  *              <td align="center"><span class="fa-table"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TABLE_TENNIS</code></td>
  *              <td align="center"><span class="fa-table-tennis"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TABLET</code></td>
  *              <td align="center"><span class="fa-tablet"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TABLET_ALT</code></td>
  *              <td align="center"><span class="fa-tablet-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TABLETS</code></td>
  *              <td align="center"><span class="fa-tablets"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TACHOMETER_ALT</code></td>
  *              <td align="center"><span class="fa-tachometer-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TAG</code></td>
  *              <td align="center"><span class="fa-tag"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TAGS</code></td>
  *              <td align="center"><span class="fa-tags"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TAPE</code></td>
  *              <td align="center"><span class="fa-tape"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TASKS</code></td>
  *              <td align="center"><span class="fa-tasks"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TAXI</code></td>
  *              <td align="center"><span class="fa-taxi"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TEETH</code></td>
  *              <td align="center"><span class="fa-teeth"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TEETH_OPEN</code></td>
  *              <td align="center"><span class="fa-teeth-open"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TEMPERATURE_HIGH</code></td>
  *              <td align="center"><span class="fa-temperature-high"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TEMPERATURE_LOW</code></td>
  *              <td align="center"><span class="fa-temperature-low"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TENGE</code></td>
  *              <td align="center"><span class="fa-tenge"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TERMINAL</code></td>
  *              <td align="center"><span class="fa-terminal"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TEXT_HEIGHT</code></td>
  *              <td align="center"><span class="fa-text-height"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TEXT_WIDTH</code></td>
  *              <td align="center"><span class="fa-text-width"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TH</code></td>
  *              <td align="center"><span class="fa-th"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TH_LARGE</code></td>
  *              <td align="center"><span class="fa-th-large"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TH_LIST</code></td>
  *              <td align="center"><span class="fa-th-list"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_THEATER_MASKS</code></td>
  *              <td align="center"><span class="fa-theater-masks"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_THERMOMETER</code></td>
  *              <td align="center"><span class="fa-thermometer"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_THERMOMETER_EMPTY</code></td>
  *              <td align="center"><span class="fa-thermometer-empty"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_THERMOMETER_FULL</code></td>
  *              <td align="center"><span class="fa-thermometer-full"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_THERMOMETER_HALF</code></td>
  *              <td align="center"><span class="fa-thermometer-half"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_THERMOMETER_QUARTER</code></td>
  *              <td align="center"><span class="fa-thermometer-quarter"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_THERMOMETER_THREE_QUARTERS</code></td>
  *              <td align="center"><span class="fa-thermometer-three-quarters"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_THUMBS_DOWN</code></td>
  *              <td align="center"><span class="fa-thumbs-down"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_THUMBS_UP</code></td>
  *              <td align="center"><span class="fa-thumbs-up"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_THUMBTACK</code></td>
  *              <td align="center"><span class="fa-thumbtack"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TICKET_ALT</code></td>
  *              <td align="center"><span class="fa-ticket-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TIMES</code></td>
  *              <td align="center"><span class="fa-times"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TIMES_CIRCLE</code></td>
  *              <td align="center"><span class="fa-times-circle"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TINT</code></td>
  *              <td align="center"><span class="fa-tint"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TINT_SLASH</code></td>
  *              <td align="center"><span class="fa-tint-slash"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TIRED</code></td>
  *              <td align="center"><span class="fa-tired"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TOGGLE_OFF</code></td>
  *              <td align="center"><span class="fa-toggle-off"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TOGGLE_ON</code></td>
  *              <td align="center"><span class="fa-toggle-on"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TOILET</code></td>
  *              <td align="center"><span class="fa-toilet"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TOILET_PAPER</code></td>
  *              <td align="center"><span class="fa-toilet-paper"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TOOLBOX</code></td>
  *              <td align="center"><span class="fa-toolbox"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TOOLS</code></td>
  *              <td align="center"><span class="fa-tools"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TOOTH</code></td>
  *              <td align="center"><span class="fa-tooth"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TORAH</code></td>
  *              <td align="center"><span class="fa-torah"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TORII_GATE</code></td>
  *              <td align="center"><span class="fa-torii-gate"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TRACTOR</code></td>
  *              <td align="center"><span class="fa-tractor"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TRADEMARK</code></td>
  *              <td align="center"><span class="fa-trademark"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TRAFFIC_LIGHT</code></td>
  *              <td align="center"><span class="fa-traffic-light"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TRAIN</code></td>
  *              <td align="center"><span class="fa-train"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TRAM</code></td>
  *              <td align="center"><span class="fa-tram"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TRANSGENDER</code></td>
  *              <td align="center"><span class="fa-transgender"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TRANSGENDER_ALT</code></td>
  *              <td align="center"><span class="fa-transgender-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TRASH</code></td>
  *              <td align="center"><span class="fa-trash"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TRASH_ALT</code></td>
  *              <td align="center"><span class="fa-trash-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TRASH_RESTORE</code></td>
  *              <td align="center"><span class="fa-trash-restore"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TRASH_RESTORE_ALT</code></td>
  *              <td align="center"><span class="fa-trash-restore-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TREE</code></td>
  *              <td align="center"><span class="fa-tree"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TROPHY</code></td>
  *              <td align="center"><span class="fa-trophy"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TRUCK</code></td>
  *              <td align="center"><span class="fa-truck"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TRUCK_LOADING</code></td>
  *              <td align="center"><span class="fa-truck-loading"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TRUCK_MONSTER</code></td>
  *              <td align="center"><span class="fa-truck-monster"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TRUCK_MOVING</code></td>
  *              <td align="center"><span class="fa-truck-moving"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TRUCK_PICKUP</code></td>
  *              <td align="center"><span class="fa-truck-pickup"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TSHIRT</code></td>
  *              <td align="center"><span class="fa-tshirt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_TTY</code></td>
  *              <td align="center"><span class="fa-tty"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_TV</code></td>
  *              <td align="center"><span class="fa-tv"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_UMBRELLA</code></td>
  *              <td align="center"><span class="fa-umbrella"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_UMBRELLA_BEACH</code></td>
  *              <td align="center"><span class="fa-umbrella-beach"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_UNDERLINE</code></td>
  *              <td align="center"><span class="fa-underline"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_UNDO</code></td>
  *              <td align="center"><span class="fa-undo"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_UNDO_ALT</code></td>
  *              <td align="center"><span class="fa-undo-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_UNIVERSAL_ACCESS</code></td>
  *              <td align="center"><span class="fa-universal-access"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_UNIVERSITY</code></td>
  *              <td align="center"><span class="fa-university"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_UNLINK</code></td>
  *              <td align="center"><span class="fa-unlink"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_UNLOCK</code></td>
  *              <td align="center"><span class="fa-unlock"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_UNLOCK_ALT</code></td>
  *              <td align="center"><span class="fa-unlock-alt"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_UPLOAD</code></td>
  *              <td align="center"><span class="fa-upload"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_USER</code></td>
  *              <td align="center"><span class="fa-user"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_USER_ALT</code></td>
  *              <td align="center"><span class="fa-user-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_USER_ALT_SLASH</code></td>
  *              <td align="center"><span class="fa-user-alt-slash"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_USER_ASTRONAUT</code></td>
  *              <td align="center"><span class="fa-user-astronaut"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_USER_CHECK</code></td>
  *              <td align="center"><span class="fa-user-check"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_USER_CIRCLE</code></td>
  *              <td align="center"><span class="fa-user-circle"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_USER_CLOCK</code></td>
  *              <td align="center"><span class="fa-user-clock"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_USER_COG</code></td>
  *              <td align="center"><span class="fa-user-cog"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_USER_EDIT</code></td>
  *              <td align="center"><span class="fa-user-edit"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_USER_FRIENDS</code></td>
  *              <td align="center"><span class="fa-user-friends"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_USER_GRADUATE</code></td>
  *              <td align="center"><span class="fa-user-graduate"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_USER_INJURED</code></td>
  *              <td align="center"><span class="fa-user-injured"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_USER_LOCK</code></td>
  *              <td align="center"><span class="fa-user-lock"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_USER_MD</code></td>
  *              <td align="center"><span class="fa-user-md"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_USER_MINUS</code></td>
  *              <td align="center"><span class="fa-user-minus"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_USER_NINJA</code></td>
  *              <td align="center"><span class="fa-user-ninja"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_USER_NURSE</code></td>
  *              <td align="center"><span class="fa-user-nurse"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_USER_PLUS</code></td>
  *              <td align="center"><span class="fa-user-plus"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_USER_SECRET</code></td>
  *              <td align="center"><span class="fa-user-secret"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_USER_SHIELD</code></td>
  *              <td align="center"><span class="fa-user-shield"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_USER_SLASH</code></td>
  *              <td align="center"><span class="fa-user-slash"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_USER_TAG</code></td>
  *              <td align="center"><span class="fa-user-tag"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_USER_TIE</code></td>
  *              <td align="center"><span class="fa-user-tie"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_USER_TIMES</code></td>
  *              <td align="center"><span class="fa-user-times"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_USERS</code></td>
  *              <td align="center"><span class="fa-users"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_USERS_COG</code></td>
  *              <td align="center"><span class="fa-users-cog"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_UTENSIL_SPOON</code></td>
  *              <td align="center"><span class="fa-utensil-spoon"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_UTENSILS</code></td>
  *              <td align="center"><span class="fa-utensils"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_VECTOR_SQUARE</code></td>
  *              <td align="center"><span class="fa-vector-square"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_VENUS</code></td>
  *              <td align="center"><span class="fa-venus"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_VENUS_DOUBLE</code></td>
  *              <td align="center"><span class="fa-venus-double"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_VENUS_MARS</code></td>
  *              <td align="center"><span class="fa-venus-mars"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_VIAL</code></td>
  *              <td align="center"><span class="fa-vial"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_VIALS</code></td>
  *              <td align="center"><span class="fa-vials"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_VIDEO</code></td>
  *              <td align="center"><span class="fa-video"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_VIDEO_SLASH</code></td>
  *              <td align="center"><span class="fa-video-slash"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_VIHARA</code></td>
  *              <td align="center"><span class="fa-vihara"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_VOICEMAIL</code></td>
  *              <td align="center"><span class="fa-voicemail"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_VOLLEYBALL_BALL</code></td>
  *              <td align="center"><span class="fa-volleyball-ball"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_VOLUME_DOWN</code></td>
  *              <td align="center"><span class="fa-volume-down"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_VOLUME_MUTE</code></td>
  *              <td align="center"><span class="fa-volume-mute"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_VOLUME_OFF</code></td>
  *              <td align="center"><span class="fa-volume-off"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_VOLUME_UP</code></td>
  *              <td align="center"><span class="fa-volume-up"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_VOTE_YEA</code></td>
  *              <td align="center"><span class="fa-vote-yea"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_VR_CARDBOARD</code></td>
  *              <td align="center"><span class="fa-vr-cardboard"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_WALKING</code></td>
  *              <td align="center"><span class="fa-walking"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_WALLET</code></td>
  *              <td align="center"><span class="fa-wallet"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_WAREHOUSE</code></td>
  *              <td align="center"><span class="fa-warehouse"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_WATER</code></td>
  *              <td align="center"><span class="fa-water"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_WAVE_SQUARE</code></td>
  *              <td align="center"><span class="fa-wave-square"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_WEIGHT</code></td>
  *              <td align="center"><span class="fa-weight"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_WEIGHT_HANGING</code></td>
  *              <td align="center"><span class="fa-weight-hanging"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_WHEELCHAIR</code></td>
  *              <td align="center"><span class="fa-wheelchair"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_WIFI</code></td>
  *              <td align="center"><span class="fa-wifi"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_WIND</code></td>
  *              <td align="center"><span class="fa-wind"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_WINDOW_CLOSE</code></td>
  *              <td align="center"><span class="fa-window-close"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_WINDOW_MAXIMIZE</code></td>
  *              <td align="center"><span class="fa-window-maximize"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_WINDOW_MINIMIZE</code></td>
  *              <td align="center"><span class="fa-window-minimize"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_WINDOW_RESTORE</code></td>
  *              <td align="center"><span class="fa-window-restore"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_WINE_BOTTLE</code></td>
  *              <td align="center"><span class="fa-wine-bottle"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_WINE_GLASS</code></td>
  *              <td align="center"><span class="fa-wine-glass"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_WINE_GLASS_ALT</code></td>
  *              <td align="center"><span class="fa-wine-glass-alt"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_WON_SIGN</code></td>
  *              <td align="center"><span class="fa-won-sign"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_WRENCH</code></td>
  *              <td align="center"><span class="fa-wrench"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_X_RAY</code></td>
  *              <td align="center"><span class="fa-x-ray"></span></td>
  *            </tr>
  *            <tr class="row-odd">
  *              <td align="right"><code>FA_YEN_SIGN</code></td>
  *              <td align="center"><span class="fa-yen-sign"></span></td>
  *            </tr>
  *            <tr class="row-even">
  *              <td align="right"><code>FA_YIN_YANG</code></td>
  *              <td align="center"><span class="fa-yin-yang"></span></td>
  *            </tr>
  *          </tbody>
  *        </table>
  *      </div><!-- wy-table-responsive -->
  *    </center>
  *
  * \endrst
  */

#pragma once

  // prevent individual pages from being generated for all of these
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

enum enum_font_awesome : ::i32
{
   e_font_awesome_ad = 0xf641,
   e_font_awesome_address_book = 0xf2b9,
   e_font_awesome_address_card = 0xf2bb,
   e_font_awesome_adjust = 0xf042,
   e_font_awesome_air_freshener = 0xf5d0,
   e_font_awesome_align_center = 0xf037,
   e_font_awesome_align_justify = 0xf039,
   e_font_awesome_align_left = 0xf036,
   e_font_awesome_align_right = 0xf038,
   e_font_awesome_allergies = 0xf461,
   e_font_awesome_ambulance = 0xf0f9,
   e_font_awesome_american_sign_language_interpreting = 0xf2a3,
   e_font_awesome_anchor = 0xf13d,
   e_font_awesome_angle_double_down = 0xf103,
   e_font_awesome_angle_double_left = 0xf100,
   e_font_awesome_angle_double_right = 0xf101,
   e_font_awesome_angle_double_up = 0xf102,
   e_font_awesome_angle_down = 0xf107,
   e_font_awesome_angle_left = 0xf104,
   e_font_awesome_angle_right = 0xf105,
   e_font_awesome_angle_up = 0xf106,
   e_font_awesome_angry = 0xf556,
   e_font_awesome_ankh = 0xf644,
   e_font_awesome_apple_alt = 0xf5d1,
   e_font_awesome_archive = 0xf187,
   e_font_awesome_archway = 0xf557,
   e_font_awesome_arrow_alt_circle_down = 0xf358,
   e_font_awesome_arrow_alt_circle_left = 0xf359,
   e_font_awesome_arrow_alt_circle_right = 0xf35a,
   e_font_awesome_arrow_alt_circle_up = 0xf35b,
   e_font_awesome_arrow_circle_down = 0xf0ab,
   e_font_awesome_arrow_circle_left = 0xf0a8,
   e_font_awesome_arrow_circle_right = 0xf0a9,
   e_font_awesome_arrow_circle_up = 0xf0aa,
   e_font_awesome_arrow_down = 0xf063,
   e_font_awesome_arrow_left = 0xf060,
   e_font_awesome_arrow_right = 0xf061,
   e_font_awesome_arrow_up = 0xf062,
   e_font_awesome_arrows_alt = 0xf0b2,
   e_font_awesome_arrows_alt_h = 0xf337,
   e_font_awesome_arrows_alt_v = 0xf338,
   e_font_awesome_assistive_listening_systems = 0xf2a2,
   e_font_awesome_asterisk = 0xf069,
   e_font_awesome_at = 0xf1fa,
   e_font_awesome_atlas = 0xf558,
   e_font_awesome_atom = 0xf5d2,
   e_font_awesome_audio_description = 0xf29e,
   e_font_awesome_award = 0xf559,
   e_font_awesome_baby = 0xf77c,
   e_font_awesome_baby_carriage = 0xf77d,
   e_font_awesome_backspace = 0xf55a,
   e_font_awesome_backward = 0xf04a,
   e_font_awesome_bacon = 0xf7e5,
   e_font_awesome_balance_scale = 0xf24e,
   e_font_awesome_balance_scale_left = 0xf515,
   e_font_awesome_balance_scale_right = 0xf516,
   e_font_awesome_ban = 0xf05e,
   e_font_awesome_band_aid = 0xf462,
   e_font_awesome_barcode = 0xf02a,
   e_font_awesome_bars = 0xf0c9,
   e_font_awesome_baseball_ball = 0xf433,
   e_font_awesome_basketball_ball = 0xf434,
   e_font_awesome_bath = 0xf2cd,
   e_font_awesome_battery_empty = 0xf244,
   e_font_awesome_battery_full = 0xf240,
   e_font_awesome_battery_half = 0xf242,
   e_font_awesome_battery_quarter = 0xf243,
   e_font_awesome_battery_three_quarters = 0xf241,
   e_font_awesome_bed = 0xf236,
   e_font_awesome_beer = 0xf0fc,
   e_font_awesome_bell = 0xf0f3,
   e_font_awesome_bell_slash = 0xf1f6,
   e_font_awesome_bezier_curve = 0xf55b,
   e_font_awesome_bible = 0xf647,
   e_font_awesome_bicycle = 0xf206,
   e_font_awesome_biking = 0xf84a,
   e_font_awesome_binoculars = 0xf1e5,
   e_font_awesome_biohazard = 0xf780,
   e_font_awesome_birthday_cake = 0xf1fd,
   e_font_awesome_blender = 0xf517,
   e_font_awesome_blender_phone = 0xf6b6,
   e_font_awesome_blind = 0xf29d,
   e_font_awesome_blog = 0xf781,
   e_font_awesome_bold = 0xf032,
   e_font_awesome_bolt = 0xf0e7,
   e_font_awesome_bomb = 0xf1e2,
   e_font_awesome_bone = 0xf5d7,
   e_font_awesome_bong = 0xf55c,
   e_font_awesome_book = 0xf02d,
   e_font_awesome_book_dead = 0xf6b7,
   e_font_awesome_book_medical = 0xf7e6,
   e_font_awesome_book_open = 0xf518,
   e_font_awesome_book_reader = 0xf5da,
   e_font_awesome_bookmark = 0xf02e,
   e_font_awesome_border_all = 0xf84c,
   e_font_awesome_border_none = 0xf850,
   e_font_awesome_border_style = 0xf853,
   e_font_awesome_bowling_ball = 0xf436,
   e_font_awesome_box = 0xf466,
   e_font_awesome_box_open = 0xf49e,
   e_font_awesome_boxes = 0xf468,
   e_font_awesome_braille = 0xf2a1,
   e_font_awesome_brain = 0xf5dc,
   e_font_awesome_bread_slice = 0xf7ec,
   e_font_awesome_briefcase = 0xf0b1,
   e_font_awesome_briefcase_medical = 0xf469,
   e_font_awesome_broadcast_tower = 0xf519,
   e_font_awesome_broom = 0xf51a,
   e_font_awesome_brush = 0xf55d,
   e_font_awesome_bug = 0xf188,
   e_font_awesome_building = 0xf1ad,
   e_font_awesome_bullhorn = 0xf0a1,
   e_font_awesome_bullseye = 0xf140,
   e_font_awesome_burn = 0xf46a,
   e_font_awesome_bus = 0xf207,
   e_font_awesome_bus_alt = 0xf55e,
   e_font_awesome_business_time = 0xf64a,
   e_font_awesome_calculator = 0xf1ec,
   e_font_awesome_calendar = 0xf133,
   e_font_awesome_calendar_alt = 0xf073,
   e_font_awesome_calendar_check = 0xf274,
   e_font_awesome_calendar_day = 0xf783,
   e_font_awesome_calendar_minus = 0xf272,
   e_font_awesome_calendar_plus = 0xf271,
   e_font_awesome_calendar_times = 0xf273,
   e_font_awesome_calendar_week = 0xf784,
   e_font_awesome_camera = 0xf030,
   e_font_awesome_camera_retro = 0xf083,
   e_font_awesome_campground = 0xf6bb,
   e_font_awesome_candy_cane = 0xf786,
   e_font_awesome_cannabis = 0xf55f,
   e_font_awesome_capsules = 0xf46b,
   e_font_awesome_car = 0xf1b9,
   e_font_awesome_car_alt = 0xf5de,
   e_font_awesome_car_battery = 0xf5df,
   e_font_awesome_car_crash = 0xf5e1,
   e_font_awesome_car_side = 0xf5e4,
   e_font_awesome_caret_down = 0xf0d7,
   e_font_awesome_caret_left = 0xf0d9,
   e_font_awesome_caret_right = 0xf0da,
   e_font_awesome_caret_square_down = 0xf150,
   e_font_awesome_caret_square_left = 0xf191,
   e_font_awesome_caret_square_right = 0xf152,
   e_font_awesome_caret_square_up = 0xf151,
   e_font_awesome_caret_up = 0xf0d8,
   e_font_awesome_carrot = 0xf787,
   e_font_awesome_cart_arrow_down = 0xf218,
   e_font_awesome_cart_plus = 0xf217,
   e_font_awesome_cash_register = 0xf788,
   e_font_awesome_cat = 0xf6be,
   e_font_awesome_certificate = 0xf0a3,
   e_font_awesome_chair = 0xf6c0,
   e_font_awesome_chalkboard = 0xf51b,
   e_font_awesome_chalkboard_teacher = 0xf51c,
   e_font_awesome_charging_station = 0xf5e7,
   e_font_awesome_chart_area = 0xf1fe,
   e_font_awesome_chart_bar = 0xf080,
   e_font_awesome_chart_line = 0xf201,
   e_font_awesome_chart_pie = 0xf200,
   e_font_awesome_check = 0xf00c,
   e_font_awesome_check_circle = 0xf058,
   e_font_awesome_check_double = 0xf560,
   e_font_awesome_check_square = 0xf14a,
   e_font_awesome_cheese = 0xf7ef,
   e_font_awesome_chess = 0xf439,
   e_font_awesome_chess_bishop = 0xf43a,
   e_font_awesome_chess_board = 0xf43c,
   e_font_awesome_chess_king = 0xf43f,
   e_font_awesome_chess_knight = 0xf441,
   e_font_awesome_chess_pawn = 0xf443,
   e_font_awesome_chess_queen = 0xf445,
   e_font_awesome_chess_rook = 0xf447,
   e_font_awesome_chevron_circle_down = 0xf13a,
   e_font_awesome_chevron_circle_left = 0xf137,
   e_font_awesome_chevron_circle_right = 0xf138,
   e_font_awesome_chevron_circle_up = 0xf139,
   e_font_awesome_chevron_down = 0xf078,
   e_font_awesome_chevron_left = 0xf053,
   e_font_awesome_chevron_right = 0xf054,
   e_font_awesome_chevron_up = 0xf077,
   e_font_awesome_child = 0xf1ae,
   e_font_awesome_church = 0xf51d,
   e_font_awesome_circle = 0xf111,
   e_font_awesome_circle_notch = 0xf1ce,
   e_font_awesome_city = 0xf64f,
   e_font_awesome_clinic_medical = 0xf7f2,
   e_font_awesome_clipboard = 0xf328,
   e_font_awesome_clipboard_check = 0xf46c,
   e_font_awesome_clipboard_list = 0xf46d,
   e_font_awesome_clock = 0xf017,
   e_font_awesome_clone = 0xf24d,
   e_font_awesome_closed_captioning = 0xf20a,
   e_font_awesome_cloud = 0xf0c2,
   e_font_awesome_cloud_download_alt = 0xf381,
   e_font_awesome_cloud_meatball = 0xf73b,
   e_font_awesome_cloud_moon = 0xf6c3,
   e_font_awesome_cloud_moon_rain = 0xf73c,
   e_font_awesome_cloud_rain = 0xf73d,
   e_font_awesome_cloud_showers_heavy = 0xf740,
   e_font_awesome_cloud_sun = 0xf6c4,
   e_font_awesome_cloud_sun_rain = 0xf743,
   e_font_awesome_cloud_upload_alt = 0xf382,
   e_font_awesome_cocktail = 0xf561,
   e_font_awesome_code = 0xf121,
   e_font_awesome_code_branch = 0xf126,
   e_font_awesome_coffee = 0xf0f4,
   e_font_awesome_cog = 0xf013,
   e_font_awesome_cogs = 0xf085,
   e_font_awesome_coins = 0xf51e,
   e_font_awesome_columns = 0xf0db,
   e_font_awesome_comment = 0xf075,
   e_font_awesome_comment_alt = 0xf27a,
   e_font_awesome_comment_dollar = 0xf651,
   e_font_awesome_comment_dots = 0xf4ad,
   e_font_awesome_comment_medical = 0xf7f5,
   e_font_awesome_comment_slash = 0xf4b3,
   e_font_awesome_comments = 0xf086,
   e_font_awesome_comments_dollar = 0xf653,
   e_font_awesome_compact_disc = 0xf51f,
   e_font_awesome_compass = 0xf14e,
   e_font_awesome_compress = 0xf066,
   e_font_awesome_compress_arrows_alt = 0xf78c,
   e_font_awesome_concierge_bell = 0xf562,
   e_font_awesome_cookie = 0xf563,
   e_font_awesome_cookie_bite = 0xf564,
   e_font_awesome_copy = 0xf0c5,
   e_font_awesome_copyright = 0xf1f9,
   e_font_awesome_couch = 0xf4b8,
   e_font_awesome_credit_card = 0xf09d,
   e_font_awesome_crop = 0xf125,
   e_font_awesome_crop_alt = 0xf565,
   e_font_awesome_cross = 0xf654,
   e_font_awesome_crosshairs = 0xf05b,
   e_font_awesome_crow = 0xf520,
   e_font_awesome_crown = 0xf521,
   e_font_awesome_crutch = 0xf7f7,
   e_font_awesome_cube = 0xf1b2,
   e_font_awesome_cubes = 0xf1b3,
   e_font_awesome_cut = 0xf0c4,
   e_font_awesome_database = 0xf1c0,
   e_font_awesome_deaf = 0xf2a4,
   e_font_awesome_democrat = 0xf747,
   e_font_awesome_desktop = 0xf108,
   e_font_awesome_dharmachakra = 0xf655,
   e_font_awesome_diagnoses = 0xf470,
   e_font_awesome_dice = 0xf522,
   e_font_awesome_dice_d20 = 0xf6cf,
   e_font_awesome_dice_d6 = 0xf6d1,
   e_font_awesome_dice_five = 0xf523,
   e_font_awesome_dice_four = 0xf524,
   e_font_awesome_dice_one = 0xf525,
   e_font_awesome_dice_six = 0xf526,
   e_font_awesome_dice_three = 0xf527,
   e_font_awesome_dice_two = 0xf528,
   e_font_awesome_digital_tachograph = 0xf566,
   e_font_awesome_directions = 0xf5eb,
   e_font_awesome_divide = 0xf529,
   e_font_awesome_dizzy = 0xf567,
   e_font_awesome_dna = 0xf471,
   e_font_awesome_dog = 0xf6d3,
   e_font_awesome_dollar_sign = 0xf155,
   e_font_awesome_dolly = 0xf472,
   e_font_awesome_dolly_flatbed = 0xf474,
   e_font_awesome_donate = 0xf4b9,
   e_font_awesome_door_closed = 0xf52a,
   e_font_awesome_door_open = 0xf52b,
   e_font_awesome_dot_circle = 0xf192,
   e_font_awesome_dove = 0xf4ba,
   e_font_awesome_download = 0xf019,
   e_font_awesome_drafting_compass = 0xf568,
   e_font_awesome_dragon = 0xf6d5,
   e_font_awesome_draw_polygon = 0xf5ee,
   e_font_awesome_drum = 0xf569,
   e_font_awesome_drum_steelpan = 0xf56a,
   e_font_awesome_drumstick_bite = 0xf6d7,
   e_font_awesome_dumbbell = 0xf44b,
   e_font_awesome_dumpster = 0xf793,
   e_font_awesome_dumpster_fire = 0xf794,
   e_font_awesome_dungeon = 0xf6d9,
   e_font_awesome_edit = 0xf044,
   e_font_awesome_egg = 0xf7fb,
   e_font_awesome_eject = 0xf052,
   e_font_awesome_ellipsis_h = 0xf141,
   e_font_awesome_ellipsis_v = 0xf142,
   e_font_awesome_envelope = 0xf0e0,
   e_font_awesome_envelope_open = 0xf2b6,
   e_font_awesome_envelope_open_text = 0xf658,
   e_font_awesome_envelope_square = 0xf199,
   e_font_awesome_equals = 0xf52c,
   e_font_awesome_eraser = 0xf12d,
   e_font_awesome_ethernet = 0xf796,
   e_font_awesome_euro_sign = 0xf153,
   e_font_awesome_exchange_alt = 0xf362,
   e_font_awesome_exclamation = 0xf12a,
   e_font_awesome_exclamation_circle = 0xf06a,
   e_font_awesome_exclamation_triangle = 0xf071,
   e_font_awesome_expand = 0xf065,
   e_font_awesome_expand_arrows_alt = 0xf31e,
   e_font_awesome_external_link_alt = 0xf35d,
   e_font_awesome_external_link_square_alt = 0xf360,
   e_font_awesome_eye = 0xf06e,
   e_font_awesome_eye_dropper = 0xf1fb,
   e_font_awesome_eye_slash = 0xf070,
   e_font_awesome_fan = 0xf863,
   e_font_awesome_fast_backward = 0xf049,
   e_font_awesome_fast_forward = 0xf050,
   e_font_awesome_fax = 0xf1ac,
   e_font_awesome_feather = 0xf52d,
   e_font_awesome_feather_alt = 0xf56b,
   e_font_awesome_female = 0xf182,
   e_font_awesome_fighter_jet = 0xf0fb,
   e_font_awesome_file = 0xf15b,
   e_font_awesome_file_alt = 0xf15c,
   e_font_awesome_file_archive = 0xf1c6,
   e_font_awesome_file_audio = 0xf1c7,
   e_font_awesome_file_code = 0xf1c9,
   e_font_awesome_file_contract = 0xf56c,
   e_font_awesome_file_csv = 0xf6dd,
   e_font_awesome_file_download = 0xf56d,
   e_font_awesome_file_excel = 0xf1c3,
   e_font_awesome_file_export = 0xf56e,
   e_font_awesome_file_image = 0xf1c5,
   e_font_awesome_file_import = 0xf56f,
   e_font_awesome_file_invoice = 0xf570,
   e_font_awesome_file_invoice_dollar = 0xf571,
   e_font_awesome_file_medical = 0xf477,
   e_font_awesome_file_medical_alt = 0xf478,
   e_font_awesome_file_pdf = 0xf1c1,
   e_font_awesome_file_powerpoint = 0xf1c4,
   e_font_awesome_file_prescription = 0xf572,
   e_font_awesome_file_signature = 0xf573,
   e_font_awesome_file_upload = 0xf574,
   e_font_awesome_file_video = 0xf1c8,
   e_font_awesome_file_word = 0xf1c2,
   e_font_awesome_fill = 0xf575,
   e_font_awesome_fill_drip = 0xf576,
   e_font_awesome_film = 0xf008,
   e_font_awesome_filter = 0xf0b0,
   e_font_awesome_fingerprint = 0xf577,
   e_font_awesome_fire = 0xf06d,
   e_font_awesome_fire_alt = 0xf7e4,
   e_font_awesome_fire_extinguisher = 0xf134,
   e_font_awesome_first_aid = 0xf479,
   e_font_awesome_fish = 0xf578,
   e_font_awesome_fist_raised = 0xf6de,
   e_font_awesome_flag = 0xf024,
   e_font_awesome_flag_checkered = 0xf11e,
   e_font_awesome_flag_usa = 0xf74d,
   e_font_awesome_flask = 0xf0c3,
   e_font_awesome_flushed = 0xf579,
   e_font_awesome_folder = 0xf07b,
   e_font_awesome_folder_minus = 0xf65d,
   e_font_awesome_folder_open = 0xf07c,
   e_font_awesome_folder_plus = 0xf65e,
   e_font_awesome_font = 0xf031,
   e_font_awesome_font_awesome_logo_full = 0xf4e6,
   e_font_awesome_football_ball = 0xf44e,
   e_font_awesome_forward = 0xf04e,
   e_font_awesome_frog = 0xf52e,
   e_font_awesome_frown = 0xf119,
   e_font_awesome_frown_open = 0xf57a,
   e_font_awesome_funnel_dollar = 0xf662,
   e_font_awesome_futbol = 0xf1e3,
   e_font_awesome_gamepad = 0xf11b,
   e_font_awesome_gas_pump = 0xf52f,
   e_font_awesome_gavel = 0xf0e3,
   e_font_awesome_gem = 0xf3a5,
   e_font_awesome_genderless = 0xf22d,
   e_font_awesome_ghost = 0xf6e2,
   e_font_awesome_gift = 0xf06b,
   e_font_awesome_gifts = 0xf79c,
   e_font_awesome_glass_cheers = 0xf79f,
   e_font_awesome_glass_martini = 0xf000,
   e_font_awesome_glass_martini_alt = 0xf57b,
   e_font_awesome_glass_whiskey = 0xf7a0,
   e_font_awesome_glasses = 0xf530,
   e_font_awesome_globe = 0xf0ac,
   e_font_awesome_globe_africa = 0xf57c,
   e_font_awesome_globe_americas = 0xf57d,
   e_font_awesome_globe_asia = 0xf57e,
   e_font_awesome_globe_europe = 0xf7a2,
   e_font_awesome_golf_ball = 0xf450,
   e_font_awesome_gopuram = 0xf664,
   e_font_awesome_graduation_cap = 0xf19d,
   e_font_awesome_greater_than = 0xf531,
   e_font_awesome_greater_than_equal = 0xf532,
   e_font_awesome_grimace = 0xf57f,
   e_font_awesome_grin = 0xf580,
   e_font_awesome_grin_alt = 0xf581,
   e_font_awesome_grin_beam = 0xf582,
   e_font_awesome_grin_beam_sweat = 0xf583,
   e_font_awesome_grin_hearts = 0xf584,
   e_font_awesome_grin_squint = 0xf585,
   e_font_awesome_grin_squint_tears = 0xf586,
   e_font_awesome_grin_stars = 0xf587,
   e_font_awesome_grin_tears = 0xf588,
   e_font_awesome_grin_tongue = 0xf589,
   e_font_awesome_grin_tongue_squint = 0xf58a,
   e_font_awesome_grin_tongue_wink = 0xf58b,
   e_font_awesome_grin_wink = 0xf58c,
   e_font_awesome_grip_horizontal = 0xf58d,
   e_font_awesome_grip_lines = 0xf7a4,
   e_font_awesome_grip_lines_vertical = 0xf7a5,
   e_font_awesome_grip_vertical = 0xf58e,
   e_font_awesome_guitar = 0xf7a6,
   e_font_awesome_h_square = 0xf0fd,
   e_font_awesome_hamburger = 0xf805,
   e_font_awesome_hammer = 0xf6e3,
   e_font_awesome_hamsa = 0xf665,
   e_font_awesome_hand_holding = 0xf4bd,
   e_font_awesome_hand_holding_heart = 0xf4be,
   e_font_awesome_hand_holding_usd = 0xf4c0,
   e_font_awesome_hand_lizard = 0xf258,
   e_font_awesome_hand_middle_finger = 0xf806,
   e_font_awesome_hand_paper = 0xf256,
   e_font_awesome_hand_peace = 0xf25b,
   e_font_awesome_hand_point_down = 0xf0a7,
   e_font_awesome_hand_point_left = 0xf0a5,
   e_font_awesome_hand_point_right = 0xf0a4,
   e_font_awesome_hand_point_up = 0xf0a6,
   e_font_awesome_hand_pointer = 0xf25a,
   e_font_awesome_hand_rock = 0xf255,
   e_font_awesome_hand_scissors = 0xf257,
   e_font_awesome_hand_spock = 0xf259,
   e_font_awesome_hands = 0xf4c2,
   e_font_awesome_hands_helping = 0xf4c4,
   e_font_awesome_handshake = 0xf2b5,
   e_font_awesome_hanukiah = 0xf6e6,
   e_font_awesome_hard_hat = 0xf807,
   e_font_awesome_hashtag = 0xf292,
   e_font_awesome_hat_wizard = 0xf6e8,
   e_font_awesome_haykal = 0xf666,
   e_font_awesome_hdd = 0xf0a0,
   e_font_awesome_heading = 0xf1dc,
   e_font_awesome_headphones = 0xf025,
   e_font_awesome_headphones_alt = 0xf58f,
   e_font_awesome_headset = 0xf590,
   e_font_awesome_heart = 0xf004,
   e_font_awesome_heart_broken = 0xf7a9,
   e_font_awesome_heartbeat = 0xf21e,
   e_font_awesome_helicopter = 0xf533,
   e_font_awesome_highlighter = 0xf591,
   e_font_awesome_hiking = 0xf6ec,
   e_font_awesome_hippo = 0xf6ed,
   e_font_awesome_history = 0xf1da,
   e_font_awesome_hockey_puck = 0xf453,
   e_font_awesome_holly_berry = 0xf7aa,
   e_font_awesome_home = 0xf015,
   e_font_awesome_horse = 0xf6f0,
   e_font_awesome_horse_head = 0xf7ab,
   e_font_awesome_hospital = 0xf0f8,
   e_font_awesome_hospital_alt = 0xf47d,
   e_font_awesome_hospital_symbol = 0xf47e,
   e_font_awesome_hot_tub = 0xf593,
   e_font_awesome_hotdog = 0xf80f,
   e_font_awesome_hotel = 0xf594,
   e_font_awesome_hourglass = 0xf254,
   e_font_awesome_hourglass_end = 0xf253,
   e_font_awesome_hourglass_half = 0xf252,
   e_font_awesome_hourglass_start = 0xf251,
   e_font_awesome_house_damage = 0xf6f1,
   e_font_awesome_hryvnia = 0xf6f2,
   e_font_awesome_i_cursor = 0xf246,
   e_font_awesome_ice_cream = 0xf810,
   e_font_awesome_icicles = 0xf7ad,
   e_font_awesome_icons = 0xf86d,
   e_font_awesome_id_badge = 0xf2c1,
   e_font_awesome_id_card = 0xf2c2,
   e_font_awesome_id_card_alt = 0xf47f,
   e_font_awesome_igloo = 0xf7ae,
   e_font_awesome_image = 0xf03e,
   e_font_awesome_images = 0xf302,
   e_font_awesome_inbox = 0xf01c,
   e_font_awesome_indent = 0xf03c,
   e_font_awesome_industry = 0xf275,
   e_font_awesome_infinity = 0xf534,
   e_font_awesome_info = 0xf129,
   e_font_awesome_info_circle = 0xf05a,
   e_font_awesome_italic = 0xf033,
   e_font_awesome_jedi = 0xf669,
   e_font_awesome_joint = 0xf595,
   e_font_awesome_journal_whills = 0xf66a,
   e_font_awesome_kaaba = 0xf66b,
   e_font_awesome_key = 0xf084,
   e_font_awesome_keyboard = 0xf11c,
   e_font_awesome_khanda = 0xf66d,
   e_font_awesome_kiss = 0xf596,
   e_font_awesome_kiss_beam = 0xf597,
   e_font_awesome_kiss_wink_heart = 0xf598,
   e_font_awesome_kiwi_bird = 0xf535,
   e_font_awesome_landmark = 0xf66f,
   e_font_awesome_language = 0xf1ab,
   e_font_awesome_laptop = 0xf109,
   e_font_awesome_laptop_code = 0xf5fc,
   e_font_awesome_laptop_medical = 0xf812,
   e_font_awesome_laugh = 0xf599,
   e_font_awesome_laugh_beam = 0xf59a,
   e_font_awesome_laugh_squint = 0xf59b,
   e_font_awesome_laugh_wink = 0xf59c,
   e_font_awesome_layer_group = 0xf5fd,
   e_font_awesome_leaf = 0xf06c,
   e_font_awesome_lemon = 0xf094,
   e_font_awesome_less_than = 0xf536,
   e_font_awesome_less_than_equal = 0xf537,
   e_font_awesome_level_down_alt = 0xf3be,
   e_font_awesome_level_up_alt = 0xf3bf,
   e_font_awesome_life_ring = 0xf1cd,
   e_font_awesome_lightbulb = 0xf0eb,
   e_font_awesome_link = 0xf0c1,
   e_font_awesome_lira_sign = 0xf195,
   e_font_awesome_list = 0xf03a,
   e_font_awesome_list_alt = 0xf022,
   e_font_awesome_list_ol = 0xf0cb,
   e_font_awesome_list_ul = 0xf0ca,
   e_font_awesome_location_arrow = 0xf124,
   e_font_awesome_lock = 0xf023,
   e_font_awesome_lock_open = 0xf3c1,
   e_font_awesome_long_arrow_alt_down = 0xf309,
   e_font_awesome_long_arrow_alt_left = 0xf30a,
   e_font_awesome_long_arrow_alt_right = 0xf30b,
   e_font_awesome_long_arrow_alt_up = 0xf30c,
   e_font_awesome_low_vision = 0xf2a8,
   e_font_awesome_luggage_cart = 0xf59d,
   e_font_awesome_magic = 0xf0d0,
   e_font_awesome_magnet = 0xf076,
   e_font_awesome_mail_bulk = 0xf674,
   e_font_awesome_male = 0xf183,
   e_font_awesome_map = 0xf279,
   e_font_awesome_map_marked = 0xf59f,
   e_font_awesome_map_marked_alt = 0xf5a0,
   e_font_awesome_map_marker = 0xf041,
   e_font_awesome_map_marker_alt = 0xf3c5,
   e_font_awesome_map_pin = 0xf276,
   e_font_awesome_map_signs = 0xf277,
   e_font_awesome_marker = 0xf5a1,
   e_font_awesome_mars = 0xf222,
   e_font_awesome_mars_double = 0xf227,
   e_font_awesome_mars_stroke = 0xf229,
   e_font_awesome_mars_stroke_h = 0xf22b,
   e_font_awesome_mars_stroke_v = 0xf22a,
   e_font_awesome_mask = 0xf6fa,
   e_font_awesome_medal = 0xf5a2,
   e_font_awesome_medkit = 0xf0fa,
   e_font_awesome_meh = 0xf11a,
   e_font_awesome_meh_blank = 0xf5a4,
   e_font_awesome_meh_rolling_eyes = 0xf5a5,
   e_font_awesome_memory = 0xf538,
   e_font_awesome_menorah = 0xf676,
   e_font_awesome_mercury = 0xf223,
   e_font_awesome_meteor = 0xf753,
   e_font_awesome_microchip = 0xf2db,
   e_font_awesome_microphone = 0xf130,
   e_font_awesome_microphone_alt = 0xf3c9,
   e_font_awesome_microphone_alt_slash = 0xf539,
   e_font_awesome_microphone_slash = 0xf131,
   e_font_awesome_microscope = 0xf610,
   e_font_awesome_minus = 0xf068,
   e_font_awesome_minus_circle = 0xf056,
   e_font_awesome_minus_square = 0xf146,
   e_font_awesome_mitten = 0xf7b5,
   e_font_awesome_mobile = 0xf10b,
   e_font_awesome_mobile_alt = 0xf3cd,
   e_font_awesome_money_bill = 0xf0d6,
   e_font_awesome_money_bill_alt = 0xf3d1,
   e_font_awesome_money_bill_wave = 0xf53a,
   e_font_awesome_money_bill_wave_alt = 0xf53b,
   e_font_awesome_money_check = 0xf53c,
   e_font_awesome_money_check_alt = 0xf53d,
   e_font_awesome_monument = 0xf5a6,
   e_font_awesome_moon = 0xf186,
   e_font_awesome_mortar_pestle = 0xf5a7,
   e_font_awesome_mosque = 0xf678,
   e_font_awesome_motorcycle = 0xf21c,
   e_font_awesome_mountain = 0xf6fc,
   e_font_awesome_mouse_pointer = 0xf245,
   e_font_awesome_mug_hot = 0xf7b6,
   e_font_awesome_music = 0xf001,
   e_font_awesome_network_wired = 0xf6ff,
   e_font_awesome_neuter = 0xf22c,
   e_font_awesome_newspaper = 0xf1ea,
   e_font_awesome_not_equal = 0xf53e,
   e_font_awesome_notes_medical = 0xf481,
   e_font_awesome_object_group = 0xf247,
   e_font_awesome_object_ungroup = 0xf248,
   e_font_awesome_oil_can = 0xf613,
   e_font_awesome_om = 0xf679,
   e_font_awesome_otter = 0xf700,
   e_font_awesome_outdent = 0xf03b,
   e_font_awesome_pager = 0xf815,
   e_font_awesome_paint_brush = 0xf1fc,
   e_font_awesome_paint_roller = 0xf5aa,
   e_font_awesome_palette = 0xf53f,
   e_font_awesome_pallet = 0xf482,
   e_font_awesome_paper_plane = 0xf1d8,
   e_font_awesome_paperclip = 0xf0c6,
   e_font_awesome_parachute_box = 0xf4cd,
   e_font_awesome_paragraph = 0xf1dd,
   e_font_awesome_parking = 0xf540,
   e_font_awesome_passport = 0xf5ab,
   e_font_awesome_pastafarianism = 0xf67b,
   e_font_awesome_paste = 0xf0ea,
   e_font_awesome_pause = 0xf04c,
   e_font_awesome_pause_circle = 0xf28b,
   e_font_awesome_paw = 0xf1b0,
   e_font_awesome_peace = 0xf67c,
   e_font_awesome_pen = 0xf304,
   e_font_awesome_pen_alt = 0xf305,
   e_font_awesome_pen_fancy = 0xf5ac,
   e_font_awesome_pen_nib = 0xf5ad,
   e_font_awesome_pen_square = 0xf14b,
   e_font_awesome_pencil_alt = 0xf303,
   e_font_awesome_pencil_ruler = 0xf5ae,
   e_font_awesome_people_carry = 0xf4ce,
   e_font_awesome_pepper_hot = 0xf816,
   e_font_awesome_percent = 0xf295,
   e_font_awesome_percentage = 0xf541,
   e_font_awesome_person_booth = 0xf756,
   e_font_awesome_phone = 0xf095,
   e_font_awesome_phone_alt = 0xf879,
   e_font_awesome_phone_slash = 0xf3dd,
   e_font_awesome_phone_square = 0xf098,
   e_font_awesome_phone_square_alt = 0xf87b,
   e_font_awesome_phone_volume = 0xf2a0,
   e_font_awesome_photo_video = 0xf87c,
   e_font_awesome_piggy_bank = 0xf4d3,
   e_font_awesome_pills = 0xf484,
   e_font_awesome_pizza_slice = 0xf818,
   e_font_awesome_place_of_worship = 0xf67f,
   e_font_awesome_plane = 0xf072,
   e_font_awesome_plane_arrival = 0xf5af,
   e_font_awesome_plane_departure = 0xf5b0,
   e_font_awesome_play = 0xf04b,
   e_font_awesome_play_circle = 0xf144,
   e_font_awesome_plug = 0xf1e6,
   e_font_awesome_plus = 0xf067,
   e_font_awesome_plus_circle = 0xf055,
   e_font_awesome_plus_square = 0xf0fe,
   e_font_awesome_podcast = 0xf2ce,
   e_font_awesome_poll = 0xf681,
   e_font_awesome_poll_h = 0xf682,
   e_font_awesome_poo = 0xf2fe,
   e_font_awesome_poo_storm = 0xf75a,
   e_font_awesome_poop = 0xf619,
   e_font_awesome_portrait = 0xf3e0,
   e_font_awesome_pound_sign = 0xf154,
   e_font_awesome_power_off = 0xf011,
   e_font_awesome_pray = 0xf683,
   e_font_awesome_praying_hands = 0xf684,
   e_font_awesome_prescription = 0xf5b1,
   e_font_awesome_prescription_bottle = 0xf485,
   e_font_awesome_prescription_bottle_alt = 0xf486,
   e_font_awesome_print = 0xf02f,
   e_font_awesome_procedures = 0xf487,
   e_font_awesome_project_diagram = 0xf542,
   e_font_awesome_puzzle_piece = 0xf12e,
   e_font_awesome_qrcode = 0xf029,
   e_font_awesome_question = 0xf128,
   e_font_awesome_question_circle = 0xf059,
   e_font_awesome_quidditch = 0xf458,
   e_font_awesome_quote_left = 0xf10d,
   e_font_awesome_quote_right = 0xf10e,
   e_font_awesome_quran = 0xf687,
   e_font_awesome_radiation = 0xf7b9,
   e_font_awesome_radiation_alt = 0xf7ba,
   e_font_awesome_rainbow = 0xf75b,
   e_font_awesome_random = 0xf074,
   e_font_awesome_receipt = 0xf543,
   e_font_awesome_recycle = 0xf1b8,
   e_font_awesome_redo = 0xf01e,
   e_font_awesome_redo_alt = 0xf2f9,
   e_font_awesome_registered = 0xf25d,
   e_font_awesome_remove_format = 0xf87d,
   e_font_awesome_reply = 0xf3e5,
   e_font_awesome_reply_all = 0xf122,
   e_font_awesome_republican = 0xf75e,
   e_font_awesome_restroom = 0xf7bd,
   e_font_awesome_retweet = 0xf079,
   e_font_awesome_ribbon = 0xf4d6,
   e_font_awesome_ring = 0xf70b,
   e_font_awesome_road = 0xf018,
   e_font_awesome_robot = 0xf544,
   e_font_awesome_rocket = 0xf135,
   e_font_awesome_route = 0xf4d7,
   e_font_awesome_rss = 0xf09e,
   e_font_awesome_rss_square = 0xf143,
   e_font_awesome_ruble_sign = 0xf158,
   e_font_awesome_ruler = 0xf545,
   e_font_awesome_ruler_combined = 0xf546,
   e_font_awesome_ruler_horizontal = 0xf547,
   e_font_awesome_ruler_vertical = 0xf548,
   e_font_awesome_running = 0xf70c,
   e_font_awesome_rupee_sign = 0xf156,
   e_font_awesome_sad_cry = 0xf5b3,
   e_font_awesome_sad_tear = 0xf5b4,
   e_font_awesome_satellite = 0xf7bf,
   e_font_awesome_satellite_dish = 0xf7c0,
   e_font_awesome_save = 0xf0c7,
   e_font_awesome_school = 0xf549,
   e_font_awesome_screwdriver = 0xf54a,
   e_font_awesome_scroll = 0xf70e,
   e_font_awesome_sd_card = 0xf7c2,
   e_font_awesome_search = 0xf002,
   e_font_awesome_search_dollar = 0xf688,
   e_font_awesome_search_location = 0xf689,
   e_font_awesome_search_minus = 0xf010,
   e_font_awesome_search_plus = 0xf00e,
   e_font_awesome_seedling = 0xf4d8,
   e_font_awesome_server = 0xf233,
   e_font_awesome_shapes = 0xf61f,
   e_font_awesome_share = 0xf064,
   e_font_awesome_share_alt = 0xf1e0,
   e_font_awesome_share_alt_square = 0xf1e1,
   e_font_awesome_share_square = 0xf14d,
   e_font_awesome_shekel_sign = 0xf20b,
   e_font_awesome_shield_alt = 0xf3ed,
   e_font_awesome_ship = 0xf21a,
   e_font_awesome_shipping_fast = 0xf48b,
   e_font_awesome_shoe_prints = 0xf54b,
   e_font_awesome_shopping_bag = 0xf290,
   e_font_awesome_shopping_basket = 0xf291,
   e_font_awesome_shopping_cart = 0xf07a,
   e_font_awesome_shower = 0xf2cc,
   e_font_awesome_shuttle_van = 0xf5b6,
   e_font_awesome_sign = 0xf4d9,
   e_font_awesome_sign_in_alt = 0xf2f6,
   e_font_awesome_sign_language = 0xf2a7,
   e_font_awesome_sign_out_alt = 0xf2f5,
   e_font_awesome_signal = 0xf012,
   e_font_awesome_signature = 0xf5b7,
   e_font_awesome_sim_card = 0xf7c4,
   e_font_awesome_sitemap = 0xf0e8,
   e_font_awesome_skating = 0xf7c5,
   e_font_awesome_skiing = 0xf7c9,
   e_font_awesome_skiing_nordic = 0xf7ca,
   e_font_awesome_skull = 0xf54c,
   e_font_awesome_skull_crossbones = 0xf714,
   e_font_awesome_slash = 0xf715,
   e_font_awesome_sleigh = 0xf7cc,
   e_font_awesome_sliders_h = 0xf1de,
   e_font_awesome_smile = 0xf118,
   e_font_awesome_smile_beam = 0xf5b8,
   e_font_awesome_smile_wink = 0xf4da,
   e_font_awesome_smog = 0xf75f,
   e_font_awesome_smoking = 0xf48d,
   e_font_awesome_smoking_ban = 0xf54d,
   e_font_awesome_sms = 0xf7cd,
   e_font_awesome_snowboarding = 0xf7ce,
   e_font_awesome_snowflake = 0xf2dc,
   e_font_awesome_snowman = 0xf7d0,
   e_font_awesome_snowplow = 0xf7d2,
   e_font_awesome_socks = 0xf696,
   e_font_awesome_solar_panel = 0xf5ba,
   e_font_awesome_sort = 0xf0dc,
   e_font_awesome_sort_alpha_down = 0xf15d,
   e_font_awesome_sort_alpha_down_alt = 0xf881,
   e_font_awesome_sort_alpha_up = 0xf15e,
   e_font_awesome_sort_alpha_up_alt = 0xf882,
   e_font_awesome_sort_amount_down = 0xf160,
   e_font_awesome_sort_amount_down_alt = 0xf884,
   e_font_awesome_sort_amount_up = 0xf161,
   e_font_awesome_sort_amount_up_alt = 0xf885,
   e_font_awesome_sort_down = 0xf0dd,
   e_font_awesome_sort_numeric_down = 0xf162,
   e_font_awesome_sort_numeric_down_alt = 0xf886,
   e_font_awesome_sort_numeric_up = 0xf163,
   e_font_awesome_sort_numeric_up_alt = 0xf887,
   e_font_awesome_sort_up = 0xf0de,
   e_font_awesome_spa = 0xf5bb,
   e_font_awesome_space_shuttle = 0xf197,
   e_font_awesome_spell_check = 0xf891,
   e_font_awesome_spider = 0xf717,
   e_font_awesome_spinner = 0xf110,
   e_font_awesome_splotch = 0xf5bc,
   e_font_awesome_spray_can = 0xf5bd,
   e_font_awesome_square = 0xf0c8,
   e_font_awesome_square_full = 0xf45c,
   e_font_awesome_square_root_alt = 0xf698,
   e_font_awesome_stamp = 0xf5bf,
   e_font_awesome_star = 0xf005,
   e_font_awesome_star_and_crescent = 0xf699,
   e_font_awesome_star_half = 0xf089,
   e_font_awesome_star_half_alt = 0xf5c0,
   e_font_awesome_star_of_david = 0xf69a,
   e_font_awesome_star_of_life = 0xf621,
   e_font_awesome_step_backward = 0xf048,
   e_font_awesome_step_forward = 0xf051,
   e_font_awesome_stethoscope = 0xf0f1,
   e_font_awesome_sticky_note = 0xf249,
   e_font_awesome_stop = 0xf04d,
   e_font_awesome_stop_circle = 0xf28d,
   e_font_awesome_stopwatch = 0xf2f2,
   e_font_awesome_store = 0xf54e,
   e_font_awesome_store_alt = 0xf54f,
   e_font_awesome_stream = 0xf550,
   e_font_awesome_street_view = 0xf21d,
   e_font_awesome_strikethrough = 0xf0cc,
   e_font_awesome_stroopwafel = 0xf551,
   e_font_awesome_subscript = 0xf12c,
   e_font_awesome_subway = 0xf239,
   e_font_awesome_suitcase = 0xf0f2,
   e_font_awesome_suitcase_rolling = 0xf5c1,
   e_font_awesome_sun = 0xf185,
   e_font_awesome_superscript = 0xf12b,
   e_font_awesome_surprise = 0xf5c2,
   e_font_awesome_swatchbook = 0xf5c3,
   e_font_awesome_swimmer = 0xf5c4,
   e_font_awesome_swimming_pool = 0xf5c5,
   e_font_awesome_synagogue = 0xf69b,
   e_font_awesome_sync = 0xf021,
   e_font_awesome_sync_alt = 0xf2f1,
   e_font_awesome_syringe = 0xf48e,
   e_font_awesome_table = 0xf0ce,
   e_font_awesome_table_tennis = 0xf45d,
   e_font_awesome_tablet = 0xf10a,
   e_font_awesome_tablet_alt = 0xf3fa,
   e_font_awesome_tablets = 0xf490,
   e_font_awesome_tachometer_alt = 0xf3fd,
   e_font_awesome_tag = 0xf02b,
   e_font_awesome_tags = 0xf02c,
   e_font_awesome_tape = 0xf4db,
   e_font_awesome_tasks = 0xf0ae,
   e_font_awesome_taxi = 0xf1ba,
   e_font_awesome_teeth = 0xf62e,
   e_font_awesome_teeth_open = 0xf62f,
   e_font_awesome_temperature_high = 0xf769,
   e_font_awesome_temperature_low = 0xf76b,
   e_font_awesome_tenge = 0xf7d7,
   e_font_awesome_terminal = 0xf120,
   e_font_awesome_text_height = 0xf034,
   e_font_awesome_text_width = 0xf035,
   e_font_awesome_th = 0xf00a,
   e_font_awesome_th_large = 0xf009,
   e_font_awesome_th_list = 0xf00b,
   e_font_awesome_theater_masks = 0xf630,
   e_font_awesome_thermometer = 0xf491,
   e_font_awesome_thermometer_empty = 0xf2cb,
   e_font_awesome_thermometer_full = 0xf2c7,
   e_font_awesome_thermometer_half = 0xf2c9,
   e_font_awesome_thermometer_quarter = 0xf2ca,
   e_font_awesome_thermometer_three_quarters = 0xf2c8,
   e_font_awesome_thumbs_down = 0xf165,
   e_font_awesome_thumbs_up = 0xf164,
   e_font_awesome_thumbtack = 0xf08d,
   e_font_awesome_ticket_alt = 0xf3ff,
   e_font_awesome_times = 0xf00d,
   e_font_awesome_times_circle = 0xf057,
   e_font_awesome_tint = 0xf043,
   e_font_awesome_tint_slash = 0xf5c7,
   e_font_awesome_tired = 0xf5c8,
   e_font_awesome_toggle_off = 0xf204,
   e_font_awesome_toggle_on = 0xf205,
   e_font_awesome_toilet = 0xf7d8,
   e_font_awesome_toilet_paper = 0xf71e,
   e_font_awesome_toolbox = 0xf552,
   e_font_awesome_tools = 0xf7d9,
   e_font_awesome_tooth = 0xf5c9,
   e_font_awesome_torah = 0xf6a0,
   e_font_awesome_torii_gate = 0xf6a1,
   e_font_awesome_tractor = 0xf722,
   e_font_awesome_trademark = 0xf25c,
   e_font_awesome_traffic_light = 0xf637,
   e_font_awesome_train = 0xf238,
   e_font_awesome_tram = 0xf7da,
   e_font_awesome_transgender = 0xf224,
   e_font_awesome_transgender_alt = 0xf225,
   e_font_awesome_trash = 0xf1f8,
   e_font_awesome_trash_alt = 0xf2ed,
   e_font_awesome_trash_restore = 0xf829,
   e_font_awesome_trash_restore_alt = 0xf82a,
   e_font_awesome_tree = 0xf1bb,
   e_font_awesome_trophy = 0xf091,
   e_font_awesome_truck = 0xf0d1,
   e_font_awesome_truck_loading = 0xf4de,
   e_font_awesome_truck_monster = 0xf63b,
   e_font_awesome_truck_moving = 0xf4df,
   e_font_awesome_truck_pickup = 0xf63c,
   e_font_awesome_tshirt = 0xf553,
   e_font_awesome_tty = 0xf1e4,
   e_font_awesome_tv = 0xf26c,
   e_font_awesome_umbrella = 0xf0e9,
   e_font_awesome_umbrella_beach = 0xf5ca,
   e_font_awesome_underline = 0xf0cd,
   e_font_awesome_undo = 0xf0e2,
   e_font_awesome_undo_alt = 0xf2ea,
   e_font_awesome_universal_access = 0xf29a,
   e_font_awesome_university = 0xf19c,
   e_font_awesome_unlink = 0xf127,
   e_font_awesome_unlock = 0xf09c,
   e_font_awesome_unlock_alt = 0xf13e,
   e_font_awesome_upload = 0xf093,
   e_font_awesome_user = 0xf007,
   e_font_awesome_user_alt = 0xf406,
   e_font_awesome_user_alt_slash = 0xf4fa,
   e_font_awesome_user_astronaut = 0xf4fb,
   e_font_awesome_user_check = 0xf4fc,
   e_font_awesome_user_circle = 0xf2bd,
   e_font_awesome_user_clock = 0xf4fd,
   e_font_awesome_user_cog = 0xf4fe,
   e_font_awesome_user_edit = 0xf4ff,
   e_font_awesome_user_friends = 0xf500,
   e_font_awesome_user_graduate = 0xf501,
   e_font_awesome_user_injured = 0xf728,
   e_font_awesome_user_lock = 0xf502,
   e_font_awesome_user_md = 0xf0f0,
   e_font_awesome_user_minus = 0xf503,
   e_font_awesome_user_ninja = 0xf504,
   e_font_awesome_user_nurse = 0xf82f,
   e_font_awesome_user_plus = 0xf234,
   e_font_awesome_user_secret = 0xf21b,
   e_font_awesome_user_shield = 0xf505,
   e_font_awesome_user_slash = 0xf506,
   e_font_awesome_user_tag = 0xf507,
   e_font_awesome_user_tie = 0xf508,
   e_font_awesome_user_times = 0xf235,
   e_font_awesome_users = 0xf0c0,
   e_font_awesome_users_cog = 0xf509,
   e_font_awesome_utensil_spoon = 0xf2e5,
   e_font_awesome_utensils = 0xf2e7,
   e_font_awesome_vector_square = 0xf5cb,
   e_font_awesome_venus = 0xf221,
   e_font_awesome_venus_double = 0xf226,
   e_font_awesome_venus_mars = 0xf228,
   e_font_awesome_vial = 0xf492,
   e_font_awesome_vials = 0xf493,
   e_font_awesome_video = 0xf03d,
   e_font_awesome_video_slash = 0xf4e2,
   e_font_awesome_vihara = 0xf6a7,
   e_font_awesome_voicemail = 0xf897,
   e_font_awesome_volleyball_ball = 0xf45f,
   e_font_awesome_volume_down = 0xf027,
   e_font_awesome_volume_mute = 0xf6a9,
   e_font_awesome_volume_off = 0xf026,
   e_font_awesome_volume_up = 0xf028,
   e_font_awesome_vote_yea = 0xf772,
   e_font_awesome_vr_cardboard = 0xf729,
   e_font_awesome_walking = 0xf554,
   e_font_awesome_wallet = 0xf555,
   e_font_awesome_warehouse = 0xf494,
   e_font_awesome_water = 0xf773,
   e_font_awesome_wave_square = 0xf83e,
   e_font_awesome_weight = 0xf496,
   e_font_awesome_weight_hanging = 0xf5cd,
   e_font_awesome_wheelchair = 0xf193,
   e_font_awesome_wifi = 0xf1eb,
   e_font_awesome_wind = 0xf72e,
   e_font_awesome_window_close = 0xf410,
   e_font_awesome_window_maximize = 0xf2d0,
   e_font_awesome_window_minimize = 0xf2d1,
   e_font_awesome_window_restore = 0xf2d2,
   e_font_awesome_wine_bottle = 0xf72f,
   e_font_awesome_wine_glass = 0xf4e3,
   e_font_awesome_wine_glass_alt = 0xf5ce,
   e_font_awesome_won_sign = 0xf159,
   e_font_awesome_wrench = 0xf0ad,
   e_font_awesome_x_ray = 0xf497,
   e_font_awesome_yen_sign = 0xf157,
   e_font_awesome_yin_yang = 0xf6ad

};

#endif // DOXYGEN_SHOULD_SKIP_THIS
