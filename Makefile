include src/options.mk
# include src/latex.mk

EXECUTABLES=server

SERVER_DEPS=$(BUILD_DIR)/server.a $(BUILD_DIR)/server-views.a $(BUILD_DIR)/libjson.a $(BUILD_DIR)/libsocket.a $(BUILD_DIR)/libfile.a $(BUILD_DIR)/models.a $(BUILD_DIR)/libexception.a
RMAKES=$(BUILD_DIR)/server.a $(BUILD_DIR)/models.a $(BUILD_DIR)/server-views.a $(BUILD_DIR)/libjson.a $(BUILD_DIR)/libfile.a $(BUILD_DIR)/libsocket.a $(BUILD_DIR)/libexception.a

all: $(addprefix $(BUILD_DIR)/bin/,$(EXECUTABLES))

$(BUILD_DIR)/bin/server: $(SERVER_DEPS) | $(BUILD_DIR)/bin/ $(BUILD_DIR)/../server-config.json
	$(CXX) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/../server-config.json: | $(BUILD_DIR)/bin/
	cp src/server/config.json.example $@

$(BUILD_DIR)/server.a:
	make -C src/server

$(BUILD_DIR)/models.a:
	make -C src/common/models

$(BUILD_DIR)/server-views.a:
	make -C src/server/views

$(BUILD_DIR)/libjson.a:
	make -C src/common/lib/json

$(BUILD_DIR)/libfile.a:
	make -C src/common/lib/file

$(BUILD_DIR)/libsocket.a:
	make -C src/common/lib/socket

$(BUILD_DIR)/libexception.a:
	make -C src/common/lib/exception

$(BUILD_DIR)/bin/:
	mkdir -p $@

doc:
	make -C doc

.PHONY: clean doc $(RMAKES)

clean:
	rm -rf build/
