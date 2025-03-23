SIM = sim/build/Simulator
TARGET = test/build/$(T).bin
TEST_SRC = test/src
TEST_BUILD = test/build
TEST_FILES = $(notdir $(wildcard $(TEST_SRC)/*.c))


all:
	@echo "-------Build Simulator-------"
	@$(MAKE) -C sim
	@echo "-------Build Test-------"
	@$(MAKE) -C test T=$(T)
	@echo "-------Start Simulation-------"
	@$(SIM) $(TARGET)

debug:
	@echo "-------Build Simulator-------"
	@$(MAKE) -C sim
	@echo "-------Build Test-------"
	@$(MAKE) -C test T=$(T)
	@echo "-------Start Simulation-------"
	@$(SIM) $(TARGET) debug

all-tests:
	@echo "-------Build Simulator-------"
	@$(MAKE) -C sim
	@echo "-------Batch Testing All Files-------"
	@for test in $(TEST_FILES:.c=); do \
		echo "-------Testing $$test-------"; \
		$(MAKE) -C test T=$$test; \
		$(SIM) $(TEST_BUILD)/$$test.bin; \
	done

clean:
	@$(MAKE) -C sim clean
	@$(MAKE) -C test clean

.PHONY: clean all all-tests debug
