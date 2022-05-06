
# ========
# = TEXT =
# ========

# Variable listing all text files in the writans directory
# The text installer depends on them (in case there was any change)
# (Too lazy to code a dependency thingy for that too)
export WRITANS_ALL_TEXT    := $(wildcard Writans/strings/*.txt)

# Main input text file
WRITANS_TEXT_MAIN   := Writans/TextMain.txt

# textprocess outputs
WRITANS_INSTALLER	:= Writans/Text.event
WRITANS_DEFINITIONS	:= Writans/TextDefinitions.event
WRITANS_CHEADER 	:= Writans/TextCHeader.h

# Make text installer and definitions from text
$(WRITANS_INSTALLER) $(WRITANS_DEFINITIONS) $(WRITANS_CHEADER): $(WRITANS_TEXT_MAIN) $(WRITANS_ALL_TEXT)
	$(NOTIFY_PROCESS)
	@$(TEXT_PROCESS) $(WRITANS_TEXT_MAIN) --installer $(WRITANS_INSTALLER) --definitions $(WRITANS_DEFINITIONS) --parser-exe $(PARSEFILE) --c-header $(WRITANS_CHEADER)

# Convert formatted text to insertable binary
# Nulling output because it's annoying
%.fetxt.dmp: %.fetxt
	$(NOTIFY_PROCESS)
	@$(PARSEFILE) $< -o $@ > /dev/null

# ==============
# = MAKE CLEAN =
# ==============

ifeq ($(MAKECMDGOALS),clean)

  CLEAN_FILES += $(WRITANS_INSTALLER) $(WRITANS_DEFINITIONS) $(WRITANS_CHEADER)
  CLEAN_DIRS  += Writans/.TextEntries

endif

