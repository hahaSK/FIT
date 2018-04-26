/**
 * Kostra programu pro 3. projekt IZP 2017/18
 *
 * Jednoducha shlukova analyza
 * Unweighted pair-group average
 * https://is.muni.cz/th/172767/fi_b/5739129/web/web/usrov.html
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h> // sqrtf
#include <limits.h> // INT_MAX

#include <stdbool.h>
#include <string.h>


#define ARGINLINE 3   //3 arguments per line allowed
#define MAXIMALVALUEOFCOORDINATES 1000              //maximal coordinates value (from 0 to 1000)
#define MAXIMALNUMBEROFCHARACTERSINLINE ((INT_MAX) <= 32768 ? 16 : 21) //maximal number of characters in line: 5 or 10 for integer + 2x(4 for 1000) + 2(spaces ' ') +1(new line '\n')

#define AVG 1   //Calculates avarage distance
#define MIN 2   //Calculates minimal distance
#define MAX 3   //Calculates maximal distance


/*****************************************************************
 * Ladici makra. Vypnout jejich efekt lze definici makra
 * NDEBUG, napr.:
 *   a) pri prekladu argumentem prekladaci -DNDEBUG
 *   b) v souboru (na radek pred #include <assert.h>
 *      #define NDEBUG
 */
#ifdef NDEBUG
#define debug(s)
#define dfmt(s, ...)
#define dint(i)
#define dfloat(f)
#else

// vypise ladici retezec
#define debug(s) printf("- %s\n", s)

// vypise formatovany ladici vystup - pouziti podobne jako printf
#define dfmt(s, ...) printf(" - "__FILE__":%u: "s"\n",__LINE__,__VA_ARGS__)

// vypise ladici informaci o promenne - pouziti dint(identifikator_promenne)
#define dint(i) printf(" - " __FILE__ ":%u: " #i " = %d\n", __LINE__, i)

// vypise ladici informaci o promenne typu float - pouziti
// dfloat(identifikator_promenne)
#define dfloat(f) printf(" - " __FILE__ ":%u: " #f " = %g\n", __LINE__, f)

#endif

/*****************************************************************
 * Deklarace potrebnych datovych typu:
 *
 * TYTO DEKLARACE NEMENTE
 *
 *   struct obj_t - struktura objektu: identifikator a souradnice
 *   struct cluster_t - shluk objektu:
 *      pocet objektu ve shluku,
 *      kapacita shluku (pocet objektu, pro ktere je rezervovano
 *          misto v poli),
 *      ukazatel na pole shluku.
 */

struct obj_t {
    int id;
    float x;
    float y;
};

struct cluster_t {
    int size;
    int capacity;
    struct obj_t *obj;
};

/*****************************************************************
 * Deklarace potrebnych funkci.
 *
 * PROTOTYPY FUNKCI NEMENTE
 *
 * IMPLEMENTUJTE POUZE FUNKCE NA MISTECH OZNACENYCH 'TODO'
 *
 */

/*
 Inicializace shluku 'c'. Alokuje pamet pro cap objektu (kapacitu).
 Ukazatel NULL u pole objektu znamena kapacitu 0.
*/
void init_cluster(struct cluster_t *c, int cap)
{
  assert(c != NULL);
  assert(cap >= 0);

  c->size=0;

  if (cap>0)
  {
    if((c->obj=malloc(cap* sizeof(struct obj_t))))
    {
      c->capacity=cap;
      return;
    }
  }

  c->capacity=0;
  c->obj=NULL;

}

/*
 Odstraneni vsech objektu shluku a inicializace na prazdny shluk.
 */
void clear_cluster(struct cluster_t *c)
{
  free(c->obj);

  init_cluster(c,0);
}

/// Chunk of cluster objects. Value recommended for reallocation.
const int CLUSTER_CHUNK = 10;

/*
 Zmena kapacity shluku 'c' na kapacitu 'new_cap'.
 */
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap)
{
  // TUTO FUNKCI NEMENTE
  assert(c);
  assert(c->capacity >= 0);
  assert(new_cap >= 0);

  if (c->capacity >= new_cap)
    return c;

  size_t size = sizeof(struct obj_t) * new_cap;

  void *arr = realloc(c->obj, size);
  if (arr == NULL)
    return NULL;

  c->obj = (struct obj_t*)arr;
  c->capacity = new_cap;
  return c;
}

/*
 Prida objekt 'obj' na konec shluku 'c'. Rozsiri shluk, pokud se do nej objekt
 nevejde.
 */
void append_cluster(struct cluster_t *c, struct obj_t obj)
{
  if (c->capacity<=c->size)
  {
    if (resize_cluster(c,c->capacity+CLUSTER_CHUNK)==0)
      return;
  }

  c->obj[c->size++]=obj;
}

/*
 Seradi objekty ve shluku 'c' vzestupne podle jejich identifikacniho cisla.
 */
void sort_cluster(struct cluster_t *c);

/*
 Do shluku 'c1' prida objekty 'c2'. Shluk 'c1' bude v pripade nutnosti rozsiren.
 Objekty ve shluku 'c1' budou serazeny vzestupne podle identifikacniho cisla.
 Shluk 'c2' bude nezmenen.
 */
void merge_clusters(struct cluster_t *c1, struct cluster_t *c2)
{
  assert(c1 != NULL);
  assert(c2 != NULL);

  for (int i = 0; i < (c2->size); i++)
  {
    append_cluster(c1, c2->obj[i]);
  }
  if (c2->size > 0)
    sort_cluster(c1);
}

/**********************************************************************/
/* Prace s polem shluku */

/*
 Odstrani shluk z pole shluku 'carr'. Pole shluku obsahuje 'narr' polozek
 (shluku). Shluk pro odstraneni se nachazi na indexu 'idx'. Funkce vraci novy
 pocet shluku v poli.
*/
int remove_cluster(struct cluster_t *carr, int narr, int idx)
{
  assert(idx < narr);
  assert(narr > 0);

  clear_cluster(&carr[idx]);

  for (int i = idx; i < narr - 1; i++)
  {
    carr[i] = carr[i + 1];
  }

  return narr - 1;

}

/*
 Pocita Euklidovskou vzdalenost mezi dvema objekty.
 */
float obj_distance(struct obj_t *o1, struct obj_t *o2)
{
  assert(o1 != NULL);
  assert(o2 != NULL);

  float a=o1->x - o2->x;
  float b=o1->y - o2->y;

  return sqrtf(powf(a, 2.0) + powf(b, 2.0));

}

/*
 Pocita vzdalenost dvou shluku.
*/
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2)
{
  assert(c1 != NULL);
  assert(c1->size > 0);
  assert(c2 != NULL);
  assert(c2->size > 0);

  float curr_dist=0;

  for (int i=0; i<c1->size;i++)
  {
    for (int j=0; j<c2->size;j++)
    {
      curr_dist+=obj_distance(&c1->obj[i],&c2->obj[j]);

    }
  }

  return curr_dist/(c2->size*c1->size);
}

/*
 Funkce najde dva nejblizsi shluky. V poli shluku 'carr' o velikosti 'narr'
 hleda dva nejblizsi shluky. Nalezene shluky identifikuje jejich indexy v poli
 'carr'. Funkce nalezene shluky (indexy do pole 'carr') uklada do pameti na
 adresu 'c1' resp. 'c2'.
*/
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2)
{
  assert(narr > 0);

  float minimal_distance=1415, curr_dist;   //1415 is of diagonal of square 1000 x 1000

  for (int i=0; i<narr;i++)
  {
    for (int j=i+1; j<narr; j++)
    {

      curr_dist=cluster_distance(&carr[i],&carr[j]);

      if (curr_dist<minimal_distance)
      {
        minimal_distance=curr_dist;
        *c1=i;
        *c2=j;
      }
    }
  }
}

// pomocna funkce pro razeni shluku
static int obj_sort_compar(const void *a, const void *b)
{
  // TUTO FUNKCI NEMENTE
  const struct obj_t *o1 = (const struct obj_t *)a;
  const struct obj_t *o2 = (const struct obj_t *)b;
  if (o1->id < o2->id) return -1;
  if (o1->id > o2->id) return 1;
  return 0;
}

/*
 Razeni objektu ve shluku vzestupne podle jejich identifikatoru.
*/
void sort_cluster(struct cluster_t *c)
{
  // TUTO FUNKCI NEMENTE
  qsort(c->obj, c->size, sizeof(struct obj_t), &obj_sort_compar);
}

/*
 Tisk shluku 'c' na stdout.
*/
void print_cluster(struct cluster_t *c)
{
  // TUTO FUNKCI NEMENTE
  for (int i = 0; i < c->size; i++)
  {
    if (i) putchar(' ');
    printf("%d[%g,%g]", c->obj[i].id, c->obj[i].x, c->obj[i].y);
  }
  putchar('\n');
}

/**
* Initializes array of narr clusters.
* @param carr array of clusters
* @param narr number of clusters in array
*/
void init_clusters(struct cluster_t **carr, const int narr)
{
  assert(carr != 0);
  assert(narr >= 0);

  if (!(*carr = malloc(narr * sizeof(struct cluster_t))))
  {
    return;
  }

  for (int i = 0; i < narr; i++)
  {
    init_cluster(&(*carr)[i], narr);
  }
}


int get_count(FILE *file, char *load, struct cluster_t **arr)
{
  int objects_count;
  char end_char;

  if (sscanf(load, "count=%d%[^\n]", &objects_count, &end_char) != 1)
  {
    fprintf(stderr, "Unexpected format of first line !\n");
    fclose(file);
    return -3;
  }

  if (objects_count <= 0)
  {
    fprintf(stderr, "Objects count needs to be integer (int) higher than 0 !\n");
    fclose(file);
    return -4;
  }

  init_clusters(arr, objects_count);
  if (*arr == NULL)
  {
    fprintf(stderr, "Allocation error.");
    fclose(file);
    return -5;
  }
  return objects_count;
}

int check_values(int input, int index, int line)
{
  if ((index == 0) && (input < 0))
  {
    fprintf(stderr, "IDs on line %d in text file is lower than 0\n", line);
    return -1;
  }
  if (((index == 1) || (index == 2)) && ((input < 0) || (input > MAXIMALVALUEOFCOORDINATES)))
  {
    fprintf(stderr, "Coordinate, that is out of the defined interval (0,1000) was found on line %d\n", line);
    return -1;
  }
  return input;

}

void save_input_lines (struct cluster_t **arr, int *readNumbers, int currentObject)
{
  struct obj_t obj;
  struct cluster_t *cluster;

  obj.id = readNumbers[0];
  obj.x = readNumbers[1];
  obj.y = readNumbers[2];
  cluster = &(*arr)[currentObject];
  append_cluster(cluster, obj);
}


void clear_input_clusters(struct cluster_t *carr, const int narr)
{
  assert(carr != 0);
  assert(narr >= 0);

  for (int i = 0; i < narr; i++)
  {
    clear_cluster(&carr[i]);
  }

  free(carr);
}



bool check_input_lines(FILE *file, struct cluster_t **arr, char *token, int currentObject, int objectsCount, int *ids)
{
  char endChar;
  bool pointsValidityFlag=0;
  int readNumbers[ARGINLINE];

  if (sscanf(token, "%d %d %d%[^\n]", &readNumbers[0], &readNumbers[1], &readNumbers[2], &endChar) !=
      ARGINLINE)
  {
    fprintf(stderr, "line %d has invalid format (should contain 3 integers separated by ' '\n", currentObject + 2);
    pointsValidityFlag = 1;
  }
  for (int i = 0; i < ARGINLINE; ++i)
  {
    readNumbers[i] = check_values(readNumbers[i], i, currentObject + 2);
    if (readNumbers[i] < 0)
      pointsValidityFlag = 1;
  }

  for (int i = 0; i < currentObject; i++)
  {
    if (readNumbers[0] == ids[i])
    {
      fprintf(stderr, "same id was used on line %d and %d (or there are less lines in file than count says)", i + 2,
              currentObject + 2);
      pointsValidityFlag = 1;
    }
  }
  ids[currentObject] = readNumbers[0];

  if (pointsValidityFlag == 1)
  {
    clear_input_clusters(*arr, objectsCount);
    *arr = NULL;
    fclose(file);
  }
  else
    save_input_lines(arr, readNumbers, currentObject);
  return pointsValidityFlag;
}

/*
 Ze souboru 'filename' nacte objekty. Pro kazdy objekt vytvori shluk a ulozi
 jej do pole shluku. Alokuje prostor pro pole vsech shluku a ukazatel na prvni
 polozku pole (ukalazatel na prvni shluk v alokovanem poli) ulozi do pameti,
 kam se odkazuje parametr 'arr'. Funkce vraci pocet nactenych objektu (shluku).
 V pripade nejake chyby uklada do pameti, kam se odkazuje 'arr', hodnotu NULL.
*/
int load_clusters(char *filename, struct cluster_t **arr)
{
  assert(arr != NULL);

  FILE *file=fopen(filename,"r");

  if (file == NULL)
  {
    fprintf(stderr, "Couldn't load file !\n");
    return -1;
  }

  char load[MAXIMALNUMBEROFCHARACTERSINLINE];

  if(!fgets(load,MAXIMALNUMBEROFCHARACTERSINLINE,file))
  {
    fclose(file);
    printf("fgets error.");
            return -2;
  }

  int stream_char_count=get_count(file, load , arr), current_object=0;
  if (stream_char_count == -1)
    return  -1;

  int ids[stream_char_count];
  while (current_object < stream_char_count)
  {
    fgets(load, MAXIMALNUMBEROFCHARACTERSINLINE, file);
    if (check_input_lines(file, arr, load, current_object, stream_char_count, ids) == 1)
      return -1;

    current_object++;
  }
  fclose(file);

  if (current_object < stream_char_count)
  {
    fprintf(stderr, "Number of objects can't be less than %d", stream_char_count);
    clear_input_clusters(*arr, stream_char_count);
    *arr = NULL;
    fclose(file);
    return -1;
  }

  return stream_char_count;




}

/*
 Tisk pole shluku. Parametr 'carr' je ukazatel na prvni polozku (shluk).
 Tiskne se prvnich 'narr' shluku.
*/
void print_clusters(struct cluster_t *carr, int narr)
{
  printf("Clusters:\n");
  for (int i = 0; i < narr; i++)
  {
    printf("cluster %d: ", i);
    print_cluster(&carr[i]);
  }
}

int input_validation (char *argv)
{
  char *endchar = NULL;
  int result = (int) strtol(argv, &endchar, 10);

  if (*endchar != '\0')
  {
    fprintf(stderr, "Argument N in user input should contain only integer number");
    return -1;
  }
  else if (result <= 0)
  {
    fprintf(stderr, "Argument N has to be higher than 0");
    return -1;
  }
  return result;
}

int set_clusters_count(struct cluster_t *carr, int narr, const int finalSize )
{
  if (finalSize > narr)
  {
    fprintf(stderr, "Value of cluster count, which is '%d' can't be bigger than objects count '%d'.", finalSize, narr);
    return -1;
  }

  int idx1, idx2;
  while (narr > finalSize)
  {
    find_neighbours(carr, narr, &idx1, &idx2);
    merge_clusters(&carr[idx1], &carr[idx2]);
    narr = remove_cluster(carr, narr, idx2);
  }
  return narr;
}

int main(int argc, char *argv[])
{
  struct cluster_t *clusters;

  if (argc > 1 && argc <= 3)
  {
    int size, finalSize = 1, calc_mode;

    if (argc == 3 || argc == 4)
    {
      finalSize = input_validation(argv[2]);
       if (finalSize == -1)
        return EXIT_FAILURE;
    }

    if (argc==3 || (argc==4 && strcmp(argv[3],"--avg")==0))
      calc_mode=AVG;
    else if (argc==4 && strcmp(argv[3],"--min")==0)
      calc_mode=MIN;
    else if (argc==4 && strcmp(argv[3],"--max")==0)
      calc_mode=MAX;



    if ((size = load_clusters(argv[1], &clusters)) == -1)
      return EXIT_FAILURE;

    int newSize;
    if ((newSize = set_clusters_count(clusters, size, finalSize, calc_mode)) == -1)  //if function returns -1, exit program
    {
      clear_input_clusters(clusters, size);
      return EXIT_FAILURE;
    }
    size = newSize;

    print_clusters(clusters, size);
    clear_input_clusters(clusters, size);

    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}