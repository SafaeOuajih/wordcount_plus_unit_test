CC := gcc
CFLAGS := -Wall -Wextra
OUTPUT_DIR := output

# List of services
SERVICES := wordcount
SRC := operations.c test/Unity/src/unity.c test/test.c

all:$(OUTPUT_DIR) $(SERVICES) TEST

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

$(SERVICES):
	$(CC) $(CFLAGS) -o $(OUTPUT_DIR)/$@ operations.c $@.c

TEST:
	$(CC) $(CFLAGS) ${SRC} -o $(OUTPUT_DIR)/test


clean:
	rm -rf $(OUTPUT_DIR)
