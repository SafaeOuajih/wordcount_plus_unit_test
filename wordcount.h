#define MAX_LINE_LENGTH 1024
#define MAX_WORD_LENGTH 50

int starts_with_hash(char *line);
int is_multi_word(char *line);
bool is_line_only_spaces(const char *line);
bool is_whitespace(char ch);
int starts_with_hash(char *line);
int word_is_already_in(char *buffer, char ***word_list, int *currentSize);
int word_in_dictfile(char *buffer, char ***word_list, int *currentSize);
void allocate_mem(int maxStringLength, char ***word_list, int *currentSize);
void add_word(char ***word_list, int *currentSize, int maxStringLength, char *newString);
