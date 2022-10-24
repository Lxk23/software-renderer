OBJS=main.o ShadowShader.o geometry.o model.o myShader.o tgaimage.o
CC=gcc
CFLAGS=-c -Wall -g 

myrenderer:$(OBJS)
	$(CC) $^ -o $@
%.o:%.c
	$(CC) $^ $(CFLAGS) -o $@

clean:
	$(RM) *.o myrenderer -r

