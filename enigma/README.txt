Proyecto Máquina Enigma

Autores: Carles Barranco y Alexis Godoy

Descripción

Este proyecto simula el funcionamiento de la maquina Enigma usada en la Segunda Guerra Mundial para encriptar y desencriptar mensajes. Hecho con c++ manteniendo el modelo básico de la Enigma real, con rotores, un reflector y la rotación de las posiciones en cada letra encriptada. 

Consta de los siguientes archivos del proyecto: 
1. main.cpp, que contiene el menú principal, la entrada del usuario, las opciones y el flujo del programa. 
2. enigma.cpp / enigma.h, estos son los archivo que cuentan con las funciones principales de encriptado, desencriptado, carga de rotores, formateo de mensaje y salida a archivo. 
3. rotor.cpp / rotor.h, estos son los que definen el funcionamiento de la rotación para que el encriptado/desencriptado este bien hecho.
4. rotor1/2/3.txt, estos son simplemente los textos que sirven para que los rotores sepan sobre que basarse para que el programa funcione.

Opciones del menú

    1. Cifrar mensaje: Introduce un texto, se cifrará y guardará en xifrat.txt.

    2. Descifrar mensaje: Introduce un texto cifrado, se descifrará y guardará en desxifrat.txt.

    3. Editar posición inicial del rotor: Define manualmente la posición de inicio para cada rotor (de 0 a 25).

    4. Salir: Termina la ejecución.

Consideraciones

    El programa solo procesa letras mayúsculas del alfabeto (A-Z). Cualquier otro carácter se ignora automáticamente.

    La rotación de los rotores simula el comportamiento real de la máquina Enigma, donde el primer rotor avanza con cada letra, el segundo cada vuelta completa del primero, y el tercero cada vuelta completa del segundo.

    Los mensajes cifrados o descifrados se agrupan automáticamente en bloques de 5 letras para mayor legibilidad.

