<?php
// $Id$
define('VIDEO_CCK_AAA_LOCAL_MAIN_URL', '');
define('VIDEO_CCK_AAA_LOCAL_PATH_DEFAULT', 'video');

function video_cck_aaa_local_info() {
  $name = t('Local');
  $features = array(
    array(t('Thumbnails'), t('No'), ''),
    array(t('Autoplay'), t('Yes'), ''),
  );
  return array(
    'provider' => 'aaa_local',
    'name' => $name,
    'url' => VIDEO_CCK_AAA_LOCAL_MAIN_URL,
    'settings_description' => t('These settings specifically affect videos displayed from !provider.', array('!provider' => l($name, VIDEO_CCK_AAA_LOCAL_MAIN_URL, array('target' => '_blank')))),
    'supported_features' => $features,
  );
}

function video_cck_aaa_local_settings() {
  $form = array();
  return $form;
}

function video_cck_aaa_local_data($field, $item) {
  $data = array();
  return $data;
}

/*
stdClass Object ( [filename] => bush.swf
[filepath] => /tmp/video/bush.swf
[filemime] => application/x-shockwave-flash2-preview
[filesize] => 30579
[source] => field_video
[newfile] => 1 ) 0
*/

function video_cck_aaa_local_extract($embed, $field) {
// //   print_r($field);
//   if(count($_POST) == 0) {
//     if (!empty($_SESSION['video_cck_aaa_local_upload_file'])) {
//       file_delete($_SESSION['video_cck_aaa_local_upload_file']->filepath);
//     }
//     unset($_SESSION['video_cck_aaa_local_upload_file']);
//     return array();
//   }
//   elseif ($upload = file_check_upload($field['field_name'])) {
//     $temppath = file_directory_temp() . '/' . variable_get('video_cck_aaa_local_path', VIDEO_CCK_AAA_LOCAL_PATH_DEFAULT);
//     file_check_directory($temppath, TRUE);
//     $file = file_save_upload($upload, $temppath .'/'. $upload->filename, FILE_EXISTS_REPLACE);
//     $file->newfile = TRUE;
//     $_SESSION['video_cck_aaa_local_upload_file'] = $file;
//   }
//   else if (!empty($_SESSION['video_cck_aaa_local_upload_file'])) {
//     $file = $_SESSION['video_cck_aaa_local_upload_file'];
//   }
//   if ($file->filepath) {
//     $return = serialize($file);
// //     print_r($return);
//     return $return;
//   }
  return array();
}

function video_cck_aaa_local_video_link($video_code) {
//   return 'http://blip.tv/file/' . $video_code;
}

function theme_video_cck_aaa_local_flash($embed, $width, $height, $field, $item, $autoplay, $flv, $thumbnail) {
  if ($embed) {
    $autoplay = $autoplay ? 'autoStart=true' : 'autoStart=false';
    $output .= '<embed wmode="transparent" src="http://blip.tv/scripts/flash/blipplayer.swf?' . $autoplay . '&file=' . $flv . '%3Fsource%3D3" quality="high" width="' .$width . '" height="' . $height . '" name="movie" type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer"></embed>';
  }
  return $output;
}

function video_cck_aaa_local_thumbnail($field, $item, $formatter, $node, $width, $height) {
  return $item['data']['thumbnail'];
}

function video_cck_aaa_local_video($embed, $width, $height, $field, $item, $autoplay) {
  $flv = $item['data']['flv'];
  $thumbnail = $item['data']['thumbnail'];
  $output = theme('video_cck_aaa_local_flash', $item['data']['post_id'], $width, $height, $field, $item, $autoplay, $flv, $thumbnail);
  return $output;
}

function video_cck_aaa_local_preview($embed, $width, $height, $field, $item, $autoplay) {
  $flv = $item['data']['flv'];
  $thumbnail = $item['data']['thumbnail'];
  $output = theme('video_cck_aaa_local_flash', $item['data']['post_id'], $width, $height, $field, $item, $autoplay, $flv, $thumbnail);
  return $output;
}

function video_cck_aaa_local_form() {
  $form = array();
//   $form['video_cck_aaa_local_upload'] = array(
//     '#type' => 'file',
//     '#title' => t('Upload video file'),
//     '#description' => t('Uploading a file will override anything entered above. Video uploads are limited to @limit.', array('@limit' => format_size(_video_cck_aaa_local_get_max_upload_size()))),
//   );
  return $form;
}

/**
 * Check PHP's post_max_size and upload_max_filesize settings and determine
 * the maximum size of a file upload.
 * (code from audio.module, via video.module)
 * @return an integer number of bytes
 */
function _video_cck_aaa_local_get_max_upload_size() {
  $limits = array();
  foreach (array('upload_max_filesize', 'post_max_size') as $setting) {
    // the post_max_size and upload_max_filesize settings could be a string
    // ('2m', '1G') or an integer (2097152 or 1073741824).
    $val = ini_get($setting);
    if (!is_numeric($val)) {
      // separate the numeric and alpha parts, then get to multiplying
      $val = trim($val);
      $last = strtolower($val{strlen($val)-1});
      switch($last) {
        case 'g':
          $val *= 1024;
        case 'm':
          $val *= 1024;
        case 'k':
          $val *= 1024;
      }
    }
    $limits[] = $val;
  }
  // the smallest value will be the limiting factor so retun it.
  return min($limits);
}