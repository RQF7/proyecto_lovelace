/*
 * Configuracipon de colores de aplicación de angular.
 * Tienda en línea.
 * Proyecto Lovelace.
 */

tienda.config(function($mdThemingProvider) {
  $mdThemingProvider.theme('default')
    .primaryPalette('grey', {
      'default': '200',
      'hue-1': '400',
      'hue-2': '500',
      'hue-3': '600'
    })
    .accentPalette('red', {
      'default' : '900'
    })
    .warnPalette('red', {
      'default' : '900'
    })
    .dark();
    $mdThemingProvider.enableBrowserColor();
});
