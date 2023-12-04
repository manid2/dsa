all: tests check

DSAVENV_ACTIVATE_FILE:=.dsavenv/bin/activate
DSAVENV_ACTIVATE_CMD:=. $(DSAVENV_ACTIVATE_FILE);

.PHONY: .dsavenv tests check clean

.dsavenv:
	test -d .dsavenv || python3 -m venv .dsavenv

tests: .dsavenv
	$(DSAVENV_ACTIVATE_CMD) pip install -Ur requirements.txt

check: tests
	$(DSAVENV_ACTIVATE_CMD) pytest

clean:
	rm -rf .dsavenv
