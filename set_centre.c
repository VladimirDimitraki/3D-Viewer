#include "3D_Viewer.h"
/// @brief **Ищет болшее и меньшее значение в x y z**
/// @param centr_x центр x
/// @param centr_y центр y
/// @param centr_z центр z
/// @return 0
int find_max_min(data_t *data, double *centr_x, double *centr_y,
                 double *centr_z, double *scale_for_centre) {
  int point = 0;
  double curr_min_x = data->vertex_value[0];
  double curr_max_x = data->vertex_value[0];
  double curr_min_y = data->vertex_value[1];
  double curr_max_y = data->vertex_value[1];
  double curr_min_z = data->vertex_value[2];
  double curr_max_z = data->vertex_value[2];
  for (data->i_v = 0; data->i_v < data->vertexes; data->i_v++) {
    point++;
    if (point == 1) {
      if (curr_min_x > data->vertex_value[data->i_v]) {
        curr_min_x = data->vertex_value[data->i_v];
      } else if (curr_max_x < data->vertex_value[data->i_v]) {
        curr_max_x = data->vertex_value[data->i_v];
      }
    } else if (point == 2) {
      if (curr_min_y > data->vertex_value[data->i_v]) {
        curr_min_y = data->vertex_value[data->i_v];
      } else if (curr_max_y < data->vertex_value[data->i_v]) {
        curr_max_y = data->vertex_value[data->i_v];
      }
    } else if (point == 3) {
      if (curr_min_z > data->vertex_value[data->i_v]) {
        curr_min_z = data->vertex_value[data->i_v];
      } else if (curr_max_z < data->vertex_value[data->i_v]) {
        curr_max_z = data->vertex_value[data->i_v];
      }
      point = 0;
    }
  }

  *centr_x = curr_min_x + (curr_max_x - curr_min_x) / 2;
  *centr_y = curr_min_y + (curr_max_y - curr_min_y) / 2;
  *centr_z = curr_min_z + (curr_max_z - curr_min_z) / 2;

  max_for_window(curr_max_x, curr_min_x, curr_max_y, curr_min_y, curr_max_z,
                 curr_min_z, scale_for_centre);
  return 0;
}

/// @brief **максимальное значение из координат**
/// @param scale_for_centre для нахождения большего из координат
void max_for_window(double max_x, double min_x, double max_y, double min_y,
                    double max_z, double min_z, double *scale_for_centre) {
  double x = max_x - min_x;
  double y = max_y - min_y;
  double z = max_z - min_z;
  if (x > y && y > z) {
    *scale_for_centre = x;
  } else if (y > x && x > z) {
    *scale_for_centre = y;
  } else {
    *scale_for_centre = z;
  }
}

/// @brief **Отцентровка**
/// @param centr_x центр x
/// @param centr_y центр y
/// @param centr_z центр z
/// @param point значение координаты
/// @param scale_for_centre большее значение из координат
/// @return 0
int set_center(data_t *data, double centr_x, double centr_y, double centr_z,
               double scale_for_centre) {
  int point = 0;
  data->i_v = 0;
  find_max_min(data, &centr_x, &centr_y, &centr_z, &scale_for_centre);
  double scale = (1 - (1 * (-1))) / scale_for_centre;
  for (data->i_v = 0; data->i_v < data->vertexes; data->i_v++) {
    point++;
    if (point == 1) {
      data->vertex_value[data->i_v] -= centr_x;
      data->vertex_value[data->i_v] *= scale;
    } else if (point == 2) {
      data->vertex_value[data->i_v] -= centr_y;
      data->vertex_value[data->i_v] *= scale;
    } else if (point == 3) {
      data->vertex_value[data->i_v] -= centr_z;
      data->vertex_value[data->i_v] *= scale;
      point = 0;
    }
  }

  return 0;
}
