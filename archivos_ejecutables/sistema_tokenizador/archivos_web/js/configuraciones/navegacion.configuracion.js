/*
 * Configuración de ruteo en sitio público.
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 *
 * Mapeo entre urls, archivos estáticos y controladores.
 *
 * TODO: hacer que ngRoute no codifique la diagonal en los parámetros de la url
 * dada después de recibida. Por ejemplo, al redirigir a un usuario a la
 * pantalla de inicio de sesión por falta de privilegios, se pasa como un
 * parámetro (siguiente) la url a la que se intentaba acceder en primer lugar,
 * por lo que se ve muy mal que las diagonales de esa url se vean como «%2F».
 *
 * Estoy seguro de que lo anterior es cosa del cliente y no de django por que
 * los paquetes que salen de django (el HTTP con el 304) llega al navegador
 * con la diagonal sin codificar; es en la aplicación en donde se está
 * codificando. También estoy seguro de que es ngRoute (o derivados) los
 * responsables y no el propio navegador por que he hecho lo mismo en otras
 * aplicaciones, pero sin ngRoute, y la diagonal se veía bien.
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

  $routeProvider.when('/control',
  {
    templateUrl: 'estaticos/html/control.html',
    controller: 'controladorControl'
  });

  $routeProvider.when('/administración',
  {
    templateUrl: 'estaticos/html/administracion.html',
    controller: 'controladorAdministracion'
  });

  $locationProvider.hashPrefix('');
  $locationProvider.html5Mode(true);

});
