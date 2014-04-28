GCC = gcc
CFLAGS = -Werror -Wbad-function-cast -Wall -Wshadow -O3
OBJS = river.o
HDRS = river.h
TARGET = proj5
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose

.PHONY: test clean environment test_ch01 test_ch02 test_ch03 test_ch04 test_ch05 test_ch06 test_bit01 test_bit02 test_bit03 test_bit04 test_bit05 test_bit06 test_bit07

proj5: $(OBJS) $(HDRS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@

test: | test0 test1 test2 test3

test0: $(TARGET) | environment
	./$(TARGET) testcases/river.in0 > screendump/0.txt
	$(VALGRIND) --log-file=outputs/memoutput_0 ./proj5 testcases/river.in0  > screendump/valgrind_0.txt
	@bin/valgrind-checker.sh outputs/memoutput_0

test1: $(TARGET) | environment
	./$(TARGET) testcases/river.in1 > screendump/1.txt
	$(VALGRIND) --log-file=outputs/memoutput_1 ./proj5 testcases/river.in1  > screendump/valgrind_1.txt
	@bin/valgrind-checker.sh outputs/memoutput_1

test2: $(TARGET) | environment
	./$(TARGET) testcases/river.in2 > screendump/2.txt
	$(VALGRIND) --log-file=outputs/memoutput_2 ./proj5 testcases/river.in2  > screendump/valgrind_2.txt
	@bin/valgrind-checker.sh outputs/memoutput_2 

test3: $(TARGET) | environment
	./$(TARGET) testcases/river.in3 > screendump/3.txt
	$(VALGRIND) --log-file=outputs/memoutput_3 ./proj5 testcases/river.in3  > screendump/valgrind_3.txt
	@bin/valgrind-checker.sh outputs/memoutput_3

environment:
	@mkdir -p outputs

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -r $(TARGET) $(OBJS) outputs/output* outputs/memoutput_* screendump/*.txt screendump/valgrind*
