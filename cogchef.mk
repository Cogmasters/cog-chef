# CogChef post-preprocessor executable that runs after CPP expansion
POST_EXPAND = cogchef-post_expand

# Input file to be preprocessed
EXTEND = $(EXTEND_NO_EXT).PRE.h
# Resulting single-file amalgamations after preprocessing input file
OUT_C  = $(OUT_NO_EXT).c
OUT_H  = $(OUT_NO_EXT).h
OUT_O  = $(OUT_NO_EXT).o

CFLAGS   ?= -O2
CFLAGS   += -I. -Wall -Wextra -Wpedantic -std=c89
CPP       = cc -E # If you run into issues, try changing this to 'cpp'
CPPFLAGS += -nostdinc -P -CC

# Convert 'foo/bar_baz-tuna.PRE.h' -> 'FOO_BAR_BAZ_TUNA_H'
# TODO: Evaluate if the sed expressions can be joined (see https://unix.stackexchange.com/a/145409)
HEADER_TAG_EXPAND   = "$$(echo '$<' | sed -e 's/\(.*\)\.PRE.h/\1/' | sed -e 's/\//_/g' | sed -e 's/-/_/g' | tr '[:lower:]' '[:upper:]')_H"
# Doxygen file description
DOXYGEN_DESC_EXPAND = "/**\n * @file $@\n * @author CogChef\n * @brief CogChef generated code\n */\n"

all: $(OUT_O)

$(POST_EXPAND):
	$(CC) $(CFLAGS) $@.c -o $@

$(OUT_O): $(OUT_C) $(OUT_H)
	$(CC) -c $(CFLAGS) $< -o $@
$(OUT_H): $(TEMPFILE) $(EXTEND) $(POST_EXPAND)
	@ echo "Generating header"
	@ echo "#ifndef $(HEADER_TAG_EXPAND)" > $@
	@ echo "#define $(HEADER_TAG_EXPAND)\n" >> $@
	$(CPP) $(CFLAGS) -DCOGCHEF_DEFINITIONS -DCOGCHEF_ENTRY=\"$<\" $(CPPFLAGS) $(EXTEND) | ./$(POST_EXPAND) >> $@
	$(CPP) $(CFLAGS) $(DFLAGS) -DCOGCHEF_HEADER -DCOGCHEF_ENTRY=\"$<\" $(CPPFLAGS) $(EXTEND) | ./$(POST_EXPAND) >> $@
	@ echo "\n#endif /* $(HEADER_TAG_EXPAND) */" >> $@
$(OUT_C): $(TEMPFILE) $(EXTEND) $(POST_EXPAND)
	@ echo "Generating forward definitions"
	@ echo "#include \"$(OUT_H)\"" > $@
	$(CPP) $(CFLAGS) $(DFLAGS) -DCOGCHEF_FORWARD -DCOGCHEF_ENTRY=\"$<\" $(CPPFLAGS) $(EXTEND) | ./$(POST_EXPAND) >> $@
	@ echo "Generating source"	
	$(CPP) $(CFLAGS) $(DFLAGS) -DCOGCHEF_ENTRY=\"$<\" $(CPPFLAGS) $(EXTEND) >> $@

headers: $(HEADERS)

$(HEADERS): $(EXTEND) $(POST_EXPAND)

.SUFFIXES: .PRE.h .h
.PRE.h.h:
	@ echo $(DOXYGEN_DESC_EXPAND) > $@
	@ echo "#ifndef $(HEADER_TAG_EXPAND)" >> $@
	@ echo "#define $(HEADER_TAG_EXPAND)\n" >> $@
	$(CPP) $(CFLAGS) -DCOGCHEF_DEFINITIONS -DCOGCHEF_ENTRY=\"$<\" $(CPPFLAGS) $(EXTEND) | ./$(POST_EXPAND) >> $@
	$(CPP) $(CFLAGS) $(DFLAGS) -DCOGCHEF_HEADER -DCOGCHEF_ENTRY=\"$<\" $(CPPFLAGS) $(EXTEND) | ./$(POST_EXPAND) >> $@
	@ echo "\n#endif /* $(HEADER_TAG_EXPAND) */" >> $@

echo:
	@ echo 'EXTEND_NO_EXT: $(EXTEND_NO_EXT)'
	@ echo 'OUT_H: $(OUT_H)'
	@ echo 'OUT_C: $(OUT_C)'
	@ echo 'OUT_O: $(OUT_O)'
	@ echo 'HEADERS: $(HEADERS)'

clean:
	@ rm -f $(OUT_H) $(OUT_C) $(OUT_O) $(HEADERS) $(POST_EXPAND)

.PHONY: headers clean
