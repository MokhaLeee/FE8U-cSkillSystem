# GameData

.SUFFIXES:
.PHONY: clean tables


# Tools
TOOLS_DIR := ../Tools
include $(TOOLS_DIR)/tools.mk

# init clean files
CLEAN_FILES :=

# Convert CSV+NMM to event
%.event: %.csv %.nmm
	$(NOTIFY_PROCESS)
	@echo | $(C2EA) -csv $*.csv -nmm $*.nmm -out $*.event $(ROM_SOURCE) > /dev/null



# Gathering targets
NMMS := $(shell find -type f -name '*.nmm')
TABLE_EVENTS := $(NMMS:.nmm=.event)
CLEAN_FILES += $(TABLE_EVENTS)



# phony
tables: $(TABLE_EVENTS)

clean:
	@rm -f $(CLEAN_FILES)
	@echo all clean!
