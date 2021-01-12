/**
 * @file kernel/thread.c
 *
 * @author Hiroyuki Chishiro
 *         Akihiro Sakurai
 */
#include <mcube/mcube.h>

struct thread_struct ths[NR_THREADS];

unsigned char PAGE_ALIGNMENT kernel_stack[NR_CPUS][KERNEL_STACK_SIZE];
unsigned char PAGE_ALIGNMENT user_stack[NR_THREADS][USER_STACK_SIZE];

/**
 * @var ThreadID
 * @brief Thread ID.
 * idle should not be in the hash, becuase its const.
 */
static uint32_t ThreadID = FIRST_DYNAMIC_THREAD_ID;


int get_tq_util(struct thread_struct *head, unsigned long cpu)
{
  struct thread_struct *p;
  int sum_util = 0;

  //  print("get_tq_util()\n");
  for (p = head; p != &kernel_th[cpu]; p = p->next) {
    //    print("p->id = %llu\n", p->id);
    sum_util += p->util;
  }

  return sum_util;
}

int alloc_thread_id(void)
{
  return ThreadID++;
}

int get_thread_id(struct thread_struct *th)
{
  return th->id;
}


void thread_main(struct thread_struct *th)
{
  __uninitialized(th);
}


struct thread_struct *do_create_thread(void *(*func)(void *),
                                       void *arg,
                                       struct th_attr *attr)
{

  //TODO set id to attr->core_id, set stack size to attr->stack_size
  unsigned long id;
  unsigned long index;
  id = alloc_thread_id();
  index = id - 1;

  if (index < NR_THREADS) {
    if (attr) {
      ths[index].id = attr->core_id;
    } else {
      ths[index].id = id;
    }
    ths[index].state = UNADMITTED;
    ths[index].tk = current_task;

    if (attr) {
      ths[index].type = attr->type;
    } else {
      ths[index].type = APERIODIC_TH;
    }

    ths[index].thflags = 0;
    ths[index].arg = arg;

    ths[index].sched.release = 0;

    if (attr) {
      ths[index].sched.period = attr->period;
      ths[index].sched.relative_deadline = attr->relative_deadline;
      ths[index].sched.deadline = attr->relative_deadline;
      ths[index].sched.wcet = attr->wcet;
    } else {
      ths[index].sched.period = ULONG_MAX;
      ths[index].sched.relative_deadline = ULONG_MAX;
      ths[index].sched.deadline = ULONG_MAX;
      ths[index].sched.wcet = ULONG_MAX;
    }

    ths[index].stack_top = USER_THREAD_STACK_ADDR(ths[index].id);
    ths[index].run_func = run_user_thread;
    ths[index].run_user_func = func;

    return &ths[index];
  } else {
    print("do_create_thread(): Error: %lu exceed NR_THREADS %d\n", id, NR_THREADS);
    return NULL;
  }
}

struct thread_struct *get_thread_struct_from_id(struct thread_map *thmap,
                                                unsigned long id)
{
  int i;
  for (i = 0; i < NR_THREADS; i++) {
    if (thmap[i].id == id) {
      return thmap[i].p_thread_struct;
    }
  }
  return NULL;
}
