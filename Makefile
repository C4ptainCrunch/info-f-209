include src/options.mk
# include src/latex.mk
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

CODE=$(call rwildcard, src/, *.cpp *.h)

EXECUTABLES=server

SERVER_DEPS=$(BUILD_DIR)/server.a $(BUILD_DIR)/server-views.a $(BUILD_DIR)/libjson.a $(BUILD_DIR)/libsocket.a $(BUILD_DIR)/libfile.a $(BUILD_DIR)/models.a $(BUILD_DIR)/libexception.a
RMAKES=$(BUILD_DIR)/server.a $(BUILD_DIR)/models.a $(BUILD_DIR)/server-views.a $(BUILD_DIR)/libjson.a $(BUILD_DIR)/libfile.a $(BUILD_DIR)/libsocket.a $(BUILD_DIR)/libexception.a $(BUILD_DIR)/libtest.a

all: $(addprefix $(BUILD_DIR)/bin/,$(EXECUTABLES))

$(BUILD_DIR)/bin/server: $(SERVER_DEPS) | $(BUILD_DIR)/bin/ $(BUILD_DIR)/../server-config.json
	$(CXX) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/../server-config.json: | $(BUILD_DIR)/bin/
	cp src/server/config.json.example $@

$(BUILD_DIR)/server.a:
	$(MAKE) -C src/server

$(BUILD_DIR)/models.a:
	$(MAKE) -C src/common/models

$(BUILD_DIR)/server-views.a:
	$(MAKE) -C src/server/views

$(BUILD_DIR)/libjson.a:
	$(MAKE) -C src/common/lib/json

$(BUILD_DIR)/libfile.a:
	$(MAKE) -C src/common/lib/file

$(BUILD_DIR)/libsocket.a:
	$(MAKE) -C src/common/lib/socket

$(BUILD_DIR)/libexception.a:
	$(MAKE) -C src/common/lib/exception

$(BUILD_DIR)/libtest.a:
	$(MAKE) -C src/common/lib/test

$(BUILD_DIR)/bin/:
	mkdir -p $@

doc: $(BUILD_DIR)/doc
	$(MAKE) -C doc

.PHONY: clean doc $(RMAKES)

$(BUILD_DIR)/doc:
	mkdir -p $@

clean:
	rm -rf build/

normalize:
	uncrustify --replace -c src/normalize.cfg $(CODE)

normalize-clean:
	find . -name "*.unc-backup.md5\~" -exec rm {} \;
	find . -name "*.unc-backup\~" -exec rm {} \;
