// Using C headers of unix
// I dont know if it works on windows

#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>

int
printIfaces(int argc, char *argv[])
{
    struct ifaddrs *ifaddr, *ifa;

    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL)
            continue;

        printf("%s\n", ifa->ifa_name);

    }

    freeifaddrs(ifaddr);
    exit(EXIT_SUCCESS);
}
