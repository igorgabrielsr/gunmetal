# Gunmetal Framework - Build System

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -Iinclude
LDFLAGS = -lX11 -lpthread -lm

BUILD_DIR = build
EXAMPLES_DIR = examples

# Colors
GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[0;33m
NC = \033[0m

.PHONY: all clean run

all: info simple_window

info:
	@echo "$(BLUE)----------------------------------------$(NC)"
	@echo "$(BLUE)  Gunmetal Framework - Build System$(NC)"
	@echo "$(BLUE)----------------------------------------$(NC)"

simple_window:
	@mkdir -p $(BUILD_DIR)
	@echo "$(GREEN)Building simple_window...$(NC)"
	@$(CC) $(CFLAGS) $(EXAMPLES_DIR)/simple_window.c -o $(BUILD_DIR)/simple_window $(LDFLAGS)
	@echo "$(GREEN)✓ Built: $(BUILD_DIR)/simple_window$(NC)"

run: simple_window
	@echo "$(BLUE)Running simple_window...$(NC)"
	@./$(BUILD_DIR)/simple_window

clean:
	@echo "$(YELLOW)Cleaning...$(NC)"
	@rm -rf $(BUILD_DIR)
	@echo "$(GREEN)✓ Clean$(NC)"

help:
	@echo "Gunmetal Framework - Makefile"
	@echo ""
	@echo "Targets:"
	@echo "  all            - Build all examples"
	@echo "  simple_window  - Build simple_window example"
	@echo "  run            - Build and run simple_window"
	@echo "  clean          - Remove build directory"
	@echo "  help           - Show this help"
