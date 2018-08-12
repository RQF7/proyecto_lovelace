/*
 * Definición de aplicación de angular global,
 * aplicación web de sistema general.
 * Proyecto Lovelace.
 */

var sistemaTokenizador = angular.module(
  'sistemaTokenizador',
  [
    'ngMaterial',       /* Estilos y componentes de angular material. */
    'ngMessages',       /* Ventanas emergentes. */
    'ngRoute',          /* Controla la navegación en la aplicación. */
    'md.data.table'     /* Directivas para tablas. */
  ]
)
