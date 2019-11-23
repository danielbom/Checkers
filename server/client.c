#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <pthread.h>

#include "utils.server.c"

// Sets
void setUsernameOnPacket(char* packet, char* user) {
  strncat(packet + (sizeof(int) * 3), user, 63);
}
void setPasswordOnPacket(char* packet, char* pass) {
  strncat(packet + (sizeof(int) * 3) + 64, pass, 63);
}
void setNameRoomOnPacket(char* packet, char* room) {
  strncat(packet + (sizeof(int) * 3) + (64 * 2), room, 63);
}

// Create
char* createPacketToListRoomsByClient(int* shift) {
  char *buffer = ByteBufferAllocate(16);
  setOperationOnPacket(buffer, OP_LIST);
  setTypeOnPacket(buffer, TYPE_CLIENT);
  setIDProtocolPacket(buffer);
  *shift = sizeof(int) * 4;
  return buffer;
}
char* createPacketToConnectByClient(char* username, char* password, char* roomName, int* shift) {
  char *buffer = ByteBufferAllocate(256);
  setOperationOnPacket(buffer, OP_CONNECT);
  setTypeOnPacket(buffer, TYPE_CLIENT);
  setIDProtocolPacket(buffer);
  *shift = sizeof(int) * 4;

  int error = 0;
  error = isNull(roomName) ? 3 : error;
  error = isNull(password) ? 2 : error;
  error = isNull(username) ? 1 : error;
  setErrorOnPacket(buffer, error);
  if (error) return buffer;

  ByteBufferPutString(buffer, shift, username, 64);
  ByteBufferPutString(buffer, shift, password, 64);
  ByteBufferPutString(buffer, shift, roomName, 64);
  return buffer;
}
char* createPacketToCreateRoomByClient(char* username, char* password, char* roomName, int numberOfUsers, int* shift) {
  char *buffer = ByteBufferAllocate(256);
  setOperationOnPacket(buffer, OP_CREATE_ROOM);
  setTypeOnPacket(buffer, TYPE_CLIENT);
  setIDProtocolPacket(buffer);
  *shift = sizeof(int) * 4;

  int error = 0;
  error = isNull(roomName) ? 3 : error;
  error = isNull(password) ? 2 : error;
  error = isNull(username) ? 1 : error;
  setErrorOnPacket(buffer, error);
  if (error) return buffer;

  ByteBufferPutString(buffer, shift, username, 64);
  ByteBufferPutString(buffer, shift, password, 64);
  ByteBufferPutString(buffer, shift, roomName, 64);
  ByteBufferPutInt(buffer, shift, numberOfUsers);
  return buffer;
}
void *createPacketToSendMessageByClient(char* username, char* roomName, char* message, int* shift) {
  char *buffer = ByteBufferAllocate(512);
  setOperationOnPacket(buffer, OP_SEND_MESSAGE);
  setTypeOnPacket(buffer, TYPE_CLIENT);
  setIDProtocolPacket(buffer);
  *shift = sizeof(int) * 4;

  int error = 0;
  error = isNull(message) ? 4 : error;
  error = isNull(roomName) ? 3 : error;
  error = isNull(username) ? 1 : error;
  setErrorOnPacket(buffer, error);
  if (error) return buffer;

  ByteBufferPutString(buffer, shift, username, 64);
  ByteBufferPutString(buffer, shift, roomName, 64);
  ByteBufferPutString(buffer, shift, message, 256);
  return buffer;
}
void *createPacketToExitByClient(char *username, char *password, int* shift) {
  char *buffer = ByteBufferAllocate(256);
  setOperationOnPacket(buffer, OP_EXIT);
  setTypeOnPacket(buffer, TYPE_CLIENT);
  setIDProtocolPacket(buffer);
  *shift = sizeof(int) * 4;

  int error = 0;
  error = isNull(password) ? 2 : error;
  error = isNull(username) ? 1 : error;
  setErrorOnPacket(buffer, error);
  if (error) return buffer;

  ByteBufferPutString(buffer, shift, username, 64);
  ByteBufferPutString(buffer, shift, password, 64);
  return buffer;
}

// Read
void readPacketToListRoomsByClient(char* packet) {
  int shift = 0;
  int error = ByteBufferGetInt(packet, &shift);
  int type = ByteBufferGetInt(packet, &shift);
  int op = ByteBufferGetInt(packet, &shift);
  int IDprotocol = ByteBufferGetInt(packet, &shift);
  printf("Error: '%d', Type: '%d', Operation: '%d', Protocol: '%d'", error, type, op, IDprotocol);
  printf("\n");
}
void readPacketToConnectByClient(char* packet) {
  int shift = 0;
  int error = ByteBufferGetInt(packet, &shift);
  int type = ByteBufferGetInt(packet, &shift);
  int op = ByteBufferGetInt(packet, &shift);
  int IDprotocol = ByteBufferGetInt(packet, &shift);
  char* username = ByteBufferGetString(packet, &shift);
  char* password = ByteBufferGetString(packet, &shift);
  char* roomName = ByteBufferGetString(packet, &shift);
  printf("Error: '%d', Type: '%d', Operation: '%d', Protocol: '%d'", error, type, op, IDprotocol);
  printf(", Username: '%s', Password: '%s', Room name: '%s'\n", username, password, roomName);
}
void readPacketToCreateRoomByClient(char* packet) {
  int shift = 0;
  int error = ByteBufferGetInt(packet, &shift);
  int type = ByteBufferGetInt(packet, &shift);
  int op = ByteBufferGetInt(packet, &shift);
  int IDprotocol = ByteBufferGetInt(packet, &shift);
  char* username = ByteBufferGetString(packet, &shift);
  char* password = ByteBufferGetString(packet, &shift);
  char* roomName = ByteBufferGetString(packet, &shift);
  int numberOfUsers = ByteBufferGetInt(packet, &shift);
  printf("Error: '%d', Type: '%d', Operation: '%d', Protocol: '%d'", error, type, op, IDprotocol);
  printf(", Username: '%s', Password: '%s', Room name: '%s', Number of users: '%d'\n", username, password, roomName, numberOfUsers);
}
void readPacketToSendMessageByClient(char* packet) {
  int shift = 0;
  int error = ByteBufferGetInt(packet, &shift);
  int type = ByteBufferGetInt(packet, &shift);
  int op = ByteBufferGetInt(packet, &shift);
  int IDprotocol = ByteBufferGetInt(packet, &shift);
  char* username = ByteBufferGetString(packet, &shift);
  char* roomName = ByteBufferGetString(packet, &shift);
  char* message = ByteBufferGetString(packet, &shift);
  printf("Error: '%d', Type: '%d', Operation: '%d', Protocol: '%d'", error, type, op, IDprotocol);
  printf(", Username: '%s', RoomName: '%s', Message: '%s'\n", username, roomName, message);
}
void readPacketToExitByClient(char* packet) {
  int shift = 0;
  int error = ByteBufferGetInt(packet, &shift);
  int type = ByteBufferGetInt(packet, &shift);
  int op = ByteBufferGetInt(packet, &shift);
  int IDprotocol = ByteBufferGetInt(packet, &shift);
  char* username = ByteBufferGetString(packet, &shift);
  char* password = ByteBufferGetString(packet, &shift);
  printf("Error: '%d', Type: '%d', Operation: '%d', Protocol: '%d'", error, type, op, IDprotocol);
  printf(", Username: '%s', Password: '%s'\n", username, password);
}

// Structure
#define BUFFER_CLIENT_SIZE 512

int socketPort = 12345;
int socketClient;
int runningClient = 1;

void *sender(void *arg) {
  char buffer[BUFFER_CLIENT_SIZE + 1] = {0};
  int size;
  while (runningClient) {
    setbuf(stdin , NULL);
    scanf("%[^\n]", buffer);
    char* packet = createPacketToSendMessageByClient("Daniel", "room", buffer, &size);
    send(socketClient, packet, size, 0);
    free(packet);
    printf("Send: %s\n", buffer);
    buffer[0] = 0;
  }
}
void senderRunner(pthread_t* thread) {
  pthread_create(thread, NULL, sender, NULL);
}
void *receiver(void *callback) {
  char buffer[BUFFER_CLIENT_SIZE + 1] = {0};
  while (runningClient) {
    int numberOfBytes = read(socketClient, buffer, BUFFER_CLIENT_SIZE);
    if (numberOfBytes == 0) {
      printf("Server disconnected\n");
      runningClient = 0;
    } else {
      buffer[numberOfBytes] = 0;
      printf("Received: '%s'\n", buffer);
    }
  }
}
void receiverRunner(pthread_t* thread, void (*callback)(void*)) {
  pthread_create(thread, NULL, receiver, callback);
}
void initClientSocket() {
  int error;

  socketClient = socket(AF_INET, SOCK_STREAM, 0);
  rejectCriticalError("(socket) Failed to create client socket", socketClient == -1);

  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(socketPort);
  error = inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
  rejectCriticalError("(inet_pton) Invalid address", error == -1);

  error = connect(socketClient, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
  rejectCriticalError("(connect) Failed to connect with the server", error == -1);
}
