
/**
 * @file
 * JavaScript to launch media browser when editing a field.
 */

(function ($) {


  // Define the nrembrowser object.
  Drupal.emfield = Drupal.emfield || {};

  /**
   * Display the Drupal throbber.
   *
   * @param $element
   *  The jQuery element to append the throbber to.
   * @param boolean throbber
   *  If TRUE, then display the throbber element.
   */
  Drupal.emfield.throbber = function($element, throbber) {
    if (throbber) {
      $element.addClass('throbbing');
    }
    else {
      $element.removeClass('throbbing');
    }
  }

  Drupal.behaviors.emfieldLaunchBrowser = function(context) {
    $('input.emfield-textfield-url:not(.emfieldLaunchBrowser-processed)', context)
      .addClass('emfieldLaunchBrowser-processed')
      .each(function() {
        $(this).bind('change', function() {
            $preset = $(this);
            var _value = $preset.val();
            if (_value) {
              Drupal.emfield.throbber($preset, true);
              $.ajax({
                url: Drupal.settings.emfield.parseUrl,
                data: 'url=' + _value,
                dataType: 'json',
                error: function (XMLHttpRequest, textStatus, errorThrown) {
                  Drupal.emfield.throbber($preset);
                  alert(Drupal.t('Unknown error at @url.', {'@url': Drupal.settings.emfield.parseUrl}));
                },
                success: function (data) {
                  Drupal.emfield.throbber($preset);
                  // @todo: Check for errors.
                  $('input.emfield-textfield-uri', $preset.parent().siblings('div')).val(data.uri);
                }
              });
            }
          });
      });
    $('input.emfield-textfield-uri:not(.emfieldLaunchBrowser-processed)', context)
      .addClass('emfieldLaunchBrowser-processed')
      .each(function() {
        $(this).hide();
      });
  }
})(jQuery);
