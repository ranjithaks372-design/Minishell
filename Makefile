CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = minishell
SRCS = main.c scan_input.c get_command.c copy_change.c check_cmd.c \
       execute_internal.c execute_external.c echo.c extract_external_cmds.c \
       n_pipes.c insert_job.c print.c delete_first.c signal_handler.c

all: $(TARGET)
$(TARGET): $(SRCS) minishell.h
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)
clean:
	rm -f $(TARGET) *.o
.PHONY: all clean
