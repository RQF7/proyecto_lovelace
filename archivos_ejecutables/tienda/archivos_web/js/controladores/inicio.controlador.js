/*
 * Controlador de página de inicio.
 * Tienda en línea.
 * Proyecto Lovelace.
 */

tienda.controller('controladorInicio', [
  '$scope',
  'api',
  function (
    $scope,
    api
  )
  {
    /* Datos públicos. *******************************************************/
    $scope.libros = [];
    $scope.totalDeLibros = 0;
    $scope.paginador = {
      pagina: 1,
      limite: 20
    };

    /* Acciones públicas. ****************************************************/
    $scope.obtenerLibros = function () {
      api.obtenerLibros($scope.paginador.pagina,
        $scope.paginador.limite).then(function (respuesta) {
          $scope.libros = respuesta.data;
          for (var i = 0; i < $scope.libros.length; i++) {
            $scope.libros[i].precio = Number($scope.libros[i].precio)
            if ($scope.buscarEnCarrito($scope.libros[i].pk) >= 0) {
              $scope.libros[i].enCarrito = true;
            } else {
              $scope.libros[i].enCarrito = false;
            }
          }
        });
    };

    $scope.avanzarPagina = function () {
      $scope.paginador.pagina++;
      $scope.obtenerLibros();
    };

    $scope.retrocederPagina = function () {
      $scope.paginador.pagina--;
      $scope.obtenerLibros();
    };

    /* Secuencia de inicio. **************************************************/
    $scope.cambiarTitulo("Catálogo", 1);
    $scope.obtenerLibros();
    api.obtenerTotalDeLibros().then(function (respuesta) {
      $scope.totalDeLibros = respuesta.data;
      var totalDePaginas = Math.ceil($scope.totalDeLibros /
        $scope.paginador.limite)
      $scope.paginador.paginas = [];
      for (var i = 0; i < totalDePaginas; i++)
        $scope.paginador.paginas.push(i + 1);
    });
  }
]);
