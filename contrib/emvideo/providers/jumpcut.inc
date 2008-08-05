<?php
// $Id$

/**
 * @file
 *   This include processes jumpcut media files for use by emfield.module.
 */

define('EMVIDEO_JUMPCUT_MAIN_URL', 'http://jumpcut.com/');

function emvideo_jumpcut_info() {
  $name = t('JumpCut');
  $features = array(
    array(t('Autoplay'), t('No'), ''),
    array(t('RSS Attachment'), t('No'), ''),
    array(t('Thumbnails'), t('No'), ''),
  );
  return array(
    'provider' => 'jumpcut',
    'name' => $name,
    'url' => EMVIDEO_JUMPCUT_MAIN_URL,
    'settings_description' => t('These settings specifically affect videos displayed from !provider.', array('!provider' => l($name, EMVIDEO_JUMPCUT_MAIN_URL, array('target' => '_blank')))),
    'supported_features' => $features,
  );
}

function emvideo_jumpcut_settings() {
  $form = array();
  return $form;
}

function emvideo_jumpcut_extract($embed) {
  return array(
    '@jumpcut\.com/view\?id=(.*)@i',
    '@jumpcut\.com/view\?id=([^\&]*)\&@i',
  );
}

function emvideo_jumpcut_video_link($video_code) {
  return 'http://jumpcut.com/view?id='. $video_code;
}

function theme_emvideo_jumpcut_flash($embed, $width, $height) {
  if ($embed) {
    $output .= '<embed src="http://jumpcut.com/media/flash/jump.swf?id='. $embed .'&asset_type=movie&asset_id='. $embed .'&eb=1" width="'. $width .'" height="'. $height .'" type="application/x-shockwave-flash"></embed>';
  }
  return $output;
}

function emvideo_jumpcut_thumbnail($field, $item, $formatter, $node, $width, $height) {
  return '';
}

function emvideo_jumpcut_video($embed, $width, $height, $field, $item) {
  $output = theme('emvideo_jumpcut_flash', $embed, $width, $height);
  return $output;
}

function emvideo_jumpcut_preview($embed, $width, $height, $field, $item) {
  $output = theme('emvideo_jumpcut_flash', $embed, $width, $height);
  return $output;
}

/**
 * Implementation of hook_emfield_subtheme.
 */
function emvideo_jumpcut_emfield_subtheme() {
  return array (
    'emvideo_jumpcut_flash' => array (
      'arguments' => array('embed' => NULL, 'width' => NULL, 'height' => NULL),
      'file' => 'providers/jumpcut.inc'
    )
  );
}
