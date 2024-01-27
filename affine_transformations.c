#include "3D_Viewer.h"

int move_x(data_t *data, double point) {
  for (data->i_v = 0; data->i_v < data->vertexes; data->i_v += 3) {
    data->vertex_value[data->i_v] += point;
  }

  return 0;
}

int move_y(data_t *data, double point) {
  for (data->i_v = 1; data->i_v < data->vertexes; data->i_v += 3) {
    data->vertex_value[data->i_v] += point;
  }

  return 0;
}

int move_z(data_t *data, double point) {
  for (data->i_v = 2; data->i_v < data->vertexes; data->i_v += 3) {
    data->vertex_value[data->i_v] += point;
  }

  return 0;
}

int size_xyz(data_t *data, double point) {
  for (data->i_v = 0; data->i_v < data->vertexes; data->i_v++) {
    data->vertex_value[data->i_v] *= point;
  }

  return 0;
}

int rotation_x(data_t *data, int point) {
  double p = (double)point;
  p *= M_PI / 180;
  for (data->i_v = 0; data->i_v < data->vertexes; data->i_v++) {
    double tmp_y = data->vertex_value[data->i_v += 1];
    double tmp_z = data->vertex_value[data->i_v + 1];
    data->vertex_value[data->i_v] = tmp_y * cos(p) + tmp_z * sin(p);
    data->i_v += 1;
    data->vertex_value[data->i_v] = -tmp_y * sin(p) + tmp_z * cos(p);
  }

  return 0;
}

int rotation_y(data_t *data, int point) {
  double p = (double)point;
  p *= M_PI / 180;
  for (data->i_v = 0; data->i_v < data->vertexes; data->i_v++) {
    double tmp_x = data->vertex_value[data->i_v];
    double tmp_z = data->vertex_value[data->i_v + 2];
    data->vertex_value[data->i_v] = tmp_x * cos(p) + tmp_z * sin(p);
    data->i_v += 2;
    data->vertex_value[data->i_v] = -tmp_x * sin(p) + tmp_z * cos(p);
  }
  return 0;
}

int rotation_z(data_t *data, int point) {
  double p = (double)point;
  p *= M_PI / 180;

  for (data->i_v = 0; data->i_v < data->vertexes; data->i_v++) {
    double tmp_x = data->vertex_value[data->i_v];
    double tmp_y = data->vertex_value[data->i_v + 1];
    data->vertex_value[data->i_v] = tmp_x * cos(p) + tmp_y * sin(p);
    data->i_v += 1;
    data->vertex_value[data->i_v] = -tmp_x * sin(p) + tmp_y * cos(p);
    data->i_v += 1;
  }
  return 0;
}