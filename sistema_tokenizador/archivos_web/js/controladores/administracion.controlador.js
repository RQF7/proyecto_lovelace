/*
 * Controlador de página de administración.
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 */

sistemaTokenizador.controller('controladorAdministracion', [
  '$scope',
  function (
    $scope
  )
  {
    $scope.cambiarTitulo("Administración", 4);
  }
]);
