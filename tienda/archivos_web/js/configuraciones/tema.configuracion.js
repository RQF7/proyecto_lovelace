/*
 * Configuracipon de colores de aplicación de angular.
 * Tienda en línea.
 * Proyecto Lovelace.
 *
 * Catálogo de colores:
 * https://material.io/design/color/
 */

tienda.config(function($mdThemingProvider) {
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
    .backgroundPalette('grey',   {
      'default' : '800',
      'hue-1': '900',
      'hue-2': '900',
      'hue-3': '900'
    })
    .dark();
    $mdThemingProvider.enableBrowserColor();
});
