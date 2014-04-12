GCC = gcc
CFLAGS = -Werror -Wbad-function-cast -Wall -Wshadow -O3
OBJS = reroot.o
HDRS = reroot.h
TARGET = proj4
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose

.PHONY: test clean environment test_ch01 test_ch02 test_ch03 test_ch04 test_ch05 test_ch06 test_bit01 test_bit02 test_bit03 test_bit04 test_bit05 test_bit06 test_bit07

proj4: $(OBJS) $(HDRS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@

test: | test0 test1 test2 test3 test4 test5 test6

test0: $(TARGET) | environment
	./$(TARGET) testcases/r0.po outputs/output_r0.txt > screendump/0.txt
	$(VALGRIND) --log-file=outputs/memoutput_0 ./proj4 testcases/r0.po outputs/output_r0.txt > screendump/valgrind_0.txt
	diff -w expected/test0.txt outputs/output_r0.txt
	diff -w screendump/0.txt expected/screenDump/r0.log.proj4
	@bin/valgrind-checker.sh outputs/memoutput_0

test1: $(TARGET) | environment
	./$(TARGET) testcases/r1.po outputs/output_r1.txt > screendump/1.txt
	$(VALGRIND) --log-file=outputs/memoutput_1 ./proj4 testcases/r1.po outputs/output_r1.txt > screendump/valgrind_1.txt
	diff -w expected/test1.txt outputs/output_r1.txt
	diff -w screendump/1.txt expected/screenDump/r1.log.proj4
	@bin/valgrind-checker.sh outputs/memoutput_1

test2: $(TARGET) | environment
	./$(TARGET) testcases/r2.po outputs/output_r2.txt > screendump/2.txt
	$(VALGRIND) --log-file=outputs/memoutput_2 ./proj4 testcases/r2.po outputs/output_r2.txt > screendump/valgrind_2.txt
	diff -w expected/test2.txt outputs/output_r2.txt
	diff -w screendump/2.txt expected/screenDump/r2.log.proj4
	@bin/valgrind-checker.sh outputs/memoutput_2 

test3: $(TARGET) | environment
	./$(TARGET) testcases/r3.po outputs/output_r3.txt > screendump/3.txt
	$(VALGRIND) --log-file=outputs/memoutput_3 ./proj4 testcases/r3.po outputs/output_r3.txt > screendump/valgrind_3.txt
	diff -w expected/test3.txt outputs/output_r3.txt
	diff -w screendump/3.txt expected/screenDump/r3.log.proj4
	@bin/valgrind-checker.sh outputs/memoutput_3

test4: $(TARGET) | environment
	./$(TARGET) testcases/r4.po outputs/output_r4.txt > screendump/4.txt
	$(VALGRIND) --log-file=outputs/memoutput_4 ./proj4 testcases/r4.po outputs/output_r4.txt > screendump/valgrind_4.txt
	diff -w expected/test4.txt outputs/output_r4.txt
	diff -w screendump/4.txt expected/screenDump/r4.log.proj4
	@bin/valgrind-checker.sh outputs/memoutput_4

test5: $(TARGET) | environment
	./$(TARGET) testcases/r5.po outputs/output_r5.txt > screendump/5.txt
	$(VALGRIND) --log-file=outputs/memoutput_5 ./proj4 testcases/r5.po outputs/output_r5.txt > screendump/valgrind_5.txt
	diff -w expected/test5.txt outputs/output_r5.txt
	diff -w screendump/5.txt expected/screenDump/r5.log.proj4
	@bin/valgrind-checker.sh outputs/memoutput_5 

test6: $(TARGET) | environment
	./$(TARGET) testcases/r6.po outputs/output_r6.txt > screendump/6.txt
	$(VALGRIND) --log-file=outputs/memoutput_6 ./proj4 testcases/r6.po outputs/output_r6.txt > screendump/valgrind_6.txt
	diff -w expected/test6.txt outputs/output_r6.txt
	diff -w screendump/6.txt expected/screenDump/r6.log.proj4
	@bin/valgrind-checker.sh outputs/memoutput_6 

environment:
	@mkdir -p outputs

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -r $(TARGET) $(OBJS) outputs/output* outputs/memoutput_* screendump/*.txt screendump/valgrind*
