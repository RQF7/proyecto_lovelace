/*
 * Configuración de ruteo en sitio público.
 * Tienda en línea.
 * Proyecto Lovelace.
 *
 * Mapeo entre urls, archivos estáticos y controladores.
 */

tienda.config(function($routeProvider, $locationProvider){

  $routeProvider.when('/',
  {
    templateUrl: 'estaticos/html/inicio.html',
    controller: 'controladorInicio'
  });

  $locationProvider.hashPrefix('');
  $locationProvider.html5Mode(true);

});
