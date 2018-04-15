--
-- Construcción de estructura de base de datos de pruebas.
-- Asume que la base ya está creada.
--
-- Proyecto Lovelace.
--

--
-- Referencias:
-- CREATE TABLE: https://dev.mysql.com/doc/refman/5.7/en/create-table.html

-- Elimina, si existen, las tablas anteriores.
-- Elimina al último la de algoritmos tokenizadores para no tener
-- problemas con las referencias existentes.

DROP TABLE IF EXISTS desempenio_tokenizacion;
DROP TABLE IF EXISTS desempenio_detokenizacion;
DROP TABLE IF EXISTS algoritmos_tokenizadores;

CREATE TABLE algoritmos_tokenizadores
(
  identificador INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
  algoritmo CHAR(24) NOT NULL
);

CREATE TABLE desempenio_tokenizacion
(
  identificador INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
  algoritmo INT NOT NULL,
  fecha TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  tiempo INT NOT NULL,
  num_operaciones INT NOT NULL,
  FOREIGN KEY (algoritmo) REFERENCES algoritmos_tokenizadores(identificador)
);

CREATE TABLE desempenio_detokenizacion
(
  identificador INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
  algoritmo INT NOT NULL,
  fecha TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  tiempo INT NOT NULL,
  num_operaciones INT NOT NULL,
  FOREIGN KEY (algoritmo) REFERENCES algoritmos_tokenizadores(identificador)
);
