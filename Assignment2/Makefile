############################################################################
# COSC1283/1284 - Programming Techniques
# Semester 1 2013 Assignment #2 - SCSIT Program Management System
# Full Name        : Hartanto Poniman Noerdjaja
# Student Number   : 3420572
# Yallara Username : s3420572
# Course Code      : CSOC1284
# Program Code     : BP162
# Start up code provided by Christopher Hoobin, Paul Miller, and Xiaodong Li
############################################################################

CC	= gcc
CFLAGS	= -Wall -ansi -pedantic
PROG	= pms
OBJS	= pms.o pms_options.o pms_program.o pms_course.o pms_utility.o
USER    = s3420572

all: $(OBJS)
	@echo "linking …"
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS)

pms.o: pms.c pms.h pms_options.h pms_utility.h
	$(CC) $(CFLAGS) -c pms.c

pms_options.o: pms_options.c pms.h pms_options.h pms_utility.h
	$(CC) $(CFLAGS) -c pms_options.c

pms_program.o: pms_program.c pms_program.h pms.h
	$(CC) $(CFLAGS) -c pms_program.c

pms_course.o: pms_course.c pms_course.h pms.h
	$(CC) $(CFLAGS) -c pms_course.c

pms_utility.o: pms_utility.c pms.h pms_options.h pms_utility.h
	$(CC) $(CFLAGS) -c pms_utility.c

clean:
	rm $(OBJS) $(PROG)

dos2unix:
	dos2unix ?

archive:
	zip $(USER)-a2.zip pms.c pms.h pms_options.c pms_options.h pms_program.c pms_program.h pms_course.c pms_course.h pms_utility.c pms_utility.h Makefile pms_readme.txt

