/*
 * Controlador de formulario de inicip de sesión,
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 */

sistemaTokenizador.controller('controladorFormularioOperarCliente', [
  '$scope',
  '$location',
  '$mdDialog',
  'api',
  'tituloOperacion',
  'operacion',
  function (
    $scope,
    $location,
    $mdDialog,
    api,
    tituloOperacion,
    operacion
  )
  {
    /* Datos públicos. *******************************************************/

    $scope.cliente = {};
    $scope.erCorreo = @@include('expresiones_regulares/correo.txt');
    $scope.erContrasenia = @@include('expresiones_regulares/contrasenia.txt');
    $scope.error = false;

    $scope.tituloOperacion = tituloOperacion;
    $scope.operacion = operacion;
    mensaje = 'Para poder iniciar sesión es necesario que '
      + 'verifique su cuenta accediendo al vínculo enviado a su '
      + 'correo electrónico (revise su carpeta de spam).'

    api.obtenerUsuarioDeSesion().then(function (respuesta) {
      if (respuesta.data != '') {
        $scope.usuario = respuesta.data[0];
      }
    });


    /* Acciones públicas. ****************************************************/

    $scope.cancelar = function () {
      $mdDialog.hide();
    };

    $scope.operar = function () {
      if (operacion == "registrar") {
        $scope.aceptarRegistro()
      } else if (operacion == "actualizar") {
        $scope.aceptarActualizacion()
      }
    };

    $scope.aceptarRegistro = function ($event) {
      api.registrarCliente($scope.cliente).then(function (respuesta) {
        if (respuesta.data == '0') {
          var aviso = $mdDialog.alert()
            .title('Registro exitoso')
            .textContent(mensaje)
            .ariaLabel('Registro exitoso')
            .targetEvent($event)
            .ok('Aceptar')
            .multiple(true);
          $mdDialog.show(aviso).then(function (respuesta) {
            $mdDialog.hide();
          });
        } else {
          $scope.error = true;
        }
      });
    };

    $scope.aceptarActualizacion = function ($event) {
      api.actualizarCliente($scope.cliente).then(function (respuesta) {
        if (respuesta.data == '0') {
          var aviso = $mdDialog.alert()
            .title('Actualización exitosa')
            .textContent(mensaje)
            .ariaLabel('Actualización exitosa')
            .targetEvent($event)
            .ok('Aceptar')
            .multiple(true);
          $mdDialog.show(aviso).then(function (respuesta) {
            $mdDialog.hide();
            location.reload();
          });
          api.cerrarSesion().then(function (respuesta) {
            $scope.usuario = undefined;
            $location.path('/');
          });
        } else if (respuesta.data == '2') {
          $mdDialog.hide();
        } else {
          $scope.error = true;
        }
      });
    };

  }
]);
