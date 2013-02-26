Overview
----------------
P4Log is a utility meant to log wins/losses in Persona 4 Arena.  However, it's customizable enough that you can use it for any fighting game - or any game where you need to track wins in different matchups (or other set criteria).

Planned features (or another version of this tool) include features that would allow it to be used more widely for general data.  (see Future Additions.)

Usage
----------------
Basic:
./p4log 
  this will display the data table
./p4log < matchup > < win/loss >
  this will increment the relevant data and print the table, with changes
  for the < win/loss > arg, the program tests only if the arg begins with 'w,' which is counted as a win.  All other inputs will be counted as a loss.  Feel free to mash the keyboard in frustration upon losing.

Customization:
p4log.h contains any customization items.  If you'd like to log changes across different characters, I recommend changing the log file to the character's name.  (You can compile the binary to different outputs if you regularly play different characters.)

If you want to change the strings matchups are compared against, change the contents of filelines[].  This will also change the name displayed on the table.
Note that if you change this after initially creating a file, you may need to delete the file (or change the format of the current file manually) for changes to take effect.

Planned Additions/Todos
-----------------------

in the interest of making it friendly towards all data - 
todo: add single line queries
todo: add increment/decrement for each line (really needed if you can set each?)
todo: add ability to set value for each line

What I want the help to look like after all features:
./p4log - display full data table
./p4log < matchup > < w/l > - increment win or loss data for matchup (also displays full data table, with changes)
./p4log -c get < w/l > < matchup > - returns current value of wins/losses for matchup
./p4log -c set < w/l > < matchup > < n > - set wins/losses for matchup to n
./p4log -h - display this help

idea behind the '-c' flag is that current or future commands won't collide with row(matchup) names

possible todo: make spinoff tool where columns/rows are user defined as well, creating almost a command-line excel.
