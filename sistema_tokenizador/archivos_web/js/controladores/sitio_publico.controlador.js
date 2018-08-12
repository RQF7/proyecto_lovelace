/*
 * Controlador general de sitio público.
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 */

sistemaTokenizador.controller('controladorSitioPublico', [
  '$scope',
  '$route',
  '$location',
  function (
    $scope,
    $route,
    $location
  )
  {
    $scope.$route = $route;
    $scope.$location = $location;

    console.log('Controlador general');
  }
]);
