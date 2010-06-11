<?php
// $Id$

/**
 * @file Contains the variables and defaults used by Embedded Media API.
 */

/**
 * Define our constants.
 */

/**
 * This is the variable namespace, automatically prepended to module variables.
 */
define('EMAPI_NAMESPACE', 'emapi__');

/**
 * Wrapper for variable_get() using the Embedded Media API variable registry.
 *
 * @param string $name
 *  The variable name to retrieve. Note that it will be namespaced by
 *  pre-pending EMAPI_NAMESPACE, as to avoid variable collisions
 *  with other modules.
 * @param unknown $default
 *  An optional default variable to return if the variable hasn't been set
 *  yet. Note that within this module, all variables should already be set
 *  in the emapi_variable_default() function.
 * @return unknown
 *  Returns the stored variable or its default.
 *
 * @see emapi_variable_set()
 * @see emapi_variable_del()
 * @see emapi_variable_default()
 */
function emapi_variable_get($name, $default = NULL) {
  // Allow for an override of the default.
  // Useful when a variable is required (like $path), but namespacing is still
  // desired.
  if (!isset($default)) {
    $default = emapi_variable_default($name);
  }
  // Namespace all variables.
  $variable_name = EMAPI_NAMESPACE . $name;
  return variable_get($variable_name, $default);
}

/**
 * Wrapper for variable_set() using the Embedded Media API variable registry.
 *
 * @param string $name
 *  The variable name to set. Note that it will be namespaced by
 *  pre-pending EMAPI_NAMESPACE, as to avoid variable collisions with
 *  other modules.
 * @param unknown $value
 *  The value for which to set the variable.
 * @return unknown
 *  Returns the stored variable after setting.
 *
 * @see emapi_variable_get()
 * @see emapi_variable_del()
 * @see emapi_variable_default()
 */
function emapi_variable_set($name, $value) {
  $variable_name = EMAPI_NAMESPACE . $name;
  return variable_set($variable_name, $value);
}

/**
 * Wrapper for variable_del() using the Embedded Media API variable registry.
 *
 * @param string $name
 *  The variable name to delete. Note that it will be namespaced by
 *  pre-pending EMAPI_NAMESPACE, as to avoid variable collisions with
 *  other modules.
 *
 * @see emapi_variable_get()
 * @see emapi_variable_set()
 * @see emapi_variable_default()
 */
function emapi_variable_del($name) {
  $variable_name = EMAPI_NAMESPACE . $name;
  variable_del($variable_name);
}

/**
 * The default variables within the Embedded Media API namespace.
 *
 * @param string $name
 *  Optional variable name to retrieve the default. Note that it has not yet
 *  been pre-pended with the EMAPI_NAMESPACE namespace at this time.
 * @return unknown
 *  The default value of this variable, if it's been set, or NULL, unless
 *  $name is NULL, in which case we return an array of all default values.
 *
 * @see emapi_variable_get()
 * @see emapi_variable_set()
 * @see emapi_variable_del()
 */
function emapi_variable_default($name = NULL) {
  static $defaults;

  if (!isset($defaults)) {
    $defaults = array(
      'class_emapimedia_description' => 'Base Embedded Media Object, to be extended by individual providers.',
      'cache_expire' => 3600,
    );
  }

  if (!isset($name)) {
    return $defaults;
  }

  if (isset($defaults[$name])) {
    return $defaults[$name];
  }
}

/**
 * Return the fully namespace variable name.
 *
 * @param string $name
 *  The variable name to retrieve the namespaced name.
 * @return string
 *  The fully namespace variable name, prepended with
 *  EMAPI_NAMESPACE.
 */
function emapi_variable_name($name) {
  return EMAPI_NAMESPACE . $name;
}
