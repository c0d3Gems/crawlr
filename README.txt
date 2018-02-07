This crawler is written for fun & so that I get to expand my area of knowledge.
I am planning to integrate it with a website that offers news from other websites, all in one place. 


What you'll need: 

    1. A linux distro (I'm using Debian 9)

    2. Install dependencies (libcurl-dev4*, build-essential, gcc, curl, cmake), 
    you can just run the setup.sh as root and you're set.

    3. (Optional) Valgrind - for memory leak testing. 
    I wrote the code to be memory-thread safe, but it seems that once 
    I make use of the lcurl libraries, Valgrind curses me with leaked 
    memory, yet no fatal errors. Based on a stackoverflow post, these 
    kind of warnings and leaks can be safely neglected.

    4. Test with an article link that has its domain as a member of 
    the structure in the crawler.h header file. (actual link following
    not implemented just yet, but will come soon.)  

How to install:

    1. Simply download this repo / clone it. 

    2. Run sh setup.sh as root. (On Debian & Ubuntu. Not tested on other distros).

    3. Build by running 'make'

How to run:

    1. Simply run 'make r' or './crawler' for basic run

    2. If you want to do some memory leaking testing with valgrind, use
    'make v' or 'valgrind ./crawler'

    3. Check the new generated file if it has the article you were 
    intending for crawlr to download. 

Implemented stuff: 
    
    1. Thread spawning function

    2. Write to file lcurl function, yet needs to be adapted to our needs
    (not overwrite itself after each run)

    3. Custom header for GET request function where there's restricted content,
    on wsj.com for example, in order to bypass the subscription request from 
    the website.

    4. Flags for Log keeping
        -m for mute
        -q for quiet mode (only to file)
        no flag = both stdout and logFile. 


What needs to be implemented from here:

    1. Actual make use of the threading spawn functions, with lcurl custom GET requests

    2. Tune the fileWriting from lcurl custom GET request not to rewrite the files

    3. Delete some of the stdout messages used for testing & debugging. (in pre-release
    stage.)


