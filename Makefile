BIN        = ./node_modules/.bin
MOCHA      = $(BIN)/mocha
MOCHA_OPTS = -b --timeout 20000 --recursive --slow 2000
TEST_FILES = test
TEST_FILE? = you_must_specify_the_test_file

lint:
	$(BIN)/jshint .
	$(BIN)/eslint .

test: lint
	$(MOCHA) $(MOCHA_OPTS) --reporter spec $(TEST_FILES)

test-silent: lint
	STOIC_LOG_LEVEL=0 $(MOCHA) $(MOCHA_OPTS) --reporter dot $(TEST_FILES)

ts: test-silent

clean:
	rm -rf build
	node-gyp clean

format-c:
	cd src && for i in `find . -name "*.cc" -o -name "*.hh"`; do clang-format -i $$i; done;

build-binary: format-c
	node-gyp configure && node-gyp build --jobs 6

build-binary-debug: format-c
	node-gyp configure && node-gyp build --debug --jobs 6

.PHONY: lint test test-silent ts clean format-c build-binary build-binary-debug
