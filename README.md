# tarea2
Programa SpotiFind

## Descripcion
Spotifind es un sistema de gestión de canciones que permite cargar, buscar y organizar música por diferentes criterios como género, artista y tempo (BPM). Además, ofrece funcionalidades para crear y gestionar listas de reproducción personalizadas.

## Requisitos previos
Compilador de C: GCC (Linux/WSL) o MinGW (Windows)

Bibliotecas requeridas: list.h, map.h, extra.h (incluidas en el proyecto)

Editor recomendado: Visual Studio Code con extensión C/C++

Dataset llamado song_dataset_.csv con la informacion

## Compilacion y ejecucion 

Clonar repositorio:
```
bash
git clone https://github.com/LoliWokey/Tarea2.git
```
Compilar:

Primero hay que ingresar correctamente en la carpeta donde fue descargado y guardado

(Luego)
```
bash
gcc tarea2.c tdas/list.c tdas/map.c tdas/extra.c -o tarea2
```
Ejecutar:
```
bash
./tarea2
```
## Funcionalidades
----Búsquedas avanzadas:----
+Por género musical

+Por artista

+Por rango de tempo (BPM)

----Gestión de listas de reproducción:----

+Creación de nuevas playlists

+Agregar canciones a playlists existentes

+Visualización de canciones en playlists

# Problemas conocidos
No persiste datos al cerrar el programa

Validación limitada de entradas de usuario

El archivo CSV debe tener un formato específico

Se pueden repetir canciones en la playlist

Error al Cargar 2 veces

## Mejoras planeadas
Busqueda por nombre de cancion

Borrar canciones de una playlist

Borrar playlist completamente 

Poner cancion y albumes en favoritos

## Ejemplo de uso
-------------------------------------------------------------------------
Cargar canciones:
```
Opción: 1) Cargar Canciones:
```
-------------------------------------------------------------------------
Buscar por género:
```
Opción: 2) Buscar por Genero
Generos disponibles:
-(GENEROS)
Insertar genero de la cancion: (Ingresar Genero)
```
-------------------------------------------------------------------------
```
Buscar por artista:
Opción: 3) Buscar por Artista
=========================================
Artistas disponibles:
-(ARTISTAS)
=========================================
Nombre del Artista: (Ingresar Artista)
```
-------------------------------------------------------------------------
Buscar por BPM:
```
Opción: 4) Buscar por BPM
Seleccione el tipo de tempo:
(Ingresar numeros de alguna opcion)
1) Lentas (BPM < 80)
2) Moderadas (80 <= BPM <= 120)
3) Rapidas (BPM > 120)
Opcion: 1, 2 o 3
```
-------------------------------------------------------------------------

Crear playlist:
```
Opción: 5) Crear Lista de Reproducción
Nombre de la Playlist: (ingresar Nombre)
```
-------------------------------------------------------------------------
Agregar canción a playlist:
```
Opción: 6) Agregar Cancion a Lista
=========================================
Listas de reproduccion disponibles:
-(LISTAS)
=========================================
Nombre de su Playlist: (ingresar Nombre)
ID de la cancion a agregar: (Ingresar ID)
```
------------------------------------------------------------------------
Mostrar canciones de una playlist:
```
Opción: 7) Mostrar Canciones de una Lista  
=========================================
Listas de reproduccion disponibles:
=========================================
-(LISTAS)
Nombre de su Playlist: (ingresar Nombre)
```
-------------------------------------------------------------------------
```
Salir:
Opción: 8) Salir:
```
