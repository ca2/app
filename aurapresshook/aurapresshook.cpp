// http://stackoverflow.com/questions/11451618/how-do-you-read-the-mouse-button-state-from-dev-input-mice
// http://stackoverflow.com/users/884434/justinb
::i32 main(::i32 argc char_pointer * argv)
{
    ::i32 fd, bytes;
    ::u8 data[3];

    const_char_pointer pDevice = "/dev/input/mice";

    // Open Mouse
    fd = open(pDevice, O_RDWR | O_CLOEXEC);
    if(fd == -1)
    {
        printf("error Opening %s\n", pDevice);
        return -1;
    }

    ::i32 l, m, r;
    ::i8 x, y;
    ::i32 last_l=0, last_m=0, last_r=0;
    while(1)
    {
        // Read Mouse
        bytes = read(fd, data, sizeof(data));

        if(bytes > 0)
        {
            l = data[0] & 0x1;
            r = data[0] & 0x2;
            m = data[0] & 0x4;

            if(last_l != l)
            {
               last_l = l;
               if(l)
               {
                  printf("-LD");
               }
               else
               {
                  printf("-LU");
               }
            }
            if(last_m != m)
            {
               last_m = m;
               if(m)
               {
                  printf("-MD");
               }
               else
               {
                  printf("-MU");
               }
            }

            if(last_r != r)
            {
               last_r = r;
               if(r)
               {
                  printf("-RD");
               }
               else
               {
                  printf("-RU");
               }
            }

            x = data[1];
            y = data[2];
//            printf("x=%d, y=%d, left=%d, middle=%d, right=%d\n", x, y, left, middle, right);
        }
    }

   }
