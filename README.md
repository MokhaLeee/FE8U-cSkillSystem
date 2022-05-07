# FE8U c-Skill-System Mokha-build

A W.I.P. project of [Skill-lite](https://github.com/StanHash/SkillsLite.git) and [C-HAX](https://github.com/StanHash/FE-CHAX.git) style FE8U SkillSystem rebuild in C, the main purpose of which is to make it properly integrated of `Skill System` & `Str/Mag Split` & `Item Effect System` and `Weapon range getter`.

## Compiling (for Windows user)

- Clone repo with command `git clone --recursive https://github.com/MokhaLeee/FE8U-cSkillSystem.git` or update submodules with `git submodule update --init --recursive` after cloning, or just download each submodule inside `Tools/` folder.

- have [devkitARM](https://devkitpro.org/wiki/Getting_Started) installed, and the `DEVKITARM` env variable set.

- have [python 3](https://www.python.org/) installed and in your path. (the makefile *should* be able to find the correct python executable name. See [`tooks.mk`](./tooks.mk)).

- Download [EventAssembler release](https://github.com/StanHash/EventAssembler/releases/tag/1.0), and unzip which in `Tools` folder.

- Put `Fire Emblem 8: Scared Stones`(sha1: c25b145e37456171ada4b0d440bf88a19f4d509f) clean rom named `FE8U.gba` in directory.
- Open `Msys2` (which will be installed on DevkitPRO installation), or `Windows terminal` and get into current folder, to build rom `FE-cSkillSys.gba`:
```
make writans
make hack
```

- Further more, you can `make clean` to clean build outputs.

You can directly assemble `Main.event` through [Event Assembler](https://github.com/StanHash/EventAssembler.git), and for more details, you can see tips on [StanH's CHAX](https://github.com/StanHash/FE-CHAX.git).

BTW, since I may update the repository of C-Lib from time to time, so I suggest you update each submodels any time you want to compile this through commands:
```
git submodule sync
git submodule update --init
git submodule update --remote
```

## Wizardry Organization


* Core Support

	* `Unit action`
	* `Unit menu`
	* `Expanded modular save`
	* `Popup rework`
	* `Icon display`
	* `Battle-unit hook`
	* `Load unit hook`
	* `Null BWL`:  null all entries to BWL table except load & save routines. 
	* `BWL Supports`:  put unit support RAM data into new BWL table, rather than unit struct. 
	* `Cahpter Init hook`: Add a function hook list when start or restart chapter.
	* `Common Space`: a common & free space with 0x40 long and will save in Suspend data, for more details, see `common-space.h`
	* `Random number extensions`: make a sub-rng system for 3DS/FE16 style unit level up, see more in `rn-ext.h`
	
	
* Core Hacks

	* `Str/mag split`: a rework to split unit strength and magic power in C.
	* `Status getter`: modular functions to get unit status with MAG & CON & MOV getter.
	* `Range getter master`: modular functions to get weapon attack range.
		* `Modular range getter`
		* `Fill-map works`: c-hax to rewrite ItemRange2Mask, and FillMap functions based on decomp.
		* `Draw item range string`: a UI rework to properly draw item range message in help-box and unit item page of stat-screen.
		* `Is item covering range`: (W.I.P.) judge can weapon counter enimies by new modular range getter.
	* `Level up rework`
		* `Modular level up (ModLU)`: modular functions for unit level up, to further add unit skill learning funcs, etc. Also add checks for unit magic power status level up.
		* `Growth getter`: modular functions to get unit status growth.
		* `Auto level`: add unit magic power auto-level for str/mag split.
		* `Check cap`:  add unit magic power check-cap.
		* `Level up screen`: rework unit level up animes for both anime-off and anime-on and promotion cases, in C based on decomp.
		* `Modular promotion getter`: same as ModLU, but for unit promotion.
	* `Stat screen`
		* Draw left page.
		* Draw skill page inside unit page.
		* Help box.
	* `Skill core`
		* Skill tester
		* `Skill fast list`: make two skill fast lists in RAM space for judge unit skill faster.
		* Skill desc & name & icon-gfx etc. getter
		* Add skill etc. misc functions
		* Draw skill page
		* Draw prep-screen pick-skill page
	* `Item effect rework`
		* Modular item menu usability
		* Modular item menu effect
		* Modular item action routine
		* Modular item prep-screen usability
		* Modular item prep-item effect
		
	* `Battle system`: check  function battle-unwind and can unit double attack	
		* `Core`: extend the Battle-Hit array.
		* `Battle order`: rework on battle-order and can-unit-double-attack judgement, introduce skill `Desperation` and skill `Vantage`
		* `Pre-battle calc`: rework on battle status calculation as atk/def/hit/avo, etc.
	
	* `Combat Art`: Three-Houses style attack skills
		* Menu & TargetSelect: Unit-Menu item & Combat Art Select menu and items & Target select
		* Misc: LoadUnit combat-art, Pre-Battle Calc modular functions
	
* Features

	* `FE16 style level up`: use `rn-ext` system for 3DS/FE16 style level.
	* `Skills installer` (W.I.P.)
		* Blow skills
		* Battle order skills
	* `Prep-Screen Rework`
	* `Skill-Anim Installer`
	
* External Patches: other hackers' work

	* `HP bars`
	* `Movement arrow hack`
	* `Modular portrait height arrangment`
	* `Stat-screen eye blink`
	* `Fix weapon ranks`
	* `Windows & menu semitransparency`
	* Some mokha small fixes.

	
## Q & A
- Q: ERROR with `switch` statement when assembling C, where EA would told me `Undefined identifier: _LP___gnu_thumb1_case_uqi`

	A: Change optimize-options of gcc from `Os` to `O1` or `O2` inside `make_wizardry.mk`.

- Q: ERROR: `ModuleNotFoundError: No module named 'six'`

	A: You need to install some modules for using TMX2EA. Make sure Python3 installed and get into `Tools/FE-PyTools/TMX2EA` folder, then, 
	
	```pip install -r requirements.txt```
	
	Just follow to [Tools/PyTools/TMS2EA/SETUP.md](https://github.com/StanHash/tmx2ea/blob/c77111a9c7a13208a2afb0984b253fa84df79479/SETUP.md).
## Thanks
- `StanH`: Main constructure of the Buildfile is based on [FE8U-CHAX](https://github.com/StanHash/FE-CHAX.git) and the framework on organization of wizardry folder is orgined [FE8U-SkillLite](https://github.com/StanHash/SkillsLite.git), both of which are developed by genius `StanHHHHHHH`. Cool guy.

- `circleseverywhere`, `Colorz`, `Laqieer`, `Teraspark`, `Alusq`, `Nintenlord`, `Zane`, `Arch`, `Camdar`, hackers and contributators for FE hack Community. Cool guys.

- all of [FEU](https://feuniverse.us/): Cool guys.