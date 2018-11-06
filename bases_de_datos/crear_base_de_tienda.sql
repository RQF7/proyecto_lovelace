-- Crea una nueva base para el caso de prueba y un nuevo usuario
-- Requiere permisos de administrador
--
-- Proyecto Lovelace

-- Elimina bases de datos anteriores
-- https://dev.mysql.com/doc/refman/5.7/en/drop-database.html

DROP DATABASE IF EXISTS tienda_caso_de_prueba;

-- Crear base de datos:
-- https://dev.mysql.com/doc/refman/5.7/en/create-database.html

CREATE DATABASE IF NOT EXISTS tienda_caso_de_prueba
  CHARACTER SET = utf8
  COLLATE = utf8_spanish_ci;

-- Borrar usuario anterior
-- https://dev.mysql.com/doc/refman/5.7/en/drop-user.html

DROP USER IF EXISTS 'administrador_tienda_caso_de_prueba'@'localhost';

-- Crear usuario:
-- https://dev.mysql.com/doc/refman/5.7/en/create-user.html

CREATE USER IF NOT EXISTS
  'administrador_tienda_caso_de_prueba'@'localhost'
  IDENTIFIED BY 't13nd4-admin';

-- Establecer privilegios:
-- https://dev.mysql.com/doc/refman/5.7/en/grant.html

GRANT ALL ON tienda_caso_de_prueba.* 
  TO 'administrador_tienda_caso_de_prueba'@'localhost';
