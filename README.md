06/04/2018:
Micro$oft has acquired github, you can find updates from this software at: https://coto88.bitbucket.io/
Have a good day.

This is the Toolchain Generic GDB stub example project:

1.	Compile Toolchain:
To compile this project you will need to follow the steps at https://github.com/cotodevel/ToolchainGenericDS:
Then simply extract the project somewhere.


2.	Compile this project: 
Open msys, through msys commands head to the directory your extracted this project.
Then write:
make clean <enter>
make <enter>

After compiling, run the example in NDS. 

Project Specific description:
You need to use a GDB client application to interact with GDB stub (server), being the DS.
So if you use a GUI based debugging tool, make sure it uses the following GDB Client binary, bundled with ToolchainGenericDS:

C:\toolchain_generic\6.2_2016q4\bin\arm-none-eabi-gdb.exe

This is for arm-none-eabi targets, the NintendoDS being one of them!

Then, write the IP and port the DS acquired into the Remote GDB Debugging tool you use, then connect.

Happy debugging!

Coto