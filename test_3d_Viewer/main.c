#include "test.h"

int main(void) {
  int failed = 0;
  Suite *Viewer_3D[] = {file_test(), affine_test(), NULL};
  for (int i = 0; Viewer_3D[i] != NULL; i++) {
    SRunner *sr = srunner_create(Viewer_3D[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);
  return 0;
}
