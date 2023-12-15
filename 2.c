#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *file;
	char ch;

	if (argc != 2) {
		fprintf(stderr, argv[0]);
		exit(EXIT_FAILURE);
	}
	
	if ((file = fopen(argv[1], "w")) == NULL) {
		perror("Error open file");
		exit(EXIT_FAILURE);
	}

	printf("\nEnter text. For exit use ctrl-F\n");
	
	while ((ch = getc(stdin)) != EOF) {
		if (ch == 6) {
			break;
		}
		if (putc(ch, file) == EOF) {
			perror("FIle record error");
			fclose(file);
			exit(EXIT_FAILURE);
		}		
	}
	
	if (fclose(file) != 0) {
		perror("FIle closing error");
		exit(EXIT_FAILURE);
	}
	
	printf("Data is record", argv[1]);
	return 0;	
}

