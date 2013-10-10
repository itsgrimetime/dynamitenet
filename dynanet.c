#include <enet/enet.h>
#include <stdio.h>
#include "objects.h"

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
    int eventStatus;

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

    eventStatus = 1;

    ENetEvent event;

    while (1) {
	eventStatus = enet_host_service(server, &event, 50000);

	// If we had some event that interested us
	if (eventStatus > 0) {
	    switch(event.type) {
		case ENET_EVENT_TYPE_CONNECT:
		    printf("(Server) We got a new connection from %x\n",
			    event.peer->address.host);
		    break;

		case ENET_EVENT_TYPE_RECEIVE:
		    printf("(Server) Message from client : %s\n", event.packet->data);
		    // Lets broadcast this message to all
		    enet_host_broadcast(server, 0, event.packet);
		    break;

		case ENET_EVENT_TYPE_DISCONNECT:
		    printf("%s disconnected.\n", event.peer->data);

		    // Reset client's information
		    event.peer->data = NULL;
		    break;
		case ENET_EVENT_TYPE_NONE:
		    printf("No event.\n");
		    break;

	    }
	}
    }

    enet_host_destroy(server);
    return 0;
}
