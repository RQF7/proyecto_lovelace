/*
 * Controlador general de sitio público.
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 */

sistemaTokenizador.controller('controladorSitioPublico', [
  '$scope',
  '$route',
  '$routeParams',
  '$location',
  function (
    $scope,
    $route,
    $routeParams,
    $location
  )
  {
    $scope.$route = $route;
    $scope.routeParams = $routeParams;
    $scope.$location = $location;

    console.log('Controlador sitio público');
  }
]);
