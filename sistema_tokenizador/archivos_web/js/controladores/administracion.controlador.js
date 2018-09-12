/*
 * Controlador de página de administración.
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 */

sistemaTokenizador.controller('controladorAdministracion', [
  '$scope',
  'api',
  function (
    $scope,
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
