# Synthesis Technology WaveEdit

This is a fork to add some features, fix some problems, and (hopefully) get stuff updated to build on contemporary systems. Currently it builds only on Linux, thanks to numerous dependencies on out-of-date packages and compiler conventions.

### Changes in v1.2

- Fixed file-overwrite problem described at https://github.com/AndrewBelt/WaveEdit/issues/17 . Saving banks should no longer overwrite wave files.
- Added interpolation between any two wavetables. Select any contiguous range of wavetables, right-click to invoke the context menu, choose Interpolate to fill the range with an interpolation between the first and last tables in the range.



 Original comments follow.


The wavetable and bank editor for the Synthesis Technology [E370](http://synthtech.com/eurorack/E370/) and [E352](http://synthtech.com/eurorack/E352/) Eurorack synthesizer modules.

### Building

Make dependencies with

	cd dep
	make

Clone the in-source dependencies.

	cd ..
	git submodule update --init --recursive

Compile the program. The Makefile will automatically detect your operating system.

	make

Launch the program.

	./WaveEdit

You can even try your luck with building the polished distributable. Although this method is unsupported, it may work with some tweaks to the Makefile.

	make dist
