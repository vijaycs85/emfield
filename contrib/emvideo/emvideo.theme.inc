<?php
// $Id$

/**
 * @file
 * This defines the various theme functions for Embedded Video Field (video_cck).
 */

/**
 *  formatter for video_cck_video_embed
 *
 *  this will return the 'embed code', typically used to embed media in an external site or blog.
 */
function theme_video_cck_video_embed($field, $item, $formatter, $node, $options = array()) {
  /*
    Note you can use this in node.tpl.php, substituting the proper field type:
    $field_type = 'field_video';
    $system_types = _content_type_info();
    $field = $system_types['fields'][$field_type];
    $field['widget'] = $system_types['content types'][$node->type]['fields'][$field_type]['widget'];
    print theme('video_cck_video_embed', $field, $node->{$field_type}[0], 'video_cck_embed', $node);

    or you can set $field to NULL and just use the options array
   */
  if ($item['value'] && $item['provider']) {
    $output = drupal_get_form('video_cck_embed_form', $field, $item, $formatter, $node, $options);
  }
  return $output;
}

/**
 *  This will return a provided thumbnail image for a video.
 *
 *  @param $field
 *    This is the field providing settings for the video thumbnail.
 *  @param $item
 *    This is the data returned by the field. It requires at the least to be an array with 'value' and 'provider'.
 *    $item['value'] will be the video code, and $item['provider'] will be the provider, such as youtube.
 *  @param $formatter
 *    This is the formatter for the view. This will nearly always be video_thumbnail.
 *  @param $node
 *    This is the node object containing the field.
 *  @param $no_link
 *    optional. if FALSE, then we provide a link to the node. (In retrospect, this should have been $link, defaulting to TRUE. TODO: fix? problem though is that this goes deeper up the tree.)
 *  @param $options
 *    optional array. this is to pass optional overrides. currently:
 *    $options['width'] and $options['height'], if provided, will override any field settings for the thumbnail w/h.
 *    $options['link_url'], if provided, will cause the thumbnail link to go to another URL other than node/nid. $no_link must be FALSE.
 *    $options['link_title'], if provided, will set the title of the link when no image is provided. otherwise, it defaults to 'See video'.
 *    $options['image_title'], if provided, will set the title attribute of the href link, defaulting to $options['link_title'].
 *    $options['image_alt'], if provided, will set the alt attribute of the href link, defaulting to $options['link_title'].
 *    $options['thumbnail_url'], if provided, will completely override the thumbnail image entirely.
 */
function theme_video_cck_video_thumbnail($field, $item, $formatter, $node, $no_link = FALSE, $options = array()) {
  if ($item['value'] && $item['provider']) {
    // if we've set $options['thumbnail_url'], then we'll just use that.
    // otherwise, if we have emthumb installed, then give it a chance to override our thumbnail
    $thumbnail_url = $options['thumbnail_url'] ? $options['thumbnail_url'] : module_invoke('emthumb', 'thumbnail_url', $item);

    // if we don't have a custom thumbnail, then see if the provider gives us a thumbnail
    $thumbnail_url = $thumbnail_url ? $thumbnail_url : module_invoke('emfield', 'include_invoke', 'video_cck', $item['provider'], 'thumbnail', $field, $item, $formatter, $node, $width, $height, $options);

    // if we still don't have a thumbnail, then apply a default thumbnail, if it exists
    if (!$thumbnail_url) {
      $default_thumbnail_url = $field['widget']['thumbnail_default_path'] ? $field['widget']['thumbnail_default_path'] : variable_get('video_cck_default_thumbnail_path', NULL);
      if ($default_thumbnail_url) {
        $thumbnail_url = base_path() . $default_thumbnail_url;
      }
    }
  }
  else {
    // seems to be an unknown video
    // apply a default thumbnail, if it exists
    if (!$thumbnail_url) {
      $default_thumbnail_url = $field['widget']['thumbnail_default_path'] ? $field['widget']['thumbnail_default_path'] : variable_get('video_cck_default_thumbnail_path', NULL);
      if ($default_thumbnail_url) {
        $thumbnail_url = base_path() . $default_thumbnail_url;
      }
    }
  }

  $link_url = isset($options['link_url']) ? $options['link_url'] : 'node/'. $node->nid;
  $link_title = isset($options['link_title']) ? $options['link_title'] : t('See video');
  $image_title = isset($options['image_title']) ? $options['image_title'] : $link_title;
  $image_alt = isset($options['image_alt']) ? $options['image_alt'] : $link_title;

  if ($thumbnail_url) {
    $width = isset($options['width']) ? $options['width'] : NULL;
    $width = isset($width) ? $width : ($field['widget']['thumbnail_width'] ? $field['widget']['thumbnail_width'] : variable_get('video_cck_default_thumbnail_width', VIDEO_CCK_DEFAULT_THUMBNAIL_WIDTH));
    $height = isset($options['height']) ? $options['height'] : NULL;
    $height = isset($height) ? $height : ($field['widget']['thumbnail_height'] ? $field['widget']['thumbnail_height'] : variable_get('video_cck_default_thumbnail_height', VIDEO_CCK_DEFAULT_THUMBNAIL_HEIGHT));
    if ($no_link) { //thickbox requires the thumbnail returned without the link
      $output = '<img src="'. $thumbnail_url .'" width="'. $width  .'" height="'. $height  .'" alt="'. $image_alt .'" title="'. $image_title .'" />';
    }
    else {
      $output = l('<img src="'. $thumbnail_url .'" width="'. $width  .'" height="'. $height  .'" alt="'. $image_alt .'" title="'. $image_title .'" />', $link_url, array(), NULL, NULL, false, true);
    }
  }
  else {
     // if all else fails, then just print a 'see video' link.
    if ($no_link) {
      $output = ''; //thickbox won't work without a thumbnail
    }
    else {
      $output = l($link_title, $link_url);
    }
  }

  return $output;
}

function theme_video_cck_video_video($field, $item, $formatter, $node, $options = array()) {
  if ($item['value'] && $item['provider']) {
    $embed = $item['value'];
    $width = $options['width'] ? $options['width'] : ($field['widget']['video_width'] ? $field['widget']['video_width'] : variable_get('video_cck_default_video_width', VIDEO_CCK_DEFAULT_VIDEO_WIDTH));
    $height = $options['height'] ? $options['height'] : ($field['widget']['video_height'] ? $field['widget']['video_height'] : variable_get('video_cck_default_video_height', VIDEO_CCK_DEFAULT_VIDEO_HEIGHT));
    $autoplay = $options['autoplay'] ? $options['autoplay'] : $field['widget']['video_autoplay'];
    $output = module_invoke('emfield', 'include_invoke', 'video_cck', $item['provider'], 'video', $embed, $width, $height, $field, $item, $autoplay, $options);
  }
  $output .= 'test2';
  return $output;
}

function theme_video_cck_default($field, $item, $formatter, $node, $options = array()) {
  return theme('video_cck_video_video', $field, $item, $formatter, $node, $options);
}

function theme_video_cck_video_preview($field, $item, $formatter, $node, $options = array()) {
  if ($item['value'] && $item['provider']) {
    $embed = $item['value'];
    $width = $options['width'] ? $options['width'] : ($field['widget']['preview_width'] ? $field['widget']['preview_width'] : variable_get('video_cck_default_preview_width', VIDEO_CCK_DEFAULT_PREVIEW_WIDTH));
    $height = $options['height'] ? $options['height'] : ($field['widget']['preview_height'] ? $field['widget']['preview_height'] : variable_get('video_cck_default_preview_height', VIDEO_CCK_DEFAULT_PREVIEW_HEIGHT));
    $autoplay = $options['autoplay'] ? $options['autoplay'] : $field['widget']['preview_autoplay'];
    $output = module_invoke('emfield', 'include_invoke', 'video_cck', $item['provider'], 'preview', $embed, $width, $height, $field, $item, $autoplay, $options);
  }
  return $output;
}

function theme_video_cck_thickbox($field, $item, $formatter, $node, $options = array()) {
  $thumbnail = theme('video_cck_video_thumbnail', $field, $item, 'video_thumbnail', $node, true, $options);

  $destination = 'video-cck/thickbox/'. $node->nid .'/'. $field['widget']['video_width'] .'/'. $field['widget']['video_height'] .'/'. $field['field_name'];
  $options = array(
    'attributes'=> array(
      'title' => $title,
      'class' => 'thickbox',
      'rel' => $field['type_name']),
    'query' => NULL,
    'fragment' => NULL,
    'absolute' => FALSE,
    'html' => TRUE,
 );
 $output = l($thumbnail, $destination, $options);
 return $output;
}
