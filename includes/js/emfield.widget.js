// $Id$

/**
 * @file
 * JavaScript to launch media browser when editing a field.
 */

(function ($) {

  Drupal.behaviors.emfieldLaunchBrowser = function(context) {
    $('input.emfield-textfield-url:not(.emfieldLaunchBrowser-processed)', context)
      .addClass('emfieldLaunchBrowser-processed')
      .each(function() {
        $(this).bind('change', function () {
          $preset = $(this);
          var _value = $preset.val();
          if (_value) {
            $.getJSON(Drupal.settings.emfield.parseUrl + '?url=' + _value, function (data) {
              // @todo: Check for errors.
              $('input', $preset.parent().siblings('div')).val(data.uri);
            });
          }
        });
      });
  }
})(jQuery);
