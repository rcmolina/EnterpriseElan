#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//unsigned int * getIntFromHexString(const char *s)
void getIntFromHexString(const char *s, unsigned int * out )
{
	int len = strlen(s)/2;
	unsigned int c, result; 
	//unsigned int *out = malloc(len);
	
	int pos, count;
	pos = count = 0;
	c = result = 0;
	//printf("len=%d\n",len);
	while (*s)
	{

		result = result << 4;
		if (c = (*s - '0'), (c >= 0 && c <= 9)) result |= c;
		else if (c = (*s - 'A'), (c >= 0 && c <= 5)) result |= (c + 10);
		else if (c = (*s - 'a'), (c >= 0 && c <= 5)) result |= (c + 10);
		else break;

		++s;
		count++;

		if (count > 1)
		{
			out[pos] = result;
			count = 0;
			result = 0;
			pos++;
		}


	}
	//printf("out=%x %x %x %x %x %x %x %x %x %x %x \n",out[0], out[1], out[2], out[3], out[4], out[5], out[6], out[7], out[8], out[9], out[10]);
	//system("pause");
	//return out;

}


int main(int argc, char **argv)
{
	// if we have all necessary args
	if (argc >= 4)
	{
		// open input and check pointer
		FILE *fpi = fopen(argv[1], "rb");
		if (!fpi)
		{
			fprintf(stderr, "Can't open input!");
			exit(1);
		}
		// open output and check pointer
		FILE *fpo = fopen(argv[4], "wb");
		if (!fpo)
		{
			fprintf(stderr, "Can't open output!");
			exit(1);
		}

		// init vars

		int skip, count, flen, rlen, reps, target, pos;
		count = reps = pos = target = skip = 0;		
		flen = strlen(argv[2]);
		rlen = strlen(argv[3]);
		//unsigned int *find,*replace;
		//unsigned int *find=malloc(flen/2);
		unsigned int find[flen/2]; 
		//unsigned int *replace=malloc(rlen/2);	  	  
		unsigned int replace[rlen/2];	

		// check our input is in pairs
		if (flen%2 > 0 || rlen%2 > 0 )
		{
			fprintf(stderr, "Invalid find/replace input.\nPlease use unprefixed pairs of characters from 0-F, eg. FF0E.\n");
			exit(1);
		}
		flen/=2;
		rlen/=2;

		// check for optional args
		if (argc > 5)
		{
			int i;
			for (i = 5; i<argc; i++)
			{
				if (*argv[i] == 's' || *argv[i] == 'S')
				{
					++argv[i];
					while (*argv[i])
					{
						skip *= 10;
						skip = skip + *argv[i]-48;
						++argv[i];
					}
					printf("skipping %d bytes\n", skip);
				} else if (*argv[i] == 'r' || *argv[i] == 'R')
				{
					++argv[i];
					while (*argv[i])
					{
						target *= 10;
						target = target + *argv[i]-48;
						++argv[i];
					}
					printf("targeting %d replacements\n", target);
				} else
				{
					printf("argument %s unknown, ignoring\n", argv[i]);
				}
			}
		}
		else skip = 0;

		// convert our hex strings to uints
		//find = getIntFromHexString(argv[2]); 	  	  	    //"11CA02A604A604DC01B803"
		getIntFromHexString(argv[2], find);  	 	 	 
		//printf("find=%d %d %d %d %d %d %d %d %d %d %d\n", find[0], find[1], find[2], find[3], find[4], find[5], find[6], find[7], find[8], find[9], find[10]);	
		
		//printf("find=%d %d %d %d %d\n", *find, *(find+1), *(find+2), *(find+3), *(find+4));
		//replace = getIntFromHexString(argv[3]);   	   	//"11E602C204C2045A027203" 
	    	
		getIntFromHexString(argv[3], replace);
		//printf("replace=%d %d %d %d %d %d %d %d %d %d %d\n", replace[0], replace[1], replace[2], replace[3], replace[4], replace[5], replace[6], replace[7], replace[8], replace[9], replace[10]);	  
		
		int ch;
		// do find/replace
		while (1)
		{
			//printf("fase0\n");
			ch = fgetc(fpi);
			//printf("fase1\n");
			if (feof(fpi))	break;

			if (skip > 0 && count < skip+1) {
				fputc(ch, fpo);
				count++;
			}
			else if (ch == find[pos] && target == 0 || ch == find[pos] && reps < target)
			{
				pos++;
				// if full sequence found, replace
				if (pos == flen)
				{
					int i;
					for (i = 0; i<rlen; i++)
					{
						fputc(replace[i], fpo);
					}
					pos = 0;
					reps++;
				}
			}
			else if (pos != 0)
			{
				// if partial sequence found, replace missing bytes and continue
				int i;
				for (i = 0; i<pos; i++)
				{
					fputc(find[i], fpo);
				}
				pos = 0;

				fputc(ch, fpo);
			}
			else fputc(ch, fpo);

			//printf("%d",ch);
		}
		// we're done, close up shop
		free(find);
		free(replace);
		fclose(fpi);
		fclose(fpo);
		printf("success, made %d replacements\n", reps);
		exit(0);
	}
	else
	{
		fprintf(stdout, "hexec by atagen 2017\narguments are: input find replace output\neg. hexec infile a0ef ffed outfile\noptional args are: s[number of bytes to skip at start] r[max number of times to replace]\n");
		exit(0);
	}
}

