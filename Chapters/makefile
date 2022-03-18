# Maps

.SUFFIXES:
.PHONY: clean maps


# Tools
TOOLS_DIR := c:/FE-Tools
include $(TOOLS_DIR)/tools.mk

# init clean files
CLEAN_FILES :=

# ========
# = MAPS =
# ========

# TMX to event + dmp
%.event %_data.dmp: %.tmx
	$(NOTIFY_PROCESS)
	@echo | $(TMX2EA) $< > /dev/null

# python c:/FE-Tools/PyTools/TMX2EA/tmx2ea.py tmxFiles C:/FE_Proj/FE8U-MokhaSys/Chapters/FE6Ch1/FE6Chapter1Map.tmx
# python c:/FE-Tools/PyTools/TMX2EA/tmx2ea.py -O C:/FE_Proj/FE8U-MokhaSys/Chapters/FE6Ch1/MapInstaller.event


# Gathering targets
# TMXs and generated files
TMXS := $(shell find -type f -name '*.tmx')
MAP_GENERATED := $(TMXS:.tmx=.event) $(TMXS:.tmx=_data.dmp)

CLEAN_FILES += $(MAP_GENERATED)


# phony
maps: $(MAP_GENERATED)

clean:
	@rm -f $(CLEAN_FILES)
	@echo all clean!
