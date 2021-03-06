GCC = gcc
CFLAGS = -Werror -Wall -Wshadow -O3
OBJS = sorting.o sorting_main.o
HDRS = sorting.h
TARGET = proj1
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose

.PHONY: test clean environment test_ch01 test_ch02 test_ch03 test_ch04 test_ch05 test_ch06 test_bit01 test_bit02 test_bit03 test_bit04 test_bit05 test_bit06 test_bit07

proj1: $(OBJS) $(HDRS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@

test: | test_1000i test_10000i test_100000i test_1000000i test_1000s test_10000s test_100000s test_1000000s

test_1000i: $(TARGET) | environment
	./$(TARGET) i testcases/1000.txt outputs/seq01_i.txt outputs/output01_i.txt
	$(VALGRIND) --log-file=outputs/memoutput_i01 ./proj1 i testcases/1000.txt outputs/seq01_i.txt outputs/output01_i.txt
	@bin/valgrind-checker.sh outputs/memoutput_i01 

test_1000s: $(TARGET) | environment
	./$(TARGET) s testcases/1000.txt outputs/seq01_s.txt outputs/output01_s.txt
	$(VALGRIND) --log-file=outputs/memoutput_s01 ./proj1 s testcases/1000.txt outputs/seq01_s.txt outputs/output01_s.txt
	@bin/valgrind-checker.sh outputs/memoutput_s01

test_10000i: $(TARGET) | environment
	./$(TARGET) i testcases/10000.txt outputs/seq02_i.txt outputs/output02_i.txt
	$(VALGRIND) --log-file=outputs/memoutput_i02 ./proj1 i testcases/10000.txt outputs/seq02_i.txt outputs/output02_i.txt
	@bin/valgrind-checker.sh outputs/memoutput_i02

test_10000s: $(TARGET) | environment
	./$(TARGET) s testcases/10000.txt outputs/seq02_s.txt outputs/output02_s.txt
	$(VALGRIND) --log-file=outputs/memoutput_s02 ./proj1 s testcases/10000.txt outputs/seq02_s.txt outputs/output02_s.txt
	@bin/valgrind-checker.sh outputs/memoutput_s02

test_100000i: $(TARGET) | environment
	./$(TARGET) i testcases/100000.txt outputs/seq03_i.txt outputs/output03_i.txt
	$(VALGRIND) --log-file=outputs/memoutput_i03 ./proj1 i testcases/100000.txt outputs/seq03_i.txt outputs/output03_i.txt
	@bin/valgrind-checker.sh outputs/memoutput_i03

test_100000s: $(TARGET) | environment
	./$(TARGET) s testcases/100000.txt outputs/seq03_s.txt outputs/output03_s.txt
	$(VALGRIND) --log-file=outputs/memoutput_s03 ./proj1 s testcases/100000.txt outputs/seq03_s.txt outputs/output03_s.txt
	@bin/valgrind-checker.sh outputs/memoutput_s03

test_1000000i: $(TARGET) | environment
	./$(TARGET) i testcases/1000000.txt outputs/seq04_i.txt outputs/output04_i.txt
	$(VALGRIND) --log-file=outputs/memoutput_i04 ./proj1 i testcases/1000000.txt outputs/seq04_i.txt outputs/output04_i.txt
	@bin/valgrind-checker.sh outputs/memoutput_i04

test_1000000s: $(TARGET) | environment
	./$(TARGET) s testcases/1000000.txt outputs/seq04_s.txt outputs/output04_s.txt
	$(VALGRIND) --log-file=outputs/memoutput_s04 ./proj1 s testcases/1000000.txt outputs/seq04_s.txt outputs/output04_s.txt
	@bin/valgrind-checker.sh outputs/memoutput_s04

environment:
	@mkdir -p outputs

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -r $(TARGET) $(OBJS) outputs/*output* outputs/memoutput* outputs/seq*
