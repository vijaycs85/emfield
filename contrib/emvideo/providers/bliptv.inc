<?php
// $Id$

/**
 * @file
 * This provider file has been replaced by the Media: BlipTV module.
 */

function emvideo_bliptv_obsolete() {
  drupal_set_message(t('Please install the !media_bliptv module for BlipTV integration with Embedded Video Field and Embedded Audio Field.', array('!media_bliptv' => l(t('Media: BlipTV'), 'http://drupal.org/project/media_bliptv'))), 'error');
}
