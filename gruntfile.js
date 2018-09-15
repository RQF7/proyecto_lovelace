/*
 * Configuración de tareas de grunt.
 * Proyecto Lovelace.
 *
 * TODO:
 * * Hacer tarea personalizada para que los archivos estáticos con mensajes
 *   y expresiones regulares se copien en la fase de compilación. Ahorita
 *   se hacen GET por cada uno, en tiempo de ejecución.
 */

/* Carpeta base */
var cc = 'sistema_tokenizador/archivos_web/'

module.exports = function (grunt) {

  /* Configuración de tareas. */
  grunt.initConfig({

    /* Leer configuración general. */
    pkg: grunt.file.readJSON('package.json'),

    /* Configuración de concatenador. ****************************************/
    concat: {
      options: {
        separator: '\n',
        stripBanners: false
      },
      librerias_css: {
        src: [
          'node_modules/angular-material/angular-material.min.css',
          'node_modules/angular-material-data-table/dist/md-data-table.min.css'
        ],
        dest: cc + 'compilados/css/librerias.min.css'
      },
      librerias_js: {
        src: [
          'node_modules/moment/moment.js',
          'node_modules/angular/angular.min.js',
          'node_modules/angular-i18n/angular-locale_es-mx.js',
          'node_modules/angular-route/angular-route.min.js',
          'node_modules/angular-sanitize/angular-sanitize.min.js',
          'node_modules/angular-animate/angular-animate.min.js',
          'node_modules/angular-messages/angular-messages.min.js',
          'node_modules/angular-aria/angular-aria.min.js',
          'node_modules/angular-material/angular-material.min.js',
          'node_modules/angular-material-data-table/dist/md-data-table.min.js'
        ],
        dest: cc + 'compilados/js/librerias.min.js'
      },
      sitio_publico: {
        src: [
          cc + 'js/sistema_tokenizador.aplicacion.js',
          cc + 'js/configuraciones/*.configuracion.js',
          cc + 'js/servicios/*.servicio.js',
          cc + 'js/controladores/*.controlador.js',
          cc + 'js/controladores/secundarios/*.controlador.js'
        ],
        dest: cc + 'compilados/js/scripts.js'
      }
    },

    /* Configuración de minimizador de js *************************************
     * https://www.npmjs.com/package/grunt-contrib-uglify */

    uglify: {
      principal: {
        options: {
          mangle: false,
          sourceMap: true
        },
        files: {
          'sistema_tokenizador/archivos_web/compilados/js/scripts.min.js':
            [cc + 'compilados/js/scripts.preprocesado.js']
        }
      }
    },

    /* Configuración de copiador. *********************************************
     * https://www.npmjs.com/package/grunt-contrib-copy */

    copy: {
      principal: {
        files: [
          {
            src: ['node_modules/angular-aria/angular-aria.min.js.map'],
            dest: cc + 'compilados/js/angular-aria.min.js.map'
          },
          {
            src: ['node_modules/angular-mocks/angular-mocks.js'],
            dest: cc + 'compilados/js/angular-mocks.js'
          },
          {
            src: [cc + 'imagenes/icono.png'],
            dest: cc + 'compilados/imagenes/icono.png'
          },
          {
            src: [cc + 'imagenes/palomita.png'],
            dest: cc + 'compilados/imagenes/palomita.png'
          },
          {
            src: [cc + 'imagenes/todo_rev.png'],
            dest: cc + 'compilados/imagenes/todo_rev.png'
          },
          {
            src: [cc + 'imagenes/todo_irrev.png'],
            dest: cc + 'compilados/imagenes/todo_irrev.png'
          },
          {
            src: [cc + 'sass/sitio_publico.sass'],
            dest: cc + 'compilados/css/sistema_tokenizador/archivos_web/sass/sitio_publico.sass'
          },
          {
            expand: true,
            flatten: true,
            src: ['node_modules/material-design-icons/iconfont/*'],
            dest: cc + 'compilados/fuentes/',
            filter: 'isFile'
          }
        ]
      }
    },

    /* Configuración de minimizador de html.
     * https://github.com/gruntjs/grunt-contrib-htmlmin *********************/

    htmlmin: {
      todo: {
        options: {
          removeComments: true,
          collapseWhitespace: true,
          maxLineLength: 80,
          preserveLineBreaks: true,
          quoteCharacter: "'",
        },
        files: [
          {
            expand: true,
            cwd: cc + 'compilados/preprocesados/',
            src: ['*.html'],
            dest: cc + 'compilados/'
          },
          {
            expand: true,
            cwd: cc + 'compilados/preprocesados/html',
            src: ['*.html'],
            dest: cc + 'compilados/html/'
          },
          {
            expand: true,
            cwd: cc + 'compilados/preprocesados/html/plantillas',
            src: ['*.html'],
            dest: cc + 'compilados/html/plantillas/'
          },
          {
            expand: true,
            cwd: cc + 'compilados/preprocesados/html/ventanas',
            src: ['*.html'],
            dest: cc + 'compilados/html/ventanas/'
          }
        ]
      }
    },

    /* Configuración de seguidor. ********************************************/

    watch: {
      js: {
        files: [
          cc + 'js/*.js',
          cc + 'js/**/*.js',
          cc + 'js/**/**/*.js'
        ],
        tasks: [
          "concat:sitio_publico",
          "includereplace:js",
          "uglify"
        ]
      },
      html: {
        files: [
          cc + '*.html',
          cc + 'html/*.html',
          cc + 'html/plantillas/*.html',
          cc + 'html/ventanas/*.html'
        ],
        tasks: [
          "includereplace:html",
          "htmlmin:todo"
        ]
      },
      css: {
        files: [
          cc + 'sass/*.sass'
        ],
        tasks: [
          "sass"
        ]
      }
    },

    /* Configuración de sass. ************************************************/

    sass: {
      options: {
        sourceMapEmbed: true
      },
      dist: {
        files:
        {
          'sistema_tokenizador/archivos_web/compilados/css/estilos.css':
            cc + 'sass/estilos.sass'
        }
      }
    },

    /* Configuración de sustituciones. ***************************************/

    includereplace: {
      html: {
        options: {
          prefix: '<!-- @@',
          suffix: ' -->',
          includesDir: 'documentos_entregables/reporte_tecnico/contenidos/analisis_y_disenio_api_web/analisis/'
        },
        files: [
          {
            expand: true,
            cwd: cc,
            src: ['*.html'],
            dest: cc + 'compilados/preprocesados/'
          },
          {
            expand: true,
            cwd: cc + 'html',
            src: ['*.html'],
            dest: cc + 'compilados/preprocesados/html/'
          },
          {
            expand: true,
            cwd: cc + 'html/plantillas',
            src: ['*.html'],
            dest: cc + 'compilados/preprocesados/html/plantillas/'
          },
          {
            expand: true,
            cwd: cc + 'html/ventanas',
            src: ['*.html'],
            dest: cc + 'compilados/preprocesados/html/ventanas/'
          }
        ]
      },
      /* El «processIncludeContents» es para quitar los saltos
       * de línea de los archivos con expresiones regulares:
       * el entorno verbatim de latex los necesita para poder mostrarlas
       * correctamente en el documento (que no se salgan del margen,
       * cuando menos), pero para js es un error tener una expersión
       * con un salto de línea en medio. */
      js: {
        options: {
          includesDir: 'documentos_entregables/reporte_tecnico/contenidos/analisis_y_disenio_api_web/analisis/',
          processIncludeContents: function(contenido) {
            return contenido.replace(/(?:\r\n|\r|\n)/g, '');
          }
        },
        files: {
          'sistema_tokenizador/archivos_web/compilados/js/scripts.preprocesado.js':
            [cc + 'compilados/js/scripts.js']
        }
      }
    }

  });

  /* Ejecución de tareas. */
  grunt.loadNpmTasks('grunt-contrib-concat');
  grunt.loadNpmTasks('grunt-contrib-watch');
  grunt.loadNpmTasks('grunt-contrib-copy');
  grunt.loadNpmTasks('grunt-contrib-uglify');
  grunt.loadNpmTasks('grunt-contrib-htmlmin');
  grunt.loadNpmTasks('grunt-include-replace');
  grunt.loadNpmTasks('grunt-sass');
  grunt.registerTask('default',
  [
    'sass',
    'concat',
    'includereplace',
    'uglify',
    'htmlmin',
    'copy'
  ]);

};
