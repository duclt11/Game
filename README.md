### Requirement 
- install [CMAKE](https://cmake.org/download/)

### Setup
- Window 
	- Run gen_prj_vs2019.bat or gen_prj_vs2022.bat
	- Go to Builds folders
	- open SandBox.sln
	
	
### Project structure
- libs : contains third-party libraries that the project depends on. These libraries can be either included directly or added as submodules , added by using FetchContent in cmake.
- tests : is for test cases and test scripts. It contains unit tests, integration tests, and any other automated tests that ensure the project functions correctly.
- resouces : holds non-source code files that the project needs, such as configuration files, images, data files, templates, or other static assets.
- release : is used for compiled binaries.
- builds : contains build artifacts. It can include cmake configure , intermediate files, or any other output generated after the configure process when generating with cmake.
- soucres : holds the main source code of the project. It is where you will code to build project.
- cmake : contains helper functions and CMake scripts that are used to configure the build system.