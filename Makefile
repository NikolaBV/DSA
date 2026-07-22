CC     := gcc
CFLAGS := -std=c11 -Wall -Wextra -Werror -g
BUILD  := build
EXTRA  :=

LIB  := $(BUILD)/libdsa.a
SRCS := dynamic-array/src/dynamic_array.c \
        singly-linked-list/src/singly-linked-list.c \
        doubly-linked-list/src/doubly-linked-list.c
OBJS := $(patsubst %.c,$(BUILD)/%.o,$(SRCS))

TEST_SRCS := $(wildcard tests/test_*.c)
TEST_BINS := $(patsubst tests/%.c,$(BUILD)/%,$(TEST_SRCS))

.PHONY: all test asan valgrind demos link-check clean

all: $(LIB)

$(LIB): $(OBJS)
	@mkdir -p $(@D)
	ar rcs $@ $^

$(BUILD)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(EXTRA) -c $< -o $@

# Tests compile the sources directly rather than linking the archive, so that
# `make asan` instruments the data structures and not just the test file.
$(BUILD)/test_%: tests/test_%.c $(SRCS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(EXTRA) $^ -o $@

test: $(TEST_BINS)
	@for t in $(TEST_BINS); do ./$$t || exit 1; done

asan:
	@$(MAKE) --no-print-directory test \
		BUILD=$(BUILD)/asan \
		EXTRA="-fsanitize=address,undefined -fno-omit-frame-pointer"

valgrind: $(TEST_BINS)
	@for t in $(TEST_BINS); do \
		echo "== valgrind $$t"; \
		valgrind -q --leak-check=full --error-exitcode=1 ./$$t || exit 1; \
	done

# Links every structure into one binary. This only succeeds because the
# symbols are prefixed -- before that, all three defined InsertAtTail,
# InsertAtHead, UpdateAtIndex, find and struct Node at global scope.
link-check: $(BUILD)/link_check
	@./$(BUILD)/link_check

$(BUILD)/link_check: tests/link_check.c $(SRCS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(EXTRA) $^ -o $@

demos: $(BUILD)/demo-da $(BUILD)/demo-sll $(BUILD)/demo-dll

$(BUILD)/demo-da: dynamic-array/main.c dynamic-array/src/dynamic_array.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD)/demo-sll: singly-linked-list/main.c singly-linked-list/src/singly-linked-list.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD)/demo-dll: doubly-linked-list/main.c doubly-linked-list/src/doubly-linked-list.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD)
