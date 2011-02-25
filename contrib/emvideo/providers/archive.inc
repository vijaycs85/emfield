<?php

/**
 * @file
 * This provider file has been replaced by the Media: Archive module.
 */

function emvideo_archive_obsolete() {
  drupal_set_message(t('Please install the !media_archive module for Archive.org integration with Embedded Video Field and Embedded Audio Field.', array('!media_archive' => l(t('Media: Archive'), 'http://drupal.org/project/media_archive'))), 'error');
}
