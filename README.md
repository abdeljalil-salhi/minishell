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

# parsing : 95%
 - [X] handle (ctrl+C , ctrl+D , ctrl+\) signals
 - [X] lexical analyse (split input into : words, special characteres('>' '<' '(' ')' '|' '&' ))
 - [X] check for syntax errors (unclosed quotes, invalid form of ">> << > < && || |", ......)
 - [X] initialize proc linked list and rdirections list
 - [X] get commands absolute path
 - [X] open files and get file descriptors
 - [X] remove unneccesery quotes and expand environement values
 - [X] clear function (free allocated memory)
 - [X] BULITINS (for execution part);
 - [X] wildcards

# execution : 95%
 - [X] execute commands
 - [X] execute builtins
 - [X] pipes
 - [X] redirections
 - [X] AND
 - [X] OR
 - [X] priorities
 - [X] history

 # EXTRA : 30%
 - [X] ZSH prompt
 - [ ] semicolon
 - [ ] aliases

## to-fix
- [X] fix leaks
- [X] piped builtins
