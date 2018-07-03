-- Crea una nueva base y un nuevo usuario
-- Requiere permisos de administrador
--
-- Proyecto Lovelace

-- Elimina bases de datos anteriores
-- https://dev.mysql.com/doc/refman/5.7/en/drop-database.html

DROP DATABASE IF EXISTS lovelace_pruebas;

-- Crear base de datos:
-- https://dev.mysql.com/doc/refman/5.7/en/create-database.html

CREATE DATABASE IF NOT EXISTS lovelace_pruebas
  CHARACTER SET = utf8
  COLLATE = utf8_spanish_ci;

-- Borrar usuario anterior
-- https://dev.mysql.com/doc/refman/5.7/en/drop-user.html

DROP USER IF EXISTS 'administrador_lovelace_pruebas'@'localhost';

-- Crear usuario:
-- https://dev.mysql.com/doc/refman/5.7/en/create-user.html

CREATE USER IF NOT EXISTS
  'administrador_lovelace_pruebas'@'localhost'
  IDENTIFIED BY 'l0v3lac3-padmin';

-- Establecer privilegios:
-- https://dev.mysql.com/doc/refman/5.7/en/grant.html

GRANT ALL ON lovelace_pruebas.* TO 'administrador_lovelace_pruebas'@'localhost';
