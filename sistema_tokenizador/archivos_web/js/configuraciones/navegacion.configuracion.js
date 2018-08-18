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
    templateUrl: 'estaticos/html/inicio.html',
    controller: 'controladorInicio'
  });

  $routeProvider.when('/documentación',
  {
    templateUrl: 'estaticos/html/documentacion.html',
    controller: 'controladorDocumentacion'
  });

  $routeProvider.when('/administración_de_tokens',
  {
    templateUrl: 'estaticos/html/administracion_de_tokens.html',
    controller: 'controladorAdministracionDeTokens'
  });

  $routeProvider.when('/administración',
  {
    templateUrl: 'estaticos/html/administracion.html',
    controller: 'controladorAdministracion'
  });

  $locationProvider.html5Mode(true);

});
