CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -fPIC -I$(INCLUDE_DIR)
LDFLAGS = -shared
TEST_CFLAGS = -g -I$(INCLUDE_DIR)
DEBUG_FLAGS = -g
LIBS = -lm

SRC_DIR = ./src
INCLUDE_DIR = ./include
TEST_DIR = ./test
BUILD_DIR = ./bin
DEBUG_LIB_DIR = $(BUILD_DIR)/debug/sharedlibs

PROJECTS = $(basename $(notdir $(wildcard $(SRC_DIR)/*.c)))

knightstour_deps = bit_array
dhcp_deps = trie
pq_heap_deps =heap dvector
scheduler_heap_deps = task pq_heap uid
heap_deps = dvector
scheduler_deps = task pq uid
pq_deps = sortedlist
task_deps = uid
sortedlist_deps = dllist
queue_deps = sllist
calculator_deps = stack
hashtable_deps = dllist

spell_checker_test_deps = hashtable

all: release debug test

release: $(foreach proj,$(PROJECTS),release_$(proj))
debug: $(foreach proj,$(PROJECTS),debug_$(proj))
test: $(foreach proj,$(PROJECTS),test_$(proj))

clean:
	@echo "Cleaning up..."
	@find $(BUILD_DIR)/release -type f -exec rm -f {} +
	@find $(BUILD_DIR)/debug -type f -exec rm -f {} +
	@find $(DEBUG_LIB_DIR) -type f -exec rm -f {} +
edit:
	gedit $(SRC_DIR)/$(FN).c $(TEST_DIR)/$(FN)_test.c $(INCLUDE_DIR)/$(FN).h &

define make_release
release_$(1): $(BUILD_DIR)/release/lib$(1).so
$(BUILD_DIR)/release/lib$(1).so: $(SRC_DIR)/$(1).c $(foreach dep,$($(1)_deps),$(BUILD_DIR)/release/lib$(dep).so)
	@echo "Building release version of $(1)..."
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(BUILD_DIR)/release/lib$(1).so $(SRC_DIR)/$(1).c $(foreach dep,$($(1)_deps),-L$(BUILD_DIR)/release -l$(dep)) $(LIBS)
endef

define make_debug
debug_$(1): $(DEBUG_LIB_DIR)/lib$(1).so
$(DEBUG_LIB_DIR)/lib$(1).so: $(SRC_DIR)/$(1).c $(foreach dep,$($(1)_deps),$(DEBUG_LIB_DIR)/lib$(dep).so)
	@echo "Building debug version of $(1)..."
	@$(CC) $(CFLAGS) $(LDFLAGS) $(DEBUG_FLAGS) -o $(DEBUG_LIB_DIR)/lib$(1).so $(SRC_DIR)/$(1).c $(foreach dep,$($(1)_deps),-L$(DEBUG_LIB_DIR) -l$(dep)) $(LIBS)
endef

define make_test
test_$(1): $(BUILD_DIR)/debug/$(1)_test
$(BUILD_DIR)/debug/$(1)_test: $(TEST_DIR)/$(1)_test.c $(foreach dep,$($(1)_deps),$(DEBUG_LIB_DIR)/lib$(dep).so)
	@echo "Building test executable for $(1)..."
	@$(CC) $(TEST_CFLAGS) -o $(BUILD_DIR)/debug/$(1)_test $(TEST_DIR)/$(1)_test.c -L$(DEBUG_LIB_DIR) -l$(1) $(foreach dep,$($(1)_deps),-L$(DEBUG_LIB_DIR) -l$(dep)) -Wl,-rpath,$(DEBUG_LIB_DIR) $(LIBS)
endef

define run_test
run_$(1):
	@echo "\n********************Running $(1) test********************\n"
	@LD_LIBRARY_PATH=$(DEBUG_LIB_DIR) $(BUILD_DIR)/debug/$(1)_test
endef

define vlg_test
vlg_$(1):
	@echo "Running $(1) test with Valgrind..."
	@LD_LIBRARY_PATH=$(DEBUG_LIB_DIR) valgrind --leak-check=yes --track-origins=yes $(BUILD_DIR)/debug/$(1)_test
endef

define gdb_test
gdb_$(1):
	@echo "Running $(1) test with GDB..."
	@LD_LIBRARY_PATH=$(DEBUG_LIB_DIR) gdb $(BUILD_DIR)/debug/$(1)_test
endef

run_all_tests: $(foreach proj,$(PROJECTS),run_$(proj))
	@echo "\n****************************************\n"
	@echo "All tests have been run."

$(foreach proj,$(PROJECTS),$(eval $(call make_release,$(proj))))
$(foreach proj,$(PROJECTS),$(eval $(call make_debug,$(proj))))
$(foreach proj,$(PROJECTS),$(eval $(call make_test,$(proj))))
$(foreach proj,$(PROJECTS),$(eval $(call run_test,$(proj))))
$(foreach proj,$(PROJECTS),$(eval $(call vlg_test,$(proj))))
$(foreach proj,$(PROJECTS),$(eval $(call gdb_test,$(proj))))

$(foreach proj,$(PROJECTS),$(eval $(proj): release_$(proj) debug_$(proj) test_$(proj)))

# New rules for spell_checker_test
test_spell_checker_test: $(BUILD_DIR)/debug/spell_checker_test
$(BUILD_DIR)/debug/spell_checker_test: $(TEST_DIR)/spell_checker_test.c $(foreach dep,$(spell_checker_test_deps),$(DEBUG_LIB_DIR)/lib$(dep).so)
	@echo "Building test executable for spell_checker_test..."
	@$(CC) $(TEST_CFLAGS) -o $(BUILD_DIR)/debug/spell_checker_test $(TEST_DIR)/spell_checker_test.c $(foreach dep,$(spell_checker_test_deps),-L$(DEBUG_LIB_DIR) -l$(dep)) -Wl,-rpath,$(DEBUG_LIB_DIR) $(LIBS)

run_spell_checker_test:
	@echo "\n********************Running spell_checker_test********************\n"
	@LD_LIBRARY_PATH=$(DEBUG_LIB_DIR) $(BUILD_DIR)/debug/spell_checker_test

vlg_spell_checker_test:
	@echo "Running spell_checker_test with Valgrind..."
	@LD_LIBRARY_PATH=$(DEBUG_LIB_DIR) valgrind --leak-check=yes --track-origins=yes $(BUILD_DIR)/debug/spell_checker_test

gdb_spell_checker_test:
	@echo "Running spell_checker_test with GDB..."
	@LD_LIBRARY_PATH=$(DEBUG_LIB_DIR) gdb $(BUILD_DIR)/debug/spell_checker_test

