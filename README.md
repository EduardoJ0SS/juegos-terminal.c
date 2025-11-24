README –           Cómo abrir y ejecutar el proyecto

1. Descomprimir el archivo flopycompartida.rar

Dentro en flopycompartida  Te va a aparecer un archivo llamado flopy.exe.

             2. Ejecutar el juego

Hacé doble clic en flopy.exe para abrir el programa.    
                  *ACLARACION:*                                             
 Si aparece un mensaje de alerta de tu sistema, haz lo siguiente: 
¿Cómo ejecutar el programa igualmente?

En el mensaje de alerta de tu sistema:

Haz clic en “Más información”

Aparecerá el botón “Ejecutar de todas formas”

Apretás y listo.  

*COMO JUGAR*
Para Jugar :
Presionar la tecla de espacio para subir y listo , trata de no chocar jsjs.

             *3. Ver el código fuente del proyecto*

Para revisar el código del juego:

Entrá a la carpeta "codigo del juego".

Abrí el archivo juegoPR.c.


               4. Ver los archivos Header

Para ver los .h del proyecto:

En la misma carpeta "codigo del juego".

Abrí puntajesPR.h y obstaculosPR.h
Estos a su vez necesitan vincularce a dos headers de raylib
en la carpeta raylib/include y raylib/lib se encuentran para quienes quieran compilar desde cmd o PowerShell:

Abrir una terminal en la carpeta del proyecto (codigo del juego/).
Ejecutar, por ejemplo:

  gcc src/juegoPR.c -o juego.exe ^
  -I./raylib/include ^
  -L./raylib/lib -lraylib ^
  -lgdi32 -lopengl32 -lwinmm -luser32

  luego ejecutar : 
  .\juego.exe
