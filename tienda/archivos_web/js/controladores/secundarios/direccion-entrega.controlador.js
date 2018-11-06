/*
 * Controlador para agregar una dirección de entrega.
 * Tienda en línea.
 * Proyecto Lovelace.
 */

tienda.controller('controladorFormularioDireccionEntrega', [
  '$scope',
  '$mdDialog',
  'api',
  function (
    $scope,
    $mdDialog,
    api
  )
  {
    /* Datos. ****************************************************************/
    $scope.direccion = {};
    $scope.estados = [];

    /* Funciones públicas. ***************************************************/

    $scope.cancelar = function () {
      $mdDialog.hide();
    };

    $scope.aceptar = function () {
      api.agregarDireccionDeEntrega($scope.direccion).then(function (respuesta){
        if (respuesta.data == '0') {
          $scope.error = 'repetida';
        } else {
          var aviso = $mdDialog.alert()
            .title('Operación exitosa')
            .textContent("@@include('mensajes/direccion_de_entrega_guardada.txt')")
            .ok('Aceptar')
            .multiple(true);
          $mdDialog.show(aviso).then(function (resultado) {
            $mdDialog.hide(respuesta.data[0]);
          });
        }
      });
    };

    api.obtenerEstados().then(function (respuesta) {
      $scope.estados = respuesta.data;
    })
  }
]);
