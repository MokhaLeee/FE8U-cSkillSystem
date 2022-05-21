# Writans

.SUFFIXES:
.PHONY: clean all



# Tools
TOOLS_DIR := c:/FE-Tools
include $(TOOLS_DIR)/tools.mk

# init clean files
CLEAN_FILES :=
CLEAN_DIRS :=

# ========
# = TEXT =
# ========

# Variable listing all text files in the writans directory
# The text installer depends on them (in case there was any change)
# (Too lazy to code a dependency thingy for that too)
WRITANS_ALL_TEXT    := $(wildcard *.txt)

# Main input text file
WRITANS_TEXT_MAIN   := $(realpath .)/TextMain.txt

# textprocess outputs
WRITANS_INSTALLER   := $(realpath .)/Text.event
WRITANS_DEFINITIONS := $(realpath .)/TextDefinitions.event

# Make text installer and definitions from text
$(WRITANS_INSTALLER) $(WRITANS_DEFINITIONS): $(WRITANS_TEXT_MAIN) $(WRITANS_ALL_TEXT)
	$(NOTIFY_PROCESS)
	@$(TEXT_PROCESS) $(WRITANS_TEXT_MAIN) --installer $(WRITANS_INSTALLER) --definitions $(WRITANS_DEFINITIONS) --parser-exe $(PARSEFILE)

# Convert formatted text to insertable binary
# Nulling output because it's annoying
%.fetxt.dmp: %.fetxt
	$(NOTIFY_PROCESS)
	@$(PARSEFILE) $< -o $@ > /dev/null

# ==============
# = MAKE CLEAN =
# ==============

ifeq ($(MAKECMDGOALS),clean)

  CLEAN_FILES += $(WRITANS_INSTALLER) $(WRITANS_DEFINITIONS)
  CLEAN_DIRS  += .TextEntries

endif



# phony
all: $(WRITANS_INSTALLER)

clean:
	@rm -f $(CLEAN_FILES)
	@rm -rf $(CLEAN_DIRS)
	@echo all clean!
