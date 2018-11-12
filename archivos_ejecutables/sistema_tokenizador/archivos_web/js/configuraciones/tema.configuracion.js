/*
 * Configuracipon de colores de aplicación de angular.
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 */

sistemaTokenizador.config(function($mdThemingProvider) {
  $mdThemingProvider.theme('default')
    .primaryPalette('grey', {
      'default': '900',
      'hue-1': '800',
      'hue-2': '700',
      'hue-3': '600'
    })
    .accentPalette('red', {
      'default' : '900'
    })
    .warnPalette('red', {
      'default' : '900'
    });
    //.dark();
    $mdThemingProvider.enableBrowserColor();
});
