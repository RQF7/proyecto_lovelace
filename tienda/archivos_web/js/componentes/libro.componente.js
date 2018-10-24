/*
 * Componenete para libros.
 * Tienda en línea.
 * Proyecto Lovelace.
 */

tienda.component('egoLibro', {
  restrict: 'E',
  templateUrl: '/estaticos/html/componentes/libro.componente.html',
  bindings: {
    datos: '='
  }
});
