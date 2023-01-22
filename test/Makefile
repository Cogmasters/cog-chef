TOP  = ..
CC  ?= gcc

API_DIR = test/api
OUT     = out
DFLAGS  = -DCOGCHEF_HELPER

BUILD = $(MAKE) API_DIR=$(API_DIR) OUT=$(OUT) -C ..
OUT_H = $(TOP)/$(OUT).h
EXES  = test

CFLAGS += -Wall -Wextra -Wpedantic -I$(TOP) -std=c89

all: $(OUT_H) $(EXES)

$(OUT_H):
	@ $(BUILD) DFLAGS="$(DFLAGS)"

clean:
	rm -f $(EXES)
	@ $(BUILD) $@

.PHONY: clean
.NOTPARALLEL: all