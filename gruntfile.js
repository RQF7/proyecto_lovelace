/*
 * Configuración de tareas de grunt.
 * Proyecto Lovelace.
 */

/* Carpeta base */
var cc_tokens = 'sistema_tokenizador/archivos_web/';
var cc_tienda = 'tienda/archivos_web/';

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
      librerias_css_tokens: {
        src: [
          'node_modules/angular-material/angular-material.min.css',
          'node_modules/angular-material-data-table/dist/md-data-table.min.css'
        ],
        dest: cc_tokens + 'compilados/css/librerias.min.css'
      },
      librerias_css_tienda: {
        src: [
          'node_modules/angular-material/angular-material.min.css',
          'node_modules/angular-material-data-table/dist/md-data-table.min.css'
        ],
        dest: cc_tienda + 'compilados/css/librerias.min.css'
      },
      librerias_js_tokens: {
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
        dest: cc_tokens + 'compilados/js/librerias.min.js'
      },
      librerias_js_tienda: {
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
        dest: cc_tienda + 'compilados/js/librerias.min.js'
      },
      scripts_tokens: {
        src: [
          cc_tokens + 'js/sistema_tokenizador.aplicacion.js',
          cc_tokens + 'js/configuraciones/*.configuracion.js',
          cc_tokens + 'js/servicios/*.servicio.js',
          cc_tokens + 'js/controladores/*.controlador.js',
          cc_tokens + 'js/controladores/secundarios/*.controlador.js'
        ],
        dest: cc_tokens + 'compilados/js/scripts.js'
      },
      scripts_tienda: {
        src: [
          cc_tienda + 'js/tienda.aplicacion.js',
          cc_tienda + 'js/configuraciones/*.configuracion.js',
          cc_tienda + 'js/filtros/*.filtro.js',
          cc_tienda + 'js/componentes/*.componente.js',
          cc_tienda + 'js/servicios/*.servicio.js',
          cc_tienda + 'js/controladores/*.controlador.js',
          cc_tienda + 'js/controladores/secundarios/*.controlador.js'
        ],
        dest: cc_tienda + 'compilados/js/scripts.js'
      }
    },

    /* Configuración de minimizador de js *************************************
     * https://www.npmjs.com/package/grunt-contrib-uglify */

    uglify: {
      tokens: {
        options: {
          mangle: false,
          sourceMap: true
        },
        files: {
          'sistema_tokenizador/archivos_web/compilados/js/scripts.min.js':
            [cc_tokens + 'compilados/js/scripts.preprocesado.js']
        }
      },
      tienda: {
        options: {
          mangle: false,
          sourceMap: true
        },
        files: {
          'tienda/archivos_web/compilados/js/scripts.min.js':
            [cc_tienda + 'compilados/js/scripts.js']
        }
      }
    },

    /* Configuración de copiador. *********************************************
     * https://www.npmjs.com/package/grunt-contrib-copy */

    copy: {
      tokens: {
        files: [
          {
            src: ['node_modules/angular-aria/angular-aria.min.js.map'],
            dest: cc_tokens + 'compilados/js/angular-aria.min.js.map'
          },
          {
            src: ['node_modules/angular-mocks/angular-mocks.js'],
            dest: cc_tokens + 'compilados/js/angular-mocks.js'
          },
          {
            expand: true,
            flatten: true,
            src: [cc_tokens + 'imagenes/*.png'],
            dest: cc_tokens + 'compilados/imagenes/'
          },
          {
            src: [cc_tokens + 'sass/estilos.sass'],
            dest: cc_tokens + 'compilados/css/sistema_tokenizador/archivos_web/sass/estilos.sass'
          },
          {
            expand: true,
            flatten: true,
            src: ['node_modules/material-design-icons/iconfont/*'],
            dest: cc_tokens + 'compilados/fuentes/',
            filter: 'isFile'
          }
        ]
      },
      tienda: {
        files: [
          {
            src: ['node_modules/angular-aria/angular-aria.min.js.map'],
            dest: cc_tienda + 'compilados/js/angular-aria.min.js.map'
          },
          {
            src: ['node_modules/angular-mocks/angular-mocks.js'],
            dest: cc_tienda + 'compilados/js/angular-mocks.js'
          },
          {
            expand: true,
            flatten: true,
            src: [cc_tienda + 'imagenes/*.png'],
            dest: cc_tienda + 'compilados/imagenes/'
          },
          {
            expand: true,
            flatten: true,
            src: [cc_tienda + '../img/*.jpg'],
            dest: cc_tienda + 'compilados/imagenes/libros/'
          },
          {
            src: [cc_tienda + 'sass/estilos.sass'],
            dest: cc_tienda + 'compilados/css/sistema_tokenizador/archivos_web/sass/estilos.sass'
          },
          {
            expand: true,
            flatten: true,
            src: ['node_modules/material-design-icons/iconfont/*'],
            dest: cc_tienda + 'compilados/fuentes/',
            filter: 'isFile'
          }
        ]
      }
    },

    /* Configuración de minimizador de html.
     * https://github.com/gruntjs/grunt-contrib-htmlmin *********************/

    htmlmin: {
      tokens: {
        options: {
          removeComments: true,
          collapseWhitespace: true,
          preserveLineBreaks: true,
          quoteCharacter: "'",
        },
        files: [
          {
            expand: true,
            cwd: cc_tokens + 'compilados/preprocesados/',
            src: ['*.html'],
            dest: cc_tokens + 'compilados/'
          },
          {
            expand: true,
            cwd: cc_tokens + 'compilados/preprocesados/html',
            src: ['*.html'],
            dest: cc_tokens + 'compilados/html/'
          },
          {
            expand: true,
            cwd: cc_tokens + 'compilados/preprocesados/html/plantillas',
            src: ['*.html'],
            dest: cc_tokens + 'compilados/html/plantillas/'
          },
          {
            expand: true,
            cwd: cc_tokens + 'compilados/preprocesados/html/ventanas',
            src: ['*.html'],
            dest: cc_tokens + 'compilados/html/ventanas/'
          }
        ]
      },
      tienda: {
        options: {
          removeComments: true,
          collapseWhitespace: true,
          preserveLineBreaks: true,
          quoteCharacter: "'",
        },
        files: [
          {
            expand: true,
            cwd: cc_tienda + 'compilados/',
            src: ['*.html'],
            dest: cc_tienda + 'compilados/'
          },
          {
            expand: true,
            cwd: cc_tienda + 'compilados/html',
            src: ['*.html'],
            dest: cc_tienda + 'compilados/html/'
          },
          {
            expand: true,
            cwd: cc_tienda + 'compilados/html/plantillas',
            src: ['*.html'],
            dest: cc_tienda + 'compilados/html/plantillas/'
          },
          {
            expand: true,
            cwd: cc_tienda + 'compilados/html/ventanas',
            src: ['*.html'],
            dest: cc_tienda + 'compilados/html/ventanas/'
          },
          {
            expand: true,
            cwd: cc_tienda + 'compilados/preprocesados/html/componentes',
            src: ['*.html'],
            dest: cc_tienda + 'compilados/html/componentes/'
          }
        ]
      }
    },

    /* Configuración de seguidor. ********************************************/

    watch: {
      js_tokens: {
        files: [
          cc_tokens + 'js/*.js',
          cc_tokens + 'js/**/*.js',
          cc_tokens + 'js/**/**/*.js'
        ],
        tasks: [
          "concat:scripts_tokens",
          "includereplace:js_tokens",
          "uglify:tokens"
        ]
      },
      js_tienda: {
        files: [
          cc_tienda + 'js/*.js',
          cc_tienda + 'js/**/*.js',
          cc_tienda + 'js/**/**/*.js'
        ],
        tasks: [
          "concat:scripts_tienda",
          "includereplace:js_tienda",
          "uglify:tienda"
        ]
      },
      html_tokens: {
        files: [
          cc_tokens + '*.html',
          cc_tokens + 'html/*.html',
          cc_tokens + 'html/plantillas/*.html',
          cc_tokens + 'html/ventanas/*.html'
        ],
        tasks: [
          "includereplace:html_tokens",
          "htmlmin:tokens"
        ]
      },
      html_tienda: {
        files: [
          cc_tienda + '*.html',
          cc_tienda + 'html/*.html',
          cc_tienda + 'html/plantillas/*.html',
          cc_tienda + 'html/ventanas/*.html',
          cc_tienda + 'html/componentes/*.html'
        ],
        tasks: [
          "includereplace:html_tienda",
          "htmlmin:tienda"
        ]
      },
      css_tokens: {
        files: [
          cc_tokens + 'sass/*.sass'
        ],
        tasks: [
          "sass"
        ]
      },
      css_tienda: {
        files: [
          cc_tienda + 'sass/*.sass'
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
      tokens: {
        files:
        {
          'sistema_tokenizador/archivos_web/compilados/css/estilos.css':
            cc_tokens + 'sass/estilos.sass'
        }
      },
      tienda: {
        files:
        {
          'tienda/archivos_web/compilados/css/estilos.css':
            cc_tienda + 'sass/estilos.sass'
        }
      }
    },

    /* Configuración de sustituciones. ***************************************/

    includereplace: {
      html_tokens: {
        options: {
          prefix: '<!-- @@',
          suffix: ' -->',
          includesDir: 'documentos_entregables/reporte_tecnico/contenidos/analisis_y_disenio_api_web/analisis/'
        },
        files: [
          {
            expand: true,
            cwd: cc_tokens,
            src: ['*.html'],
            dest: cc_tokens + 'compilados/preprocesados/'
          },
          {
            expand: true,
            cwd: cc_tokens + 'html',
            src: ['*.html'],
            dest: cc_tokens + 'compilados/preprocesados/html/'
          },
          {
            expand: true,
            cwd: cc_tokens + 'html/plantillas',
            src: ['*.html'],
            dest: cc_tokens + 'compilados/preprocesados/html/plantillas/'
          },
          {
            expand: true,
            cwd: cc_tokens + 'html/ventanas',
            src: ['*.html'],
            dest: cc_tokens + 'compilados/preprocesados/html/ventanas/'
          }
        ]
      },
      /* El «processIncludeContents» es para quitar los saltos
       * de línea de los archivos con expresiones regulares:
       * el entorno verbatim de latex los necesita para poder mostrarlas
       * correctamente en el documento (que no se salgan del margen,
       * cuando menos), pero para js es un error tener una expersión
       * con un salto de línea en medio. */
      js_tokens: {
        options: {
          includesDir: 'documentos_entregables/reporte_tecnico/contenidos/analisis_y_disenio_api_web/analisis/',
          processIncludeContents: function(contenido) {
            return contenido.replace(/(?:\r\n|\r|\n)/g, ' ');
          }
        },
        files: {
          'sistema_tokenizador/archivos_web/compilados/js/scripts.preprocesado.js':
            [cc_tokens + 'compilados/js/scripts.js']
        }
      },
      html_tienda: {
        options: {
          prefix: '<!-- @@',
          suffix: ' -->',
          includesDir: 'documentos_entregables/reporte_tecnico/contenidos/analisis_y_disenio_tienda/analisis/'
        },
        files: [
          {
            expand: true,
            cwd: cc_tienda,
            src: ['*.html'],
            dest: cc_tienda + 'compilados/'
          },
          {
            expand: true,
            cwd: cc_tienda + 'html',
            src: ['*.html'],
            dest: cc_tienda + 'compilados/html/'
          },
          {
            expand: true,
            cwd: cc_tienda + 'html/plantillas',
            src: ['*.html'],
            dest: cc_tienda + 'compilados/html/plantillas/'
          },
          {
            expand: true,
            cwd: cc_tienda + 'html/ventanas',
            src: ['*.html'],
            dest: cc_tienda + 'compilados/html/ventanas/'
          },
          {
            expand: true,
            cwd: cc_tienda + 'html/componentes',
            src: ['*.html'],
            dest: cc_tienda + 'compilados/html/componentes/'
          }
        ]
      },
      js_tienda: {
        options: {
          includesDir: 'documentos_entregables/reporte_tecnico/contenidos/analisis_y_disenio_tienda/analisis/',
          processIncludeContents: function(contenido) {
            return contenido.replace(/(?:\r\n|\r|\n)/g, ' ');
          }
        },
        files: {
          'tienda/archivos_web/compilados/js/scripts.js':
            [cc_tienda + 'compilados/js/scripts.js']
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
