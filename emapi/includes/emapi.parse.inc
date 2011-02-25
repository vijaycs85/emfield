<?php

/**
 * @file
 * Parsing JSON callback for Embedded Media API.
 */

/**
 * Callback for /emapi/parse/json.
 */
function emapi_parse_json() {
  $url = $_GET['url'];
  if ($media = emapi_parse($url)) {
    emapi_media_save($media);
    drupal_json(array('status' => TRUE, 'uri' => $media->get_uri()));
  }
  else {
    drupal_json(array('status' => FALSE));
  }
}
