<?php
// $Id$

/**
 * @file
 * The subclass simply adds properties,
 * for field-specific subclasses to use if they need to.
 */
class emvideo_handler_argument_duration extends content_handler_argument_numeric {
  /**
   * Override the behavior of title().
   */
  function title() {
    $duration = $this->argument;
    return emvideo_seconds_to_time($duration);
  }
}