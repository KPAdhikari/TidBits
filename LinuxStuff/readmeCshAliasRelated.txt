Trying to make evio2hipo conversion work simpler so that I can only use ‘e2h name.evio’:
* Following removes the filename extension and returns the name only:  (Source: https://stackoverflow.com/questions/12152626/how-can-i-remove-the-extension-of-a-filename-in-a-shell-script)

  echo foo.txt | rev | cut -f 2- -d '.' | rev

* Following defines an alias to which I can pass two args:
    * alias kpShow 'echo -i \!:1 -o \!:2' (Source: https://docstore.mik.ua/orelly/unix3/upt/ch29_03.htm)

* Success:
Finally, going through several other webpages and then ultimately coming down to this page (https://www.cyberciti.biz/faq/bash-get-filename-from-given-path-on-linux-or-unix/) for ‘basename’ command which works both on bash and csh, I came up with a shorter and easier way for executing the ‘evio2hipo’ command. What I want is instead of always doing ‘evio2hipo -i filename.evio -o filename.hipo’, I wanted to do ‘e2h fname.evio’ or ‘e2h path/fname.evio’ just like ‘h2root filename.hbook’ to convert hbook files into root ones. So, I defined the following alias for this:

	 alias e2h 'set bname=`basename \!:1 .evio`; evio2hipo -i \!:1 -o {$bname}.hipo'


* Explanation:
                * Here, e2h alias represents execution of two commands in sequence. The two are separated by the semicolon above. The first one is defining a variable called ‘bname’, where its value would be what the ‘basename’ command would return if two parameters ‘path/filename.evio’ and ‘evio’ were to be passed to it. Try for example, try ‘basename /what/ever/directory/myfile.ext ext’ in a linux terminal and it would return the basename of the filename i.e. ‘myfile’. It simply ignores the path and if the second parameter matches with the file extension, it returns only the file’s basename otherwise, it returns basename.ext without the pathname. For example ‘basename /what/ever/directory/myfile.ext txt’ would return myfile.ext.
                * \!:1 represents the first parameter of the ‘e2h’ command later when we use this aliased command. So, \!:1 is actually for substituting the ‘path/filename.ext’ as the first argument for ‘basename’ command. Now once the first command before the semicolon in the definition of ‘e2h’ is completed, the variable ‘bname’ can be used in the second command that comes after the semicolon. Here in the second command, we are executing ‘evio2hipo’ command with both input and output argument. For the input argument we again use ‘\!:1’ i.e., whatever the evio file name (including the path and extension) is and for the second we use the ‘bname’ variable.
        * This command has now been added to my .cshrc file in the jlab CUE home directory (which uses .csh shell by default, at least in my account).

