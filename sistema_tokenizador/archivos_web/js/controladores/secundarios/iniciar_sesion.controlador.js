/*
 * Controlador de formulario de inicip de sesión,
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 */

sistemaTokenizador.controller('controladorFormularioIniciarSesion', [
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

    /* Acciones públicas. ****************************************************/

    $scope.cancelar = function () {
      $mdDialog.hide();
    };

    $scope.aceptar = function () {
      api.iniciarSesion($scope.usuario).then(function (respuesta) {
        if (respuesta.data == '') {
          /* Error. */
          console.log("Error");
        } else {
          /* Sesión iniciada */
          $mdDialog.hide(respuesta.data);
        }
      });
    };
  }
]);
