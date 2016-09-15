This program demonstrates a possible memory leak in OpenCV's video writer.

#Dependencies
OpenCV 2.4.9

#Build instructions
$ make

#Valgrind result
Issue 5404 states that this is [fixed](https://github.com/opencv/opencv/issues/5404) for 2.4.9.
pherHowever, here is my output when running with valgrind:

    $ make
    g++ -c test_no_thread.cpp -o test_no_thread.o -Wall -Wextra -Werror -I/usr/include/opencv -lopencv_highgui -lopencv_core
    g++ test_no_thread.o -o test_no_thread -Wall -Wextra -Werror -I/usr/include/opencv -lopencv_highgui -lopencv_core
    $ valgrind ./test_no_thread
    ==7328== Memcheck, a memory error detector
    ==7328== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
    ==7328== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
    ==7328== Command: ./test_no_thread
    ==7328== 
    No thread. OpenCV version: 2.4.9
    ==7328== 
    ==7328== HEAP SUMMARY:
    ==7328==     in use at exit: 3,842,945 bytes in 1,438 blocks
    ==7328==   total heap usage: 4,802 allocs, 3,364 frees, 14,877,696 bytes allocated
    ==7328== 
    ==7328== LEAK SUMMARY:
    ==7328==    definitely lost: 4,320 bytes in 180 blocks
    ==7328==    indirectly lost: 3,612,960 bytes in 360 blocks
    ==7328==      possibly lost: 1,352 bytes in 18 blocks
    ==7328==    still reachable: 224,313 bytes in 880 blocks
    ==7328==                       of which reachable via heuristic:
    ==7328==                         newarray           : 1,536 bytes in 16 blocks
    ==7328==         suppressed: 0 bytes in 0 blocks
    ==7328== Rerun with --leak-check=full to see details of leaked memory
    ==7328== 
    ==7328== For counts of detected and suppressed errors, rerun with: -v
    ==7328== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
