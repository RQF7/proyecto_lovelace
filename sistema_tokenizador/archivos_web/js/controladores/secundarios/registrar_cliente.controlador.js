/*
 * Controlador de formulario de inicip de sesión,
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 */

sistemaTokenizador.controller('controladorFormularioRegistrarCliente', [
  '$scope',
  '$mdDialog',
  'api',
  function (
    $scope,
    $mdDialog,
    api
  )
  {
    /* Datos públicos. *******************************************************/

    $scope.usuario = {};
    $scope.erCorreo = @@include('expresiones_regulares/correo.txt');
    $scope.erContrasenia = @@include('expresiones_regulares/contrasenia.txt');

    /* Acciones públicas. ****************************************************/

    $scope.cancelar = function () {
      $mdDialog.hide();
    };

    $scope.aceptar = function () {
      console.log("En construcción");
    };
  }
]);
