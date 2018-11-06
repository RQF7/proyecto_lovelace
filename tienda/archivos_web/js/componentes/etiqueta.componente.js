/*
 * Componenete para etiquetas.
 * Tienda en línea.
 * Proyecto Lovelace.
 */

tienda.component('egoEtiqueta', {
  restrict: 'E',
  transclude: true,
  templateUrl: '/libreria/estaticos/html/componentes/etiqueta.componente.html',
  bindings: {
    descripcion: '='
  }
});
