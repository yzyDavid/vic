# TODO LIST

##cautions
###be careful on edge-checking!
###still have problem on backspace in insert mode.

##issues:
* insert mode may have problem against length = 0

* editing empty file and creating new file lead to segfault.

* backspace on first column should take care of cursor position.

##todo memo:
* get terminal lines on windows should be implements.
having bug, when adjusted the window size, error occurred.

* getchar / WIN32 API / getch
  all can be taken into consideration.

* implements menu bar

* implements new file. open/save file, etc.
save file and assigning file name is finished.
aiming to finish open file.

* take nano as a goal.

* new file, add chars and save has segfault.
needing more test.

* highlight string, comments, etc.
i don't wanna implement this function.

* redesign drawing methods
	cross platform should be considered.
	nearly finished, needing more test.

####below finished, curses are not taken.
* allowing resize window.
* ncurses can be taken into consideration.
