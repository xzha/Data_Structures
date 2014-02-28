GCC = gcc
CFLAGS = -Werror -Wall -Wshadow -O3
OBJS = sorting.o sorting_main.o mymalloc.o
HDRS = sorting.h
TARGET = proj2
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose

.PHONY: test clean environment test_ch01 test_ch02 test_ch03 test_ch04 test_ch05 test_ch06 test_bit01 test_bit02 test_bit03 test_bit04 test_bit05 test_bit06 test_bit07

proj2: $(OBJS) $(HDRS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@

test: | test1000 test10000 test100000 test1000000

test1000: $(TARGET) | environment
	./$(TARGET) testcases/1000.txt outputs/output01_i.txt
	$(VALGRIND) --log-file=outputs/memoutput_i01 ./proj2 testcases/1000.txt outputs/output01_i.txt
	@bin/valgrind-checker.sh outputs/memoutput_i01 

test10000: $(TARGET) | environment
	./$(TARGET) testcases/10000.txt outputs/output02_i.txt
	$(VALGRIND) --log-file=outputs/memoutput_i02 ./proj2 testcases/10000.txt outputs/output02_i.txt
	@bin/valgrind-checker.sh outputs/memoutput_i02

test100000: $(TARGET) | environment
	./$(TARGET) testcases/100000.txt outputs/output03_i.txt
	$(VALGRIND) --log-file=outputs/memoutput_i03 ./proj2 testcases/100000.txt outputs/output03_i.txt
	@bin/valgrind-checker.sh outputs/memoutput_i03

test1000000: $(TARGET) | environment
	./$(TARGET) testcases/1000000.txt outputs/output04_i.txt
	$(VALGRIND) --log-file=outputs/memoutput_i04 ./proj2 testcases/1000000.txt outputs/output04_i.txt
	@bin/valgrind-checker.sh outputs/memoutput_i04

environment:
	@mkdir -p outputs

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -r $(TARGET) $(OBJS) outputs/*output* outputs/memoutput* outputs/seq*
