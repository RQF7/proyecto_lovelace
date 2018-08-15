/*
 * Configuración de ruteo en sitio público.
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 *
 * Mapeo entre urls, archivos estáticos y controladores.
 */

sistemaTokenizador.config(function($stateProvider) {

  $stateProvider.state({
    name: 'inicio',
    controller: 'controladorSitioPublico',
    url: '/inicio',
    templateUrl: 'estaticos/html/sitio_publico.html'
  });

  $stateProvider.state({
    name: 'documentacion',
    controller: 'controladorDocumentacion',
    url: '/documentación',
    templateUrl: 'estaticos/html/sitio_publico.html'
  });

});
