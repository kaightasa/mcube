/**
 * @file user/arm/raspi3/mailbox.c
 *
 * @author Hiroyuki Chishiro
 */
#include <mcube/mcube.h>

#include "homer.c"

void raspi3_mailbox_main(void)
{
  print("get_serial_number() = 0x%016lu\n", get_serial_number());
  print("random number = %u\n", rand_raspi3(0, UINT_MAX));
}


void raspi3_frame_buffer_main(void)
{
  struct frame_buffer fb = {
    .width = 1024,
    .height = 768,
    .virtual_width = 1024,
    .virtual_height = 768,
    .depth = 32,
    .state = PIXEL_ORDER_STATE_RGB,
    .pointer = 4096,
    .size = 0,
    .pitch = 0
  };
  print("raspi3_frame_buffer_main()\n");
  init_frame_buffer(&fb);
  //  fb_show_picture(homer_data, homer_width, homer_height);
  fb_print(10, 5, "Hello World!");
}

void raspi3_sd_main(void)
{
  //  extern unsigned char __end;
  unsigned int cluster;
  // initialize EMMC and detect SD card type
  if (init_sd() == SD_OK) {
    // read the master boot record after our bss segment
#if 0
    if (sd_readblock(0, &__end, 1)) {
      // dump it to serial console
      memdump(&__end, 512);
    }
#endif
    // read the master boot record and find our partition
    if (fat_getpartition()) {
      // list root directory entries
      //      fat_listdirectory();
      /* find out file in root directory entries */
      cluster = fat_getcluster("HOGE    TXT");
      /*
      if (cluster == 0) {
        cluster = fat_getcluster("HOGE TXT");
      }
      */
      if (cluster) {
        // read into memory
        memdump(fat_readfile(cluster), 512);
      }
    } else {
      printk("FAT partition not found???\n");
    }
  }
}


int user_raspi3_main(void)
{
  //  raspi3_mailbox_main();
  //  raspi3_frame_buffer_main();
  raspi3_sd_main();
  return 0;
}
