# Simple Shell

##### Why was the shell always invited to computer parties?

###### Because it knew how to "grep" everyone's attention

---
A shell is a program that interprets and executes system commands,
like `ls`, `git commit`, or `rm -rf /*`. (Tip: ***never*** run `rm -rf /*   `)
A shell should take text input; read and parse it; execute the command,
if valid; print output, if there is any; and repeat. You can navigate
a file system; create, edit, delete, and run files; and maybe even access
the internet using a shell. A couple examples of a shell are Bash and
PowerShell. Examples of things that may be confused with a shell, but
are **not** are: the terminal/console, Vim, Ubuntu, or the Sandbox/VM.

### Examples of this concept:

Example input/output:
```
Welcome to the Gates Of Shell. Type "exit" to quit.

[Go$H] | SmartFridge@fedora:/home/SmartFridge/CLionProjects/atlas-simple_shell$ invalidfji1j
./OpenShellGates: 1: invalidfji1j: not found
[Go$H] | SmartFridge@fedora:/home/SmartFridge/CLionProjects/atlas-simple_shell$ ls -a
.           AUTHORS             bashlist           env2.c              shell_loop.c
..          CMakeLists.txt      cmake-build-debug  front_lawn          shellf_destruct.c
.git        OpenShellGates      colors.h           main.c              super-simple_shell
.gitignore  README.md           custom_commands.c  main.h
.idea       TestRunScript.bash  env.c              man_3_simple_shell
[Go$H] | SmartFridge@fedora:/home/SmartFridge/CLionProjects/atlas-simple_shell$ ls ../..
Applications   Desktop    Downloads      Music     Public     Videos
CLionProjects  Documents  Miscellaneous  Pictures  Templates
[Go$H] | SmartFridge@fedora:/home/SmartFridge/CLionProjects/atlas-simple_shell$ echo Hello, World! This is a simple $hell
Hello, World! This is a simple $hell
[Go$H] | SmartFridge@fedora:/home/SmartFridge/CLionProjects/atlas-simple_shell$ pwd
/home/SmartFridge/CLionProjects/atlas-simple_shell
[Go$H] | SmartFridge@fedora:/home/SmartFridge/CLionProjects/atlas-simple_shell$ whoami
SmartFridge
[Go$H] | SmartFridge@fedora:/home/SmartFridge/CLionProjects/atlas-simple_shell$ ./OpenShellGates
Welcome to the Gates Of Shell. Type "exit" to quit.

[Go$H] | unknown@unknown:/home/SmartFridge/CLionProjects/atlas-simple_shell$ touch grass
[Go$H] | unknown@unknown:/home/SmartFridge/CLionProjects/atlas-simple_shell$ exit

The Gates Of Shell have closed. Goodbye.
[Go$H] | SmartFridge@fedora:/home/SmartFridge/CLionProjects/atlas-simple_shell$ ls
AUTHORS            colors.h           front_lawn  man_3_simple_shell  super-simple_shell
bashlist           custom_commands.c  grass       README.md           TestRunScript.bash
cmake-build-debug  env2.c             main.c      shellf_destruct.c
CMakeLists.txt     env.c              main.h      shell_loop.c
[Go$H] | SmartFridge@fedora:/home/SmartFridge/CLionProjects/atlas-simple_shell$ self-destruct
Segmentation fault
Shellf destruct mode activated.

5
4
3
2
1

The Gates Of Shell have closed. Goodbye.

SmartFridge@fedora:~/CLionProjects/atlas-simple_shell$ █
```

This shell is called the Gates of Shell. The prompt, `[Go$H] | SmartFridge@fedora:/home/SmartFridge/CLionProjects/atlas-simple_shell$ `,
consists of:
- `[Go$H]` (which stands for Gates of Shell) - helps differentiate the shell
from the real shell, as the rest of the prompt looks
identical to an Ubuntu prompt;
- `User` - the user's username or log name, taken from the environment variables
- `Hostname` or PC name - usually the user's Linux distro or the user's PC name
- `Path` - the current working directory
- `$` - end of prompt (not sure what to call this, but some shells may use
`:` or `#` instead)

**Custom Commands**
- exit - exits the shell
- quit - exits the shell
- selfdestr - activates self-destruct sequence, counts down from a
user-specified number, or 5 if unspecified, and then exits the shell
- self-destruct - activates self-destruct sequence, counts down from a
user-specified number, or 5 if unspecified, and then exits the shell
- env - prints the environment variables
- setenv - sets an environment variable
- unsetenv - deletes an environment variable

---

Back to Atlas Low Level Programming Readme:

[@Zytronium](https://github.com/Zytronium/atlas-low_level_programming?tab=readme-ov-file#c---simple-shell-but-not-io-task-number-7-right-1)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[@TheSnewby](https://github.com/TheSnewby/atlas-low_level_programming?tab=readme-ov-file#atlas-low_level_programming)
