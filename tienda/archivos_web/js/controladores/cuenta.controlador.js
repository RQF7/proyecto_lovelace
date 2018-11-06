/*
 * Controlador de cuenta de usuario.
 * Tienda en línea.
 * Proyecto Lovelace.
 */

tienda.controller('controladorCuenta', [
  '$scope',
  '$route',
  '$routeParams',
  '$location',
  '$mdDialog',
  'api',
  function (
    $scope,
    $route,
    $routeParams,
    $location,
    $mdDialog,
    api
  )
  {
    /* Funciones públicas. ***************************************************/

    $scope.actualizarUsuario = function ($event) {
      var padre = angular.element(document.body);
      $mdDialog.show({
        parent: padre,
        targetEvent: $event,
        templateUrl: '/estaticos/html/ventanas/operar_usuario.ventana.html',
        controller: 'controladorFormularioOperarUsuario',
        locals: {
          "tituloOperacion": "Actualizar datos",
          "operacion": "actualizar",
          "usuario": $scope.usuario
        }
      });
    };

    $scope.quitarMetodoDePago = function($event, tarjeta) {
      var confirmacion = $mdDialog.confirm()
        .title('Advertencia')
        .textContent("¿Está seguro de que quiere eliminar esta forma de pago? "
          + "Esta acción es irreversible.")
        .ariaLabel('Confirmación de eliminación de método de pago')
        .targetEvent($event)
        .ok('Aceptar')
        .cancel('Cancelar');
      $mdDialog.show(confirmacion).then(function (respuesta) {
        api.eliminarTarjeta(tarjeta.pk).then(function (respuesta) {
          for (var i = 0; i < $scope.tarjetas.length; i++)
            if (tarjeta.pk == $scope.tarjetas[i].pk){
              $scope.tarjetas.splice(i, 1);
              break;
            }
        });
      }, function () {});
    };

    $scope.quitarDireccionDeEntrega = function($event, direccion) {
      var confirmacion = $mdDialog.confirm()
        .title('Advertencia')
        .textContent("¿Está seguro de que quiere eliminar esta "
          + "dirección de entrega? "
          + "Esta acción es irreversible.")
        .ariaLabel('Confirmación de eliminación de dirección de entrega')
        .targetEvent($event)
        .ok('Aceptar')
        .cancel('Cancelar');
      $mdDialog.show(confirmacion).then(function (respuesta) {
        api.eliminarDireccion(direccion.pk).then(function (respuesta) {
          for (var i = 0; i < $scope.direcciones.length; i++)
            if (direccion.pk == $scope.direcciones[i].pk){
              $scope.direcciones.splice(i, 1);
              break;
            }
        });
      }, function () {});
    };

    /* Secuencia de inicio. **************************************************/
    $scope.cambiarTitulo("Administración de cuenta", 3);

  }
]);
