#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "wordcount.h"

/**
 * @is_multi_word check if the line has more than one word.
 *
 * @line pointer to the line.
 * @return 0 if only one word 1 otherwise.
 */
int is_multi_word(char *line) {
	int word_count = 0;
	const char *delimiters = " \t\n";
	char *token;
	char *tmp = strdup(line);

	if (starts_with_hash(line))
		return 0;

	token = strtok(tmp, delimiters);
	while (token != NULL) {
		word_count++;
		token = strtok(NULL, delimiters);
	}

	free(tmp);
	return (word_count > 1);
}

/**
 * @is_line_only_spaces check if line only contains spaces/tabs.
 *
 * @line pointer to the line..
 * @return false if the line contains a word true otherwise.
 */
bool is_line_only_spaces(const char *line) {
	while (*line) {
		if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r')
			return false;
		line++;
	}
	return true;
}

/**
 * @is_whitespace check if the character is a space/\n/\r or tab.
 *
 * @ch character.
 * @return false non of the above true otherwise.
 */
bool is_whitespace(char ch) {
	return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

/**
 * @starts_with_hash check if line starts with hash.
 *
 * @line pointer to the line.
 * @return 1 if the line starts with a hash 0 otherwise.
 */
int starts_with_hash(char *line) {
	const char *delimiters = " \t\n";
	char *token;
	int ret;
	char *tmp = strdup(line);

	if (!tmp)
	{
		printf("Failed to allocate memory\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(tmp, delimiters);
	ret = (token[0] == '#');

	free(tmp);
	return ret;
}

/**
 * @word_is_already_in check if word is already in the word list.
 *
 * @buffer pointer to the word.
 * @word_list pointer to the word list.
 * @currentSize pointer to the actual length of word list.
 *
 * @return the index of the first occurrence of the word plus one 0 otherwise.
 */
int word_is_already_in(char *buffer, char ***word_list, int *currentSize) {
	for (int i = 0; i < *currentSize; i++) {
		if (strcmp(buffer, (*word_list)[i]) == 0)
			return i + 1;
	}
	return 0;
}

/**
 * @word_in_dictfile check if word is already in the dictfile.
 *
 * @buffer pointer to the word.
 * @word_list pointer to the dictfile.
 * @currentSize pointer to the actual length of word list.
 *
 * @return the index of the first occurrence of the word plus one 0 otherwise.
 */
int word_in_dictfile(char *buffer, char ***word_list, int *currentSize) {
	for (int i = 0; i < *currentSize; i++) {
		if (strcmp(buffer, (*word_list)[i]) == 0)
			return i + 1;
	}
	return 0;
}


/**
 * @allocate_mem allocate memory for the word list and the first word.
 *
 * @maxStringLength max length of a word.
 * @word_list pointer to the word list.
 * @currentSize pointer to the actual length of word list.
 *
 */
void allocate_mem(int maxStringLength, char ***word_list, int *currentSize) {
	*word_list = (char **)malloc(1 * sizeof(char *));
	if (*word_list == NULL) {
		printf("Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}

	*currentSize = 1;

	(*word_list)[0] = (char *)malloc(maxStringLength * sizeof(char));
	if ((*word_list)[0] == NULL) {
		printf("Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * @add_word allocate memory for the word to add and add it to word_list.
 *
 * @maxStringLength max length of a word.
 * @word_list pointer to the word list.
 * @currentSize pointer to the actual length of word list.
 * @newString pointer to the new word to add.
 *
 */
void add_word(char ***word_list, int *currentSize, int maxStringLength, char *newString) {
	const char *delimiters = " \t\n";
	char *tmp;
	char *token;

	if (*currentSize == 0) {
		allocate_mem(maxStringLength, word_list, currentSize);
	} else if (*currentSize > 0) {
		/* Reallocate memory for more strings when needed */
		*word_list = (char **)realloc(*word_list, (*currentSize + 1) * sizeof(char *));
		if (*word_list == NULL) {
			printf("Memory reallocation failed for string pointers.\n");
			exit(EXIT_FAILURE);
		}

		(*word_list)[*currentSize] = (char *)malloc(maxStringLength * sizeof(char));
		if ((*word_list)[*currentSize] == NULL) {
			printf("Memory allocation failed for string \n");
			exit(EXIT_FAILURE);
		}
		*currentSize += 1;
	}

	tmp = strdup(newString);
	if (!tmp)
	{
		printf("Failed to allocate memory\n");
		exit(EXIT_FAILURE);
	}

        token = strtok(tmp, delimiters);

	/* Copy the new string into the allocated memory */
	strncpy((*word_list)[*currentSize - 1], token, maxStringLength - 1);
	(*word_list)[*currentSize - 1][maxStringLength - 1] = '\0';
	free(tmp);
}
