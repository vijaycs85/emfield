<?php
// $Id$
define('VIDEO_CCK_CURRENTTV_MAIN_URL', 'http://current.tv/');

function video_cck_currenttv_info() {
  $name = t('Current TV');
  $features = array(
    array(t('Autoplay'), t('No'), ''),
    array(t('RSS attachment'), t('No'), t('')),
    array(t('Thumbnails'), t('No'), ''),
  );
  return array(
    'provider' => 'currenttv',
    'name' => $name,
    'url' => VIDEO_CCK_CURRENTTV_MAIN_URL,
    'settings_description' => t('These settings specifically affect videos displayed from !provider.', array('!provider' => l($name, VIDEO_CCK_CURRENTTV_MAIN_URL, array('target' => '_blank')))),
    'supported_features' => $features,
  );
}

function video_cck_currenttv_settings() {
  $form = array();
  return $form;
}

function video_cck_currenttv_extract($embed) {
  // http://www.current.tv/screening.htm?id=38373500
  // <embed src="http://www.current.tv/studio/vm2/vmm.swf" flashvars="videoType=preview&mrss=http%3a%2f%2fwww.current.tv%2Frss%2Fvideo%2Fviewing.htm%3Fid=38373500%26ctv=1" pluginspage="http://www.macromedia.com/go/getflashplayer" type="application/x-shockwave-flash" quality="high" height="400" width="400"></embed>

  return array(
    '@current\.tv\%2Frss\%2Fvideo\%2Fviewing\.htm\%3Fid=([^\%]*)"@i',
    '@current\.tv/screening\.htm\?id=([^"\&]*)@i',
  );
}

function video_cck_currenttv_video_link($video_code) {
  return 'http://current.tv/screening.htm?id=' . $video_code;
}

function video_cck_currenttv_thumbnail($field, $item, $formatter, $node, $width, $height) {
  return $tn;
}

function theme_video_cck_currenttv_flash($video_code, $width, $height, $autoplay) {
  if ($video_code) {
    $output .= "<embed src=\"http://www.current.tv/studio/vm2/vmm.swf\" flashvars=\"videoType=preview&mrss=http%3a%2f%2fwww.current.tv%2Frss%2Fvideo%2Fviewing.htm%3Fid=$video_code%26ctv=1\" pluginspage=\"http://www.macromedia.com/go/getflashplayer\" type=\"application/x-shockwave-flash\" quality=\"high\" height=\"$height\" width=\"$width\"></embed>";
  }
  return $output;
}

function video_cck_currenttv_video($embed, $width, $height, $field, $item, $autoplay) {
  $output = theme('video_cck_currenttv_flash', $embed, $width, $height, $autoplay);
  return $output;
}

function video_cck_currenttv_preview($embed, $width, $height, $field, $item, $autoplay) {
  $output = theme('video_cck_currenttv_flash', $embed, $width, $height, $autoplay);
  return $output;
}

