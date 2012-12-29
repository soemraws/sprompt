NAME
----

sprompt - Prompt the user for a value with readline support

SYNOPSIS
--------

**sprompt** \[**-a** *char*\] \[**-b** *chars*\] \[**-q** *chars*\] \[**-i**\] \[**-f**\] \[*string*\]

DESCRIPTION
-----------

**sprompt** is a simple program that prompts the user for input, after
reading a list of newline-separated items from stdin. The user can enter
input using *readline* editing, and tab complete items in the list. The
selected value is written to standard output. Optionally, *string*
will be used to prompt the user for input. This program is useful
in shell scripts as a console user interface alternative to the
shell's built-in *read*.

OPTIONS
-------

**-a** *char*
The character *char* is automatically appended after tab completion. This
is typically a character that is in the list of characters that break words
(see **-b**). By default this is a space.

**-b** *chars*
The characters in *chars* will be assumed to break words for completion. The
default value of *readline* is used.

**-q** *chars*
The characters in *chars* will be assumed to be quote characters.

**-i**
Set tab completion to do case-insensitive matches.

**-f**
Use filename completion instead. **sprompt** will not read a list of
completion items from standard input. Moreover, the other options,
**-a**, **-b**, **-q** and **-i** should not be used.

AUTHOR
------

Sumant S. R. Oemrawsingh

SEE ALSO
--------

*readline*(3), *read*(1P)
