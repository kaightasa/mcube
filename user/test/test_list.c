/**
 * @file user/test/test_list.c
 *
 * @author Hiroyuki Chishiro
 */
/*
 * Copyright (C) 2010 Ahmed S. Darwish <darwish.07@gmail.com>
 */

#include <mcube/mcube.h>


struct test {
  uint64_t x;
  struct list_node node;
};

static void test_0_elements(void)
{
  struct test *t1, *t2, *t3, *spare;
  uint64_t x;

  if (!(t1 = (struct test *) kmalloc(sizeof(struct test)))) {
    printk("Error: cannot allocate memory %lu\n", sizeof(struct test));
    return;
  }

  t1->x = x = UINT64_MAX;
  list_init(&t1->node);
  assert(list_empty(&t1->node));

  t2 = list_entry(&t1->node, struct test, node);
  assert(t1 == t2);

  list_for_each(&t1->node, t3, node)
  assert(false);

  list_for_each_safe(&t1->node, t3, spare, node)
  assert(false);

  list_del(&t1->node);
  assert(t2->x == x);
  kfree(t2);

  printk("%s: SUCCESS\n", __func__);
}

enum list_type {
  STACK,
  QUEUE,
};

static void test_1_element(int type)
{
  struct list_node head;
  struct test *t1, *t2, *t3, *spare = NULL;

  list_init(&head);
  assert(list_empty(&head));

  if (!(t1 = (struct test *) kmalloc(sizeof(struct test)))) {
    printk("Error: cannot allocate memory %lu\n", sizeof(struct test));
    return;
  }

  t1->x = UINT64_MAX;

  switch (type) {
  case STACK:
    list_add(&head, &t1->node);
    break;

  case QUEUE:
    list_add_tail(&head, &t1->node);
    break;

  default:
    assert(false);
  }

  assert(!list_empty(&head));

  t2 = list_entry(head.next, struct test, node);
  assert(t1 == t2);

  t2 = list_entry(head.prev, struct test, node);
  assert(t1 == t2);

  list_for_each(&head, t3, node)
  assert(t1 == t3);

  list_for_each_safe(&head, t3, spare, node) {
    assert(t1 == t3);

    list_del(&t3->node);
    assert(t1->x == t3->x);
  }

  assert(t1->x == t2->x);
  kfree(t2);

  assert(list_empty(&head));
  printk("%s(%s): SUCCESS\n", __func__, type == STACK ? "stack" : "queue");
}

static void test_several_elements(int count, int type)
{
  struct list_node head;
  struct test **t, *te = NULL, *spare = NULL;

  list_init(&head);
  assert(list_empty(&head));

  if (!(t = (struct test **) kmalloc(sizeof(struct test *) * count))) {
    panic("Error: cannot allocate memory %lu\n", sizeof(struct test *) * count);
  }

  for (int i = 0; i < count; i++) {
    if (!(t[i] = (struct test *) kmalloc(sizeof(struct test)))) {
      panic("Error: cannot allocate memory %lu\n", sizeof(struct test));
    }

    t[i]->x = i;

    switch (type) {
    case STACK:
      list_add(&head, &t[i]->node);
      break;

    case QUEUE:
      list_add_tail(&head, &t[i]->node);
      break;

    default:
      assert(false);
    }

    assert(!list_empty(&head));
  }

  /* First, iterate over the list */
  list_for_each(&head, te, node) {
    printk(" %ld ", te->x);
  }
  printk("\n");

  /* Then, popup elements as you go */
  list_for_each_safe(&head, te, spare, node) {
    printk(" %ld ", te->x);
    list_del(&te->node);
    kfree(te);
  }
  kfree(t);
  printk("\n");

  assert(list_empty(&head));
  printk("%s(%d, %s): SUCCESS\n", __func__, count,
         type == STACK ? "stack" : "queue");
}

bool test_list(void)
{
  test_0_elements();

  test_1_element(STACK);
  test_1_element(QUEUE);

  test_several_elements(1, STACK);
  test_several_elements(2, STACK);
  test_several_elements(5, STACK);
  test_several_elements(10, STACK);
  test_several_elements(20, STACK);

  test_several_elements(1, QUEUE);
  test_several_elements(2, QUEUE);
  test_several_elements(5, QUEUE);
  test_several_elements(10, QUEUE);
  test_several_elements(20, QUEUE);
  return true;
}
