<?php
// $Id$

/**
 *  @file
 *  Our administrative settings pages.
 */

/**
 * Callback for admin/content/emfield
 */
function emfield_settings() {
  if (!module_exists('video_cck') && !module_exists('image_ncck') && !module_exists('emaudio')) {
    drupal_set_message(t('The Embedded Media Field module does nothing on its own. You should also install the Embedded Video Field, Embedded Image Field, and/or Embedded Audio Field modules from the !modules. (If you do not see them listed there, under the CCK section, you may need to !download from its project page. They are all in the same package.)', array('!download' => l(t('download the module'), 'http://drupal.org/project/emfield'), '!modules' => l(t('modules administration page'), 'admin/build/modules'))), 'error');
  }
  $form = array();
  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General Settings'),
    '#description' => t('These features will be generally available for use by related modules as needed.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  if (module_exists('swfobject_api')) {
    $swfobject_desc = t('As you have the !swfobject_api module installed, Embedded Media Field will use those settings, assuming you\'ve configured them properly. Visit its !settings for more information.', array('!swfobject_api' => l(t('SWFObject API'), 'http://drupal.org/project/swfobject_api', array('target' => '_blank')), l(t('settings page'), 'admin/settings/swfobject_api')));
  }
  else {
    $swfobject_desc = t('If you have the swfobject.js file installed on your system, you can make it available to Embedded Media Field and its related modules by entering the information here. You can download and find out more about !here. You may also choose to install the !swfobject_api module, which will integrate automatically with this module..', array('!here' => l(t('SWFObject here'), 'http://code.google.com/p/swfobject/', array('target' => '_blank')), '!swfobject_api' => l(t('SWFObject API'), 'http://drupal.org/project/swfobject_api', array('target' => '_blank'))));
  }
  $form['general']['swfobject'] = array(
    '#type' => 'fieldset',
    '#title' => t('SWF Object'),
    '#description' => $swfobject_desc,
    '#collapsible' => TRUE,
  );
  $form['general']['swfobject']['emfield_swfobject'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use SWFObject'),
    '#default_value' => variable_get('emfield_swfobject', FALSE),
    '#description' => t('When checked, then Embedded Media Field will use the SWFObject javascript library when it is able.'),
  );
  if (!module_exists('swfobject_api')) {
    $form['general']['swfobject']['emfield_swfobject_location'] = array(
      '#type' => 'textfield',
      '#title' => t('SWFObject location'),
      '#default_value' => variable_get('emfield_swfobject_location', ''),
      '#description' => t('Enter the relative path to the swfobject.js file, without the preceding slash (/).'),
    );
  }
  $header = array(t('Feature'), t('Supported'), t('Notes'));
  foreach (module_implements('emfield_info', TRUE) as $module) {
    $emfield_info = module_invoke($module, 'emfield_info');
    $providers = emfield_system_list($module);
    $form[$module] = array(
      '#type' => 'fieldset',
      '#title' => t('@neighborhood', array('@neighborhood' => $emfield_info['#name'])),
      '#description' => $emfield_info['#settings_description'],
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form[$module]['providers'] = array(
      '#type' => 'fieldset',
      '#title' => t('Providers'),
      '#description' => t('The following settings determine what providers are allowed, and what provider-specific options, if any, are set.'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    foreach ($providers as $provider) {
      $info = emfield_include_invoke($module, $provider->name, 'info');
      $form[$module]['providers'][$provider->name] = array(
        '#type' => 'fieldset',
        '#title' => t('@provider configuration', array('@provider' => $info['name'])),
        '#description' => $info['settings_description'],
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      if (is_array($info['supported_features']) && !empty($info['supported_features'])) {
        $form[$module]['providers'][$provider->name]['supported_features'] = array(
          '#type' => 'fieldset',
          '#title' => t('Supported features'),
          '#description' => t('This is a list of the current state of support for the following features by %provider:', array('%provider' => $info['name'])),
          '#collapsible' => TRUE,
          '#collapsed' => TRUE,
          '#weight' => 7,
        );
        $form[$module]['providers'][$provider->name]['supported_features']['features'] = array(
          '#type' => 'markup',
          '#value' => theme('table', $header, $info['supported_features']),
        );
      }
      $form[$module]['providers'][$provider->name]['emfield_'. $module .'_allow_'. $provider->name] = array( '#type' => 'checkbox',
        '#title' => t('Allow content from %provider', array('%provider' => $info['name'])),
        '#description' => t('If checked, then content types may be created that allow content to be provided by %provider.', array('%provider' => $info['name'])),
        '#weight' => -10,
        '#default_value' => variable_get('emfield_'. $module .'_allow_'. $provider->name, TRUE),
      );
      $form[$module]['providers'][$provider->name][] = emfield_include_invoke($module, $provider->name, 'settings');
    }
    $form[$module] = array_merge($form[$module], module_invoke($module, 'emfield_settings'));
  }

  return system_settings_form($form);
}

