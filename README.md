# Simple Shell

##### Why was the shell always invited to computer parties?

###### Because it knew how to "grep" everyone's attention

---
A shell is a program that interprets and executes system commands,
like `ls`, `git commit`, or `rm -rf`. (Tip: ***never*** run `rm -rf`)
A shell should take text input; read and parse it; execute the command,
if valid; print output, if there is any; and repeat. You can navigate
a file system; create, edit, delete, and run files; and maybe even access
the internet using a shell. A couple examples of a shell are Bash and
PowerShell. Examples of things that may be confused with a shell, but 
are **not** are: the terminal/console, Vim, Ubuntu, or the Sandbox/VM. 

### Examples of this concept:

Example input/output:
```
Welcome to the Gates Of Shell. Type "help" for a list of commands. Type "exit" to quit.

/mnt/c/Users/Owner/CLionProjects/atlas-simple_shell$ ls la 
ls: cannot access 'la': No such file or directory
/mnt/c/Users/Owner/CLionProjects/atlas-simple_shell$ ls -la  
total 44
drwxrwxrwx 1 zytronium zytronium  4096 Jul 18 20:25 .
drwxrwxrwx 1 zytronium zytronium  4096 Jul 18 14:18 ..
drwxrwxrwx 1 zytronium zytronium  4096 Jul 18 20:17 .git
-rwxrwxrwx 1 zytronium zytronium    71 Jul 18 18:43 .gitignore
-rwxrwxrwx 1 zytronium zytronium  3687 Jul 18 14:18 README.md
-rwxrwxrwx 1 zytronium zytronium   218 Jul 18 19:51 TestRunScript.bash
-rwxrwxrwx 1 zytronium zytronium  3228 Jul 18 18:42 colors.h
-rwxrwxrwx 1 zytronium zytronium   632 Jul 18 18:44 main.c
-rwxrwxrwx 1 zytronium zytronium   509 Jul 18 18:46 main.h
-rwxrwxrwx 1 zytronium zytronium  4696 Jul 18 20:00 shell_loop.c
-rwxrwxrwx 1 zytronium zytronium   955 Jul 18 20:20 shellf_destruct.c
-rwxrwxrwx 1 zytronium zytronium 17048 Jul 18 20:25 testRun
/mnt/c/Users/Owner/CLionProjects/atlas-simple_shell$ touch grass
/mnt/c/Users/Owner/CLionProjects/atlas-simple_shell$ ls
CMakeLists.txt  TestRunScript.bash  colors.h  main.c  shell_loop.c       testRun
README.md       cmake-build-debug   grass     main.h  shellf_destruct.c
/mnt/c/Users/Owner/CLionProjects/atlas-simple_shell$ echo Hello, World! This is a simple shell
Hello, World! This is a simple shell
/mnt/c/Users/Owner/CLionProjects/atlas-simple_shell$ pwd 
/mnt/c/Users/Owner/CLionProjects/atlas-simple_shell
/mnt/c/Users/Owner/CLionProjects/atlas-simple_shell$ whoami
zytronium
/mnt/c/Users/Owner/CLionProjects/atlas-simple_shell$ █
```

###### Everything below (except the last two lines) is a placeholder.

```c
float primary(NULL)
{
	writef("Goodbye, user. I must terminate now."
		   "It's been a fun 3 milliseconds!\n");
	exit(RETURN_SUCCESS);
}

```


Back to Atlas Low Level Programming Readme:

[@Zytronium](https://github.com/Zytronium/atlas-low_level_programming?tab=readme-ov-file#c---simple-shell-but-not-io-task-number-7-right-1)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[@TheSnewby](https://github.com/TheSnewby/atlas-low_level_programming?tab=readme-ov-file#atlas-low_level_programming)
