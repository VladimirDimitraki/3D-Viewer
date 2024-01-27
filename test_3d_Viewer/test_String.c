#include "test.h"

START_TEST(file_test_0) {
  data_t data = {0};
  int error = 0;
  char file[150] = "test_3d_Viewer/test_file/cube.txt";
  error = read_file(&data, file);
  free_mem(&data);
  ck_assert_int_eq(SUCCESS, error);
}
END_TEST

START_TEST(file_test_1) {
  data_t data = {0};
  int error = 0;
  char file[150] = "test_3d_Viewer/test_file/cube_neg.txt";  // тут
  error = read_file(&data, file);
  free_mem(&data);
  ck_assert_int_eq(SUCCESS, error);
}
END_TEST

START_TEST(file_test_4) {
  data_t data = {0};
  int error = SUCCESS;
  char file[150] =
      "test_3d_Viewer/test_file/"
      "facet_that_less_than_1.txt";  // тут
  error = read_file(&data, file);
  free_mem(&data);
  ck_assert_int_eq(INCORRECT_POL, error);
}
END_TEST

START_TEST(file_test_8) {
  data_t data = {0};
  int error = 0;
  char file[150] = "test_3d_Viewer/test_file/bison.txt";  // тут
  error = read_file(&data, file);
  free_mem(&data);
  ck_assert_int_eq(SUCCESS, error);
}
END_TEST

START_TEST(file_test_9) {
  data_t data = {0};
  int error = 0;
  char file[150] = "test_3d_Viewer/test_file/glass.txt";  // тут
  error = read_file(&data, file);
  free_mem(&data);
  ck_assert_int_eq(SUCCESS, error);
}
END_TEST

START_TEST(file_test_10) {
  data_t data = {0};
  int error = 0;
  char file[150] = "test_3d_Viewer/test_file/ERROR_1.txt";
  error = read_file(&data, file);
  free_mem(&data);
  ck_assert_int_eq(ERROR, error);
}
END_TEST

START_TEST(file_test_11) {
  data_t data = {0};
  int error = 0;
  char file[150] = "test_3d_Viewer/test_file/ERROR_2.txt";
  error = read_file(&data, file);
  free_mem(&data);
  ck_assert_int_eq(INCORRECT_VER, error);
}
END_TEST

START_TEST(file_test_12) {
  data_t data = {0};
  int error = 0;
  char file[150] = "test_3d_Viewer/test_file/NOFILE.txt";
  error = read_file(&data, file);
  free_mem(&data);
  ck_assert_int_eq(ERROR, error);
}
END_TEST

START_TEST(file_test_13) {
  data_t data = {0};
  int error = 0;
  char file[150] = "test_3d_Viewer/test_file/ERROR_3.txt";
  error = read_file(&data, file);
  free_mem(&data);
  ck_assert_int_eq(INCORRECT_POL, error);
}
END_TEST

START_TEST(file_test_15) {
  data_t *data = NULL;
  int error = 0;
  error = memory_allocate(data);
  free_mem(data);
  ck_assert_int_eq(ERROR, error);
}
END_TEST

Suite *file_test(void) {
  Suite *s = suite_create("\033[45m-=OP_VALIDATOR=-\033[0m");
  TCase *tc1_1 = tcase_create("OP_VALIDATOR: ");

  suite_add_tcase(s, tc1_1);

  tcase_add_test(tc1_1, file_test_0);
  tcase_add_test(tc1_1, file_test_1);
  tcase_add_test(tc1_1, file_test_4);
  tcase_add_test(tc1_1, file_test_8);
  tcase_add_test(tc1_1, file_test_9);
  tcase_add_test(tc1_1, file_test_10);
  tcase_add_test(tc1_1, file_test_11);
  tcase_add_test(tc1_1, file_test_12);
  tcase_add_test(tc1_1, file_test_13);
  tcase_add_test(tc1_1, file_test_15);

  return s;
}
