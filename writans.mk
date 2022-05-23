
# ========
# = TEXT =
# ========

# Variable listing all text files in the writans directory
# The text installer depends on them (in case there was any change)
# (Too lazy to code a dependency thingy for that too)
export WRITANS_ALL_TEXT    := $(wildcard Writans/strings-cn/*.txt) $(wildcard Writans_EN/strings-en/*.txt)

# CN Texts
WRITANS_TEXT_MAIN	:= Writans/TextMain-cn.txt
WRITANS_INSTALLER	:= Writans/Text.event
WRITANS_DEFINITIONS	:= Writans/TextDefinitions.event
WRITANS_CHEADER		:= Writans/TextCHeader.h

WRITANS_TEXT_MAIN_EN	:= Writans_EN/TextMain-en.txt
WRITANS_INSTALLER_EN	:= Writans_EN/Text.event
WRITANS_DEFINITIONS_EN	:= Writans_EN/TextDefinitions.event
WRITANS_CHEADER_EN 		:= Writans_EN/TextCHeader.h

.PHONY: writans
writans : $(WRITANS_INSTALLER) $(WRITANS_DEFINITIONS) $(WRITANS_CHEADER) $(WRITANS_INSTALLER_EN) $(WRITANS_DEFINITIONS_EN)

# Make text installer and definitions from text
$(WRITANS_INSTALLER) $(WRITANS_DEFINITIONS) $(WRITANS_CHEADER): $(WRITANS_TEXT_MAIN) $(WRITANS_ALL_TEXT)
	$(NOTIFY_PROCESS)
	@$(TEXT_PROCESS) $(WRITANS_TEXT_MAIN) --installer $(WRITANS_INSTALLER) --definitions $(WRITANS_DEFINITIONS) --c-header $(WRITANS_CHEADER)


# Make text installer and definitions from EN text
# $(WRITANS_INSTALLER_EN) $(WRITANS_DEFINITIONS_EN) $(WRITANS_CHEADER_EN): $(WRITANS_TEXT_MAIN_EN) $(WRITANS_ALL_TEXT)
# $(NOTIFY_PROCESS)
# @$(TEXT_PROCESS) $(WRITANS_TEXT_MAIN_EN) --installer $(WRITANS_INSTALLER_EN) --definitions $(WRITANS_DEFINITIONS_EN) --c-header $(WRITANS_CHEADER_EN)



$(WRITANS_INSTALLER_EN) $(WRITANS_DEFINITIONS_EN): $(WRITANS_TEXT_MAIN_EN) $(WRITANS_ALL_TEXT)
	$(NOTIFY_PROCESS)
	@$(TEXT_PROCESS_V) $(WRITANS_TEXT_MAIN_EN) --installer $(WRITANS_INSTALLER_EN) --definitions $(WRITANS_DEFINITIONS_EN) --parser-exe $(PARSEFILE_V)



## --parser-exe $(PARSEFILE)

# Convert formatted text to insertable binary
# Nulling output because it's annoying
%.fetxt.dmp: %.fetxt
	$(NOTIFY_PROCESS)
	@$(PARSEFILE) -i $< -o $@ > /dev/null






# ==============
# = MAKE CLEAN =
# ==============

ifeq ($(MAKECMDGOALS),clean)

  CLEAN_FILES += $(WRITANS_INSTALLER) $(WRITANS_DEFINITIONS) $(WRITANS_CHEADER) $(WRITANS_INSTALLER_EN) $(WRITANS_DEFINITIONS_EN) $(WRITANS_CHEADER_EN)
  CLEAN_DIRS  += Writans/.TextEntries
  CLEAN_DIRS  += Writans_EN/.TextEntries
  
endif

