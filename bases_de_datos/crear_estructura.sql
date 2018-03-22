--
-- Construcción de estructura de base de datos.
-- Asume que la base ya está creada.
--
-- Proyecto Lovelace.
--

--
-- Referencias:
-- CREATE TABLE: https://dev.mysql.com/doc/refman/5.7/en/create-table.html
-- CHAR:         https://dev.mysql.com/doc/refman/5.7/en/char.html
-- BIGINT:       https://dev.mysql.com/doc/refman/5.7/en/integer-types.html
-- DATE:         https://dev.mysql.com/doc/refman/5.7/en/datetime.html
--

DROP TABLE IF EXISTS registro;

CREATE TABLE registro
(
  identificador INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
  pan CHAR(19) NOT NULL UNIQUE,
  token CHAR(19) NOT NULL UNIQUE
);


DROP TABLE IF EXISTS contador;

CREATE TABLE contador
(
  identificador INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
  nombre VARCHAR(15) NOT NULL,
  valor BIGINT UNSIGNED NOT NULL
);
