include src/options.mk
# include src/latex.mk

EXECUTABLES=server

all: $(addprefix $(BUILD_DIR)/bin/,$(EXECUTABLES))

$(BUILD_DIR)/bin/server: $(BUILD_DIR)/server.a $(BUILD_DIR)/server-views.a $(BUILD_DIR)/libjson.a $(BUILD_DIR)/libsocket.a $(BUILD_DIR)/libfile.a $(BUILD_DIR)/models.a | $(BUILD_DIR)/bin/
	$(CXX) $(LDFLAGS) -o $@ $^

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

$(BUILD_DIR)/bin/:
	mkdir -p $@

.PHONY: clean

clean:
	rm -rf build/
