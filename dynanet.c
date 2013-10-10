#include <enet/enet.h>
#include <stdio.h>

#define SERVER_PORT 3333
#define MAX_CONN    32


int main(int argc, char **argv) {

    if (enet_initialize() != 0) {
	fprintf(stderr, "An error occurred while initializing ENet.\n");
	return EXIT_FAILURE;
    } else {
	fprintf(stdout, "ENet initialized correctly.\n");
    }
    atexit(enet_deinitialize);

    ENetAddress address;
    ENetHost *server;

    /* Bind the server to the default localhost.    */
    /* A specific host address can be specified by  */
    /* enet_address_set_host(&address, "x.x.x.x");  */

    address.host = ENET_HOST_ANY;

    address.port = SERVER_PORT;

    server = enet_host_create(&address, MAX_CONN, 2, 0, 0);

    if (server == NULL) {
	fprintf(stderr, "An error occured while try to create an ENet server host.\n");
	exit(EXIT_FAILURE);
    } else {
	fprintf(stdout, "ENet server created successfully.\n");
    }


    enet_host_destroy(server);
    return 0;
}
