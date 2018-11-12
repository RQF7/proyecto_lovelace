/*
 * Componenete para etiquetas.
 * Tienda en línea.
 * Proyecto Lovelace.
 */

tienda.component('egoEtiqueta', {
  restrict: 'E',
  transclude: true,
  templateUrl: '/estaticos/html/componentes/etiqueta.componente.html',
  bindings: {
    descripcion: '='
  }
});
