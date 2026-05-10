Made my Alex Gkiafis sdi2200284

Just type make to compile, then run my_program from inside the build folder.

For a list of available commands you can type help.

My program is made to work similar to a game. You make changes, then when you are done you can type end season to have all students
have the exams, then you can view the results and stuff, then when you are ready you can type next season to start a new season. You
will need to register students to new courses and when you are ready end season again. Repeat this as much time as you like. To graduate
one needs to pass all mandatory courses and collect 30% of the points that the optional courses sum up to. You can use import to import
from file and I have a few testing files there so you can see what the format should be like.

This project turned out a little big, I tried taking into account as many stuff as possible, trying to predict possible false inputs the
user could try, whenever an entity is updated I try to also update it's relationship with all other entities. For example, if a course
changes semester I check if any of the students that were taking that class can no longer take the class because of their year and if
they cant I update them. Also try to fix all relationship when I delete instances too. But it is possible I may have missed something,
I performed few tests and everything seems to work alright though.