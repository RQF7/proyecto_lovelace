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

-- Desactivar temporalmente las advertencias de que ya existe la tabla.
SET sql_notes = 0;

CREATE TABLE IF NOT EXISTS algoritmos_tokenizadores
(
  identificador INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
  algoritmo CHAR(24) NOT NULL
);

CREATE TABLE IF NOT EXISTS desempenio_tokenizacion
(
  identificador INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
  algoritmo INT NOT NULL,
  fecha TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  tiempo INT NOT NULL,
  num_operaciones INT NOT NULL,
  FOREIGN KEY (algoritmo) REFERENCES algoritmos_tokenizadores(identificador)
);

CREATE TABLE IF NOT EXISTS desempenio_detokenizacion
(
  identificador INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
  algoritmo INT NOT NULL,
  fecha TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  tiempo INT NOT NULL,
  num_operaciones INT NOT NULL,
  FOREIGN KEY (algoritmo) REFERENCES algoritmos_tokenizadores(identificador)
);

-- Activar nuevamente las advertencias de que ya existe la tabla.
SET sql_notes = 1;
