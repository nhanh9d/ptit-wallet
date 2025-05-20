# Detect OS
UNAME_S := $(shell uname -s)
ifeq ($(OS),Windows_NT)
	TARGET = wallet_app.exe
	OPENSSL_INC = -IC:/OpenSSL-Win64/include
	OPENSSL_LIB = -LC:/OpenSSL-Win64/lib
else
	ifeq ($(UNAME_S),Darwin)
		TARGET = wallet_app
		OPENSSL_INC = -I/opt/homebrew/opt/openssl@3/include
		OPENSSL_LIB = -L/opt/homebrew/opt/openssl@3/lib
	else
		TARGET = wallet_app
		OPENSSL_INC =
		OPENSSL_LIB =
	endif
endif

SRC = main.cpp user.cpp manager.cpp wallet.cpp transaction.cpp utils.cpp data_manager.cpp otp.cpp qrcodegen.cpp
OBJ = $(addprefix src/,$(SRC))
BUILD_DIR = build
BIN = $(BUILD_DIR)/$(TARGET)
CXXFLAGS = -std=c++17 $(OPENSSL_INC) $(OPENSSL_LIB)
LDFLAGS = -lssl -lcrypto

all: $(BUILD_DIR) $(BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

run: all
	@echo "--- Chạy ứng dụng ---"
	@$(BIN)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean 