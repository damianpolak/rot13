/* Mezc4L @ 2013
 * Usage: rot13.exe INPUT_FILE OUTPUT_FILE
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *fsource;
FILE *fdestin;

long fSize;
char *buffer;

char *RotEncode(char *PlainText);
char *RotDecode(char *RotText);

int main(int argc, char **argv)
{
	char text[1024];
	memset(text, 0, 1024);
	
	if(argc > 1)
	{
		if(argv[1])
		{
			if(argv[2])
			{
				fsource = fopen(argv[1], "rb");

					if(fsource == NULL) 
					{ 
						fputs("File error", stderr); 
						exit(1); 
					}

					fseek(fsource, 0, SEEK_END);
					fSize = ftell (fsource);
					rewind(fsource);

					buffer = (char*) malloc (sizeof(char)*fSize + 1);
					memset(buffer, 0, (sizeof(char)*fSize + 1));

					if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

					size_t result = fread(buffer, 1, fSize, fsource);
					if (result != fSize) {fputs ("Reading error",stderr); exit (3);}

				fclose(fsource);

				fdestin = fopen(argv[2], "w");
					fprintf(fdestin, "%s", RotEncode(buffer));
				fclose(fdestin);

				free(buffer);

			}
		}
	} else {
		printf("USAGE: rot13.exe [INPUT_FILE] [OUTPUT_FILE]")
	}

	return 0;
}

char *RotDecode(char *RotText)
{
	return RotEncode(RotText);
}

char *RotEncode(char *PlainText)
{
	int move = 13;
	int len = strlen(PlainText);

	char *rot13 = new char [len+1];
	memset(rot13, 0, len+1);

	for(int i = 0; i <= len - 1; i++)
	{
		
		if(((int)PlainText[i] >= 65) && ((int)PlainText[i] <= 90))
		{
			if(((int)PlainText[i] + move) <= 90)
			{
				rot13[i] = (char)((int)PlainText[i] + move);
			}
			else 
			{
				rot13[i] = (char)(65 + (move - (90 - (int)PlainText[i]) - 1));
			}

		} 
		
		else if(((int)PlainText[i] >= 97) && ((int)PlainText[i] <= 122))
		{
			if(((int)PlainText[i] + move) <= 122)
			{
				rot13[i] = (char)((int)PlainText[i] + move);
			}
			else
			{
				rot13[i] = (char)(97 + (move - (122 - (int)PlainText[i]) - 1));
			}

		} else 
		{
			rot13[i] = PlainText[i];
		}
			
	}

	return rot13;
}