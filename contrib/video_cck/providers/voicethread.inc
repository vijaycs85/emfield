<?php

define('VIDEO_CCK_VOICETHREAD_MAIN_URL', 'http://www.voicethread.com/');

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
function video_cck_voicethread_info() {
  $name = t('VoiceThread');
  $features = array(
    array(t('Autoplay'), t('Yes'), ''),
    array(t('RSS Attachment'), t('No'), ''),
    array(t('Thumbnails'), t('No'), t('')),
    array(t('Custom player colors'), t('No'), t('')),
  );
  return array(
    'provider' => 'voicethread',
    'name' => $name,
    'url' => VIDEO_CCK_VOICETHREAD_MAIN_URL,
    // 'settings_description' => '[settings description]',
    'settings_description' => t('These settings specifically affect videos displayed from !voicethread.', array('!voicethread' => l($name, VIDEO_CCK_VOICETHREAD_MAIN_URL, array('target' => '_blank')), )),
    'supported_features' => $features,
  );
}

/**
 * hook video_cck_PROVIDER_settings
 * this should return a subform to be added to the video_cck_settings() admin settings page.
 * note that a form field will already be provided, at $form['PROVIDER'] (such as $form['youtube'])
 * so if you want specific provider settings within that field, you can add the elements to that form field.
 */

function video_cck_voicethread_settings() {
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

function video_cck_voicethread_extract($embed = '') {
  return array(
    '@voicethread\.com/book.swf\?b=(\d+)@i',
    '@voicethread\.com/share/(\d+)@i',
  );
}

/**
 * hook video_cck_PROVIDER_embedded_link($book_id)
 * returns a link to view the video at the provider's site
 *  @param $book_id
 *    the id of the VoiceThread
 *  @return
 *    a string containing the URL to view the video at the original provider's site
 */
function video_cck_voicethread_embedded_link($book_id) {
  return 'http://www.voicethread.com/share/'. $book_id;
}

/**
 * the embedded flash displaying the voicethread
 */
function theme_video_cck_voicethread_flash($embed, $width, $height, $autoplay) {
  if ($embed) {
    if ($autoplay) {
      $autoplay_value = '&autoplay=1';
    }
    $output = "    <object type=\"application/x-shockwave-flash\" height=\"$height\" width=\"$width\" data=\"http://www.voicethread.com/book.swf?b=$embed" . $autoplay_value ."\" id=\"VideoPlayback\" >
      <param name=\"movie\" value=\"http://www.voicethread.com/book.swf?b=$embed" . $autoplay_value ."\" wmode=\"transparent\" />
    </object>\n";
  }
  return $output;
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
function video_cck_voicethread_video($embed, $width, $height, $field, $item, $autoplay) {
  $output = theme('video_cck_voicethread_flash', $embed, $width, $height, $autoplay);
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
function video_cck_voicethread_preview($embed, $width, $height, $field, $item, $autoplay) {
  $output = theme('video_cck_voicethread_flash', $embed, $width, $height, $autoplay);
  return $output;
}
