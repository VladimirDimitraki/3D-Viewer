#include "3D_Viewer.h"

/// @brief **Считывание файла**
/// @param file_path строка с директорией файла
/// @return Код ошибки true(0) false(1)
int read_file(data_t *data, char *file_path) {
  int error_code = SUCCESS;
  char array[SIZE] = {0};
  FILE *fp = NULL;

  if ((fp = fopen(file_path, "rb")) == NULL) {
    return ERROR;
  }

  while (fgets(array, SIZE, fp) != NULL && !error_code) {
    if ((*array == 'v' && *(array + 1) == ' ')) {
      if (check_string_errors(array) == SUCCESS) {
        data->vertexes++;
      } else {
        error_code = ERROR;
      }
    } else if (*array == 'f' && *(array + 1) == ' ') {
      data->polygon += count_polygons(array);
    }
  }

  data->polygon *= 2;
  if (error_code == SUCCESS && memory_allocate(data) == SUCCESS) {
    error_code = parse_data(data, array, fp);
    data->vertexes *= 3;
    double centr_x = 0, centr_y = 0, centr_z = 0, scale_for_centre = 0;
    if (error_code == SUCCESS)
      set_center(data, centr_x, centr_y, centr_z, scale_for_centre);
  } else {
    error_code = ERROR;
  }

  fclose(fp);

  return error_code;
}

/// @brief **Счетчик полигонов**
/// @param array указатель на строку
/// @param ISDIGIT функция для считывание цифры
/// @param count_args счетчик аргументов
/// @param slash_count счетчик '\'
/// @return Количество аргументов в полигонах
int count_polygons(char *array) {
  int count_args = 0;
  int slash_count = 0;

  while (*array != '\n' && *array != '\0' && *array != '\r') {
    if (*array == 'f') array++;

    if (IS_DIGIT(*array) && !slash_count) {
      count_args++;
      while (IS_DIGIT(*array)) array++;
    } else if (*array == '/') {
      if (slash_count < 2) {
        slash_count++;
        array++;
      }
      while (IS_DIGIT(*array)) array++;
    } else if (*array == ' ') {
      slash_count = 0;
      array++;

    } else if (!IS_DIGIT(*array) && *array != ' ' && *array != '.') {
      array++;
    } else if (*array == '.') {
      return ERROR;
    }
  }

  return count_args;
}

/// @brief **Запись данных вершин и полигонов**
/// @param data_t структура данных для полигонови вершин
/// @param array указатель на строку
/// @param vertex_counter счетчик вершин
/// @return Код ошибки true(0) false(1)
int parse_data(data_t *data, char *array, FILE *fp) {
  int error_code = SUCCESS;
  fseek(fp, 0, SEEK_SET);
  int vertex_counter = 0;

  while (fgets(array, SIZE, fp) != NULL && error_code == SUCCESS) {
    error_code = write_data(data, array, &vertex_counter);
  }

  return error_code;
}

/// @brief **Парсер вершин**
/// @param data_t структура данных для полигонови вершин
/// @param array указатель на строку
/// @param vertex_counter счетчик вершин
/// @return Код ошибки true(0) false(1)
int write_data(data_t *data, char *array, int *vertex_counter) {
  int error_code = SUCCESS;
  double value = 0;
  char *endptr = NULL;
  int args = 0;
  int flag = 0;

  if (*array == 'v' && *(array + 1) == ' ') {
    *vertex_counter += 1;
    while (*array && error_code == SUCCESS) {
      if (IS_DIGIT(*array)) {
        if (!IS_DIGIT(*(array + 1)) && *(array + 1) != ' ' &&
            *(array + 1) != '.') {
          flag = 1;
          array++;
          error_code = INCORRECT_VER;
        } else if (args < 3 && !flag) {
          args++;
        } else {
          array++;
        }
        if (!flag && error_code == SUCCESS) {
          value = strtod(array, &endptr);
          array = endptr;
          data->vertex_value[data->i_v++] = value;
        }
      } else if (*array == ' ') {
        flag = 0;
      }
      array++;
    }
  } else if (*array == 'f' && *(array + 1) == ' ') {
    error_code = parse_polygons(data, array, vertex_counter);
  }
  return error_code;
}

/// @brief **Парсер полигонов**
/// @param first_vertex первая вершина
/// @param index значение полигона
/// @param slash_count счетчик '\'
/// @return Код ошибки true(0) false(1)
int parse_polygons(data_t *data, char *array, int *vertex_counter) {
  int error_code = SUCCESS;
  char *endptr = NULL;
  int first_vertex = 0;
  bool first_check = false;
  int slash_count = 0;
  long int index = 0;

  while (*array != '\n' && *array != '\0' && *array != '\r' &&
         error_code == SUCCESS) {
    if (*array == 'f') array++;
    if (IS_DIGIT(*array) && !slash_count) {
      index = strtol(array, &endptr, 10);
      array = endptr;
      if (index < 0) {
        data->polygons_value[data->i_p++] = *vertex_counter - labs(index);
      } else if (index == 0) {
        error_code = INCORRECT_POL;
      } else {
        if (index > data->vertexes) error_code = INCORRECT_POL;
        data->polygons_value[data->i_p++] = index - 1;
      }
      if (!first_check) {
        first_vertex = data->polygons_value[data->i_p - 1];
        first_check = true;
      } else {
        data->polygons_value[data->i_p] = data->polygons_value[data->i_p - 1];
        data->i_p++;
      }
    } else if (*array == '/') {
      if (slash_count < 2) {
        slash_count++;
        array++;
      } else {
        error_code = ERROR;
      }
      while (IS_DIGIT(*array)) array++;
    } else if (*array == ' ') {
      slash_count = 0;
      array++;
    } else if (!IS_DIGIT(*array) && *array != ' ' && *array != '.') {
      array++;
    }
    if (*array == '\n' || *array == '\0' || *array == '\r') {
      data->polygons_value[data->i_p++] = first_vertex;
      first_check = false;
    }
  }
  return error_code;
}

/// @brief Выделение памяти
/// @return Код ошибки true(0) false(1)
int memory_allocate(data_t *data) {
  int error_code = SUCCESS;
  if (data == NULL) {
    return ERROR;
  }

  data->polygons_value = (int *)calloc(data->polygon, sizeof(int));

  if (data->polygons_value) {
    data->vertex_value = (double *)calloc(3 * data->vertexes, sizeof(double));
  }

  if (!data->vertex_value || !data->polygons_value) {
    error_code = ERROR;
  }
  return error_code;
}

/// @brief **Очистка памяти**
/// @param polygon количество полигонов
/// @param vertexes количество вершин
/// @param polygons_value значение полигона
/// @param vertex_value значение вершины
/// @return Код ошибки true(0) false(1)
int free_mem(data_t *data) {
  if (data == NULL) {
    return ERROR;
  }

  if (data->polygons_value != NULL) {
    free(data->polygons_value);
    data->polygons_value = NULL;
  }

  if (data->vertex_value != NULL) {
    free(data->vertex_value);
    data->vertex_value = NULL;
  }

  data->polygon = 0;
  data->vertexes = 0;
  data->i_p = 0;
  data->i_v = 0;

  return SUCCESS;
}

int check_string_errors(char *String) {
  int error_code = SUCCESS;
  if (*String == 'v') String++;
  while (*String && *String != '\n' && *String != '\0' && *String != '\r' &&
         !error_code) {
    if (IS_DIGIT(*String)) {
      error_code = check_digit(&String);
    } else if (*String == ' ') {
      String++;
    } else {
      error_code = INCORRECT_VER;
    }
  }
  return error_code;
}

int check_digit(char **String) {
  int error_code = SUCCESS;
  char *endptr = NULL;
  if (IS_DIGIT(**String)) {
    strtod(*String, &endptr);
    *String = endptr;
  }
  if (**String != ' ' && **String != '\n' && **String != '\0' &&
      **String != '\r') {
    error_code = INCORRECT_VER;
  }

  return error_code;
}
