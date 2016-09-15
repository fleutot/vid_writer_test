This program demonstrates a possible memory leak in OpenCV's video writer.

#Dependencies
OpenCV 2.4.9

#Build instructions
$ make

#Valgrind result
Issue 5404 states that this is [fixed](https://github.com/opencv/opencv/issues/5404) for 2.4.9.
However, here is my output when running with valgrind:

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

With `--leack-check=full`, the portion about definitely lost gives:

    ==15005== 3,617,280 (4,320 direct, 3,612,960 indirect) bytes in 180 blocks are definitely lost in loss record 271 of 271
    ==15005==    at 0x4C2E006: memalign (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==15005==    by 0x4C2E111: posix_memalign (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==15005==    by 0xA6A3F6F: av_malloc (in /usr/lib/x86_64-linux-gnu/libavutil-ffmpeg.so.54.27.100)
    ==15005==    by 0xA6A427D: av_mallocz (in /usr/lib/x86_64-linux-gnu/libavutil-ffmpeg.so.54.27.100)
    ==15005==    by 0xA691A5E: av_buffer_create (in /usr/lib/x86_64-linux-gnu/libavutil-ffmpeg.so.54.27.100)
    ==15005==    by 0xA691FD3: av_buffer_realloc (in /usr/lib/x86_64-linux-gnu/libavutil-ffmpeg.so.54.27.100)
    ==15005==    by 0x901EBE6: av_new_packet (in /usr/lib/x86_64-linux-gnu/libavcodec-ffmpeg.so.56.41.100)
    ==15005==    by 0x9482BF1: ??? (in /usr/lib/x86_64-linux-gnu/libavcodec-ffmpeg.so.56.41.100)
    ==15005==    by 0x93E53FA: ??? (in /usr/lib/x86_64-linux-gnu/libavcodec-ffmpeg.so.56.41.100)
    ==15005==    by 0x94833C3: avcodec_encode_video2 (in /usr/lib/x86_64-linux-gnu/libavcodec-ffmpeg.so.56.41.100)
    ==15005==    by 0x4E514B7: ??? (in /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.9)
    ==15005==    by 0x4E529D7: CvVideoWriter_FFMPEG::writeFrame(unsigned char const*, int, int, int, int, int) (in /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.9)
