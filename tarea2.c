#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
  char id[100];
  char genero[100];
  char cancion[100];
  char album[100];
  int BPM;
  List *artistas;
} cancioneros;


// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Bienvenido a Spotifind");
  puts("========================================");

  puts("1) Cargar Canciones");
  puts("2) Buscar por Genero");
  puts("3) Buscar por Artista");
  puts("4) Buscar por Tempo");
  puts("5) Crear Lista de Reproduccion");
  puts("6) Agregar Cancion a Lista de Reproduccion");
  puts("7) Mostrar Canciones de una Lista");
  puts("8) Salir");
}

/**
 * Compara dos claves de tipo string para determinar si son iguales.
 * Esta función se utiliza para inicializar mapas con claves de tipo string.
 *
 * @param key1 Primer puntero a la clave string.
 * @param key2 Segundo puntero a la clave string.
 * @return Retorna 1 si las claves son iguales, 0 de lo contrario.
 */
int is_equal_str(void *key1, void *key2) {
  return strcmp((char *)key1, (char *)key2) == 0;
}

/**
 * Compara dos claves de tipo entero para determinar si son iguales.
 * Esta función se utiliza para inicializar mapas con claves de tipo entero.
 *
 * @param key1 Primer puntero a la clave entera.
 * @param key2 Segundo puntero a la clave entera.
 * @return Retorna 1 si las claves son iguales, 0 de lo contrario.
 */
int is_equal_int(void *key1, void *key2) {
  return *(int *)key1 == *(int *)key2; // Compara valores enteros directamente
}

Map *canciones_byid;
Map *canciones_bygenres;
Map *canciones_byartists;
Map *playlists_byname;

/**
 * Carga películas desde un archivo CSV y las almacena en un mapa por ID.
 */
void cargar_canciones(Map *canciones_byid, Map *canciones_bygenres, Map *canciones_byartists) {
  // Intenta abrir el archivo CSV que contiene datos de películas
  FILE *archivo = fopen("data/song_dataset_.csv", "r");
  if (archivo == NULL) {
    perror(
        "Error al abrir el archivo"); // Informa si el archivo no puede abrirse
    return;
  }

  char **campos;
  // Leer y parsear una línea del archivo CSV. La función devuelve un array de
  // strings, donde cada elemento representa un campo de la línea CSV procesada.
  campos = leer_linea_csv(archivo, ','); // Lee los encabezados del CSV
  puts("Esperando a cargar canciones...");

 

// Lee cada línea del archivo CSV hasta el final
 while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    // Crea una nueva estructura Canciones y almacena los datos de cada película
    cancioneros *nuevacancion = (cancioneros *)malloc(sizeof(cancioneros));
    if (nuevacancion == NULL) {
      perror("Error al asignar memoria para la Cancion");
      fclose(archivo);
      return;
    }
    strncpy(nuevacancion->id, campos[0], sizeof(nuevacancion->id));
    nuevacancion->artistas = split_string(campos[2], ";");
    strncpy(nuevacancion->album, campos[3], sizeof(nuevacancion->album));
    strncpy(nuevacancion->cancion, campos[4], sizeof(nuevacancion->cancion));
    nuevacancion->BPM = (int)atof(campos[18]);
    
// PARA GENEROS

    map_insert(canciones_byid, nuevacancion->id, nuevacancion);
    char *genero = campos[20];
    MapPair *Par = map_search(canciones_bygenres, genero);
    if (Par == NULL) {
    List *nuevalista = list_create();
    list_pushBack(nuevalista, nuevacancion);
    map_insert(canciones_bygenres, strdup(genero), nuevalista);
    } else {
      list_pushBack(Par->value, nuevacancion);
    }
  

// PARA ARTISTAS

    for (char *PrimerArtista = list_first(nuevacancion->artistas); PrimerArtista; PrimerArtista= list_next(nuevacancion->artistas)) {
      MapPair *Par2 = map_search( canciones_byartists, PrimerArtista);
      if (Par2 == NULL) {
        List *lista2 = list_create();
        list_pushBack(lista2, nuevacancion);
        map_insert(canciones_byartists, strdup(PrimerArtista), lista2);
      } else {
        list_pushBack((List *)Par2->value, nuevacancion);
      }
    }
  }
  fclose(archivo); // Cierra el archivo después de leer todas las líneas
 // Cierra el archivo después de leer todas las líneas
  puts("Canciones cargadas con exito");
}

//Busca y muestra la información de una película por su ID en un mapa.
void buscar_por_artista(Map *canciones_byartists) {
  char art[100];
  printf("Nombre del Artista: "); 
  scanf(" %[^\n]", art);
  MapPair *mp = map_search(canciones_byartists, art);
  if (!mp) {
    printf("Ninguna canción de %s\n", art);
    return;
  }
  for (cancioneros *c = list_first(mp->value); c; c = list_next(mp->value)) {
    printf("ID: %s \nTema: %s [%s] \nBPM:%d\n\n", c->id, c->cancion, c->album, c->BPM);
  }
}


void buscar_por_genero(Map *canciones_bygenres) {
  char gen[100];
  printf("Insertar genero de la cancion: "); scanf("%99s", gen);
  MapPair *mp = map_search(canciones_bygenres, gen);
  if (!mp) {
    printf("No hay canciones del genero %s\n", gen);
    return;
  }
  for (cancioneros *c = list_first(mp->value); c; c = list_next(mp->value)) {
    printf("ID: %s  \nTema: %s [%s] \nBPM:%d\n\n", c->id, c->cancion, c->album, c->BPM);
  }
}
 
void mostrar_generos(Map *canciones_bygenres) {
  puts("Generos disponibles:");
  for (MapPair *p = map_first(canciones_bygenres); p; p = map_next(canciones_bygenres)) {
    printf("- %s\n", (char *)p->key);
  }
}

void buscar_por_BPM(Map *canciones_byid) {
  printf("Seleccione el tipo de tempo:\n");
  printf("1) Lentas (BPM < 80)\n");
  printf("2) Moderadas (80 <= BPM <= 120)\n");
  printf("3) Rapidas (BPM > 120)\n");
  printf("Opcion: ");
  
  int opcion;
  scanf("%d", &opcion);

  int min = 0, max = 9999;

  switch (opcion) {
    case 1:
      min = 0;
      max = 79;
      break;
    case 2:
      min = 80;
      max = 120;
      break;
    case 3:
      min = 121;
      max = 9999;
      break;
    default:
      printf("Opcion invalida.\n");
      return;
  }

  printf("\nCanciones en la categoria seleccionada:\n\n");
  int found = 0;
  for (MapPair *p = map_first(canciones_byid); p; p = map_next(canciones_byid)) {
    cancioneros *c = p->value;
    if (c->BPM >= min && c->BPM <= max) {
      printf("ID: %s\nTema: %s [%s]\nBPM: %d\n\n", c->id, c->cancion, c->album, c->BPM);
      found = 1;
    }
  }

  if (!found)
    printf("No se encontraron canciones en este rango de tempo.\n");
}

// Crear una nueva playlist
void crear_playlist(Map *playlists_byname) {
  char name[100];
  printf("Nombre de nueva playlist: "); 
  scanf(" %[^\n]", name);
  if (map_search(playlists_byname, name)) {
    printf("Ya existe la playlist %s\n", name);
  } else {
    List *NuevaPlaylist = list_create();
    map_insert(playlists_byname, strdup(name), NuevaPlaylist);
    printf("Playlist '%s' creada.\n", name);
  }
}

// Agregar canción a playlist
void agregar_a_playlist(Map *playlists_byname, Map *canciones_byid) {
  char name[100], id[100];
  printf("Nombre de su Playlist:\n"); 
  scanf(" %[^\n]", name);
  MapPair *mp = map_search(playlists_byname, name);
  if (!mp) { 
    printf("No existe la Playlist %s\n", name); return;
  }

  printf("ID de la cancion a agregar:\n"); 
  scanf("%99s", id);
  MapPair *songmp = map_search(canciones_byid, id);
  if (!songmp) {
    printf("ID %s no encontrada\n", id);
    return;
  }

  list_pushBack(mp->value, songmp->value);
  printf("Cancion agregada con exito.\n");
}
void mostrar_playlist(Map *playlists_byname) {
  char name[100];
  printf("Nombre de tu Playlist:\n"); 
  scanf(" %[^\n]", name);
  MapPair *mp = map_search(playlists_byname, name);
  if (!mp) { printf("No existe %s\n", name);
    return; 
  }
  printf("Playlist %s:\n", name);
  for (cancioneros *c = list_first(mp->value); c; c = list_next(mp->value)) {
    printf("%s - %s [%s]\n", c->id, c->cancion, c->album);
  }
}
void mostrar_nombres_playlists(Map *playlists_byname) {
  puts("=========================================");
  puts("Listas de reproduccion disponibles:");
  for (MapPair *p = map_first(playlists_byname); p; p = map_next(playlists_byname)) {
    printf("- %s\n", (char *)p->key);
  }
  puts("=========================================");
}
void mostrar_artistas_disponibles(Map *canciones_byartists) {
  puts("=========================================");
  puts("Artistas disponibles:");
  for (MapPair *p = map_first(canciones_byartists); p; p = map_next(canciones_byartists)) {
    printf("- %s\n", (char *)p->key);
  }
  puts("=========================================");
  
}

int main() {
  char opcion; 

  canciones_byid      = map_create(is_equal_str);
  canciones_bygenres  = map_create(is_equal_str);
  canciones_byartists = map_create(is_equal_str);
  playlists_byname    = map_create(is_equal_str);

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opcion: ");
    scanf(" %c", &opcion);

    switch (opcion) {
    case '1':
      cargar_canciones(canciones_byid,canciones_bygenres , canciones_byartists);
      break;
    case '2':
      limpiarPantalla();                                                                  //Felipe Aguilera hizo desde cargar_canciones hasta el buscar_por_artista
      mostrar_generos(canciones_bygenres);
      buscar_por_genero(canciones_bygenres);
      break;
    case '3':
      limpiarPantalla();
      mostrar_artistas_disponibles(canciones_byartists);
      buscar_por_artista(canciones_byartists);
      break;
    case '4':
      limpiarPantalla();
      buscar_por_BPM(canciones_byid);
      break;
    case '5':
      limpiarPantalla();
      crear_playlist(playlists_byname);
      break;
    case '6':                                                                             //Pablo Saldivia hizo desde buscar_por_genero hasta el mostrar_artistas_disponibles
      limpiarPantalla();
      mostrar_nombres_playlists(playlists_byname);
      agregar_a_playlist(playlists_byname,canciones_byid);
      break;
    case '7':
      limpiarPantalla();
      mostrar_nombres_playlists(playlists_byname);
      mostrar_playlist(playlists_byname);
      break;
    case '8':
      puts("Saliendo...");
      break;
    }
    presioneTeclaParaContinuar();

  } while (opcion != '8');

  return 0;
}
