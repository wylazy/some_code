topdir = ${shell readlink -f ./../..}
INCLUDES  = -I$(topdir)/include -I$(topdir)/sql -I$(topdir)/regex
LIBS = -lpthread -lz -lcrypt -lnsl -lm
DEPS =

CPPFLAGS := -g $(CPPFLAGS) $(INCLUDES) -g -DSAFE_MUTEX -DSAFEMALLOC -fno-implicit-templates -fno-exceptions -fPIC

all : udf_qcdump.so


udf_qcdump.so: udf_qcdump.o
	g++ -o $@ -shared $< $(DEPS)

clean : 
	rm *.o &> /dev/null rm *.so &> /dev/null
