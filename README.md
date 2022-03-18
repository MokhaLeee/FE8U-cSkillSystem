# FE8U c-Skill-System Mokha-build

(W.I.P.) A [Skill-lite](https://github.com/StanHash/SkillsLite.git) and [C-HAX](https://github.com/StanHash/FE-CHAX.git) style FE8U SkillSystem re-build in C, the main purpose of which is to make it properly integrated of `Skill System` & `Str/Mag Split` & `Item Effect System` and `Weapon range getter`.

## Compiling
You can directly assemble `Main.event` through [Event Assembler](https://github.com/StanHash/EventAssembler.git). 

To make components, refer to `readme` file of [FE-CHAX by StanH](https://github.com/StanHash/FE-CHAX.git): make sure `DevkitPro`, `Python3` installed, then put [FE-Clib](https://github.com/StanHash/FE-CLib.git), [FE-CLib-Decompatible](https://github.com/boviex/FE-CLib-Decompatible.git), [EventAssember](https://github.com/StanHash/EventAssembler/releases/tag/1.0) and [PyTools](https://github.com/StanHash/FE-PyTools.git) inside `/Tools` folder, after put `Fire Emblem 8 (the U.S. ver)` clean rom named as `FE8U.gba` in the directory and finally `make hack` to build rom.

One thing to be attention for skilled hacks: [C-Lib used here](https://github.com/MokhaLeee/FE-CLib-Mokha.git) has been updated to newest decomp, rather than [SanH ver FE-Clib](https://github.com/StanHash/FE-CLib.git).


## Wizardry Organization


* Core Support

	* `Unit action`
	* `Unit menu`
	* `Expanded modular save`
	* `Popup rework`
	* `Icon display`
	* `Battle-unit hook`
	* `Load unit hook`
	* `Brief BWL`:  null all entries to BWL table except load & save routines. 
	* `BWL Supports`:  put unit support RAM data into new BWL table, rather than unit struct. 
	* `Cahpter Init hook`: Add a function hook list when start or restart chapter.
	
	
	
* Core Hacks

	* `Str/mag split`: a rework to split unit strength and magic power in C.
	* `Random number extensions`: make a sub-rng system for 3DS/FE16 style unit level up, see more in `rn-ext.h`
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
		* Draw skill page.
	* `Item effect rework`
		* Modular item menu usability
		* Modular item menu effect
		* Modular item action routine
		* Modular item prep-screen usability
		* Modular item prep-item effect
		
		
		
* Features

	* `FE16 style level up`: use `rn-ext` system for 3DS/FE16 style level.
	* `Skills installer` (W.I.P.)
		* Blow skills
	
	
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

	A: You need to install some modules for using TMX2EA. Make sure Python3 installed and get into FE-PyTools/TMX2EA folder, then, 
	
	```pip install -r requirements.txt```
	
	Just follow to [Tools/PyTools/TMS2EA/SETUP.md](https://github.com/StanHash/tmx2ea/blob/c77111a9c7a13208a2afb0984b253fa84df79479/SETUP.md).
## Thanks
- `StanH`: Main constructure of the Buildfile is based on [FE8U-CHAX](https://github.com/StanHash/FE-CHAX.git) and the framework on organization of wizardry folder is orgined [FE8U-SkillLite](https://github.com/StanHash/SkillsLite.git), both of which are developed by genius `StanHHHHHHH`. Cool guy.

- `circleseverywhere`, `Colorz`, `Laqieer`, `Teraspark`, `Alusq`, `Nintenlord`, `Zane`, `Arch`, `Camdar`, hackers and contributators for FE hack Community. Cool guys.

- all of [FEU](https://feuniverse.us/): Cool guys.