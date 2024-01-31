gcc `pkg-config --cflags gtk+-3.0` -o frontend frontend.c `pkg-config --libs gtk+-3.0` -rdynamic
