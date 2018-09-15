/*
 * Controlador de formulario de inicip de sesión,
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 */

sistemaTokenizador.controller('controladorFormularioActualizarCliente', [
  '$scope',
  '$location',
  '$mdDialog',
  'api',
  function (
    $scope,
    $location,
    $mdDialog,
    api
  )
  {
    /* Datos públicos. *******************************************************/

    $scope.cliente = {};
    $scope.erCorreo = @@include('expresiones_regulares/correo.txt');
    $scope.erContrasenia = @@include('expresiones_regulares/contrasenia.txt');
    $scope.error = false;

    api.obtenerUsuarioDeSesion().then(function (respuesta) {
      if (respuesta.data != '') {
        $scope.usuario = respuesta.data[0];
      }
    });


    /* Acciones públicas. ****************************************************/

    $scope.cancelar = function () {
      $mdDialog.hide();
    };

    $scope.aceptar = function ($event) {
      api.actualizarCliente($scope.cliente, $scope.usuario.pk)
      .then(function (respuesta) {
        if (respuesta.data == '0') {
          var aviso = $mdDialog.alert()
            .title('Actualización exitosa')
            .textContent('Para poder iniciar sesión es necesario que '
              + 'verifique su cuenta accediendo al vínculo enviado a su '
              + 'correo electrónico (revise su carpeta de spam).')
            .ariaLabel('Actualización exitosa')
            .targetEvent($event)
            .ok('Aceptar')
            .multiple(true);
          $mdDialog.show(aviso).then(function (respuesta) {
            $mdDialog.hide();
          });
          api.cerrarSesion().then(function (respuesta) {
            $scope.usuario = undefined;
            $location.path('/');
          });
        } else {
          $scope.error = true;
        }
      });
    };
  }
]);
