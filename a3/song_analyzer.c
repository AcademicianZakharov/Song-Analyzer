/** @file song_analyzer.c
 *  @brief A small program to analyze songs data.
 *  @author Mike Z.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Juan G.
 *  @author Gabriel Maryshev
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX_LINE_LEN 1024
/**
 * @brief Serves as an incremental counter for navigating the list.
 *
 * @param p The pointer of the node to print.
 * @param arg The pointer of the index.
 *
 */
void inccounter(node_t *p, void *arg)
{
    int *ip = (int *)arg;
    (*ip)++;
}

/**
 * @brief Prints out the contents of the nodes for a specific metric, these 3 functions are similar
 *
 * @param p The pointer of the node to print.
 * @param arg The format of the string.
 *
 */
void print_nodebypop(node_t *p, void *arg)
{
    char *fmt = (char *)arg;
    printf(fmt, p->artist, p->songtitle, p->year, p->popularity);
}

void print_nodebydanceability(node_t *p, void *arg)
{
    char *fmt = (char *)arg;
    printf(fmt, p->artist, p->songtitle, p->year, p->dancebility);
}

void print_nodebyenergy(node_t *p, void *arg)
{
    char *fmt = (char *)arg;
    printf(fmt, p->artist, p->songtitle, p->year, p->energy);
}


/**
 * @brief Allows to print each node in the list.
 *
 * @param l The first node in the list
 * @param displaynum number of songs to display
 * @param metric 0,1,2 used instead of popularity, danceability and energy respectively
 *
 */
void analysis(node_t *l, int displaynum, int metric)
{

    if(metric == 0){
        for(int i = 0; i < displaynum; i++) {
            print_nodebypop(l, "%s,%s,%s,%s\n");
            l = l->next;
        }
    }
    else if(metric == 1){
        for(int i = 0; i < displaynum; i++) {
            print_nodebydanceability(l, "%s,%s,%s,%s\n");
            l = l->next;
        }
    }
    else if(metric == 2){
        for(int i = 0; i < displaynum; i++) {
            print_nodebyenergy(l, "%s,%s,%s,%s\n");
            l = l->next;
        }
    }
}

/**
 * @brief puts data into linked list
 *
 * @param file one of the files
 * 
 * @param metric 0,1,2 used instead of popularity, danceability and energy respectively
 *
 * @param list1 linked list
 * 
 * @return node_t* list1
 */
node_t* read_file(char* file, int metric, node_t* list1) {
    printf("%s\n", file);

    FILE* filePointer;
    filePointer = fopen(file, "r");
    if(filePointer == NULL) {
      printf("error opening file");
    }
    //node_t *list1 = NULL;
    char sLine[300];
    int lcount = 0;
    //get data from line and put it into the linked list
    while (fgets(sLine, MAX_LINE_LEN, filePointer) != NULL) {
        char *art = strtok(sLine, ",");
        char *song = strtok(NULL, ",");
        char *year = strtok(NULL, ",");
        year = strtok(NULL, ",");
        year = strtok(NULL, ",");
        char *pop = strtok(NULL, ",");
        char *dance = strtok(NULL, ",");   
        char *energy = strtok(NULL, ",");

        list1 = add_inorder(list1, new_node(art, song, year, pop, dance, energy), metric);
        lcount++;
    }
    printf("%d\n", lcount);
    fclose(filePointer);
    return list1;
}

/**
 * @brief get a number 0, 1, 2 from "popularity", "danceability" and "eneergy" respectively
 *
 * @param sortbyval the string after sortby=, one of the above strings
 * 
 * @return int metric
 *
 */
int getmetric(char* sortbyval) {
    int metric;//used a number instead of a string
    if(strcmp(sortbyval, "popularity") == 0){
        metric = 0;
        printf("this is metric %d\n", metric);
    }
    else if(strcmp(sortbyval, "danceability") == 0){
        metric = 1;
        printf("this is metric %d\n", metric);
    }
    else if(strcmp(sortbyval, "energy") == 0){
        metric = 2;
        printf("this is metric %d\n", metric);
    }
    return metric;
}


/**
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main(int argc, char *argv[])
{
    //get arguments from console
    char firstarg[50], secondarg[50], filearg[100];
    strcpy(firstarg, argv[1]);
    strcpy(secondarg, argv[2]);
    strcpy(filearg, argv[3]);
    //parse arguments
    char* sortbyval = strtok(firstarg, "=");
    sortbyval += strlen(firstarg) + 1;
    int metric = getmetric(sortbyval);//used a number instead of a string
    char* displayval = strtok(secondarg, "=");   
    displayval += strlen(secondarg) + 1;
    int displaynum = atoi(displayval);

    char* files = strtok(filearg, "="); //strtok to get files
    files += strlen(filearg) + 1;  
    char* file1 = strtok(files, ",");
    char* file2 = strtok(NULL, ",");
    char* file3 = strtok(NULL, ",");
    printf("this is file1:%s, file2:%s, file3:%s\n", file1, file2, file3);

    //calling readfile to put data into linked list
    node_t* list1 = NULL;
    if(file1 != NULL) {
        list1 = read_file(file1, metric, list1);
    }
    if(file2 != NULL) {
        list1 = read_file(file2, metric, list1);
    }
    if(file3 != NULL) {
        list1 = read_file(file3, metric, list1);
    }

    //print stdout to file
    freopen("output.csv", "w", stdout);
    //header line
    printf("artist,song,year,%s\n", sortbyval);
    //print out the linked list
    analysis(list1, displaynum, metric);
    //free linked list
    node_t *temp_n = NULL;
    for (; list1 != NULL; list1 = temp_n)
    {
        temp_n = list1->next;
        free(list1->artist);
        free(list1->songtitle);
        free(list1->year);
        free(list1->popularity);
        free(list1->dancebility);
        free(list1->energy);
        free(list1);
    }
    fclose (stdout);
    exit(0);
}
