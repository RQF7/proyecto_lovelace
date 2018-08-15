/*
 * Configuración de ruteo en sitio público.
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 *
 * Mapeo entre urls, archivos estáticos y controladores.
 */

sistemaTokenizador.config(function($routeProvider, $locationProvider){

  $routeProvider.when('/',
  {
    templateUrl: 'estaticos/html/sitio_publico.html',
    controller: 'controladorSitioPublico'
  });

  $routeProvider.when('/documentación',
  {
    templateUrl: 'estaticos/html/sitio_publico.html',
    controller: 'controladorSitioPublico'
  });

  $locationProvider.html5Mode(true);

});
