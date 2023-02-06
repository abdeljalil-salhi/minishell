<h1 align="center">
	📖 minishell - 42 Project
</h1>

<p align="center">
    <a href="https://projects.intra.42.fr/projects/42cursus-minishell/projects_users/2933758" alt="absalhi's minishell">
        <img src="https://user-images.githubusercontent.com/65598953/216946380-4573b9e1-aecf-47be-98a5-269c7d051166.png" alt="minishell" />
    </a>
    <br />
    <a href="https://projects.intra.42.fr/projects/42cursus-minishell/projects_users/2933758">
        <img src="https://badge42.vercel.app/api/v2/cl9iseqxd00640gl9mg4g0mxp/project/2933758" alt="absalhi's 42 minishell Score" />
    </a>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/abdeljalil-salhi/minishell?color=lightblue" />
	<img alt="Number of lines of code" src="https://img.shields.io/tokei/lines/github/abdeljalil-salhi/minishell?color=critical" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/abdeljalil-salhi/minishell?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/abdeljalil-salhi/minishell?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/abdeljalil-salhi/minishell?color=green" />
</p>

---

<p align="center">
	<img src="https://user-images.githubusercontent.com/65598953/216952972-65becc16-bb71-40a1-aac0-de4c0e0824c3.png" width="500" alt="My minishell :3" />
</p>

## Table of Contents

- [minishell - 42 project](#minishell-42-project)
  * [Introduction](#introduction)
  * [Features](#features)
  * [Quoting](#quoting)
  * [Token recognition](#token-recognition)
  * [Tokens execution](#tokens-execution)
  * [Exit status](#exit-status)
  * [Signals](#signals)
  * [Pipelines](#pipelines)
  * [AND-OR Lists](#and-or-lists)
  * [Parentheses](#parentheses)
  * [Conclusion](#conclusion)

## Introduction

The goal of this project is to create a simple shell. The shell is the command-line interpreter that provides a traditional Unix-like command line user interface. The shell operates according to the following general overview of operations:

1. The shell reads its input from a file, from the **-c** option or from the __*system()*__ and __*popen()*__ functions, _(you won't need the last ones but good to know anyway)_.

2. The shell breaks the input into **tokens**: words and operators.

3. The shell parses the input into [**simple commands**](https://www.gnu.org/software/bash/manual/html_node/Simple-Commands.html) and [**compound commands**](https://www.gnu.org/software/bash/manual/html_node/Compound-Commands.html#:~:text=In%20most%20cases%20a%20list,execute%20them%20as%20a%20unit.).

4. The shell perfoms various [**expansions**](https://www.gnu.org/software/bash/manual/html_node/Shell-Expansions.html) _(separately)_ on different parts of each command, resulting in a list of pathnames and fields to be treated as a command and arguments

5. The shell perfoms [**redirections**](https://www.gnu.org/software/bash/manual/html_node/Redirections.html) and removes redirection operators and their operands from the parameter list.

6. The shell executes a function _(otherly known as [**function definition commands**](https://www.gnu.org/software/bash/manual/html_node/Shell-Functions.html))_, [**builtin**](https://www.gnu.org/software/bash/manual/html_node/Bash-Builtins.html) command, executable file, or script, giving the names of the arguments as positional parameters numbered from **1** to **n**, and the name of the command _(or in the case of a function within a script, the name of the script)_ as the positional parameter numbered **0** _(see [**command search and execution**](https://www.gnu.org/software/bash/manual/html_node/Command-Search-and-Execution.html))_.

7. The shell waits for the command to complete, and then collects the **exit status** of the last executed child process _(see [**exit status**](https://www.gnu.org/software/bash/manual/html_node/Exit-Status.html))_.

---

<p align="center">
	<img src="https://user-images.githubusercontent.com/65598953/217110452-a3dc8e9a-54a9-46d9-9f15-3e97cd2f27ee.png" width="500" alt="Shell" />
</p>

## Features

- [x] **Builtins**:
	- [x] `echo`
	- [x] `cd`
	- [x] `pwd`
	- [x] `export`
	- [x] `unset`
	- [x] `env`
	- [x] `exit`

- [x] **Redirections**:
	- [x] `>`
	- [x] `<`
	- [x] `>>`
	- [x] `<<`

- [x] **Pipes**:
	- [x] `|`

- [x] **Environment variables**:
	- [x] `$ENV_VAR`
	- [x] `$?`

- [x] **Quotes**:
	- [x] `'`
	- [x] `"`
	- [x] `"'`
	- [x] `'"`

- [x] **Wildcards**:
	- [x] `*`

- [x] **Priority**:
	- [x] `()`
	- [x] `&&`
	- [x] `||`

- [x] **Signals**:
	- [x] `Ctrl-C`
	- [x] `Ctrl-D`
	- [x] `Ctrl-\`

- [x] **History**:
	- [x] `Up arrow`
	- [x] `Down arrow`

- [x] **Autocompletion**:
	- [x] `Tab`

- [x] **Complete error handling**

- [x] **ZSH-like prompt**

---

<p align="center">
	<img src="https://user-images.githubusercontent.com/65598953/217110917-21289b92-9920-4a56-bb2d-c3f8e760a9f5.png" width="500" alt="Shell quoting" />
	<br />
	<i>A quote by a shell, because you know... ~shell quotes :v</i>
</p>

## Quoting

Quoting is a way to tell the shell to treat a sequence of characters as a single word. The shell uses the following rules to determine how to interpret the characters in a word:

- If the first character of a word is a **single-quote** (`'`), all characters of the word are taken literally, except for **single-quote** itself. A **single-quote** may not occur between single-quotes, even when preceded by a backslash (`\`).

- If the first character of a word is a **double-quote** (`"`), the shell does not treat any characters specially. The only exception is that **double-quote** must be matched. Within double-quotes, the backslash retains its special meaning as an escape character. A **double-quote** may be quoted within double-quotes by preceding it with a backslash.

- If the first character of a word is neither a **single-quote** nor a **double-quote**, the shell treats each character of the word as a potential **metacharacter**. These are some of the metacharacters:

	- `|` - The **pipe** character. The shell uses the **pipe** character to separate commands in a **pipeline**.

	- `&` - The **ampersand** character. The shell uses the **ampersand** character to separate commands in a **list**.

	- `<` - The **less-than** character. The shell uses the **less-than** character to redirect **input**.

	- `>` - The **greater-than** character. The shell uses the **greater-than** character to redirect **output**.

	- `<<` - The **less-than** character followed by the **less-than** character. The shell uses the **less-than** character followed by the **less-than** character to declare a [**here-document**](https://linuxize.com/post/bash-heredoc/).

	- `>>` - The **greater-than** character followed by the **greater-than** character. The shell uses the **greater-than** character followed by the **greater-than** character to redirect **output** in **APPEND** mode.

	- `&&` - The **ampersand** character followed by the **ampersand** character. The shell uses the **ampersand** character followed by the **ampersand** character to separate commands in a **list** and to execute the second command only if the first command returns an exit status of zero.

	- `||` - The **vertical bar** character followed by the **vertical bar** character. The shell uses the **vertical bar** character followed by the **vertical bar** character to separate commands in a **list** and to execute the second command only if the first command returns a non-zero exit status.

	- `;` - The **semicolon** character. The shell uses the **semicolon** character to separate commands in a **list** and to execute the second command regardless of the exit status of the first command.

	- `(` - The **left parenthesis** character. The shell uses the **left parenthesis** character to group commands for the purposes of **control operators**.

	- `)` - The **right parenthesis** character. The shell uses the **right parenthesis** character to end a group started with a **left parenthesis** character.

	- `$` - The **dollar sign** character. The shell uses the **dollar sign** character to introduce a **variable reference**.

	- `` ` `` - The **backquote** character. The shell uses the **backquote** character to introduce a **command substitution**.

	- `\` - The **backslash** character. The shell uses the **backslash** character to quote the next character in a word or to introduce a **backslash-escaped** character.

	- `#` - The **hash mark** character. The shell uses the **hash mark** character to introduce a comment when it is the first character of a word.

	- `=` - The **equal sign** character. The shell uses the **equal sign** character to introduce a **variable assignment**.

	- `*` - The **asterisk** character. The shell uses the **asterisk** character to introduce a **globbing pattern**, it is used to search for a particular character(s) for zero or more times.

	- `?` - The **question mark** character. The shell uses the **question mark** character to introduce a **globbing pattern**, it is used to search for a fixed number of characters where each question mark `?` indicates each character.

- If the first character of a word is neither a **single-quote** nor a **double-quote**, and the word contains no **metacharacters**, the shell treats the entire word as a **simple word**.

- If the first character of a word is neither a **single-quote** nor a **double-quote**, and the word contains **metacharacters**, the shell treats the entire word as a **compound word**.

All being said, the various quoting mechanisms are the escape character, single-quotes, and double-quotes. The here-document represents another form of quoting; however, it is not a quoting mechanism in the sense that it does not affect the interpretation of the characters in the here-document. The here-document is a way to feed input to a command.

---

<p align="center">
	<img src="https://user-images.githubusercontent.com/65598953/217112077-cf52c8b7-a64f-45bf-8664-f3fda12b59dc.png" width="500" alt="Shell token - 1909" />
	<br />
	<i>A shell token from ~1909...</i>
</p>

## Token recognition

The shell shall read its input in terms of lines from a file, from a terminal in the case of an interactive shell, or from a string in the case of `sh -c` or `system()`. The input lines can be of unlimited length. These lines shall be parsed using two major modes: **ordinary token recognition** and processing of **here-documents**.

When a **heredoc** token has been recognized, one or more of the subsequent lines immediately following the next NEWLINE token form the body of one or more here-documents and shall be parsed according to the rules of the here-document:

- The redirection operators `<<` and `<<-` both allow redirection of lines contained in a shell input file, known as a **"here-document"**, to the input of a command; the difference is that `<<` does not remove leading tab characters from input lines, while `<<`- does. The here-document shall be treated as a single word that begins after the next newline `\n` and continues until there is a line containing only the **DELIMITER** and a newline `\n`, with no blanks in between. Then the next here-document starts, if there is one. The format of the here-document is `cmd << DELIMITER` or `cmd <<- DELIMITER`.

- If any character in the **DELIMITER** is quoted, the delimiter shall be formed by performing quote removal on it, and the here-document lines shall not be expanded. Otherwise, the delimiter should be the same as the one specified, and the here-document lines shall be expanded _(if we write `$PATH` in the here-document lines, it will be expanded to the actual value of `PATH` in `env`)_. The **DELIMITER** shall not be expanded.

When it is not in the middle of processing a here-document, the shell shall parse the input line into tokens;

- A **token** is a sequence of one or more characters that is recognized as a single unit by the shell. The shell shall recognize the following tokens:

	- **NEWLINE** - A newline character. The shell shall recognize a newline character as a token.

	- **WORD** - A sequence of characters that is not a **NEWLINE** or a **SHELL METACHARACTER**. The shell shall recognize a sequence of characters that is not a **NEWLINE** or a **SHELL METACHARACTER** as a token.

	- **SHELL METACHARACTER** - A character that has a special meaning to the shell. The shell shall recognize the characters mentionned previously as **SHELL METACHARACTERS**.

- If the end of input is recognized, the current token shall be delimited. If there is no current token, the end-of-input indicator shall be returned as the token.

- If the previous character was used as part of an operator and the current character is not quoted and can be used with the current characters to form an operator, it shall be used as part of that (operator) token.

- If the previous character was used as part of an operator and the current character cannot be used with the current characters to form an operator, the operator containing the previous character shall be delimited.

- If the current character is backslash, single-quote, or double-quote ( `\`, `"`, or `'` ) and it is not quoted, it shall affect quoting for subsequent characters up to the end of the quoted text. The rules for quoting are as described in [Quoting](#quoting). During token recognition no substitutions shall be actually performed, and the result token shall contain exactly the characters that appear in the input, unmodified, including any embedded or enclosing quotes or substitution operators, between the quote mark and the end of the quoted text. The token shall not be delimited by the end of the quoted field.

- If the current character is not quoted and can be used as the first character of a new operator, the current token (if any) shall be delimited. The current character shall be used as the beginning of the next (operator) token.

- If the current character is an unquoted newline `\n`, the current token shall be delimited.

- If the current character is an unquoted blank, any token containing the previous character is delimited and the current character shall be discarded.

- If the previous character was part of a word, the current character shall be appended to that word.

- If the current character is a `#`, it and all subsequent characters up to, but excluding, the next newline `\n` shall be discarded as a comment. The newline `\n` that ends the line is not considered part of the comment.

- The current character is used as the start of a new word.

Once a token is delimited, it is categorized as required, this is my token enum:

```c
enum e_token
{
	RIGHT_ARROW = '>',
	LEFT_ARROW = '<',
	PIPE = '|',
	DOLLAR_SIGN = '$',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '"',
	SPACE = ' ',
	TAB = '\t',
	QUESTION_MARK = '?',
	AMPERSAND = '&',
	OPEN_PARENTHESIS = '(',
	CLOSE_PARENTHESIS = ')',
	ASTERISK = '*',
};
```

## Tokens execution

After getting the tokens, the shell shall execute the command. The shell shall execute the command by performing the following steps:

- The shell shall go through the tokens and check if there is a **here-document**. If there is, the shell shall execute the here-document by performing the following steps:

	- The shell shall check if the **DELIMITER** is a **WORD**. If it is, the shell shall execute the **WORD**.

	- If the **DELIMITER** is not a **WORD**, the shell shall print an error message.

- The shell shall go through the tokens and check if there is any `command not found` error. If there is, the shell shall print an error message.

- The shell shall check if the command is a **built-in** command. If it is, the shell shall execute the built-in command on the main process, and the shell shall not fork. If it is piped, the shell shall fork and execute the command on the child process.

- If the command is not a built-in command, it looks for the command in the **PATH**. The shell shall execute the command by performing the following steps:

	- The shell shall check if the command is a **shell script**. If it is, the shell shall execute the shell script.

	- If the command is not a shell script, the shell shall check if the command is a **binary**. If it is, the shell shall execute the binary.

	- If the command is not a binary, the shell shall print an error message.

- When executing the command, the shell shall check if there is a redirection. If there is, the shell shall perform the redirection by performing the following steps:

	- The shell shall check if the redirection is a **input/here-document redirection**. If it is, the shell shall perform the input redirection by duplicating the file descriptor of the standard input to the file descriptor of the file specified in the redirection.

	- If the redirection is not a input redirection, the shell shall check if the redirection is a **output/append redirection**. If it is, the shell shall perform the output/append redirection by duplicating the file descriptor of the standard output to the file descriptor of the file specified in the redirection.

---

<p align="center">
	<img src="https://thumbs.gfycat.com/TallConcernedGrouper-max-1mb.gif" width="500"/>
</p>

## Exit status

The shell shall return the exit status of the last command executed. If the last command is completed successfully, the shell shall return zero. If the last command is not completed successfully, the shell shall return a non-zero value.

The exit status can be retrieved by using the `waitpid` function. The `waitpid` function shall wait for a child process to change state and return the exit status of the child process. You can use the following macros to achieve this:

```c
/*
	Evaluates to a non-zero value if status was returned for a child process that terminated normally.
*/
WIFEXITED(stat_val)
/*
	If the value of WIFEXITED(stat_val) is non-zero, this macro evaluates to the low-order 8 bits of the status argument that the child process passed to _exit() or exit(), or the value the child process returned from main().
*/
WEXITSTATUS(stat_val)

/*
	Evaluates to a non-zero value if status was returned for a child process that terminated due to the receipt of a signal that was not caught.
*/
WIFSIGNALED(stat_val)
/*
	If the value of WIFSIGNALED(stat_val) is non-zero, this macro evaluates to the number of the signal that caused the termination of the child process.
*/
WTERMSIG(stat_val)
```

## Signals

The shell shall handle the following signals:

- `SIGINT` - The shell shall print a new line and return to the prompt.

- `SIGQUIT` - The shell shall ignore the signal, except when the shell is executing a blocking command _(like `cat`, `grep`)_.

## Pipelines

The shell shall support pipelines. A pipeline is a sequence of one or more commands separated by one or more operators of the form `|`. The standard output of all but the last command shall be connected to the standard input of the next command.

The format of a pipeline is:

```c
command1 | command2 | command3 | ... | commandN
```

The standard output of `command1` shall be connected to the standard input of `command2`. The standard input, standard output, or both of a command shall be considered to be assigned by the pipeline before any redirection specified by redirection operators that are part of the command.

## AND-OR Lists

The shell shall support AND-OR lists. An AND-OR list is a sequence of one or more pipelines separated by one or more operators of the form `&&` or `||`. The AND-OR list shall be executed left to right.

The operators `&&` and `||` shall have equal precedence and shall be evaluated with left associativity. For example, both of the following commands write solely `bar` to standard output:

```bash
false && echo foo || echo bar
true || echo foo && echo bar
```

A `;` or newline `\n` terminator shall cause the preceding AND-OR list to be executed sequentially; an `&` shall cause asynchronous execution of the preceding AND-OR list.

## Parentheses

The shell shall support parentheses. A group is a sequence of one or more commands enclosed in parentheses. The group shall be executed as a command.

This the way I interpret the parentheses:

<p align="center">
	<img src="https://user-images.githubusercontent.com/65598953/217078098-ff74ea95-c652-4c15-9fe4-35beea00e3ed.png" />
</p>

Each outer parentheses represent a group, and each inner parentheses represent a sub-group. Giving each of them a level, with the outer commands being in the **level 01**, and the inner commands being in the **level 02**, and so on...

---

<p align="center">
	<img src="https://i.pinimg.com/originals/22/d7/a7/22d7a7c0eee4f44de655e484301b482d.gif" />
</p>

## Conclusion

Well, the minishell project is a challenging and rewarding experience that allows students to dive deep into the intricacies of system programming. By building a functional shell from scratch, students are able to understand the complexities of how the command line interface works and the role it plays in operating systems. The project provides hands-on experience with various concepts such as process management, environment variables, and file redirection, making it an essential component of a solid understanding of system programming.

I hope this guide helped you understand how a shell works. If you have any questions, feel free to ask them in the comments. If you want to contribute to this guide, feel free to open a pull request.

---

Made by **absalhi**: absalhi@student.1337.ma

[![Hits](https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2Fabdeljalil-salhi%2Fminishell&count_bg=%23C83D3D&title_bg=%23555555&icon=&icon_color=%23E7E7E7&title=REPO+VIEWS&edge_flat=true)](https://github.com/abdeljalil-salhi)
