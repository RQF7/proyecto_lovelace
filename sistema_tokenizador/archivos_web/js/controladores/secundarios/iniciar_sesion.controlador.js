/*
 * Controlador de formulario de inicip de sesión,
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 */

sistemaTokenizador.controller('controladorFormularioIniciarSesion', [
  '$scope',
  '$mdDialog',
  function (
    $scope,
    $mdDialog
  )
  {
    /* Acciones públicas. ****************************************************/

    $scope.cancelar = function () {
      $mdDialog.hide();
    };

    $scope.aceptar = function () {
      console.log("En construcción");
    };
  }
]);
