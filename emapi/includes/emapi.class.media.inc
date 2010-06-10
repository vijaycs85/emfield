<?php
// $Id$

/**
 * @file
 * Base Embedded Media Object, to be extended by individual providers.
 */

class EmapiMedia {
  // The raw URL or embed code from our provider.
  public $original;

  // The URI for final storage (using the format of Drupal 7's PHP Stream
  // Wrappers, in the form of scheme://unique-code).
  public $uri;

  // The value extracted from the original.
  public $value;

  // The provider; matches the scheme:// of the $uri.
  public $provider = '';

  // The specific media identifier prefix. The URI will be built from this
  // by default, using scheme://IDENTIFIER/value.
  public $identifier = 'id';

  // An array of any provider-specific metadata to store.
  public $data = array();

  // Regex patterns for matching while parsing a URL.
  public $patterns = array();

  // Use these for building the URL to the original location.
  public $prefix_url = '';
  public $suffix_url = '';

  public function __construct($uri = NULL) {
    $this->set_uri($uri);
  }

  public function get_original() {
    return $this->get('original');
  }
  public function set_original($value) {
    return $this->set('original', $value);
  }

  public function get_uri() {
    return $this->get('uri');
  }
  public function set_uri($value) {
    if ($id = $this->extract_value($value)) {
      $this->set_value($id);
    }
    return $this->set('uri', $value);
  }

  public function get_value() {
    return $this->get('value');
  }
  public function set_value($value) {
    return $this->set('value', $value);
  }

  public function get_provider() {
    return $this->get('provider');
  }
  public function set_provider($value) {
    return $this->set('provider', $value);
  }

  public function get_identifier() {
    return $this->get('identifier');
  }
  public function set_identifier($value) {
    return $this->set('identifier', $value);
  }

  public function get_data() {
    return $this->get('data');
  }
  public function set_data($value) {
    return $this->set('data', $value);
  }

  public function get_patterns() {
    return $this->get('patterns');
  }
  public function set_patterns($value) {
    return $this->set('patterns', $value);
  }

  public function get_prefix_url() {
    return $this->get('prefix_url');
  }
  public function set_prefix_url($value) {
    return $this->set('prefix_url', $value);
  }

  public function get_suffix_url() {
    return $this->get('suffix_url');
  }
  public function set_suffix_url($value) {
    return $this->set('suffix_url', $value);
  }

  public function get($variable) {
    return $this->$variable;
  }
  public function set($variable, $value) {
    return $this->$variable = $value;
  }

  public function parse($original) {
    if (is_array($patterns = $this->get_patterns())) {
      foreach ($patterns as $pattern) {
        if (preg_match($pattern, $original, $matches)) {
          $this->set_original($original);
          // Note that we set the value during set_uri.
          return $this->set_uri($this->get_provider() .'://'. $this->get_identifier() .'/'. $matches[1]);
        }
      }
    }
  }

  /**
   * A helper function for set_uri. This allows the value to be captured.
   */
  public function extract_value($uri) {
    if (preg_match('@/'. $this->get_identifier() .'/([^/]*)@i', $uri, $matches)) {
      return $matches[1];
    }
  }

  /**
   * Build the URL to the original location.
   */
  public function url() {
    return $this->get_prefix_url() . $this->get_value() . $this->get_suffix_url();
  }
}
