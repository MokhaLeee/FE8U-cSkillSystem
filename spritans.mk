
# =============
# = PORTRAITS =
# =============

PORTRAIT_LIST      := Spritans/PortraitList.txt
PORTRAIT_INSTALLER := Spritans/Portraits.event

# Make the portrait installer
$(PORTRAIT_INSTALLER): $(PORTRAIT_LIST) $(shell $(PORTRAIT_PROCESS) $(PORTRAIT_LIST) --list-files)
	$(NOTIFY_PROCESS)
	@$(PORTRAIT_PROCESS) $< --output $@

# Convert a png to portrait components
%_mug.dmp %_palette.dmp %_frames.dmp %_minimug.dmp: %.png
	$(NOTIFY_PROCESS)
	@$(PORTRAITFORMATTER) $<

# ==========================
# = GRAPHICS & COMPRESSION =
# ==========================

# PNG to 4bpp rule
%.4bpp: %.png
	$(NOTIFY_PROCESS)
	@$(PNG2DMP) $< -o $@


# Palette
%.gbapal: %.png
	$(NOTIFY_PROCESS)
	@$(PNG2DMP) $< -po $@ --palette-only

# Compress TSA
%.lz: %
	$(NOTIFY_PROCESS)
	@$(COMPRESS) $< $@






ifeq ($(MAKECMDGOALS),clean)

  PNG_FILES := $(shell find -type f -name '*.png')
  TSA_FILES := $(shell find -type f -name '*.tsa')
  
  PORTRAITS := $(wildcard Spritans/Portraits/*.png)
  PORTRAIT_GENERATED := \
    $(PORTRAITS:.png=_mug.dmp) $(PORTRAITS:.png=_palette.dmp) \
    $(PORTRAITS:.png=_frames.dmp) $(PORTRAITS:.png=_minimug.dmp)

  CLEAN_FILES += $(PORTRAIT_INSTALLER) $(PORTRAIT_GENERATED)
  CLEAN_FILES += $(PNG_FILES:.png=.4bpp) $(PNG_FILES:.png=.4bpp.lz) $(PNG_FILES:.png=.gbapal)
  CLEAN_FILES += $(TSA_FILES:.tsa=.tsa.lz)
endif
