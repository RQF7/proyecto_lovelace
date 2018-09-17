/*
 * Controlador de página de administración de tokens.
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 */

sistemaTokenizador.controller('controladorControl', [
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
    $scope.cambiarTitulo("Control", 3);
    $scope.cliente = {};

    $scope.actualizarCliente = function ($event) {
      var padre = angular.element(document.body);
      $mdDialog.show({
        parent: padre,
        targetEvent: $event,
        templateUrl: '/estaticos/html/ventanas/actualizar_cliente.ventana.html',
        controller: 'controladorFormularioActualizarCliente'
      }).then(function (respuesta) {
        if (respuesta != undefined) {
          console.log(respuesta);
        }
      });
    };

    $scope.eliminarCliente = function ($event) {
      var aviso = $mdDialog.confirm()
        .title('Advertencia')
        .textContent("@@include('mensajes/adv_eliminar_cliente.txt')")
        .ariaLabel('Advertencia')
        .targetEvent($event)
        .ok('Aceptar')
        .cancel('Cancelar')
        .multiple(true);
      $mdDialog.show(aviso).then(function (respuesta) {
        api.eliminarCliente($scope.usuario.pk).then(function (respuesta) {
          api.cerrarSesion().then(function (respuesta) {
            $scope.usuario = undefined;
           $location.path('/');
          });
        });

        $mdDialog.hide();
      });
    };

    $scope.iniciarRefrescoDeLlaves = function ($event) {
      api.iniciarRefrescoDeLlaves($scope.usuario.pk).then(function (respuesta) {
        $scope.usuario.fields.estadoDeUsuario = 'en cambio de llaves'
      });
    };

    $scope.terminarRefrescoDeLlaves = function ($event) {
      api.terminarRefrescoDeLlaves($scope.usuario.pk).then(function (respuesta) {
        if (respuesta.data == "0") {
          $scope.usuario.fields.estadoDeUsuario = 'aprobado'

        } else if (respuesta.data == "1") {
          var aviso = $mdDialog.alert()
            .title('Error')
            .textContent("@@include('mensajes/error_cliente_no_esta_en_cambio.txt')")
            .ariaLabel('Error')
            .targetEvent($event)
            .ok('Aceptar')
            .multiple(true);
          $mdDialog.show(aviso).then(function (respuesta) {
            $mdDialog.hide();
          });

        } else if (respuesta.data == "2") {
          var aviso = $mdDialog.confirm()
            .title('Advertencia')
            .textContent("@@include('mensajes/adv_retokenizacion_incompleta.txt')")
            .ariaLabel('Advertencia')
            .targetEvent($event)
            .ok('Aceptar')
            .cancel('Cancelar')
            .multiple(true);
          $mdDialog.show(aviso).then(function (respuesta) {
            api.eliminarTokens($scope.usuario.pk).then(function (respuesta) {
              api.terminarRefrescoDeLlaves($scope.usuario.pk).then(function (respuesta) {
                $scope.usuario.fields.estadoDeUsuario = 'aprobado'
              });
            });
            $mdDialog.hide();
          });
        }
      });
    };

  }
]);
