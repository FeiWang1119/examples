# Bash Navigation

| Shortcut           | description                                                                       |
| ------------------ | --------------------------------------------------------------------------------- |
| Ctrl + A           | Move to the start of the command line                                             |
| Ctrl + E           | Move to the end of the command line                                               |
| Ctrl + F           | Move one character forward                                                        |
| Ctrl + B           | Move one character backward                                                       |
| Ctrl + XX          | Switch cursor position between start of the command line and the current position |
| Ctrl + ] + x       | Moves the cursor forward to next occurrence of x                                  |
| Alt + F / Esc + F  | Moves the cursor one word forward                                                 |
| Alt + B / Esc + B  | Moves the cursor one word backward                                                |
| Alt + Ctrl + ] + x | Moves cursor to the previous occurrence of x                                      |

# Bash Control/Process

| Shortcut | description                                                       |
| -------- | ----------------------------------------------------------------- |
| Ctrl + L | Similar to clear command, clears the terminal screen              |
| Ctrl + S | Stops command output to the screen                                |
| Ctrl + Z | Suspends current command execution and moves it to the background |
| Ctrl + Q | Resumes suspended command                                         |
| Ctrl + C | Sends SIGI signal and kills currently executing command           |
| Ctrl + D | Closes the current terminal                                       |

# Bash History

| Shortcut              | description                                                          |
| --------------------- | -------------------------------------------------------------------- |
| Ctrl + R              | Incremental reverse search of bash history                           |
| Alt + P               | Non-incremental reverse search of bash history                       |
| Ctrl + J              | Ends history search at current command                               |
| Ctrl + _              | Undo previous command                                                |
| Ctrl + P / Up arrow   | Moves to previous command                                            |
| Ctrl + N / Down arrow | Moves to next command                                                |
| Ctrl + S              | Gets the next most recent command                                    |
| Ctrl + O              | Runs and re-enters the command found via Ctrl + S and Ctrl + R       |
| Ctrl + G              | Exits history search mode                                            |
| !!                    | Runs last command                                                    |
| !*                    | Runs previous command except its first word                          |
| !*:p                  | Displays what !* substitutes                                         |
| !x                    | Runs recent command in the bash history that begins with x           |
| !x:p                  | Displays the x command and adds it as the recent command in history  |
| !$                    | Same as OPTION+., brings forth last argument of the previous command |
| !^                    | Substitutes first argument of last command in the current command    |
| !$:p                  | Displays the word that !$ substitutes                                |
| ^123^abc              | Replaces 123 with abc                                                |
| !n:m                  | Repeats argument within a range (i.e, m 2-3)                         |
| !fi                   | Repeats latest command in history that begins with fi                |
| !n                    | Run nth command from the bash history                                |
| !n:p                  | Prints the command !n executes                                       |
| !n:$                  | Repeat arguments from the last command (i.e, from argument n to $)   |

# Bash Editing

| Shortcut         | description                                            |
| ---------------- | ------------------------------------------------------ |
| Ctrl + U         | Cuts before the cursor until the start of the command  |
| Ctrl + K         | Cuts after the cursor until the end of the command     |
| Ctrl + Y         | Paste the last cut text                                |
| Alt + y          | Paste the second most recent cut text                  |
| Ctrl + W         | Removes the command/argument before the cursor         |
| Ctrl + D         | Removes the character under the cursor                 |
| Ctrl + H         | Removes character before the cursor                    |
| Alt + D          | Removes from the character until the end of the word   |
| Alt + Backspace  | Removes from the character until the start of the word |
| Alt + . / Esc+.  | Uses last argument of previous command                 |
| Alt + <          | Moves to the first line of the bash history            |
| Alt + >          | Moves to the last line of the bash history             |
| Esc + T          | Switch between last two words before cursor            |
| Alt + T          | Switches current word with the previous                |
| Ctrl + shift + - | Undo the last change                                   |

# Bash Information

| Shortcut | description                                            |
| -------- | ------------------------------------------------------ |
| TAB      | Autocompletes the command or file/directory name       |
| ~TAB TAB | List all Linux users                                   |
| Ctrl + I | Completes the command like TAB                         |
| Alt + ?  | Display files/folders in the current path for help     |
| Alt + *  | Display files/folders in the current path as parameter |

# Process Control Shortcuts

| Shortcut | description                                                                                  |
| -------- | -------------------------------------------------------------------------------------------- |
| Ctrl + C | Send the SIGINT signal to the current foreground process, usually resulting in termination   |
| Ctrl + Z | Send the SIGTSTP signal to the current foreground process, suspending its execution          |
| Ctrl + D | Send an EOF (End of File) to the current process, usually resulting in termination or logout |
| Ctrl + S | Pause the output to the terminal (useful when scrolling through large amounts of output)     |
| Ctrl + Q | Resume output to the terminal after pausing with Ctrl + s                                    |
| bg       | Resume a suspended process in the background                                                 |
| fg       | Resume a suspended process in the foreground                                                 |

# Miscellaneous Shortcuts

| Shortcut | description                                                 |
| -------- | ----------------------------------------------------------- |
| Ctrl + T | Transpose (swap) the characters before and under the cursor |
| Alt + T  | Transpose (swap) the words before and under the cursor      |
| Alt + U  | Uppercase the word from the cursor to the end of the word   |
| Alt + L  | Lowercase the word from the cursor to the  end of the word  |