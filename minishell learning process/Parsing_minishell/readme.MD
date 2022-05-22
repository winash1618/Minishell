# Parsing
## List all the set of possible commands:
- echo -n "some string"
- echo -n stringwithoutquotesshouldhavenospaces
- echo "some string"
- echo stringwithoutquotesshouldhavenospaces
- cd
- cd [path]
- pwd
- export backup=”/nas10/mysql”
- unset $(backup)
- env 
- export VAR=abc
- export VARNAME="my value"
- MYDEPT=Sales
- export $(MYDEPT)
- env 
- exit
- echo -n
- cat 
- echo "End of directory listing" >> allmyfiles.txt
- ls > allmyfiles.txt
- var="100 hi dfasdf"
- echo $var
- echo "$var"
- echo $(var) //Wrong way
- my="bye"
- echo $var $my
- echo "$var $my"
- var="100 hi""dfsdf "
- echo $var
- 100 hi dfsdf //output

## errors
- ls >> 
	- (zsh: parse error near `\n')
- cat <<
	- (zsh: parse error near `\n')
