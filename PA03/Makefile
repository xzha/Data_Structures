GCC = gcc
CFLAGS = -Werror -Wbad-function-cast -Wall -Wshadow -O3
OBJS = packing.o
HDRS = packing.h
TARGET = proj3
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose

.PHONY: test clean environment test_ch01 test_ch02 test_ch03 test_ch04 test_ch05 test_ch06 test_bit01 test_bit02 test_bit03 test_bit04 test_bit05 test_bit06 test_bit07

proj3: $(OBJS) $(HDRS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@

test: | test0 test1 test2 test3 test4 test5 test6

test0: $(TARGET) | environment
	./$(TARGET) testcases/r0_flr.txt outputs/output_r0.txt > screendump/0.txt
	$(VALGRIND) --log-file=outputs/memoutput_0 ./proj3 testcases/r0_flr.txt outputs/output_r0.txt > screendump/valgrind_0.txt
	diff expected/test0.txt outputs/output_r0.txt
	@bin/valgrind-checker.sh outputs/memoutput_0

test1: $(TARGET) | environment
	./$(TARGET) testcases/r1_flr.txt outputs/output_r1.txt > screendump/1.txt
	$(VALGRIND) --log-file=outputs/memoutput_1 ./proj3 testcases/r1_flr.txt outputs/output_r1.txt > screendump/valgrind_1.txt
	diff expected/test1.txt outputs/output_r1.txt
	@bin/valgrind-checker.sh outputs/memoutput_1

test2: $(TARGET) | environment
	./$(TARGET) testcases/r2_flr.txt outputs/output_r2.txt > screendump/2.txt
	$(VALGRIND) --log-file=outputs/memoutput_2 ./proj3 testcases/r2_flr.txt outputs/output_r2.txt > screendump/valgrind_2.txt
	diff expected/test2.txt outputs/output_r2.txt
	@bin/valgrind-checker.sh outputs/memoutput_2 

test3: $(TARGET) | environment
	./$(TARGET) testcases/r3_flr.txt outputs/output_r3.txt > screendump/3.txt
	$(VALGRIND) --log-file=outputs/memoutput_3 ./proj3 testcases/r3_flr.txt outputs/output_r3.txt > screendump/valgrind_3.txt
	diff expected/test3.txt outputs/output_r3.txt
	@bin/valgrind-checker.sh outputs/memoutput_3

test4: $(TARGET) | environment
	./$(TARGET) testcases/r4_flr.txt outputs/output_r4.txt > screendump/4.txt
	$(VALGRIND) --log-file=outputs/memoutput_4 ./proj3 testcases/r4_flr.txt outputs/output_r4.txt > screendump/valgrind_4.txt
	diff expected/test4.txt outputs/output_r4.txt
	@bin/valgrind-checker.sh outputs/memoutput_4

test5: $(TARGET) | environment
	./$(TARGET) testcases/r5_flr.txt outputs/output_r5.txt > screendump/5.txt
	$(VALGRIND) --log-file=outputs/memoutput_5 ./proj3 testcases/r5_flr.txt outputs/output_r5.txt > screendump/valgrind_5.txt
	diff expected/test5.txt outputs/output_r5.txt
	@bin/valgrind-checker.sh outputs/memoutput_5 

test6: $(TARGET) | environment
	./$(TARGET) testcases/r6_flr.txt outputs/output_r6.txt > screendump/6.txt
	$(VALGRIND) --log-file=outputs/memoutput_6 ./proj3 testcases/r6_flr.txt outputs/output_r6.txt > screendump/valgrind_6.txt
	diff expected/test6.txt outputs/output_r6.txt
	@bin/valgrind-checker.sh outputs/memoutput_6 

environment:
	@mkdir -p outputs

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -r $(TARGET) $(OBJS) outputs/output* outputs/memoutput_* screendump/*.txt screendump/valgrind*
