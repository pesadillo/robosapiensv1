/*
 * CONTROL REMOTO DESDE PC PARA ROBOSAPIENS V1
 * Version  del codigo 1.0
 * 
 * File: IRcontrol_robosapiens_v1.ino
 * 
 * Based on IRSend demo from ken Shirriffs library - this sends simple commands to a RoboSapien V1 using and IR Transmitter with Arduino
 * Based on http://www.pesadillo.com/pesadillo/?p=11092
 * 
 * La historia:
 * Despues de haber conseguido por wallapop un Robosapiens v 1.0, me encontre que su mando estaba estropeado. Trasteando por Internet, me he encontrado
 * cientos de ejemplos con códigos a medias, o sin explicar completamente. Me decidí a entrar de lleno en la programación y control de este robot
 * tan facil y asequible de conseguir ahora. Y facilitar el acceso a la documentación a todos los seguidores de la web www.pesadillo.com
 * 
 * Que hace el codigo:
 * Permite enviar un caracter por el terminal serie, que luego se convierte en codigo decimal que entiende el robosapiens al ser transmitido por el IR.
 * En el ejemplo , si enviamos w avanza, s retocede, d gira derecha, a giro izquierda. c para detenerse.
 * 
 * De interés:
 * La libreria a utilizar es IRRemote V 1.0.0 (modificada) que he incluido desde el apartado Programa/Incluir Libreria/Añadir libreria ZIP
 * Esta libreria puedes descargarla desde https://drive.google.com/file/d/0BwYG1PFb3ZByaTAxMlJZS2pIM1E/edit?usp=sharing o https://github.com/pesadillo/robosapiensv1
 * 
 * Si ya tienes una libreria mas actualizada instalada, puedes escoger la version activa en el apartado Programa/Incluir Libreria/Gestionar Libreria/IRRemote
 * Selecciona la version 1.0.0 y funcionará a la primera
 * 
 * The circuit:
 * IR LED - LED emisor en pin 3 con su respectiva resistencia de 100 Ohm.
 * 
 * www.pesadillo.com
 * created 10/05/2019
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
irsend.sendRSV1(142); // Envio sonido test de inicio
Serial.setTimeout(50); // Establezco un limite de tiempo de lectura del puerto serie (para que deje de leer la entrada)
}
void loop() {

  if (Serial.available()) //si hay lectura
   {
      char data = Serial.read(); //Captura la lectura y almacenala en "data"
      
      if ((data >= 'A'  && data <= 'Z') || (data >= 'a' && data <= 'z'))//si es caracter
      {
         Serial.println(data); // Veo datos enviados en monitor serie
         if (data == 'w'){irsend.sendRSV1(134);} //si enviamos w, avance
         if (data == 's'){irsend.sendRSV1(135);} //si enviamos s, retroceso
         if (data == 'd'){irsend.sendRSV1(118);} //si enviamos d, giro derecha
         if (data == 'a'){irsend.sendRSV1(136);} //si enviamos d, giro izquierda
         if (data == 'x'){irsend.sendRSV1(165);} //si enviamos x, agacharse
         if (data == 'c'){irsend.sendRSV1(142);} //si enviamos c, detenerse
         
     }
   }
}
