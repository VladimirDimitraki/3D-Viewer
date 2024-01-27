#ifndef v_3D_VIEWER
#define v_3D_VIEWER

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 512
#define IS_DIGIT(c) (((c) >= '0' && (c) <= '9') || (c) == '-')

typedef enum error_code {
  SUCCESS,
  ERROR,
  INCORRECT_VER,
  INCORRECT_POL,
  MEMORY_FAIL
} errnum;

typedef struct {
  int vertexes;
  int polygon;
  double *vertex_value;
  int *polygons_value;
  int i_p;
  int i_v;
} data_t;

/*          Affine Transformations          */
// Size
int size_xyz(data_t *data, double point);
// Move
int move_x(data_t *data, double point);
int move_y(data_t *data, double point);
int move_z(data_t *data, double point);
// Rotate
int rotation_x(data_t *data, int point);
int rotation_y(data_t *data, int point);
int rotation_z(data_t *data, int point);

/*                Set Centre                */
int find_max_min(data_t *data, double *centr_x, double *centr_y,
                 double *centr_z, double *scale_for_centre);
void max_for_window(double max_x, double min_x, double max_y, double min_y,
                    double max_z, double min_z, double *scale_for_centre);

int set_center(data_t *data, double centr_x, double centr_y, double centr_z,
               double scale_for_centre);

/*                  Memory                  */
int memory_allocate(data_t *points_v);
int free_mem(data_t *data);

/*        #READ FILE AND PARSE DATA#        */
int read_file(data_t *data, char *File_open);
int count_polygons(char *array);
int parse_data(data_t *data, char *array, FILE *fp);
int write_data(data_t *data, char *array, int *vertex_counter);
int parse_polygons(data_t *data, char *array, int *vertex_counter);

/*                  VALID                   */
int check_string_errors(char *String);
int check_digit(char **String);

#endif
