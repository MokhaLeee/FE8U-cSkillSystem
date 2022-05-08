
# Paths
BASE_DIR=$(dirname "$(readlink -f "$0")")
TOOLS_DIR="$BASE_DIR/Tools"
EA_DIR="$TOOLS_DIR/EventAssembler"


# EA main buildfile
main_event="$BASE_DIR/Main.event"


# ROMs
source_rom="$BASE_DIR/FE8U.gba"
target_rom="$BASE_DIR/FE-cSkillSys.gba"


# Tools
EA="$EA_DIR/ColorzCore.exe"



if [[ $1 == all ]]; then
	
	make clean
	make writans
	make hack
	
fi


if [[ $1 != all ]]; then
	# Preparing ROM
	cd "$BASE_DIR"
	echo "===== Copy ROM ====="
	cp -f "$source_rom" "$target_rom"
	echo "Copy Target ROM .. done!"

	# Make Hack
	cd "$BASE_DIR"
	echo "===== Make Hack ====="
	"$EA" A FE8 "-input:$main_event" "-output:$target_rom"
	echo "done!"
fi
