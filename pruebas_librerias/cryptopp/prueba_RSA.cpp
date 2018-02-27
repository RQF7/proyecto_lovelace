/*
 * Prueba de RSA, implementacón, crypto++
 * Implentacion fuera de estandar de pruebas.
 * Proyecto Lovelace.
 */

#include <iostream>
#include  <iomanip>
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>

using namespace std;
using namespace CryptoPP;

/*
 * Estructura para el par de llaves <sk,pk>.
 */
typedef struct pairkeys{
  RSA::PrivateKey privada;
  RSA::PublicKey publica;
} keys;

/*
 * Función para imprimir una linea de '='.
 */
void printseparator(){
	for(int i=0; i<80; i++) cout << "=";
	cout <<endl;
}

/*
 * Función para imprimir en hexadecimal una cadena.
 */
void printhex(string str){
    for(unsigned int i=0; i<str.size(); i++){
    	if (i%16 == 0) cout << endl;
    	byte c = static_cast<byte>(str[i]);
        cout << "0x" << setfill('0') << setw(2) << hex << (0xFF & c) << " ";
    }cout << endl;
}

/*
 * Función para cifrar una cadena con la llave pública del receptor.
 */
string cifrar(string msg, RSA::PublicKey pk){
	string out;
	AutoSeededRandomPool PRNG;
	PK_EncryptorFilter *transcipher;
	/* Se genera una cifrador con la llave publica pk */
	RSAES_OAEP_SHA_Encryptor cipher(pk);
	/* Se hace una transformacion con el cifrador */
	transcipher = new PK_EncryptorFilter(PRNG, cipher, new StringSink(out));
	/* Se transforma la cadena con el cifrador */
	StringSource ss(msg, true, transcipher);
	return out;
}

/*
 * Función para descifrar una cadena con la llave privada del receptor.
 */
string descifrar(string msg, RSA::PrivateKey sk){
	string out;
	AutoSeededRandomPool PRNG;
	PK_DecryptorFilter *transdescipher;
	/* Se genera una descifrador con la llave privada sk */
	RSAES_OAEP_SHA_Decryptor descipher(sk);
	/* Se hace una transformacion con el descifrador */
	transdescipher = new PK_DecryptorFilter(PRNG, descipher, new StringSink(out));
	/* Se transforma la cadena con el descifrador */
	StringSource ss(msg, true, transdescipher);
	return out;
}

/*
 * Función para generar un par de llaves en la estrucutura keys.
 */
keys generarLlaves(){
	AutoSeededRandomPool PRNG;
	InvertibleRSAFunction parametros;
	parametros.GenerateRandomWithKeySize(PRNG, 3072);
	keys llave;
	RSA::PublicKey  pk(parametros);
	RSA::PrivateKey sk(parametros);
	llave.publica = pk;
	llave.privada = sk;
	return llave;	
}

/*
 *  # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
 *  # # # # # # # # # # # # # # #   M A I N   # # # # # # # # # # # # # # # # #
 */
int main(int argc, char* argv[]) {

	string textoClaro = "Mensaje de prueba!";
	string textoCifrado, textoObtenido;
	
	cout << "Prueba de RSA" << endl;
	printseparator();
	cout << "Texto en Claro: " << endl;
	cout << textoClaro << endl;
	printseparator();
	
	// Generacion de llaves ===========
	keys llave = generarLlaves();

	// Cifrado ========================
	textoCifrado = cifrar(textoClaro, llave.publica);
	cout << "Texto Cifrado: (" << textoCifrado.size() << " bytes):";
	printhex(textoCifrado);
	printseparator();
	
	// Descifrado =====================
	textoObtenido = descifrar(textoCifrado, llave.privada);
	cout << "Texto Obtenido: " << endl;
	cout << textoObtenido << endl;
	printseparator();

	return 0;

}
