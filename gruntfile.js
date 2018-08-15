/*
 * Configuración de tareas de grunt.
 * Proyecto Lovelace.
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
          cc + 'js/configuraciones/tema.configuracion.js',
          cc + 'js/configuraciones/navegacion.configuracion.js',
          cc + 'js/controladores/general.controlador.js',
          cc + 'js/controladores/inicio.controlador.js',
          cc + 'js/controladores/documentacion.controlador.js'
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
            [cc + 'compilados/js/scripts.js']
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
            cwd: cc,
            src: ['*.html'],
            dest: cc + 'compilados/'
          },
          {
            expand: true,
            cwd: cc + 'html',
            src: ['*.html'],
            dest: cc + 'compilados/html/'
          },
          {
            expand: true,
            cwd: cc + 'html/plantillas',
            src: ['*.html'],
            dest: cc + 'compilados/html/plantillas/'
          },
          {
            expand: true,
            cwd: cc + 'html/ventanas',
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
    }

  });

  /* Ejecución de tareas. */
  grunt.loadNpmTasks('grunt-contrib-concat');
  grunt.loadNpmTasks('grunt-contrib-watch');
  grunt.loadNpmTasks('grunt-contrib-copy');
  grunt.loadNpmTasks('grunt-contrib-uglify');
  grunt.loadNpmTasks('grunt-contrib-htmlmin');
  grunt.loadNpmTasks('grunt-sass');
  grunt.registerTask('default',
  [
    'sass',
    'concat',
    'uglify',
    'htmlmin',
    'copy'
  ]);

};
