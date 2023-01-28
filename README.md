<h1 align="center">
	📖 minishell - 42 Project
</h1>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/abdeljalil-salhi/minishell?color=lightblue" />
	<img alt="Number of lines of code" src="https://img.shields.io/tokei/lines/github/abdeljalil-salhi/minishell?color=critical" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/abdeljalil-salhi/minishell?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/abdeljalil-salhi/minishell?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/abdeljalil-salhi/minishell?color=green" />
</p>

---

# parsing : 90%
 - handle (ctrl+C , ctrl+D , ctrl+\) signals
 - lexical analyse (split input into : words, special characteres('>' '<' '(' ')' '|' '&' ))
 - check for syntax errors (unclosed quotes, invalid form of ">> << > < && || |", ......)
 - initialize proc linked list and rdirections list
 - get commands absolute path
 - open files and get file descriptors
 - remove unneccesery quotes and expand environement values
 - clear function (free allocated memory)
 - BULITINS (for execution part);

# execution : 30%
 - [X] execute commands
 - [X] execute builtins
 - [X] pipes
 - [ ] redirections
 - [ ] AND
 - [ ] OR
 - [ ] semicolon
 - [ ] wildcards
 - [ ] priorities
 - [X] history
 - [ ] aliases
