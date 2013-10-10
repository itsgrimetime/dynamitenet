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

    ENetEvent event;

    while (enet_host_service(server, &event, 30000) > 0) {
	switch (event.type) {
	    case ENET_EVENT_TYPE_CONNECT:
		printf("A new client connected from %x:%u.\n",
			event.peer->address.host,
			event.peer->address.port);

		/* Store any relevant client info here */
		event.peer->data = "Client information";
		break;
	    case ENET_EVENT_TYPE_RECEIVE:
		printf("Packet received containing %s from %s on channel %u.\n",
			event.packet->data,
			event.peer->data,
			event.channelID);
		enet_packet_destroy(event.packet);
		break;
	    case ENET_EVENT_TYPE_DISCONNECT:
		printf("%s disconnected.\n", event.peer->data);
		event.peer->data = NULL;
		break;
	    case ENET_EVENT_TYPE_NONE:
		printf("no event.\n");
		// no event occured?
		break;
	}
    }

    enet_host_destroy(server);
    return 0;
}
