<?php
// $Id$

/**
 *  @file
 *  Basic theme functions for Embedded Media Field.
 */

/**
 * Display a link to the original media.
 */
function theme_emfield_formatter_default($element) {
  if ($uri = $element['#item']['uri']) {
    $media = emapi_media_from_uri($uri);
    if ($media) {
      return l($uri, $media->url());
    }
  }
}
