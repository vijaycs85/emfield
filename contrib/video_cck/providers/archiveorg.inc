<?php
// $Id$

define('VIDEO_CCK_ARCHIVEORG_MAIN_URL', 'http://www.archive.org/');

/**
 * hook video_cck_PROVIDER_info
 * this returns information relevant to a specific 3rd party video provider
 * @return
 *   an array of strings requested by various admin and other forms
 *   'name' => the translated name of the provider
 *   'url' => the url to the main page for the provider
 *   'settings_description' => a description of the provider that will be posted in the admin settings form
 *   'supported_features' => an array of rows describing the state of certain supported features by the provider.
 *      These will be rendered in a table, with the columns being 'Feature', 'Supported', 'Notes'.
 */
function video_cck_archiveorg_info() {
  $name = t('Archive.org');
  $features = array(
    array(t('Autoplay'), t('Yes'), ''),
    array(t('Resizable video'), t('No'), t('Unfortunately, at this time, videos from Archive.org will appear with the player at a constant size of 320x263.')),
    array(t('RSS attachment'), t('No'), ''),
    array(t('Thumbnails'), t('No'), ''),
  );
  return array(
    'provider' => 'archiveorg',
    'name' => $name,
    'url' => VIDEO_CCK_ARCHIVEORG_MAIN_URL,
    'settings_description' => t('These settings specifically affect videos displayed from !archiveorg.', array('!archiveorg' => l($name, VIDEO_CCK_ARCHIVEORG_MAIN_URL, array('target' => '_blank')))),
    'supported_features' => $features,
  );
}

/**
 * hook video_cck_PROVIDER_settings
 * this should return a subform to be added to the video_cck_settings() admin settings page.
 * note that a form field will already be provided, at $form['PROVIDER'] (such as $form['archiveorg'])
 * so if you want specific provider settings within that field, you can add the elements to that form field.
 */
function video_cck_archiveorg_settings() {
  $form = array();
  return $form;
}

/**
 * hook video_cck_PROVIDER_extract
 * this is called to extract the video code from a pasted URL or embed code.
 * @param $embed
 *   an optional string with the pasted URL or embed code
 * @return
 *   either an array of regex expressions to be tested, or a string with the video code to be used
 *   if the hook tests the code itself, it should return either the string of the video code (if matched), or an empty array.
 *   otherwise, the calling function will handle testing the embed code against each regex string in the returned array.
 */
function video_cck_archiveorg_extract($embed = '') {
  // src="http://www.archiveorg.com/v/nvbQQnvxXDk"
  // http://archiveorg.com/watch?v=nvbQQnvxXDk
  // http://www.archiveorg.com/watch?v=YzFCA-xUc8w&feature=dir
  // http://www.archive.org/details/peril_of_doc_ock
  return array(
//    '@archive\.org/details/([^/]*)/(.*)@',
    '@archive\.org/details/(.*)@i',
  );
}

function video_cck_archiveorg_data($field, $item) {
  $data = array();
  $code = $item['embed'];
  $section = $code;
  if ($code && preg_match('@([^/]*)/(.*)@', $code, $matches)) {
    $section = $matches[1];
    $code = $matches[2];
  }
  $data['section'] = $section;
  $data['video'] = $code;
  return $data;
}

/**
 * hook video_cck_PROVIDER_embedded_link($video_code)
 * returns a link to view the video at the provider's site
 *  @param $video_code
 *    the string containing the video to watch
 *  @return
 *    a string containing the URL to view the video at the original provider's site
 */
function video_cck_archiveorg_embedded_link($video_code) {
  return 'http://www.archiveorg.com/details/' . $video_code;
}

/**
 * the embedded flash displaying the archiveorg video
 */
function theme_video_cck_archiveorg_flash($section, $embed, $width, $height, $autoplay) {
  $autoplay = $autoplay ? 'true' : 'false';
  if ($embed) {
    $output .= "<object type=\"application/x-shockwave-flash\" width=\"$width\" height=\"$height\" id=\"FlowPlayer\" data=\"http://www.archive.org/flv/FlowPlayerWhite.swf\">
  <param name=\"movie\" value=\"http://www.archive.org/flv/FlowPlayerWhite.swf\"/>
  <param name=\"scale\" value=\"noScale\"/>
  <param name=\"wmode\" value=\"transparent\"/>
  <param name=\"allowScriptAccess\" value=\"sameDomain\"/>
  <param name=\"quality\" value=\"high\"/>
  <param name=\"flashvars\" value=\"config={
    loop:false,
    autoPlay:$autoplay,
    hideControls:false,
    videoFile:'http://www.archive.org/download/$section/$embed.flv',
  }\"/>
</object>";
  }
  return $output;
}

/**
 * hook video_cck_PROVIDER_thumbnail
 * returns the external url for a thumbnail of a specific video
 * TODO: make the args: ($embed, $field, $item), with $field/$item provided if we need it, but otherwise simplifying things
 *  @param $field
 *    the field of the requesting node
 *  @param $item
 *    the actual content of the field from the requesting node
 *  @return
 *    a URL pointing to the thumbnail
 */
function video_cck_archiveorg_thumbnail($field, $item, $formatter, $node, $width, $height) {
  return '';
}

/**
 * hook video_cck_PROVIDER_video
 * this actually displays the full/normal-sized video we want, usually on the default page view
 *  @param $embed
 *    the video code for the video to embed
 *  @param $width
 *    the width to display the video
 *  @param $height
 *    the height to display the video
 *  @param $field
 *    the field info from the requesting node
 *  @param $item
 *    the actual content from the field
 *  @return
 *    the html of the embedded video
 */
function video_cck_archiveorg_video($embed, $width, $height, $field, $item, $autoplay) {
  $section = $item['data']['section'];
  $code = $item['data']['video'];
  $output = theme('video_cck_archiveorg_flash', $section, $code, $width, $height, $autoplay);
  return $output;
}

/**
 * hook video_cck_PROVIDER_video
 * this actually displays the preview-sized video we want, commonly for the teaser
 *  @param $embed
 *    the video code for the video to embed
 *  @param $width
 *    the width to display the video
 *  @param $height
 *    the height to display the video
 *  @param $field
 *    the field info from the requesting node
 *  @param $item
 *    the actual content from the field
 *  @return
 *    the html of the embedded video
 */
function video_cck_archiveorg_preview($embed, $width, $height, $field, $item, $autoplay) {
  $section = $item['data']['section'];
  $code = $item['data']['video'];
  $output = theme('video_cck_archiveorg_flash', $section, $code, $width, $height, $autoplay);
  return $output;
}
