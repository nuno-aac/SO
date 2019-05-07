#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

ssize_t getOp(int fildes, char *buf){
    ssize_t n;
    int i;
    char byte;

    i = 0;

    while((n=read(fildes, &byte, 1)) > 0){
        buf[i] = byte;
        i++;
        if(byte == '\n') break;
    }

    buf[i-1] = '\0';

    return i;
}

int main(int argc, char* argv[]) {
	char buf[128], op, *currentTok;
    int numread, codigo;

    numread = getOp(0, buf);

	int server = open("pip", O_WRONLY);
	if (server < 0) {
		printf("Server offline\n");
		return 1;
	}
	while (numread > 1)
		currentTok = strtok(buf, " ");
        op = currentTok[0];

        switch (op) {
            case 'a':
                currentTok = strtok(NULL, " ");
                stdizeName(stdName, currentTok);

                currentTok = strtok(NULL, " ");
                preco = atoi(currentTok);
                a = newArtigo(sizeof(stdName),preco);
                saveArtigo(a, stdName);
                break;
            case default:
                printf("[DEBUG] Introduza uma operação válida\n");
                break;


		write(server, argv[i], strlen(argv[i]));

		numread = getOp(0, buf);
	close(server);
	return 0;
}