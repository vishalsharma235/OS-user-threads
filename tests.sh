printf "\nRUNNING TESTS FOR ONE-ONE THREADS\n\n"

printf "TEST CASE 1 : Create & Join three threads.\n"
cc -o test1 one-one/tests/1_create_join.c one-one/userthreads.c one-one/stack.c one-one/queue.c one-one/spinlock.c one-one/attr.c
./test1
printf "\n-----------------------------------------------------\n"


printf "TEST CASE 2(1) : Testing Spin Lock.\n"
printf "Spin Lock is not used.\n"
cc -o test2 one-one/tests/2_1_noLock.c one-one/userthreads.c one-one/stack.c one-one/queue.c one-one/spinlock.c one-one/attr.c
./test2
printf "\n-----------------------------------------------------\n"


printf "TEST CASE 2(2) : Testing Spin Lock.\n"
printf "Spin Lock is used.\n"
cc -o test2_2 one-one/tests/2_2_Lock.c one-one/userthreads.c one-one/stack.c one-one/queue.c one-one/spinlock.c one-one/attr.c
./test2_2
printf "\n-----------------------------------------------------\n"


printf "Test case 3 : Testing parameter passing into thread.\n"
cc -o test3 one-one/tests/3_parameter.c one-one/userthreads.c one-one/stack.c one-one/queue.c one-one/spinlock.c one-one/attr.c
./test3
printf "\n-----------------------------------------------------\n"


printf "Test Case 4(1): Testing thread_kill function with SIGKILL signal.\n"
cc -o test4 one-one/tests/4_1_sigkill.c one-one/userthreads.c one-one/stack.c one-one/queue.c one-one/spinlock.c one-one/attr.c
./test4
printf "\n-----------------------------------------------------\n"


printf "Test Case 4(2): Testing thread_kill function with SIGTERM signal.\n"
cc -o test4_3 one-one/tests/4_3_sigterm.c one-one/userthreads.c one-one/stack.c one-one/queue.c one-one/spinlock.c one-one/attr.c
./test4_3
printf "\n-----------------------------------------------------\n"


printf "Test Case 5 : Creating 200 threads.\n"
cc -o test5 one-one/tests/5_threads.c one-one/userthreads.c one-one/stack.c one-one/queue.c one-one/spinlock.c one-one/attr.c
./test5
printf "\n-----------------------------------------------------\n"


printf "Test Case 6 : Testing ATTR.\n"
cc -o test6 one-one/tests/6_attr.c one-one/userthreads.c one-one/stack.c one-one/queue.c one-one/spinlock.c one-one/attr.c
./test6
printf "\n-----------------------------------------------------\n"


printf "Test Case 7 : Testing Matrix Multiplication.\n"
cc -o test7 one-one/tests/7_matrix.c one-one/userthreads.c one-one/stack.c one-one/queue.c one-one/spinlock.c one-one/attr.c
./test7
printf "\n-----------------------------------------------------\n"


rm ./test1 ./test2 ./test2_2 ./test3 ./test4 ./test4_3 ./test5 ./test6 ./test7