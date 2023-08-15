#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "wordcount.h"

int main(int argc, char **argv) {
	FILE *file;
	char **dictfile;
	int current_dictfile_size = 0;
	char buffer[MAX_LINE_LENGTH];
	char word[MAX_WORD_LENGTH];
	int *count;
	int line_number = 1, total = 0, ix = 0, word_index = 0, ch, len;
	bool in_word = false;

	if (argc < 2) {
		printf("Enter dictfile name\n");
		exit(EXIT_FAILURE);
	}

	/* Check dictfile is valid : exit otherwise */
	file = fopen(argv[1], "r");
	if (file == NULL) {
		printf("Error opening file\n");
		exit(EXIT_FAILURE);
	}

	while (fgets(buffer, sizeof(buffer), file)) {
		if ((strcmp(buffer, "\n") == 0) || starts_with_hash(buffer) || is_line_only_spaces(buffer)) {
			printf("Ignore line found at line %d\n", line_number);
		} else if (is_multi_word(buffer)) {
			printf("FAIL: Multi words at line %d\n", line_number);
			exit(EXIT_FAILURE);
		} else if (word_is_already_in(buffer, &dictfile, &current_dictfile_size)) {
			printf("Fail: Word already exists : %d\n", line_number);
			exit(EXIT_FAILURE);
		} else {
			add_word(&dictfile, &current_dictfile_size, MAX_WORD_LENGTH, buffer);
		}
		line_number++;
	}

	fclose(file);

	/* allocate memory for counting occurrences */
	count = (int *) malloc(current_dictfile_size * sizeof(int));
	if (count == NULL) {
		fprintf(stderr, "Memory allocation failed for count pointers.\n");
		exit(EXIT_FAILURE);
	}

	/* Set initial words occurrence to 0 */
	memset(count, 0, sizeof(int)*current_dictfile_size);

	if(argc > 2)
	{
		/* Count the occurences */
		for (int it = 2; it < argc; it++) {
			file = fopen(argv[it], "r");

			if (file == NULL) {
				printf("Error opening file\n");
				exit(EXIT_FAILURE);
			}

			line_number = 1;
			word_index = 0;
			in_word = false;

			while ((ch = fgetc(file)) != EOF) {
				if (in_word) {
					if (is_whitespace(ch)) {
						word[word_index] = '\0';
						ix = word_in_dictfile(word, &dictfile, &current_dictfile_size);
						if (ix)
							count[ix - 1]++;
						word_index = 0;
						in_word = false;
					} else if (word_index < MAX_WORD_LENGTH - 1) {
						word[word_index++] = ch;
					}
				} else {
					if (!is_whitespace(ch)) {
						in_word = true;
						word[word_index++] = ch;
					}
				}
			}

			fclose(file);
		}
	} else
	{
		while (fgets(word, sizeof(word), stdin) != NULL) {
			if (!strcmp(word,"END\n")) /* QUIT USING END KEY */
				break;
			len = strlen(word);
			word[len-1] ='\0';
			ix = word_in_dictfile(word, &dictfile, &current_dictfile_size);
			if (ix)
				count[ix - 1]++;
		}
	}

	/* Print results */
	for (ix = 0; ix < current_dictfile_size; ix++) {
		if (count[ix])
		{
			printf("%d\t%s\n", count[ix], dictfile[ix]);
			total += count[ix];
		}
	}

	printf("%d\ttotal words\n", total);

	for (ix = 0; ix < current_dictfile_size; ix++) {
		free(dictfile[ix]);
	}
	free(dictfile);
	free(count);

	return 0;
}
