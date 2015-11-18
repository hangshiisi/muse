all: CFLAGS := -O2 $(CFLAGS)
all: pace2_integration_example

debug: CFLAGS := -g -O0 $(CFLAGS)
debug: pace2_integration_example

clean:
	rm pace2_integration_example

pace2_integration_example: pace2_integration_example.c event_handler.c pace2_netfilter.c 
	cc $? $(CFLAGS) -rdynamic ../ipoque/lib/libipoque_pace2_static.a -lpcap -lnfnetlink -lnetfilter_queue -lz -I../ipoque/include/ipoque -o $@
