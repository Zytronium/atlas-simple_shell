#include <stdlib.h>

int main(void)
{
	system("git config --global user.email \"dastelljes@outlook.com\"");
	system("git config --global user.name \"Daniel Stelljes\"");
	system("git add .");
	system("git commit -m \"testCommitFromWithinTheLiteralCustomShell\"");
	system("git push");
}
