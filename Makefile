all: student_record.o
	g++ student_record.o -o binary
student_record.o:
	g++ -c assignment2.cpp -I./ -o student_record.o
clean:
	rm *.o binary