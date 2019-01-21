/**
 * @file user/test/test.c
 *
 * @author Hiroyuki Chishiro
 */
#include <mcube/mcube.h>

int test_ring_buf(void);
int test_bitmap(void);
int test_string(void);
int test_atmoic(void);

int user_test_main(void)
{
  test_ring_buf();
  test_bitmap();
  test_string();
  return 0;
}
