<?php

/**
 * @file
 * This provider file has been supplanted by the Media: Flickr module.
 */

function emimage_flickr_obsolete() {
  drupal_set_message(t('Please install the !media_flickr module for Flickr integration with Embedded Image Field.', array('!media_flickr' => l(t('Media: Flickr'), 'http://drupal.org/project/media_flickr'))), 'error');
}
