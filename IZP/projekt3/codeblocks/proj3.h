/**
 * Kostra hlavickoveho souboru 3. projekt IZP 2017/18
 * a pro dokumentaci Javadoc.
 */

/**
 * Date: 14.12.2017
 * Author: Juraj Lahvička (xlahvi00)
 * Project: IZP - dokumentace zdrojových kódů
 * URL: https://wis.fit.vutbr.cz/FIT/st/cwk.php?title=IZP:Projekt4&csid=647749&id=12214
 */

/**
 * Object in two dimensional space
 */
struct obj_t {
    int id;   ///< id - identifier of object
    float x;  ///< x - coordinate in x plane (axis)
    float y;  ///< y - coordinate in y plane (axis)
};

/**
 * cluster of objects in two dimensional space
 */
struct cluster_t {
    int size;           /**< size - number of objects stored in cluster */
    int capacity;       /**< capacity - number of objects, that can be stored in the cluster */
    struct obj_t *obj;  /**< array of objects, that are stored in the cluster */
};

/**
 * @defgroup Memory_work_functions Functions, which are working with memory
 * Functions, which allocate and deallocate memory space
 * @{
 */

/** @} */ // end of Memory_work_functions

/**
 * @defgroup Working_with_clusters Functions, which are working with clusters
 * Functions, which are appeding, merging, sorting and printing clusters
 * @{
 */

/** @} */ // end of Working_with_clusters

/**
 * @defgroup Distance_calculation Distance calculation
 * Function, which calculates distance between objects and clusters
 * @{
 */

/** @} */ // end of Distance_calculation

/**
 * Initialize cluster. Allocates memory for capacity of object. Pointer NULL in array of objects symbolizes 0 capacity.
 * @ingroup Memory_work_functions
 * @param c - initialized cluster
 * @param cap - capacity of cluster
 * @pre cap > 0
 * @post c->capacity = cap
 * @post c->size = 0
 */
void init_cluster(struct cluster_t *c, int cap);

/**
 * Removes all the objects from cluster and initializes cluster to empty cluster.
 * @ingroup Memory_work_functions
 * @param c - cluster that is going to be removed
 * @post c->obj = NULL
 * @post c->capacity = 0
 */
void clear_cluster(struct cluster_t *c);

/**
 * Chunk of cluster objects. Default value recommended for reallocation.
 */
extern const int CLUSTER_CHUNK;

/**
 * Changes capacity of cluster to new capacity.
 * @ingroup Memory_work_functions
 * @param c - cluster, whose capatity is required to be changed
 * @param new_cap - new capacity of cluster
 * @return returns modified cluster with new capacity
 */
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap);

/**
 * Appends object to end of cluster. If cluster is too small, it extends the capacity of cluster.
 * @ingroup Working_with_clusters
 * @param c - cluster that is going to be extended
 * @param obj - object that will be appended
 * @pre c->capacity <= c->size
 * @post c->obj[c->size++] = obj
 */
void append_cluster(struct cluster_t *c, struct obj_t obj);

/**
 * Appends objects of c2 to c1. c1 will be resized if needed. Sorts objects in c1 in ascending order by their ID. c2 will be unchanged
 * @ingroup Working_with_clusters
 * @param c1 - array of clusters that will obtain objects of c2
 * @param c2 - array of clusters that will hand his objects to c1 and will be unchanged.
 */
void merge_clusters(struct cluster_t *c1, struct cluster_t *c2);

/**
 * Removes cluster from field of clusters.
 * @ingroup Memory_work_functions
 * @param carr - array of clusters
 * @param narr - number of clusters in array
 * @param idx - id of cluster that will be removed
 * @return returns the new number of clusters in the cluster field
 */
int remove_cluster(struct cluster_t *carr, int narr, int idx);

/**
 * Calculates Euclidean distance between two objects
 * @ingroup Distance_calculation
 * @param o1 - first object that is being compared
 * @param o2 - second object that is being compared
 * @return returns the calculated distance
 */
float obj_distance(struct obj_t *o1, struct obj_t *o2);

/**
 * Calculates the distance between two clusters.
 * @ingroup Distance_calculation
 * @param c1 - first cluster that is being compared
 * @param c2 - second cluster that is being compared
 * @return returns the calculated distance
 */
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2);

/**
 * Finds two neighbours clusters (depends on mode if closest, furthest or Unweighted pair-group average).
 * @ingroup Distance_calculation
 * @param carr - array of clusters
 * @param narr - number of clusters in array
 * @param c1 - pointer to address in which id of first neighbour is stored
 * @param c2 - pointer to address in which id of second neighbour is stored
 */
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2);

/**
 * Sorts objects in cluster in ascending order according to their ID
 * @ingroup Working_with_clusters
 * @param c - sorted cluster
 */
void sort_cluster(struct cluster_t *c);

/**
 * Prints cluster to stdout
 * @ingroup Working_with_clusters
 * @param c - printed cluster
 */
void print_cluster(struct cluster_t *c);

/**
 * Loads objects from file. Creates cluster for each object and saves it to array of clusters. Allocates space for
 * array of all the clusters and saves the pointer to the first element.
 * @ingroup Working_with_clusters
 * @param filename - file from which the data are loaded
 * @param arr - array of clusters
 * @return returns number of objects loaded, if successful
 * @return returns -3 if file couldn't be loaded
 * @return returns -4 on fgets error
 * @return returns -6 on get_count function Error
 * @return returns -9 if error in objects file
 * @return returns -10 if number of objects is incorrect
 */
int load_clusters(char *filename, struct cluster_t **arr);

/**
 * Prints array of clusters
 * @ingroup Working_with_clusters
 * @param carr - array of clusters
 * @param narr - number of clusters in array
*/
void print_clusters(struct cluster_t *carr, int narr);