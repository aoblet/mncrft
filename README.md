#IMAC2 - OpenGL project
Team: 		Mncrft3000  
Software:	mncrft

Members:  

	- Armand 	Biteau
	- Alexis 	Oblet
	- Hugo  	Garrido
	- Mathias 	Goyheneche
	
Scripts shell for easy use: scripts/  

	- compile project
	- launch minecraft default
	- launch minecraft other map
	- compile/install jsoncpp if error 

Just for fun  
	
	- possibility to change map for adventure: ./launchNice.sh or ./Imacraft perfo 
	  (just for visit, map is not fully filled of cubes)

Shorkeys:  

	- z q s d 		=> regulary move
	- space   		=> jump
	- left ctrl 	=> easy edge build
	- t 			=> change universe
	- o 			=> quit window focus(for resize or leave sdl wrapper to do something else) 
	- b 			=> large wide camera mode
	- n 			=> normal camera mode
	- escape 		=> quit game(save included)

	- left click 	=> hit cube(can stay pressed)
	- right click 	=> build cube(can stay pressed)
	- scroll 		=> change current type cube(no callback for the moment)

Possible problems:  

	- texture error
		- if you use bash and not our scripts, be sure to be in build/bin path, it's not possible to do that: ./smth/mncrft/build/bin/Imacraft. But cd smth/mncrft/build/bin/ && ./Imacraft (perfo?)
	- jsoncpp
		- problems may be encoutered because of pc architecture
			- exception possible: "Json reader parse error"
		- solution
			- compile with your own pc jsoncpp:
				- ./compile_install_jsoncpp.sh
	- compilation shader
		- No problem on our own pc. But we observed a problem on others whith following function at: shaders/tex3D.fs.glsl(49): texture2Darray "(error c1115)" 

Tips:  
	- tests folder is inactive from cmake: to active uncomment in CMakeLists.txt  add_subdirectory(tests) (line 91)
