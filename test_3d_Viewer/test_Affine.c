#include "test.h"
/*VALID*/
START_TEST(affine_test_0) {
  data_t data = {0};
  int error = 0;
  double point = 3.0;
  char file[150] = "test_3d_Viewer/test_file/cube.txt";
  read_file(&data, file);
  error = move_x(&data, point);
  free_mem(&data);
  ck_assert_int_eq(SUCCESS, error);
}
END_TEST

START_TEST(affine_test_1) {
  data_t data = {0};
  int error = 0;
  double point = 3.0;
  char file[150] = "test_3d_Viewer/test_file/cube.txt";
  read_file(&data, file);
  error = move_y(&data, point);
  free_mem(&data);
  ck_assert_int_eq(SUCCESS, error);
}
END_TEST

START_TEST(affine_test_2) {
  data_t data = {0};
  int error = 0;
  double point = 3.0;
  char file[150] = "test_3d_Viewer/test_file/cube.txt";
  read_file(&data, file);
  error = move_z(&data, point);
  free_mem(&data);
  ck_assert_int_eq(SUCCESS, error);
}
END_TEST

START_TEST(affine_test_3) {
  data_t data = {0};
  int error = 0;
  double point = 3.0;
  char file[150] = "test_3d_Viewer/test_file/cube.txt";
  read_file(&data, file);
  error = size_xyz(&data, point);
  free_mem(&data);
  ck_assert_int_eq(SUCCESS, error);
}
END_TEST

START_TEST(affine_test_4) {
  data_t data = {0};
  int error = 0;
  double point = 3.0;
  char file[150] = "test_3d_Viewer/test_file/cube.txt";
  read_file(&data, file);
  error = rotation_x(&data, point);
  free_mem(&data);
  ck_assert_int_eq(SUCCESS, error);
}
END_TEST

START_TEST(affine_test_5) {
  data_t data = {0};
  int error = 0;
  double point = 3.0;
  char file[150] = "test_3d_Viewer/test_file/cube.txt";
  read_file(&data, file);
  error = rotation_y(&data, point);
  free_mem(&data);
  ck_assert_int_eq(SUCCESS, error);
}
END_TEST

START_TEST(affine_test_6) {
  data_t data = {0};
  int error = 0;
  double point = 3.0;
  char file[150] = "test_3d_Viewer/test_file/cube.txt";
  read_file(&data, file);
  error = rotation_z(&data, point);
  free_mem(&data);
  ck_assert_int_eq(SUCCESS, error);
}
END_TEST

/*FAIL*/

START_TEST(affine_test_7) {
  data_t data = {0};
  int error = 0;
  double point = 30000.0;
  char file[150] = "test_3d_Viewer/test_file/cube.txt";
  read_file(&data, file);
  error = move_x(&data, point);
  free_mem(&data);
  ck_assert_int_eq(SUCCESS, error);
}
END_TEST

START_TEST(affine_test_8) {
  data_t data = {0};
  int error = 0;
  double point = 30000.0;
  char file[150] = "test_3d_Viewer/test_file/cube.txt";
  read_file(&data, file);
  error = move_y(&data, point);
  free_mem(&data);
  ck_assert_int_eq(SUCCESS, error);
}
END_TEST

START_TEST(affine_test_9) {
  data_t data = {0};
  int error = 0;
  double point = 30000.0;
  char file[150] = "test_3d_Viewer/test_file/cube.txt";
  read_file(&data, file);
  error = move_z(&data, point);
  free_mem(&data);
  ck_assert_int_eq(SUCCESS, error);
}
END_TEST

START_TEST(affine_test_10) {
  data_t data = {0};
  int error = 0;
  double point = 30000.0;
  char file[150] = "test_3d_Viewer/test_file/cube.txt";
  read_file(&data, file);
  error = size_xyz(&data, point);
  free_mem(&data);
  ck_assert_int_eq(SUCCESS, error);
}
END_TEST

START_TEST(affine_test_11) {
  data_t data = {0};
  int error = 0;
  double point = 30000.0;
  char file[150] = "test_3d_Viewer/test_file/cube.txt";
  read_file(&data, file);
  error = rotation_x(&data, point);
  free_mem(&data);
  ck_assert_int_eq(SUCCESS, error);
}
END_TEST

START_TEST(affine_test_12) {
  data_t data = {0};
  int error = 0;
  double point = 30000.0;
  char file[150] = "test_3d_Viewer/test_file/cube.txt";
  read_file(&data, file);
  error = rotation_y(&data, point);
  free_mem(&data);
  ck_assert_int_eq(SUCCESS, error);
}
END_TEST

START_TEST(affine_test_13) {
  data_t data = {0};
  int error = 0;
  double point = 30000.0;
  char file[150] = "test_3d_Viewer/test_file/cube.txt";
  read_file(&data, file);
  error = rotation_z(&data, point);
  free_mem(&data);
  ck_assert_int_eq(SUCCESS, error);
}
END_TEST

Suite *affine_test(void) {
  Suite *s = suite_create("\033[45m-=AFFINE=-\033[0m");
  TCase *tc1_1 = tcase_create("OP_VALIDATOR: ");

  suite_add_tcase(s, tc1_1);

  tcase_add_test(tc1_1, affine_test_0);
  tcase_add_test(tc1_1, affine_test_1);
  tcase_add_test(tc1_1, affine_test_2);
  tcase_add_test(tc1_1, affine_test_3);
  tcase_add_test(tc1_1, affine_test_4);
  tcase_add_test(tc1_1, affine_test_5);
  tcase_add_test(tc1_1, affine_test_6);
  tcase_add_test(tc1_1, affine_test_7);
  tcase_add_test(tc1_1, affine_test_8);
  tcase_add_test(tc1_1, affine_test_9);
  tcase_add_test(tc1_1, affine_test_10);
  tcase_add_test(tc1_1, affine_test_11);
  tcase_add_test(tc1_1, affine_test_12);
  tcase_add_test(tc1_1, affine_test_13);

  return s;
}