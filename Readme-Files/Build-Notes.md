## Build for C-SkillSys(for Windows user)

- Clone repo with command `git clone --recursive https://github.com/MokhaLeee/FE8U-cSkillSystem.git` or update submodules with `git submodule update --init --recursive` after cloning, or just download each submodule inside `Tools/` folder.

- have [devkitARM](https://devkitpro.org/wiki/Getting_Started) installed, and the `DEVKITARM` env variable set.

- have [python 3](https://www.python.org/) installed and in your path. (the makefile *should* be able to find the correct python executable name. See [`tooks.mk`](../tooks.mk)).

- Download [EventAssembler release](https://github.com/StanHash/EventAssembler/releases/tag/1.0), and unzip which in `Tools` folder.

- Put `Fire Emblem 8: Scared Stones`(sha1: c25b145e37456171ada4b0d440bf88a19f4d509f) clean rom named `FE8U.gba` in directory.
- Open `Msys2` (which will be installed on DevkitPRO installation), or `Windows terminal` and get into current folder, to build rom `FE-cSkillSys.gba`:
```
sh makehack.sh all
```

- Further more, you can `make clean` to clean build outputs.

You can directly assemble `Main.event` through [Event Assembler](https://github.com/StanHash/EventAssembler.git), and for more details, you can see tips on [StanH's CHAX](https://github.com/StanHash/FE-CHAX.git).

BTW, since I may update the repository of C-Lib from time to time, so I suggest you update each submodels any time you want to compile this through commands:
```
git submodule sync
git submodule update --init
git submodule update --remote
```


## Q & A
- Q: ERROR with `switch` statement when assembling C, where EA would told me `Undefined identifier: _LP___gnu_thumb1_case_uqi`

	A: Change optimize-options of gcc from `Os` to `O1` or `O2` inside `make_wizardry.mk`.

- Q: ERROR: `ModuleNotFoundError: No module named 'six'`

	A: You need to install some modules for using TMX2EA. Make sure Python3 installed and get into `Tools/FE-PyTools/TMX2EA` folder, then, 
	
	```pip install -r requirements.txt```
	
	Just follow to [../Tools/PyTools/TMS2EA/SETUP.md](https://github.com/StanHash/tmx2ea/blob/c77111a9c7a13208a2afb0984b253fa84df79479/SETUP.md).
	
