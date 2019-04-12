CC=gcc


compile:
	CC run.c \
	   common_http.c \
	   conn.c cv.c lock.c \
	   queue.c \
	   read_static_page.c \
	   requests.c \
	   response.c \
	   send_page.c \
	   utils.c
