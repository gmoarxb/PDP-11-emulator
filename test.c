#include <stdlib.h>
#include <check.h>
#include "pdp.h"

START_TEST(test_name) {

}
END_TEST

int main() {
    Suite* suite = suite_create("Memory");
    TCase* test_case = tcase_create("Memory");

    suite_add_tcase(suite, test_case);
    tcase_add_test(test_case, test_name);

    SRunner* suite_runner = srunner_create(suite);
    srunner_set_fork_status(suite, CK_NOFORK);

    srunner_run_all(suite_runner, CK_NORMAL);
    size_t failed_count = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);
    
    if (failed_count != 0) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}