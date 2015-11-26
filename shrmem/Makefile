all: CFLAGS := -std=c99 -O2 $(CFLAGS)
all: shm_server shm_client 

debug: CFLAGS := -std=c99 -g -O0 $(CFLAGS)
debug: shm_server shm_client 

clean:
	rm shm_server shm_client 

shm_server: shm_server.c  
	gcc $? $(CFLAGS) -o $@



shm_client: shm_client.c  
	gcc $? $(CFLAGS)  -o $@
