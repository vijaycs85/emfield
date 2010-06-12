<?php
// $Id$

/**
 * @file
 * Administrative callbacks.
 */

/**
 * Page callback for admin/content/emapi.
 */
function emapi_admin_list_page() {
  $limit = isset($_GET['limit']) ? $_GET['limit'] : emapi_variable_get('admin_pager_query');
  $results = pager_query("SELECT emid FROM {emapi_media} ORDER BY timestamp DESC", $limit);
  while ($result = db_fetch_object($results)) {
    $media[] = $result->emid;
  }
  $media = emapi_media_load_multiple($media);
  foreach ($media as $item) {
    $output .= ' '. l($item->get_uri(), $item->url());
  }
  return $output;
}
