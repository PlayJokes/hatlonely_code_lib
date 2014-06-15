PROJECT(SOCKET_SAMPLE)
SET(SRC_LIST server.c client.c)
ADD_EXECUTABLE(server server.c)
ADD_EXECUTABLE(client client.c)
