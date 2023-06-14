#include <stdlib.h>
#include <check.h>
#include "../pdp.h"

START_TEST(write_byte_read_byte) {
    Memory mem = {0};
    address ad  = 0;
    byte by = 0x12;
    memory_write_byte(&mem, ad, by);
    ck_assert_uint_eq(by, memory_read_byte(&mem, ad));
}
END_TEST

START_TEST(write_word_read_word) {
    Memory mem = {0};
    address ad  = 2;
    word wo = 0x3456;
    memory_write_word(&mem, ad, wo);
    ck_assert_uint_eq(wo, memory_read_word(&mem, ad));
}
END_TEST

START_TEST(write_two_bytes_read_word) {
    Memory mem = {0};
    address ad = 4;
    byte by = 0xb2;
    memory_write_byte(&mem, ad, by);
    by = 0xa1;
    memory_write_byte(&mem, ad + 1, by);
    word wo = 0xa1b2;
    ck_assert_uint_eq(wo, memory_read_word(&mem, ad));
}

START_TEST(write_word_read_two_bytes) {
    Memory mem = {0};
    address ad = 6;
    word wo = 0xc3e4;
    memory_write_word(&mem, ad, wo);
    byte by = 0xc3;
    ck_assert_uint_eq(by, memory_read_byte(&mem, ad));
    by = 0xe4;
    ck_assert_uint_eq(by, memory_read_byte(&mem, ad + 1));
}

Suite* memory_suite_create() {
    Suite* suite = suite_create("Memory");
    TCase* test_case = tcase_create("Memory w/r");
    tcase_add_test(test_case, write_byte_read_byte);
    //tcase_add_test(test_case, write_word_read_word);
    //tcase_add_test(test_case, write_two_bytes_read_word);
    //tcase_add_test(test_case, write_word_read_two_bytes);
    suite_add_tcase(suite, test_case);
    return suite;
}

int main() {
    Suite* suite = memory_suite_create();
    SRunner* suite_runner = srunner_create(suite);

    srunner_set_fork_status(suite_runner, CK_NOFORK);
    srunner_run_all(suite_runner, CK_NORMAL);

    size_t failed_count = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);
    
    if (failed_count != 0) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}