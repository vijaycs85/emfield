// $Id$

/**
 * @file
 * JavaScript to launch media browser when editing a field.
 */

(function ($) {

  Drupal.behaviors.emfieldLaunchBrowser = function(context) {
    $('#edit-field-emfield-0-url', context).bind('change', function () {
      $preset = $(this);
      if ($preset.val()) {
        $.getJSON(Drupal.settings.basePath + Drupal.settings.emfield.parseUrl + '?url=' + $preset.val(), function (data) {
          // @todo: Check for errors.
          $('#edit-field-emfield-0-uri').val(data.uri);
        });
      }
    });
  }
})(jQuery);
