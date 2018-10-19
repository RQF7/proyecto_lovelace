/*
 * Controlador para aregar un método de pago.
 * Tienda en línea.
 * Proyecto Lovelace.
 */

tienda.controller('controladorFormularioTarjeta', [
  '$scope',
  '$mdDialog',
  'api',
  'direcciones',
  function (
    $scope,
    $mdDialog,
    api,
    direcciones
  )
  {
    /* Datos públicos. *******************************************************/
    $scope.tarjeta = {};
    $scope.direccion = {};
    $scope.direcciones = direcciones;
    $scope.objetoPadre = {};
    $scope.objetoPadre.direccionAnterior = undefined;

    /* El «objetoPadre» es para colocar el modelo de los radiobuttons
     * adentro de un objeto y así poder acceder a su valor desde este
     * controlador. Sin él, se modifica «direccionAnterior» en un controlador
     * virtual hijo definido por el nf-if. Ver:
     * https://stackoverflow.com/questions/18342917/
     * angularjs-ng-model-doesnt-work-inside-ng-if#18342974 */

    $scope.emisores = [];
    $scope.metodos = [];
    $scope.tipos = [];
    $scope.estados = [];
    $scope.erTarjeta = @@include('expresiones_regulares/numero_de_tarjeta.txt');
    $scope.hoy = new Date();

    /* Funciones públicas. ***************************************************/

    $scope.cancelar = function () {
      $mdDialog.hide();
    };

    $scope.cambioEnDireccionAnterior = function () {
      for (var i = 0; i < $scope.direcciones.length; i++) {
        if ($scope.direcciones[i].pk == $scope.objetoPadre.direccionAnterior) {
          if ($scope.direcciones[i].banderaDeSeleccion) {
            $scope.objetoPadre.direccionAnterior = undefined;
            $scope.direcciones[i].banderaDeSeleccion = false;
            $scope.direccion = {};
          } else {
            $scope.direcciones[i].banderaDeSeleccion = true;
            $scope.direccion = $scope.direcciones[i];
          }
        } else {
          $scope.direcciones[i].banderaDeSeleccion = false;
        }
      }
    }

    /* Secuencia de inicio. **************************************************/

    api.obtenerEmisores().then(function (respuesta) {
      $scope.emisores = respuesta.data;
    });

    api.obtenerMetodos().then(function (respuesta) {
      $scope.metodos = respuesta.data;
    });

    api.obtenerTipos().then(function (respuesta) {
      $scope.tipos = respuesta.data;
    });

    api.obtenerEstados().then(function (respuesta) {
      $scope.estados = respuesta.data;
    });

    for (var i = 0; i < $scope.direcciones.length; i++) {
      $scope.direcciones[i].banderaDeSeleccion = false;
    }
  }
]);
