/*
 * Configuracipon de colores de aplicación de angular.
 * Tienda en línea.
 * Proyecto Lovelace.
 *
 * Catálogo de colores:
 * https://material.io/design/color/
 */

tienda.config(function($mdThemingProvider) {

  /* Extensión de tema. */
  var paletaObscura = $mdThemingProvider.extendPalette('grey', {
    '500': '000000',
    '900': '101010',
    'contrastDefaultColor': 'light'});
  $mdThemingProvider.definePalette('negro', paletaObscura);

  /* Definición para aplicación. */
  $mdThemingProvider.theme('default')
    .primaryPalette('grey', {
      'default': '200',
      'hue-1': '200',
      'hue-2': '200',
      'hue-3': '200'
    })
    .accentPalette('yellow', {
      'default' : 'A400'
    })
    .warnPalette('yellow', {
      'default' : 'A400'
    })
    .backgroundPalette('negro', {
      'default' : '900',
      'hue-1': '500',
      'hue-2': '500',
      'hue-3': '500'
    })
    .dark();
    $mdThemingProvider.enableBrowserColor();
});
