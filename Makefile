
BUILD_DIR = build

all: configure build

configure:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake ..

build:
	@cmake --build $(BUILD_DIR)

run: build
	@./$(BUILD_DIR)/visualizer

clean:
	@rm -rf $(BUILD_DIR)

.PHONY: all configure build run clean
