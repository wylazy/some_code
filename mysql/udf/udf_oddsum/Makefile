CC = gcc
MYSQL_PATH = $(HOME)/programs/mysql-5.1.63
MYSQL_CONFIG = $(MYSQL_PATH)/bin/mysql_config
INCLUDES = -I$(MYSQL_PATH)/include/mysql

INCLUDES = ${shell $(MYSQL_CONFIG) --include}
LIBS = ${shell $(MYSQL_CONFIG) --libs}
EMBLIBS = ${shell $(MYSQL_CONFIG) --libmysqld-libs}

CPPFLAGS := -g $(CPPFLAGS) $(INCLUDES) -fPIC

all: udf_oddsum.so

udf_oddsum.so: udf_oddsum.o
        $(CC) -o $@ -shared $<

install: all
	cp udf_oddsum.so $(MYSQL_PATH)/lib/mysql/plugin/

clean: 
	rm -f *.o *.gch *.so &> /dev/null
