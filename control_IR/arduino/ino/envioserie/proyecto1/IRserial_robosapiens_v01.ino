/*
 * CONTROL REMOTO DESDE PC PARA ROBOSAPIENS V1
 * Version  del codigo 1.0
 * 
 * File: IRserial_robosapiens_v01.ino
 *
 * Based on IRSend demo from ken Shirriffs library - this sends simple commands to a RoboSapien V1 using and IR Transmitter with Arduino
 * Based on https://daverobertson63.wordpress.com/2013/05/05/updated-robosapien-ir-control-arduino/
 * 
 * La historia:
 * Despues de haber conseguido por wallapop un Robosapiens v 1.0, me encontre que su mando estaba estropeado. Trasteando por Internet, me he encontrado
 * cientos de ejemplos con códigos a medias, o sin explicar completamente. Me decidí a entrar de lleno en la programación y control de este robot
 * tan facil a asequible de conseguir ahora y facilitar el acceso a la documentación a todos los seguidores de la web www.pesadillo.com
 * 
 * 
 * De interés:
 * La libreria a utilizar es IRRemote V 1.0.0 (modificada) que he incluido desde el apartado Programa/Incluir Libreria/Añadir libreria ZIP
 * Esta libreria puedes descargarla desde https://drive.google.com/file/d/0BwYG1PFb3ZByaTAxMlJZS2pIM1E/edit?usp=sharing
 * que he encontrado en la pagina https://cae2100.wordpress.com/2014/01/15/robosapienwowwee-ir-arduino-library/ y dedonde he conseguido parte del codigo
 * Si ya tienes una libreria mas actualizada instalada, puedes escoger la version activa en el apartado Programa/Incluir Libreria/Gestionar Libreria/IRRemote
 * Selecciona la version 1.0.0 y funcionará a la primera
 * 
 * The circuit:
 * IR LED - LED emisor en pin 3 controlado por 2n2222A con sus respectivas resistencias.
 * 
 * www.pesadillo.com
 * created 09/05/2019
 * by pesadillo <http://www.pesadillo.com>
 * This example code is in the public domain.
*/

/*
 * Lista de comandos disponibles:
 * Fuente : https://daverobertson63.wordpress.com/2013/05/05/updated-robosapien-ir-control-arduino/
 * Botón   Color mando   Función                             Pinzas   Codigo arduino
 * 12      rojo          Girar a la derecha                    1           128
 * 1       rojo          Brazo derecho arriba                  2           129
 * 4       rojo          Brazo derecho hacia fuera             2           130
 * 5       rojo          Inclinar cuerpo derecho               1           131
 * 2       rojo          Brazo derecho abajo                   2           132
 * 3       rojo          Brazo derecho encogido                2           133
 * 11      rojo          Caminar hacia adelante                2           134
 * 15      rojo          Caminar hacia atrás                   2           135
 * 14      rojo          Girar a la izquierda                  1           136
 * 6       rojo          Brazo izquierdo arriba                2           137
 * 9       rojo          Brazo izquierdo hacia fuera           2           138
 * 10      rojo          Inclinar cuerpo derecho               1           139
 * 7       rojo          Brazo izquierdo hacia abajo           2           140
 * 8       rojo          Brazo izquierdo encogido              2           141
 * 13      rojo          Detener                               1           142
 * 19      rojo          Programa de Comando Maestro           1           144
 * 20      rojo          Programa de juego                     1           145
 * 16      rojo          Programa de sensor derecho            1           146
 * 18      rojo          Programa de sensor izquierdo          1           147
 * 17      rojo          Programa de sensor sonoro             1           148
 * 12      Verde         Paso a la derecha                     1           160
 * 1       Verde         Golpe derecho                         1           161
 * 4       Verde         Lanzamiento diestro                   1           162
 * 5       Verde         Dormir                                1           163
 * 2       Verde         Recolección de la mano derecha        1           164
 * 3       Verde         Inclinarse hacia atrás                1           165
 * 11      Verde         Paso adelante                         1           166
 * 15      Verde         Paso hacia atras                      1           167
 * 14      Verde         Paso a la izquierda                   1           168
 * 6       Verde         Golpe izquierdo                       1           169
 * 9       Verde         Tiro de la mano izquierda             1           170
 * 10      Verde         Escucha                               1           171
 * 7       Verde         Recogida de la mano izquierda         1           172
 * 8       Verde         Inclinación hacia delante             1           173
 * 13      Verde         Reiniciar                             1           174
 * 19      Verde         Programa de Comando Maestro           1           176
 * 20      Verde         Despierta                             1           177
 * 16      Verde         Programa de sensor derecho Ejecutar   1           178
 * 18      Verde         Programa de Sensor Izquierdo Ejecutar 1           179
 * 17      Verde         Programa de sensor sonoro ejecutado   1           180
 * 12      Naranja       Golpe de mano derecha 3               1           192
 * 1       Naranja       Barrido de la mano derecha            1           193
 * 4       Naranja       Eructar                               1           194
 * 5       Naranja       LLave de la mano derecha              1           195
 * 2       Naranja       Alta 5                                1           196
 * 3       Naranja       LLave de la mano derecha              1           197
 * 11      Naranja       Excavadora                            1           198
 * 15      Naranja       Ups                                   1           199
 * 14      Naranja       Golpe de mano izquierda 3             1           200
 * 6       Naranja       Barrido de la mano izquierda          1           201
 * 9       Naranja       Silbar                                1           202
 * 10      Naranja       LLave de la mano izquierda            1           203
 * 7       Naranja       Replicar                              1           204
 * 8       Naranja       LLave de la mano izquierda            1           205
 * 13      Naranja       Rugido                                1           206
 * 19      Naranja       Todo demo                             1           208
 * 20      Naranja       Apagado                               1           209
 * 16      Naranja       Demo 1                                1           210
 * 18      Naranja       Demo 2                                1           211
 * 17      Naranja       Demostración de baile                 1           212
*/

#include <IRremote.h>
IRsend irsend;        // pin 3 es IR LED salida
int data;             // Variable de almace de datos de la lectura serie
void setup()
{
Serial.begin(9600);
irsend.sendRSV1(142);// Envio sonido test de inicio
}
void loop() {
  while (Serial.available()> 0) {
    data = Serial.parseFloat(); //Capturo valor DECIMAL introducido
    Serial.println(data); // Veo datos enviados en monitor serie
    irsend.sendRSV1(data); //Envio datos al pin 3

}
}
