
# Minishell Tests

## Execution Tests

| Status| Test						| Bash						|
|-------|---------------------------|---------------------------|
| OK	|`ls`						|`ls` output				|							
| OK	|`/usr/bin/ls`				|bash: /usr/bin/ls: No such file or directory| 			
| OK	|`usr/bin/ls`				|no such file or dir		|							
| OK	|`./ls`						|no such file or dir		|			
| KO	|`hello`					|command not found			|	
| OK	|`/usr/bin/hello`			|no such file or dir		|		
| OK	|`./hello`					|no such file or dir		|		
| KO	|`""`						|command not found			|		
| KO	|`.`						|filename arg required		|		
| KO	|`..`						|`..`: command not found	|		
| KO	|`$`						|`$`: command not found		|	
| KO 	|`./`						|is a directory				|	
| KO	|`../`						|is a directory				|	
| KO	|`../existing_dir`			|is a directory				|	
| KO	|`../fake_dir`				|no such file or dir		|	
| OK	|`./Makefile`				|permission denied			|	
| OK	|`./does_not_exist`			|no such file or dir		|		
| OK	|`./minishell`				|executes new minishell		|	
| KO	|`minishell`				|command not found			|			
| KO	|`.minishell`				|command not found			|			

## CD

| Status| Test						| Bash								| 
|-------|---------------------------|-----------------------------------|
| 	|`cd ../../../../../..`		|`pwd` shows `/`						|							
| 	|`cd /home/user/`			|`pwd` shows `/home/user`				|						
| 	|`cd $HOME`					|`pwd` shows `/home/user`				|							
| 	|`cd $HOME/Documents`      	|`pwd` shows `/home/user/Documents`		|							
| 	|`unset HOME`, then `cd` 	|HOME not set							|							
| 	|`export HOME=` then `cd`	|No error msg							|							
| 	|`cd /t /w`					|Too many arguments						|							
| 	|`cd ./fakepath`			|No such directory						|							
| 	|`cd -`						|Return to OLDPWD, print CWD			|									
| 	|`unset OLDPWD`; `cd -`		|OLDPWD not set;						|							
|	|`mkdir a`; `mkdir a/b`; `cd a/b`; `rm -r ../../a`; `cd ..`			| 							  

## ECHO

| Status| Test						| Bash				| 
|-------|---------------------------|-------------------|
| OK	|`echo -n -n -nnnn -nnnnm`	|`-nnnnm`           |			
| OK	|`echo a	-nnnnma`		|`a -nnnnma`		|			
| KO	|`echo -n -nnn hello -n`	|`hello -n`			|			
| OK	|`echo a	hello -na`		|`a hello -na`		|			

## EXPORT

| Status| Test						| Bash								|
|-------|---------------------------|-----------------------------------|
| 	|`export ""`				|Not a valid identifier				|
| 	|`export 42`				|Not a valid identifier				|
| 	|`export =`					|Not a valid identifier				|
| 	|`export hello`				|`env \| grep hello` shows nothing	|
| 	|`export var=foo`			|`env \| grep var=` shows var		|
| 	|`export $var=test`			|`env \| grep foo=` shows `foo=test`|
| 	|`echo $var $foo`			|`foo test`							|
| 	|`export t="abc def"`		|`env \| grep t` shows `t=abc def`	|

## UNSET

| Status| Test							| Bash							| 
|-------|-------------------------------|-------------------------------|
| 	|`unset PATH`					|`echo $PATH` shows `(newline)`	|
| 	|`ls` (after `unset PATH`)		|No such file or directory		|
| 	|`unset "" test`				|Does nothing					|
| 	|`unset =`						|Does nothing					|
| 	|`unset FAKEVAR`				|Does nothing					|
| 	|`export var1=test`				|`env \| grep var` shows var1	|
| 	|`unset var` (following `var1`)	|Does not delete `var1`			|

## ENV

| Status| Test										| Bash				| 
|-------|-------------------------------------------|-------------------|
| 		|`env` then `export d=3 a=12 c=0` then `env`|					|				

## EXIT

| Status| Test							| Bash													| 
|-------|-------------------------------|-------------------------------------------------------|
| 	|`exit 10`						|exits shell											|
| 	|`exit -10`						|exits shell											|							
| 	|`exit abc`						|exits shell; error numeric arg required				|
| 	|`exit --10`					|exits shell; error numeric arg required				|
| 	|`exit ++10`					|exits shell; error numeric arg required				|
| 	|`exit abc 5`					|exits shell; error numeric arg required				|
| 	|`exit 5 abc`					|does not exit shell; too many args						|
| 	|`exit 5 < Makefile`			|exits shell											|
| 	|`exit 8 > test`				|exits shell; write exit to terminal, file empty		|
| 	|`ls \| exit`					|does not exit shell; no output							|
| 	|`ls \| exit 42`				|does not exit shell; no output							|
| 	|`ls \| exit 12 abc`			|does not exit shell; exit too many args				|
| 	|`ls \| exit abc 12`			|does not exit shell; exit numeric arg error			|
| 	|`exit \| ls`					|does not exit shell; `ls` output						|
| 	|`exit 42 \| ls`				|does not exit shell; `ls` output						|
| 	|`exit 12 abc \| ls`			|does not exit shell; exit too many args + `ls` output	|
| 	|`exit abc 12 \| ls`			|does not exit shell; exit numeric arg error + `ls` out	|
| 	|`ls > file \| exit`			|`ls` output in `file` (does not exit shell)			|
| 	|`sleep 5 \| exit`				|Sleeps 5 seconds (does not exit shell)					|
| 	|`ls -l > x \| exit \| wc -l`	|Output `0`; file `x` contains `ls` (no exit)			|
| 	|`exit \| ls`					|`ls` output (does not exit shell)						|
| 	|`exit 1 \| exit 0`				|Does nothing (does not exit shell)						|
| 	|`exit 0 \| exit 1`				|Does nothing (does not exit shell)						|

## Pipe tests

| Status| Test										| Bash									| 
|-------|-------------------------------------------|---------------------------------------|
| 	|`cat \| cat \| cat \| ls`					|`ls` output then hangs, `enter` 3 times|
| 	|`cat Makefile \| grep a \| wc -l \| cd x`	|No such file or directory				|
| 	|`cat Makefile \| grep a \| wc -l \| x`		|command not found						|
| 	|`echo test \|cat`							|`test`									|
| 	|`echo test \|\|\| cat`						|syntax error							|
| 	|`export A=1 B=2 C=3 D=4 E=5 F=6 G=7 H=8`	|`env` shows vars						|
| 	|`echo "$A'$B"'$C"$D'$E'"$F"'"'$G'$H"`		|`1'2$C"$D5"$F"'7'8`					|

## Variable Expansion Tests 
🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰

Leading and trailling spaces in the output are denoted with the `█` character.

| Status| Test					| Bash				| 
|-------|-----------------------|-------------------|
| 	OK	|`echo $USER`			|`username`			|					
| 	OK	|`echo $`				|`$`				|					
| 	❌  |`echo $""`				|`(newline)`		|				
|	KO	|`echo $$$USER`			|`26153username`	|					
|	KO	|`echo $$USER`			|`26153USER`		|					
| 	OK	|`echo $USER$USER`		|`usernameusername`	|					
| 	OK	|`echo $USER""$USER`	|`usernameusername`	|					
| 	OK	|`echo $USER" "$USER`	|`username username`|					
| 	KO	|`echo test$1test`		|`testtest`			|					
| 	OK	|`echo test$FAKE_VAR`	|`test`				|					
| 	OK	|`echo "$USER>>"`		|`username>>`		|					
| 	OK	|`echo "$USER11111ffjf"`|`(newline)`		|					
| 	OK(diff)	|`echo $\"echo`			|`$"echo`	|					
|  OK		|`echo "test$<test"`	|`test$<test`		|					
| OK	|`echo test$<test`		|test: no such file	|					
| KO	|`echo "test$-r"`		|`testhimBHsr`		|					
| KO	|`echo "test$-?"`		|`testhimBHs?`		|					
| 	KO	|`echo $-1$USER`		|`himBHs1username`	|					
| 	KO	|`echo $1`				|`(newline)`		|					
| 	KO	|`echo "$1"`			|`(newline)`		|					
| OK	|`echo $"USER"`			|`USER`				|					
| OK	|`echo $'USER'`			|`USER`				|					
| 	OK	|`echo $NULL test`		|`test`				|					
| 	OK	|`echo hello$USER`		|`hellousername`	|					
| 	OK	|`echo hello$USERtest`	|`hello`			|					
| 	OK	|`echo $USER.test`		|`username.test`	|					
|	OK	| `echo $0`				|					|					
| OK	| `echo "'$fake'"`		|	`''`			|					
| OK	| `echo """$fake"""`	| `(newline)`		|					
| OK	| `echo "'"$fake"'"`	| 	`''`			|					
| OK	| `echo '"'"$fake"'"'`	|	`""`			|					
| OK	| `echo $"fake"`		|	`fake`		|					

## Quote Handling Tests

Leading and trailling spaces in the output are denoted with the `█` character.

| Status| Test					| Bash				| 
|-------|-----------------------|-------------------|
|  OK  |`ec""ho test`			|`test` 			|			
| OK	|`""echo test`			|`test`				|				
| OK	|`echo"" test`			|`test`				|				
| OK 	|`echo "" test`			|`█test`			|		---->	
| OK	|`echo $USE""R`			|`R`				|			
| OK	|`echo ""$USER`			|`username`			|		
| OK	|`echo "$"USER`			|`$USER`			|			
| OK	|`echo  $""USER`		|`USER`				|				
| OK	|`ec''ho test`			|`test`				|				
| OK	|`''echo test`			|`test`				|				
| OK	|`echo'' test`			|`test`				|				
| OK 	|`echo '' test`			|`█test`			|			
| OK	|`echo $USE''R`			|`R`				|				
| OK	|`echo ''$USER`			|`username`			|			
| OK	|`echo '$'USER`			|`$USER`			|			
| OK	|`echo  $''USER`		|`USER`				|		
| OK	|`echo "" "" "" test`	|`███test`			|			
| OK	|`echo """""" test`		|`█test`			|			
| OK	|`echo $USER"" ''`		|`username`			|			
| OK	|`ls ""`				|ls: : No such file or directory|	
| OK	|`ls '"`				|syntax error msg	|	
| OK	|`ls "'`				|syntax error msg	|	
| OK	|`ls " "`				|ls:  : No such file or directory	| 
| OK	|`ls " ' "`				|ls:  ' : No such file or directory|				
| OK	|`"ls"`					|`ls` output	|					
| OK	|`l"s"`					|`ls` output	|	
| OK	|`ls"" -la`				|`ls -la` output		|	
| OK	|`ls "" -la`			|ls: : No such file or directory / ls: -la: No such file or directory	|
| OK	|`ls """"-la`			|`ls -la` output		|		
| OK	|`ls ""-la`				|`ls -la` normal output		|		
| OK	|`echo test""test`		|`testtest`			|		
| OK	|`echo test ""test`		|`test test`		|		
| OK	|`echo test "'"test`	|`test 'test`		|		
| OK	|`echo "\|" ls`			|`\| ls`			|			
| OK	|`echo "t \| es <>t"`	|`t \| es <>t`		|		
| OK	|`echo '"abc"'`			|`"abc"`			|			
| OK	|`echo '  "abc" '`		|`█"abc"█`			|	
| OK	|`echo "'abc'"`			|`'abc'`			|			
| OK	|`echo " $ " \| cat -e`	|`█$ $`				|	
| OK	|`echo $:$= \| cat -e`	|`$:$=$`			|	
| DIFF(exec)	|`export FOO=' " '`		|`env` shows `FOO`	|			
| DIFF	|`echo "$FOO" \| cat -e`|`$`				|	
| OK	|`echo "\x"`			|`\x`				|		
| OK	|`echo "\\x"`			|`\x`				|	
| OK	|`echo "\\\x"`			|`\\x`				|	
| OK	| `echo '"'"$fake"'"'`		|	`""`			|		


## Heredoc Tests
| Status| Test								| Bash							| 
|-------|-----------------------------------|-------------------------------|
| 	|`<< END cat`; `$USER$USER`; `END`	|`usernameusername`				|		
| 	|`<< END cat`; `$USER'$USER'`; `END`|`username'username'`			|		
| 	|`<< END cat`; `$USER"$USER"`; `END`|`username"username"`			|		
|  	|`<< END cat`; `$USER $USER`; `END`	|`username username`			|			
| 	|`<< END cat`; `helloEND`			|Heredoc keeps waiting for input|
| 	|`<< END cat`; `ENDhello`			|Heredoc keeps waiting for input|
| 	|`<< END cat`; `helloENDhello`		|Heredoc keeps waiting for input|						
| 	|`< Makefile cat \| << END cat`		|Heredoc + cat execute			|		
| 	|`export $VAR=test`					|`env` shows `VAR=test`			|			
| 	|`<< $VAR cat`; `$USER`; `$VAR`		|Heredoc ends with `$VAR` input	|	

## Redirection Tests
🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰 
| Status| Test					| Bash													|
|-------|-----------------------|-------------------------------------------------------|
| OK(parse)	|`< hello`				|hello: no such file or directory						|
| OK(parse)	|`cat <t`				|t: no such file or directory							|     			  	
| OK(parse)	|`> x`					|`x` file created empty									|									
| OK(parse)	|`< Ma < Makefile cat`	|Ma: no such file or directory (no cat output)			|												
| OK(parse)	|`<a cat <b <c`			|`cat` shows contents of file `c` only					|		
| OK(parse)	|`<a cat <b <c`			|`b: Permission denied`, does not show `c`				|		
| OK(parse)	|`>a cat <b >>c`		|Create empty `a`, `c` gets contents of `b` (because `cat<b` will output content of b)|		
| OK(parse)	|`>a ls >b >>c >d`		|`a`, `b`, `c`, `d` created, `ls` ouput only in `d`		|	
| OK(parse)	|`>a ls <e >>b >c`		|`e`: no such file; `a` created `b` and `c` not created	|			
| OK(parse)	|`cat -e >t1 <t2`		|`t2`: no such file; `t1` created						|			
| OK(parse)	|`echo 2 >o1 >>o2`		|`2` written to `o2`, `o1` empty						|		
| OK(parse)	|`echo 42 >o2 >>o1`		|`o1` contains `42`, `o2` empty							|				
| OK(parse)	|`echo hello > k\ 1`	|Creates file "`k 1`"									|	
| OK(parse)	|`echo test >f test1`	|Creates file `f` with contents `test test1`			|							
| OK(parse)	|`fakecmd hello > z`	|Command not found, file `z` created					|	
| OK(parse)	| `ls > a > b -l`		| create empty `a` and `b` with content of `ls -l`		|		
| OK(parse)	|`ls > p \| env > q`	|`p` contains `ls` output; `q` contains `env` output	|												
| OK(parse)	|`echo "File A" > a`	|Create file `a` with contents `File A`					|												
| OK(parse)	|`echo "File B" >> b`	|Create file `b` with contents `File B`					|											
| OK(parse)	|`echo File C >c`		|Create file `c` with contents `File C`					|												
| OK(parse)	|`chmod 000 b`			|Remove rights to `b` file								|					
| OK(parse)	|`chmod 644 b`; `rm a`	|Restore rights to `b` file, delete `a`					|			
| OK(parse)	|`rm a b c`				|Delete `a`, `b` and `c` files							|				
| OK(parse)	|`< Ma < Maa echo a`	| bash: Ma: No such file or directory + `echo a` don't get executed|	
| OK(parse)	|`echo a < Ma < Maa`	| bash: Ma: No such file or directory + `echo a` don't get executed|	
| OK(parse)	| `echo hello < txt sweetie` (txt exist)	| `hello sweetie` |					
|			| `ls > e \| cat<e`  | bash: e: No such file or directory + `e` created with content of ls |		
|			| `cat<f \| ls >f`			|	bash: f: No such file or directory + `f` get created with ls content |	
|			| `echo hello > a \| echo fuck > a` | behavior change; sometimes a contains `hello` sometimes `fuck` |	
|			| `echo hello > a > b \| echo fuck >b` | `a` and `b` created b contains hello, b doesn't get overwritten |	
|			| ` echo hello > b\| echo ddd>> b` | `b` created b contains hello, b doesn't get overwritten |		

## Signal Tests
| Status| Test						| Bash								| 
|-------|---------------------------|-----------------------------------|
| 	|`ctrl+c`					|`^C` + new prompt on new line		|	| 
| 	|`abc` + `ctrl + c`			|`abc^C` + new prompt				|				
| 	|`ctrl+d`					|print `exit` + exit shell			|			
| 	|`abc` + `ctrl+d`			|does nothing						|					
| 	|`ctrl+\`					|does nothing						|						
| 	|`abc` + `ctrl+\`			|does nothing						|						
| 	|`cat` + `enter` + `ctrl+c`	|interrupt cat; do not quit shell	|	
| 	|`cat` + `enter` + `ctrl+d`	|quit cat; do not quit shell		|		
| 	|`cat` + `enter` + `ctrl+\`	|quit cat; do not kill shell		|		

🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰🔰 
## Other Syntax Error Tests
| Status| Test						| Bash						| 
|-------|---------------------------|---------------------------|
| OK	|`\|`						|syntax error near `\|`		|
| OK	|`ls \|`					|syntax unexpected EOF		|
| OK	|`ls < \|`					|syntax error near `\|`		|		
| OK	|`ls << \|`					|syntax error near `\|`		|		
| OK	|`ls > \|`					|syntax error near `\|`		|		
| OK	|`ls >> \|`					|syntax error near `\|`		|	
| OK	|`ls \| <`					|syntax error near `newline`|	
| OK	|`ls \| <<`					|syntax error near `newline`|		
| OK	|`ls \| >`					|syntax error near `newline`|		
| OK	|`ls \| >>`					|syntax error near `newline`|		
| OK	|`ls >> >`					|syntax error near `>`		|		
| OK	|`ls > >>`					|syntax error near `>>`		|		
| OK	|`ls << <`					|syntax error near `<`		|		
| OK	|`ls < <<`					|syntax error near `<<`		|		
| OK	|`ls > >> \|`				|syntax error near `>>`		|		
| OK	|`ls >>`					|syntax error near `newline`|		
| OK	|`echo test > > out`		|syntax error near `>`		|		
| OK	|`echo test >> > out`		|syntax error near `>`		|		
| OK	|`echo hello > $fakevar`	|ambiguous redirect			|		
| OK	|`echo hello >> $fakevar`	|ambiguous redirect			|			
| OK	|`echo hello < $fakevar`	|ambiguous redirect			|			
| OK	|`cat < $fakevar`			|ambiguous redirect			|		
| OK	|`echo hello > $realvar`	|write to var file			|		
| OK	|`echo hello >> $realvar`	|append to var file			|		
| OK	|`< $realvar cat`			|read from var file			|		
| 	|`export t="abc def"`		|`env` shows `t=abc def`	|	| 
| OK	|`echo test > $t"`			|bash: unexpected EOF while looking for matching `"' bash ..|				
| OK	|`echo test > "$t"`			|write to file `"abc def"`	|		
| OK	|`echo hello >>> test`		|syntax error near `>`		|
| OK	|`echo hello \| \|`			|syntax error near `\|`		|
| 	|`echo hello \|;`			|syntax error near `;`		|		
| OK	|`echo\ a`					|`echo a` cmd not found		|	
|OK	|`<`						|							|	
|OK	|`<<`						|							|			
|OK	|`<<<`							|							|
|OK	| `<<<<`						|							|
|OK	| `>`							|							|	
|OK	| `>>`							|							|
|OK	| `>>>`							|							|
|OK	| `>>>`							|							|	

## Other Exit Status Tests
| Status| Test					| Bash						|
|-------|-----------------------|---------------------------|
| 	|`fake_cmd`				|Command not found			|
| 	|`ls not_a_path`		|No such file or dir		|
| 	|`./not_executable_file`|Permission denied			|
| 	|`cat clac 3`			|2 error msg				|
| 	|`cd $?`				|Number: no such file or dir|
| 	|`cat \|\|\|`			|syntax error				|
| 	|`echo "hell`			|unexpected EOF + syntax	|
