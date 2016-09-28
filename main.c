#include <stdio.h>
#include <stdlib.h>
#include "inc/interface.h"

int main(int argc, char *argv[])
{
    LIST *l = NULL;
    l = get_from_file("googlebot.txt");
    menu(l);
    erase_list(l);
    return 0;
}
