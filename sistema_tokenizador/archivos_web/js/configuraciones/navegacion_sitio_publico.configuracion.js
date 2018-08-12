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
    templateUrl: 'estaticos/html/inicio_sitio_publico.html',
    controller: 'controladorInicioSitioPublico'
  });

  $routeProvider.when('/documentación',
  {
    templateUrl: 'estaticos/html/documentacion.html',
    controller: 'controladorDocumentacion'
  });

  $locationProvider.html5Mode(true);

});
