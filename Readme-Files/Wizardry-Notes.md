## Wizardry Organization


* Core Support
	
	* `Mokha Lib`: basic div & mod functions, etc.
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
	* `Negative Stat Boosts`
	
	
* Core Hacks

	* `Str/mag split`: a rework to split unit strength and magic power in C.
	* `Status getter`: modular functions to get unit status with MAG & CON & MOV getter.
	* `Range getter master`: modular functions to get weapon attack range.
		* `Modular range getter`
		* `Fill-map works`: c-hax to rewrite ItemRange2Mask, and FillMap functions based on decomp.
		* `Draw item range string`: a UI rework to properly draw item range message in help-box and unit item page of stat-screen.
		* `Is item covering range`: judge can weapon counter enimies by new modular range getter.
	* `Level up rework`
		* `Modular level up (ModLU)`: modular functions for unit level up, to further add unit skill learning funcs, etc. Also add checks for unit magic power status level up.
		* `Growth getter`: modular functions to get unit status growth.
		* `Auto level`: add unit magic power auto-level for str/mag split.
		* `Check cap`:  add unit magic power check-cap.
		* `Level up screen`: rework unit level up animes for both anime-off and anime-on and promotion cases, in C based on decomp.
		* `Modular promotion getter`: same as ModLU, but for unit promotion.
	* `Stat screen`
		* Draw left & unit * item page
		* Draw skill page inside unit page
		* Help box.
		* Function: BattleGenerateUiStats rework
		* C-style growth-based text color
	* `Skill core`
		* Skill tester
		* `Skill fast list`: make two skill fast lists in RAM space for judge unit skill faster.
		* Skill desc & name & icon-gfx etc. getter
		* Add skill etc. misc functions
		* Draw skill page
		* Skill activition anim core
	* `Prep Pick Skill Screen`: Equip skills in prep-screen
		
	* `Item effect rework`
		* Modular item menu usability
		* Modular item menu effect
		* Modular item action routine
		* Modular item prep-screen usability
		* Modular item prep-item effect
		
	* `Battle system`: check  function battle-unwind and can unit double attack	
		* `Core`: extend the Battle-Hit array.
		* `Battle order`: rework on battle-order and can-unit-double-attack judgement, introduce skill `Desperation` and skill `Vantage`
		* `Battle calc`: Pre-Battle calculation, Battle hit, Battle calc real
		* `Battle effective`: check whether unit or item effective to enimy
		* `Battle forcast`: reworked on BkSel
		* `Battle can counter`: introduced a modular check loop
		* `Battle exp getter`
		* `Battle accuracy calc`
		* `Weapon equipment`: remove check can-counter routine
		* `Weapon tri-angle`
	
	* `Combat Art`: Three-Houses style attack skills
		* Menu & TargetSelect: Unit-Menu item & Combat Art Select menu and items & Target select
		* Misc: LoadUnit combat-art, Pre-Battle Calc modular functions
		* `BkSel`: reworked on battle-forcast UI
		* Select-Target: rewoked on target-select core so that we can change combat-art during target-selection
	
	* `Unit Status`: a rework on unit buff & debuff status: 2 bits duration + 6 bits index
		* Blinky Icon: diy on sprite's debuff object
		* Duration Depletion: unit duration--
		* Core: use 2 bits to ensure unit hold 4 turns duration
	* `Posy Action Hook`: add a blocking proc and hook loop to enable hackers inset own proc. For example, debuff anim, etc.
* Features

	* `FE16 style level up`: use `rn-ext` system for 3DS/FE16 style level.
	* `Skills installer`
		* Skills Info Table
		* Various skills and their info
	* `Combat-Arts installer` 
		* Combat-Arts Info Table
		* Various combat-arts and their info
	
	* `Skill Activition Anims`
		* Various skills anims installer
	* Map Anims
		* Some Map object effect procs (for example, debuff:gravity's post-action effect anim, etc)
	* Unit Status Installer
		* Define vairous unit buff & debuff status informations
	* `Prep-Screen Rework`
	* `Skill-Anim Installer`
	
* External Patches: other hackers' work

	* `HP bars`
	* `Movement arrow hack`
	* `Modular portrait height arrangment`
	* `Stat-screen eye blink`
	* `Fix weapon ranks`
	* `Windows & menu semitransparency`
	* `Game Start Screen`: a diy H & S screen
	* `Remove A`: replace vanilla item's "A or a" to " "(space character)
	* Some mokha small fixes.