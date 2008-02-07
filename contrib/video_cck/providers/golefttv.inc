<?php
// $Id$
define('VIDEO_CCK_GOLEFTTV_MAIN_URL', 'http://goleft.tv/');

function video_cck_golefttv_info() {
  $name = t('GoLeft TV');
  $features = array(
    array(t('Autoplay'), t('Yes'), ''),
    array(t('RSS attachment'), t('No'), ''),
    array(t('Thumbnails'), t('Yes'), ''),
  );
  return array(
    'provider' => 'golefttv',
    'name' => $name,
    'url' => VIDEO_CCK_GOLEFTTV_MAIN_URL,
    'settings_description' => t('These settings specifically affect videos displayed from !provider.', array('!provider' => l($name, VIDEO_CCK_GOLEFTTV_MAIN_URL, array('target' => '_blank')))),
    'supported_features' => $features,
  );
}

function video_cck_golefttv_settings() {
  $form = array();
  return $form;
}

function video_cck_golefttv_extract($embed) {
  // http://goleft.tv/view.asp?v=1024
  // <object codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=9,0,0,0" width="366" height="330" align="middle" id="player" classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000"><param name="movie" value="http://www.goleft.tv/interface/flash/embed_preview.swf?id=1024" /><param name="quality" value="high" /><param name="play" value="true" /><param name="loop" value="true" /><param name="scale" value="showall" /><param name="wmode" value="window" /><param name="devicefont" value="false" /><param name="bgcolor" value="#ffffff" /><param name="menu" value="true" /><param name="allowFullScreen" value="true" /><param name="allowScriptAccess" value="always" /><param name="salign" value="" /><embed width="366" height="330" src="http://www.goleft.tv/interface/flash/embed_preview.swf?id=1024" quality="high" pluginspage="http://www.macromedia.com/go/getflashplayer" align="middle" play="true" loop="true" scale="showall" wmode="window" devicefont="false" bgcolor="#ffffff" name="player" menu="true" allowFullScreen="true" allowScriptAccess="always" salign="" type="application/x-shockwave-flash"></embed></object>
  return array(
    '@goleft\.tv/viewer\.asp\?v=([^"\&]+)@i',
    '@goleft\.tv/view\.asp\?v=([^"\&]+)@i',
    '@goleft\.tv/interface/flash/embed_preview\.swf\?id\=([^"\&]+)"@i',
  );
}

function video_cck_golefttv_video_link($video_code) {
  return 'http://goleft.tv/viewer.asp?v=' . $video_code;
}

function theme_video_cck_golefttv_flash($video, $width, $height, $field, $item, $autoplay) {
  static $count;
  // set css id count
  $count++;
  $output .= "<object codebase=\"http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=9,0,0,0\" width=\"$width\" height=\"$height\" align=\"middle\" id=\"emfield-videocck-player-goleft-$count\" classid=\"clsid:d27cdb6e-ae6d-11cf-96b8-444553540000\"><param name=\"movie\" value=\"http://www.goleft.tv/interface/flash/embed_preview.swf?id=$video\" /><param name=\"quality\" value=\"high\" /><param name=\"play\" value=\"true\" /><param name=\"loop\" value=\"true\" /><param name=\"scale\" value=\"showall\" /><param name=\"wmode\" value=\"window\" /><param name=\"devicefont\" value=\"false\" /><param name=\"bgcolor\" value=\"#ffffff\" /><param name=\"menu\" value=\"true\" /><param name=\"allowFullScreen\" value=\"true\" /><param name=\"allowScriptAccess\" value=\"always\" /><param name=\"salign\" value=\"\" /><embed width=\"$width\" height=\"$height\" src=\"http://www.goleft.tv/interface/flash/embed_preview.swf?id=$video\" quality=\"high\" pluginspage=\"http://www.macromedia.com/go/getflashplayer\" align=\"middle\" play=\"true\" loop=\"true\" scale=\"showall\" wmode=\"window\" devicefont=\"false\" bgcolor=\"#ffffff\" name=\"player\" menu=\"true\" allowFullScreen=\"true\" allowScriptAccess=\"always\" salign=\"\" type=\"application/x-shockwave-flash\"></embed></object>";
  return $output;
}

function video_cck_golefttv_thumbnail($field, $item, $formatter, $node, $width, $height) {
}

function video_cck_golefttv_video($video, $width, $height, $field, $item, $autoplay) {
  $output = theme('video_cck_golefttv_flash', $video, $width, $height, $field, $item, $autoplay);
  return $output;
}

function video_cck_golefttv_preview($video, $width, $height, $field, $item, $autoplay) {
  $output = theme('video_cck_golefttv_flash', $video, $width, $height, $field, $item, $autoplay);
  return $output;
}

