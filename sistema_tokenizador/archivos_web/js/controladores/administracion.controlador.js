/*
 * Controlador de página de administración.
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 */

sistemaTokenizador.controller('controladorAdministracion', [
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

    $scope.clientesEnEspera = [];
    $scope.totalDeClientesEnEspera = 0;
    $scope.paginacionEnEspera = {
      limite: 5,
      pagina: 1
    };

    $scope.clientesEnListaNegra = [];
    $scope.totalDeClientesEnListaNegra = 0;
    $scope.paginacionEnListaNegra = {
      limite: 5,
      pagina: 1
    };

    $scope.clientesAprobados = [];
    $scope.totalDeClientesAprobados = 0;
    $scope.paginacionAprobados = {
      limite: 5,
      pagina: 1
    };

    /* Acciones públicas. ****************************************************/

    $scope.obtenerClientesEnEspera = function () {
      api.obtenerClientesEnEspera($scope.paginacionEnEspera.pagina,
        $scope.paginacionEnEspera.limite).then(function (clientes) {
          $scope.clientesEnEspera = clientes.data;
        });
    };

    $scope.obtenerClientesEnListaNegra = function () {
      api.obtenerClientesEnListaNegra($scope.paginacionEnListaNegra.pagina,
        $scope.paginacionEnListaNegra.limite).then(function (clientes) {
          $scope.clientesEnListaNegra = clientes.data;
        });
    };

    $scope.obtenerClientesAprobados = function () {
      api.obtenerClientesAprobados($scope.paginacionAprobados.pagina,
        $scope.paginacionAprobados.limite).then(function (clientes) {
          $scope.clientesAprobados = clientes.data;
        });
    };

    $scope.aprobarCliente = function ($event, cliente) {
      api.aprobarCliente(cliente.pk).then(function (respuesta) {
        $scope.obtenerClientesEnEspera();
        $scope.obtenerClientesAprobados();
        $scope.totalDeClientesEnEspera--;
        $scope.totalDeClientesAprobados++;
      });
    };

    $scope.rechazarCliente = function ($event, cliente) {
      var confirmacion = $mdDialog.confirm()
        .title('Confirmación de rechazo de cliente')
        .textContent("@@include('mensajes/adv_rechazar_cliente.txt')")
        .ariaLabel('Confirmación de rechazo de cliente')
        .targetEvent($event)
        .ok('Aceptar')
        .cancel('Cancelar');
      $mdDialog.show(confirmacion).then(function (respuesta) {
        api.rechazarCliente(cliente.pk).then(function (respuesta) {
          $scope.obtenerClientesEnEspera();
          $scope.totalDeClientesEnEspera--;
        });
      }, function () {});
    };

    /* Secuencia de inicio. **************************************************/

    $scope.cambiarTitulo("Administración", 4);

    $scope.obtenerClientesEnEspera();
    api.obtenerTotalDeClientesEnEspera().then(function (total) {
      $scope.totalDeClientesEnEspera = total.data;
    });

    $scope.obtenerClientesEnListaNegra();
    api.obtenerTotalDeClientesEnListaNegra().then(function (total) {
      $scope.totalDeClientesEnListaNegra = total.data;
    });

    $scope.obtenerClientesAprobados();
    api.obtenerTotalDeClientesAprobados().then(function (total) {
      $scope.totalDeClientesAprobados = total.data;
    });
  }
]);
