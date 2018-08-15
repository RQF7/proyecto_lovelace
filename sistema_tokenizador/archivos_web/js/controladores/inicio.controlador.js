/*
 * Controlador de página de inicio de sitio público.
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 */

sistemaTokenizador.controller('controladorInicio', [
  '$scope',
  function (
    $scope
  )
  {
    $scope.cambiarTitulo("Inicio", 1);
  }
]);
