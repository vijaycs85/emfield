<?php
// $Id$
define('VIDEO_CCK_BLIPTV_MAIN_URL', 'http://blip.tv/');

function video_cck_bliptv_info() {
  $name = t('Blip.tv');
  $features = array(
    array(t('Thumbnails'), t('Yes'), ''),
    array(t('Autoplay'), t('Yes'), ''),
  );
  return array(
    'provider' => 'bliptv',
    'name' => $name,
    'url' => VIDEO_CCK_BLIPTV_MAIN_URL,
    'settings_description' => t('These settings specifically affect videos displayed from !provider.', array('!provider' => l($name, VIDEO_CCK_BLIPTV_MAIN_URL, array('target' => '_blank')))),
    'supported_features' => $features,
  );
}

function video_cck_bliptv_settings() {
  $form = array();
  return $form;
}

function video_cck_bliptv_data($field, $item) {
  $data = array();

  // use the page id, since we'll have that in most cases (except in embed pastes, which gets parsed during extraction)
  // we use this to get an rss feed w/ all the info for the video. interesting reading ;)
  $rss = video_cck_bliptv_request($item['value']);

  // get our thumbnail url
  $data['thumbnail'] = $rss['ITEM']['MEDIA:THUMBNAIL'][1]['URL'];

  // this is the code actually used by the player, even though it's different than for the page
  $data['post_id'] = $rss['ITEM']['BLIP:POSTS_ID'][0];

  // this gets sent to the player
  $data['flv'] = $rss['ITEM']['ENCLOSURE'][1]['URL'];
  return $data;
}

function video_cck_bliptv_request($code, $cacheable = TRUE) {
  $args = array();
  return module_invoke('emfield', 'request_xml', 'bliptv', "http://blip.tv/file/$code?skin=rss", $args, $cacheable, false, $code);
}

function video_cck_bliptv_extract($embed) {
  // http://blip.tv/file/177952
  // http://blip.tv/file/177952/

  // http://blip.tv/file/177952?skin=rss

  // this gets all convoluted, because the file code is different than the video post id, which is different than the video filename,
  // and they don't all show up in the same places :(
  //<center>                              <script type="text/javascript" src="http://blip.tv/scripts/pokkariPlayer.js"></script><script type="text/javascript" src="http://blip.tv/syndication/write_player?skin=js&posts_id=182146&source=3&autoplay=true&file_type=flv&player_width=&player_height="></script><div id="blip_movie_content_182146"><a href="http://blip.tv/file/get/Make-WhatDoYouMake201.flv" onclick="play_blip_movie_182146(); return false;"><img src="http://blip.tv/file/get/Make-WhatDoYouMake201.flv.jpg" border="0" title="Click To Play" /></a><br /><a href="http://blip.tv/file/get/Make-WhatDoYouMake201.flv" onclick="play_blip_movie_182146(); return false;">Click To Play</a></div>                   </center>
  if ($embed && preg_match('@http://blip\.tv/syndication/write_player\?skin=js\&posts_id=([^\&]*)\&@i', $embed, $matches)) {
    $match = $matches[1];
    unset($matches);
    $result = drupal_http_request("http://blip.tv/syndication/write_player/?posts_id=$match&skin=js");
    if (preg_match('@setPermalinkUrl\(\"http://blip.tv/file/view/([^/\?\"]*)[/\?\"]@i', $result->data, $matches)) {
      $code = $matches[1];
    }
  }
  else if ($embed && preg_match('@blip\.tv/file/view/([^\?]*)[/\?]@i', $embed, $matches)) {
    $code = $matches[1];
  }
  else if ($embed && preg_match('@blip\.tv/file/view/(.*)@i', $embed, $matches)) {
    $code = $matches[1];
  }
  else if ($embed && preg_match('@blip\.tv/file/([^/\?]*)[/\?]@i', $embed, $matches)) {
    $code = $matches[1];
  }
  else if ($embed && preg_match('@blip\.tv/file/(.*)@i', $embed, $matches)) {
    $code = $matches[1];
  }
  if ($code) {
    return $code;
  }
  return array();
}

function video_cck_bliptv_video_link($video_code) {
  return 'http://blip.tv/file/' . $video_code;
}

function theme_video_cck_bliptv_flash($embed, $width, $height, $field, $item, $autoplay, $flv, $thumbnail) {
  if ($embed) {
    $autoplay = $autoplay ? 'autoStart=true' : 'autoStart=false';
    $output .= '<embed wmode="transparent" src="http://blip.tv/scripts/flash/blipplayer.swf?' . $autoplay . '&file=' . $flv . '%3Fsource%3D3" quality="high" width="' .$width . '" height="' . $height . '" name="movie" type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer"></embed>';
  }
  return $output;
}

function video_cck_bliptv_thumbnail($field, $item, $formatter, $node, $width, $height) {
  return $item['data']['thumbnail'];
}

function video_cck_bliptv_video($embed, $width, $height, $field, $item, $autoplay) {
  $flv = $item['data']['flv'];
  $thumbnail = $item['data']['thumbnail'];
  $output = theme('video_cck_bliptv_flash', $item['data']['post_id'], $width, $height, $field, $item, $autoplay, $flv, $thumbnail);
  return $output;
}

function video_cck_bliptv_preview($embed, $width, $height, $field, $item, $autoplay) {
  $flv = $item['data']['flv'];
  $thumbnail = $item['data']['thumbnail'];
  $output = theme('video_cck_bliptv_flash', $item['data']['post_id'], $width, $height, $field, $item, $autoplay, $flv, $thumbnail);
  return $output;
}

